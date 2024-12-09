#ifndef SONG_PANEL_H
#define SONG_PANEL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <filesystem>
#include <functional>
#include "AudioVisualizer.h"  // integracja odtwarzacza

class SongPanel {
public:
    SongPanel(AudioVisualizer& audioVisualizer, const std::string& songsDirectory, const sf::Vector2f& position = {0.f, 0.f});
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    

private:
    void loadSongs(const std::string& songsDirectory);
    void createButtons();
    void playSong(const std::string& filename);
    void navigateToPage(int pageNumber);
    void toggleMenu();

    AudioVisualizer& audioVisualizer;
    std::vector<std::string> songs;
    std::vector<sf::Text> songButtons;
    std::vector<sf::Text> navigationButtons;

    sf::Font font;
    size_t currentPage;
    size_t songsPerPage;

    const float buttonWidth = 200.f;
    const float buttonHeight = 40.f;

    bool menuVisible;               // śledzi, czy menu jest widoczne
    bool toggleButtonPressed;       // sprawdza, czy przycisk jest przytrzymywany (flaga)
    sf::Text toggleButton;          // przycisk toggle

    
};

#endif // SONG_PANEL_H
