#ifndef AUDIO_VISUALIZER_H
#define AUDIO_VISUALIZER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fftw3.h>
#include <vector>
#include <complex>
#include <string>

class AudioVisualizer {
public:
    AudioVisualizer();
    ~AudioVisualizer();
    
    bool loadAudio(const std::string& filename);
    void play();
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
private:
    static const size_t BUFFER_SIZE = 2048;
    static const size_t NUM_BARS = 140;

    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
    
    std::vector<double> inputBuffer;
    std::vector<std::complex<double>> outputBuffer;
    fftw_plan fftPlan;
    
    std::vector<sf::RectangleShape> bars;
};

#endif
