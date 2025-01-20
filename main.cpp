#include <SFML/Graphics.hpp>
#include "src/Header/SettingsPanel.h"
#include "src/Header/AudioVisualizer.h"
#include "src/Header/SongPanel.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Audio Visualizer");

    AudioVisualizer visualizer;
    SongPanel songPanel(visualizer, "../songs/");
    songPanel.setSongsDirectory("../songs/");
    sf::Vector2f position(550, 50);

    SettingsPanel settingsPanel(window, visualizer, songPanel, position);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            settingsPanel.handleEvent(event);
            songPanel.update(window);
            
        }

        visualizer.update(window);

        window.clear();
        visualizer.draw(window);
        settingsPanel.draw();
        songPanel.draw(window);
        
        window.display();
        
        
    }

    return 0;
}
