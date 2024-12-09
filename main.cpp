#include <SFML/Graphics.hpp>
#include "src/Header/AudioVisualizer.h"
#include "src/Header/SongPanel.h"
#include "src/Header/SettingsPanel.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Audio Visualizer");
    window.setFramerateLimit(60);

    std::string songsDirectory = "../songs";

    AudioVisualizer visualizer;
    SongPanel songPanel(visualizer, songsDirectory, sf::Vector2f(10.f, 10.f));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black); // Czyszczenie okna

        // Wywolanie metod klasy SongPanel
        songPanel.update(window);  // Handlowanie input
        songPanel.draw(window);    // rysownie przyciskw

        visualizer.update(window);  // aktualizacja animacji
        visualizer.draw(window); // rysowanie animacji

        window.display(); // aktualizacja okna
    }

    return 0;
}
