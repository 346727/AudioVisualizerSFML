#include "../Header/AudioVisualizer.h"
#include <cmath>
#include <iostream>

AudioVisualizer::AudioVisualizer()
    : inputBuffer(BUFFER_SIZE), outputBuffer(BUFFER_SIZE / 2 + 1), bars(NUM_BARS) {  // Resize outputBuffer
    fftPlan = fftw_plan_dft_r2c_1d(BUFFER_SIZE, inputBuffer.data(),
                                   reinterpret_cast<fftw_complex*>(outputBuffer.data()),
                                   FFTW_ESTIMATE);

    const float BAR_WIDTH = 10.0f;
    const float BAR_SPACING = 2.0f;
    for (size_t i = 0; i < NUM_BARS; ++i) {
        bars[i].setFillColor(sf::Color::Cyan);
        bars[i].setPosition(i * (BAR_WIDTH + BAR_SPACING), 0);
        bars[i].setSize(sf::Vector2f(BAR_WIDTH, 0));
    }
}

AudioVisualizer::~AudioVisualizer() {
    fftw_destroy_plan(fftPlan);
}

bool AudioVisualizer::loadAudio(const std::string& filename) {
    if (!soundBuffer.loadFromFile(filename)) {
        return false;
    }
    sound.setBuffer(soundBuffer);
    return true;
}

void AudioVisualizer::play() {
    sound.play();
}

void AudioVisualizer::update(sf::RenderWindow& window) {
    if (sound.getStatus() != sf::Sound::Playing) {
        return;
    }

    sf::Time offset = sound.getPlayingOffset();
    const sf::Int16* samples = soundBuffer.getSamples();
    size_t sampleCount = soundBuffer.getSampleCount();
    size_t position = static_cast<size_t>(offset.asSeconds() * soundBuffer.getSampleRate()) * soundBuffer.getChannelCount();


    for (size_t i = 0; i < BUFFER_SIZE && (position + i) < sampleCount; ++i) {
        inputBuffer[i] = static_cast<double>(samples[position + i]) / 32768.0;  // Normalize input data
    }

    // FFTW plan
    fftw_execute(fftPlan);

    const float windowHeight = static_cast<float>(window.getSize().y);
    const float scale = windowHeight / 50.0f;
    const float barWidth = static_cast<float>(window.getSize().x) / NUM_BARS;

    for (size_t i = 0; i < NUM_BARS; ++i) {
        double magnitude = 0.0;
        size_t startIdx = i * (BUFFER_SIZE / 2 / NUM_BARS);
        size_t endIdx = (i + 1) * (BUFFER_SIZE / 2 / NUM_BARS);

        // liczenie magnitudy
        for (size_t j = startIdx; j < endIdx && j < outputBuffer.size(); ++j) {  // Bounds check
            double real = outputBuffer[j].real();
            double imag = outputBuffer[j].imag();
            magnitude += std::sqrt(real * real + imag * imag);
        }

        magnitude /= (endIdx - startIdx);
        magnitude = std::log(1 + magnitude) * scale * std::pow(2, (i / (float)NUM_BARS))*5;

        // dostosowywanie wysokości
        float barHeight = std::min(static_cast<float>(magnitude), windowHeight);
        bars[i].setSize(sf::Vector2f(barWidth - 2.0f, barHeight));
        bars[i].setPosition(i * barWidth, windowHeight - barHeight);

        // kolorking
        float intensity = std::min(barHeight / windowHeight, 1.0f);
        bars[i].setFillColor(sf::Color(
            static_cast<sf::Uint8>(intensity * 255),
            static_cast<sf::Uint8>((1.0f - intensity) * 255),
            180
        ));
    }
}

void AudioVisualizer::draw(sf::RenderWindow& window) {
    for (const auto& bar : bars) {
        window.draw(bar);
    }
}
