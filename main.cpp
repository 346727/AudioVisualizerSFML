#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fftw3.h>
#include <vector>
#include <complex>
#include <cmath>

class AudioVisualizer {
private:
    static const size_t BUFFER_SIZE = 2048;
    static const size_t NUM_BARS = 70;
    
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
    
    std::vector<double> inputBuffer;
    std::vector<std::complex<double>> outputBuffer;
    fftw_plan fftPlan;
    
    std::vector<sf::RectangleShape> bars;
    
public:
    AudioVisualizer() : 
        inputBuffer(BUFFER_SIZE),
        outputBuffer(BUFFER_SIZE),
        bars(NUM_BARS)
    {
        // Initialize FFT plan
        fftPlan = fftw_plan_dft_r2c_1d(
            BUFFER_SIZE,
            inputBuffer.data(),
            reinterpret_cast<fftw_complex*>(outputBuffer.data()),
            FFTW_ESTIMATE
        );
        
        // Initialize visualization bars
        const float BAR_WIDTH = 10.0f;
        const float BAR_SPACING = 2.0f;
        
        for (size_t i = 0; i < NUM_BARS; ++i) {
            bars[i].setFillColor(sf::Color::Cyan);
            bars[i].setPosition(i * (BAR_WIDTH + BAR_SPACING), 0);
            bars[i].setSize(sf::Vector2f(BAR_WIDTH, 0)); // Initial height set to 0
        }
    }
    
    ~AudioVisualizer() {
        fftw_destroy_plan(fftPlan);
    }
    
    bool loadAudio(const std::string& filename) {
        if (!soundBuffer.loadFromFile(filename)) {
            return false;
        }
        sound.setBuffer(soundBuffer);
        return true;
    }
    
    void play() {
        sound.play();
    }
    
    void update(sf::RenderWindow& window) {
        if (sound.getStatus() != sf::Sound::Playing) {
            return;
        }
        
        // Get current playing offset
        sf::Time offset = sound.getPlayingOffset();
        const sf::Int16* samples = soundBuffer.getSamples();
        size_t sampleCount = soundBuffer.getSampleCount();
        size_t position = (offset.asSeconds() * soundBuffer.getSampleRate()) * soundBuffer.getChannelCount();
        
        // Fill input buffer
        for (size_t i = 0; i < BUFFER_SIZE && (position + i) < sampleCount; ++i) {
            inputBuffer[i] = static_cast<double>(samples[position + i]) / 32768.0;
        }
        
        // Perform FFT
        fftw_execute(fftPlan);
        
        // Update visualization
        const float height = static_cast<float>(window.getSize().y);
        const float scale = height / 100.0f;
        
        for (size_t i = 0; i < NUM_BARS; ++i) {
            // Calculate magnitude for this frequency band
            double magnitude = 0.0;
            size_t start = i * (BUFFER_SIZE / 2 / NUM_BARS);
            size_t end = (i + 1) * (BUFFER_SIZE / 2 / NUM_BARS);
            
            for (size_t j = start; j < end; ++j) {
                double real = outputBuffer[j].real();
                double imag = outputBuffer[j].imag();
                magnitude += std::sqrt(real * real + imag * imag);
            }
            
            magnitude /= (end - start);
            
            // Update bar height
            float barHeight = std::min(static_cast<float>(magnitude * scale), height);
            bars[i].setSize(sf::Vector2f(bars[i].getSize().x, barHeight));
            bars[i].setPosition(bars[i].getPosition().x, height - barHeight);
            
            // Update bar color based on height
            float hue = (barHeight / height) * 360.0f;
            bars[i].setFillColor(sf::Color::White);
        }
    }
    
    void draw(sf::RenderWindow& window) {
        for (const auto& bar : bars) {
            window.draw(bar);
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Audio Visualizer");
    window.setFramerateLimit(60);
    std::string songPath = "../songs/BackToBlack.wav"; 

    
    AudioVisualizer visualizer;
    if (!visualizer.loadAudio(songPath)) {
        return -1;
    }
    
    visualizer.play();
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        window.clear(sf::Color::Black);
        
        visualizer.update(window);
        visualizer.draw(window);
        
        window.display();
    }
    
    return 0;
}