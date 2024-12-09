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
                std::string fileName = entry->d_name;

                // Rozszerzenia audio
                if (fileName.find(".mp3") != std::string::npos ||
                    fileName.find(".wav") != std::string::npos ||
                    fileName.find(".ogg") != std::string::npos) {
                    files.push_back(fileName);
                }
            }
        }
        closedir(dir);
    }
    return files;
}


SongPanel::SongPanel(AudioVisualizer& audioVisualizer, const std::string& songsDirectory, const sf::Vector2f& position)
    : audioVisualizer(audioVisualizer), currentPage(0), songsPerPage(5), menuVisible(false), toggleButtonPressed(false) {

    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    loadSongs(songsDirectory);

    // Inicjalizacja przycisku toggle
    toggleButton.setFont(font);
    toggleButton.setString("Show Menu");
    toggleButton.setCharacterSize(20);
    toggleButton.setFillColor(sf::Color::White);
    toggleButton.setPosition(10.f, 10.f);

    createButtons();
}


void SongPanel::toggleMenu() {
    menuVisible = !menuVisible;
    toggleButton.setString(menuVisible ? "Hide Menu" : "Show Menu");
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
    navigationButtons.clear(); // czyszczenie przycisku nawigacji

    size_t startIndex = currentPage * songsPerPage;
    size_t endIndex = std::min(startIndex + songsPerPage, songs.size());

    std::cout << "Creating buttons for page " << currentPage << std::endl;

    // Tworzenie przyciskow piosenek
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

    // Tworzenie przyciskow nawigacji
    if (currentPage > 0) { // dodaj przycisk "previous"
        sf::Text prevButton("Previous", font, 20);
        prevButton.setFillColor(sf::Color::White);
        prevButton.setPosition(10.f, 10.f + (songButtons.size()) * (buttonHeight + 10.f));
        navigationButtons.push_back(prevButton);
    }

    if (currentPage * songsPerPage + songsPerPage < songs.size()) { // dodaj PRZYCISK "next"
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
    // przycisk toggle logika
    if (toggleButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            toggleButtonPressed = true; // przycisk jest przytrzymany
        } else if (toggleButtonPressed) {
            // przycisk upuszczony
            toggleMenu();
            toggleButtonPressed = false;
        }
    } else {
        toggleButtonPressed = false; // reset flagi
    }

    // nie aktulaizuj, jak ukryte
    if (!menuVisible) return;

    bool buttonPressed = false;

    // sprawdzanie kliknięć przyciskow piosenek
    for (size_t i = 0; i < songButtons.size(); ++i) {
        if (songButtons[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                playSong(songs[currentPage * songsPerPage + i]);
                buttonPressed = true;
            }
        }
    }

    // sprawdzanie przyciskow nawigacji
    for (size_t i = 0; i < navigationButtons.size(); ++i) {
        if (navigationButtons[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !buttonPressed) {
                if (navigationButtons[i].getString() == "Previous" && currentPage > 0) {
                    navigateToPage(currentPage - 1);
                } else if (navigationButtons[i].getString() == "Next" && currentPage * songsPerPage + songsPerPage < songs.size()) {
                    navigateToPage(currentPage + 1);
                }
            }
        }
    }
}





void SongPanel::draw(sf::RenderWindow& window) {
    // rysuj przycisk toggle
    window.draw(toggleButton);

    // nie rysuj, jak ukryte
    if (!menuVisible) return;

    
    float startY = toggleButton.getPosition().y + toggleButton.getGlobalBounds().height + 10.f;

    for (size_t i = 0; i < songButtons.size(); ++i) {
        songButtons[i].setPosition(10.f, startY + i * (buttonHeight + 10.f));
        window.draw(songButtons[i]);
    }

    // rysuj przyciski nawigacji
    for (size_t i = 0; i < navigationButtons.size(); ++i) {
        navigationButtons[i].setPosition(10.f + i * 150.f, startY + songButtons.size() * (buttonHeight + 10.f));
        window.draw(navigationButtons[i]);
    }
}

