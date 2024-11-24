#include "../Header/SongPanel.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <filesystem>
#include <dirent.h>
#include <string>
#include <vector>

std::vector<std::string> getFilesInDirectory(const std::string& directory) {
    std::vector<std::string> files;
    DIR* dir = opendir(directory.c_str());
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_REG) { // Regular file
                files.push_back(entry->d_name); // nazwa pliku
            }
        }
        closedir(dir);
    }
    return files;
}

SongPanel::SongPanel(AudioVisualizer& audioVisualizer, const std::string& songsDirectory, const sf::Vector2f& position)
    : audioVisualizer(audioVisualizer), currentPage(0), songsPerPage(5) {
    
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    loadSongs(songsDirectory);
    createButtons();
}

void SongPanel::loadSongs(const std::string& songsDirectory) {
    songs = getFilesInDirectory(songsDirectory);
    std::cout << "Loaded songs:" << std::endl;
    for (const auto& song : songs) {
        std::cout << song << std::endl;
    }
}

void SongPanel::createButtons() {
        songButtons.clear();
        size_t startIndex = currentPage * songsPerPage;
        size_t endIndex = std::min(startIndex + songsPerPage, songs.size());

        std::cout << "Creating buttons for page " << currentPage << std::endl;

        for (size_t i = startIndex; i < endIndex; ++i) {
            sf::Text button;
            button.setFont(font);
            button.setString(songs[i]);
            button.setCharacterSize(20);
            button.setFillColor(sf::Color::White);
            button.setPosition(10.f, 10.f + (i - startIndex) * (buttonHeight + 10.f));

            songButtons.push_back(button);
            std::cout << "Created button: " << songs[i] << std::endl;
        }

        // Przyciski nawigacji (do naprawy)
        if (currentPage > 0 && navigationButtons.empty()) {
            sf::Text prevButton("Previous", font, 20);
            prevButton.setFillColor(sf::Color::White);
            prevButton.setPosition(10.f, 10.f + (songButtons.size()) * (buttonHeight + 10.f));
            navigationButtons.push_back(prevButton);
        }

        if (currentPage * songsPerPage + songsPerPage < songs.size() && navigationButtons.size() < 2) {
            sf::Text nextButton("Next", font, 20);
            nextButton.setFillColor(sf::Color::White);
            nextButton.setPosition(200.f, 10.f + (songButtons.size()) * (buttonHeight + 10.f));
            navigationButtons.push_back(nextButton);
        }

        std::cout << "Finished creating buttons. Created " << songButtons.size() << " buttons." << std::endl;

    
}

void SongPanel::navigateToPage(int pageNumber) {
    currentPage = pageNumber;
    createButtons();
}



void SongPanel::playSong(const std::string& filename) {
    if (audioVisualizer.loadAudio("../songs/" + filename)) {
        audioVisualizer.play();
    } else {
        std::cerr << "Error loading song: " << filename << std::endl;
    }
}


void SongPanel::update(sf::RenderWindow& window) {
    bool buttonPressed = false;

    // sprawdzenie kliknięcia przycisku piosenki
    for (size_t i = 0; i < songButtons.size(); ++i) {
        if (songButtons[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                playSong(songs[currentPage * songsPerPage + i]);
                buttonPressed = true;
            }
        }
    }

    // sprawdzenie przyciskow nawigacji
    if (!navigationButtons.empty()) {
        if (navigationButtons[0].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentPage > 0 && !buttonPressed) {
                navigateToPage(currentPage - 1);
            }
        }

        if (navigationButtons.size() > 1 && navigationButtons[1].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentPage * songsPerPage + songsPerPage < songs.size() && !buttonPressed) {
                navigateToPage(currentPage + 1);
            }
        }
    }
}

void SongPanel::draw(sf::RenderWindow& window) {
    //std::cout << "Drawing panel elements..." << std::endl;

    // rysowanie przyciskow
    for (const auto& button : songButtons) {
        //std::cout << "Drawing button: " << button.getString().toAnsiString() << std::endl;
        window.draw(button);
    }

    // nawigacja (jezeli pptrzebne)
    for (const auto& navButton : navigationButtons) {
        window.draw(navButton);
    }
}