#include "../Header/SettingsPanel.h"
#include "../Header/tinyfiledialogs.h"

#include <sstream>
#include <vector>
#include <filesystem>

std::string SettingsPanel::getTruncatedPath(const std::string& fullPath) {
    const int maxSegments = 3;

    // podziel segmenty
    std::vector<std::string> segments;
    std::filesystem::path path(fullPath);
    for (const auto& part : path) {
        segments.push_back(part.string());
    }

    // Jak ma mniej segmentow, pokaz cale
    if (segments.size() <= maxSegments) {
        return fullPath;
    }

    // weź ostatnie segmenty i polacz
    std::ostringstream truncatedPath;
    truncatedPath << ".../";
    for (size_t i = segments.size() - maxSegments; i < segments.size(); ++i) {
        truncatedPath << segments[i];
        if (i < segments.size() - 1) {
            truncatedPath << "/";
        }
    }
    return truncatedPath.str();
}


SettingsPanel::SettingsPanel(sf::RenderWindow& window, AudioVisualizer& visualizer, SongPanel& songPanel, const sf::Vector2f& position)
    : window(window), visualizer(visualizer), songPanel(songPanel), position(position), isDragging(false), isShrunk(false) {
    loadFont();
    setupUI();
}

void SettingsPanel::loadFont() {
    if (!font.loadFromFile("Arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
}

void SettingsPanel::setupUI() {
    // Background panel
    panelBackground.setSize(sf::Vector2f(250, 150));
    panelBackground.setPosition(position);
    panelBackground.setFillColor(sf::Color(50, 50, 50, 200));

    // Title text
    titleText.setFont(font);
    titleText.setString("Settings");
    titleText.setCharacterSize(24);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(position.x + 10, position.y + 10);

    // Songs directory label
    songsDirectoryLabel.setFont(font);
    songsDirectoryLabel.setString("Songs Directory:");
    songsDirectoryLabel.setCharacterSize(18);
    songsDirectoryLabel.setFillColor(sf::Color::White);
    songsDirectoryLabel.setPosition(position.x + 10, position.y + 50);

    // Songs directory value 
    songsDirectoryValue.setFont(font);
    songsDirectoryValue.setString(getTruncatedPath(songPanel.getSongsDirectory()));
    songsDirectoryValue.setCharacterSize(18);
    songsDirectoryValue.setFillColor(sf::Color::White);
    songsDirectoryValue.setPosition(position.x + 10, position.y + 80);

    // Browse button
    browseButton.setSize(sf::Vector2f(100, 30));
    browseButton.setPosition(position.x + 10, position.y + 115);
    browseButton.setFillColor(sf::Color(100, 100, 255));
    browseText.setPosition(position.x + 20, position.y + 120);
    browseText.setFont(font);
    browseText.setCharacterSize(18);
    browseText.setFillColor(sf::Color::White);
    browseText.setString("Browse...");
}


void SettingsPanel::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;

    // Update UI
    panelBackground.setPosition(position);
    titleText.setPosition(position.x + 10, position.y + 10);
    songsDirectoryLabel.setPosition(position.x + 10, position.y + 50);
    songsDirectoryValue.setPosition(position.x + 10, position.y + 80);
    browseButton.setPosition(position.x + 10, position.y + 115);
    browseText.setPosition(position.x + 20, position.y + 120);
}

void SettingsPanel::shrinkPanel() {
    isShrunk = true;

    // Shrink
    panelBackground.setSize(sf::Vector2f(150, 40));
    titleText.setPosition(position.x + 10, position.y + 5);

    // Hide
    songsDirectoryLabel.setString("");
    songsDirectoryValue.setString("");
    browseButton.setSize(sf::Vector2f(0, 0));
    browseText.setString("");
}

void SettingsPanel::expandPanel() {
    isShrunk = false;

    // Restore 
    panelBackground.setSize(sf::Vector2f(250, 150));
    setupUI();
}

void SettingsPanel::draw() {
    window.draw(panelBackground);
    window.draw(titleText);

    if (!isShrunk) {
        window.draw(songsDirectoryLabel);
        window.draw(songsDirectoryValue);
        window.draw(browseButton);
        window.draw(browseText);
    }
}

void SettingsPanel::handleEvent(const sf::Event& event) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);


    if (event.type == sf::Event::MouseButtonPressed) {
        if (titleText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            if (isShrunk) {
                expandPanel();
            } else {
                shrinkPanel();
            }
        }
    }

    // wyszukiwanie, okno dialogowe.
    if (!isShrunk && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (browseButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            const char* path = tinyfd_selectFolderDialog("Select Songs Directory", songPanel.getSongsDirectory().c_str());
            if (path) {
                songPanel.setSongsDirectory(path);

                songsDirectoryValue.setString(getTruncatedPath(path));
                songPanel.update(window);
                songPanel.loadSongs(songPanel.getSongsDirectory());
                songPanel.createButtons();
                songPanel.draw(window);
            }
        }
    }

// Dragging logic
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (panelBackground.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            isDragging = true;
            dragOffset = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)) - position;
        }
    } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        isDragging = false;
    } else if (event.type == sf::Event::MouseMoved && isDragging) {
        sf::Vector2f newPanelPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        setPosition(newPanelPosition - dragOffset);
    }

    
}


void SettingsPanel::update() {
    // Placeholder for future updates
}
