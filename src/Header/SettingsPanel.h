#ifndef SETTINGS_PANEL_H
#define SETTINGS_PANEL_H

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include "../Header/SongPanel.h"
#include "../Header/AudioVisualizer.h"

class SettingsPanel {
public:
    SettingsPanel(sf::RenderWindow& window, AudioVisualizer& visualizer, SongPanel& songPanel, const sf::Vector2f& position);

    void draw();
    void handleEvent(const sf::Event& event);
    void update();

private:
    void loadFont();
    void setupUI();
    void setPosition(const sf::Vector2f& newPosition);
    void shrinkPanel();
    void expandPanel();
    std::string getTruncatedPath(const std::string& fullPath); // New helper function

    sf::RenderWindow& window;
    AudioVisualizer& visualizer;
    SongPanel& songPanel;
    sf::Vector2f position;

    sf::RectangleShape panelBackground;
    sf::Text titleText;
    sf::Text songsDirectoryLabel;
    sf::Text songsDirectoryValue;
    sf::RectangleShape browseButton;
    sf::Text browseText;

    sf::Font font;

    bool isDragging;
    bool isShrunk;
    sf::Vector2f dragOffset;
};


#endif // SETTINGS_PANEL_H
