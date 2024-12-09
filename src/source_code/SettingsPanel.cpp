#include "SettingsPanel.h"
#include <iostream>
#include <filesystem>

SettingsPanel::SettingsPanel(const sf::Vector2f& position, const sf::Vector2f& size)
    : visible(false), backgroundIsImage(false), sensitivity(1.0f), lineThickness(2.0f) {
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    // Panel design
    panelShape.setPosition(position);
    panelShape.setSize(size);
    panelShape.setFillColor(sf::Color(50, 50, 50, 200));
    panelShape.setOutlineColor(sf::Color::White);
    panelShape.setOutlineThickness(2);

    // tło
    backgroundPreview.setSize({size.x - 20.f, 100.f});
    backgroundPreview.setPosition(position.x + 10.f, position.y + 10.f);
    backgroundPreview.setFillColor(sf::Color::Black);

    // suwaki
    sensitivitySlider.setSize({size.x - 40.f, 10.f});
    sensitivitySlider.setPosition(position.x + 20.f, position.y + 130.f);
    sensitivitySlider.setFillColor(sf::Color::Green);

    lineThicknessSlider.setSize({size.x - 40.f, 10.f});
    lineThicknessSlider.setPosition(position.x + 20.f, position.y + 170.f);
    lineThicknessSlider.setFillColor(sf::Color::Blue);

    createButtons();
}

void SettingsPanel::createButtons() {
    buttons.clear();

    std::vector<std::string> labels = {
        "Set Background Image", "Set Background Color",
        "Set Line Color", "Reset to Default"
    };

    float buttonHeight = 40.f;
    sf::Vector2f buttonSize(panelShape.getSize().x - 20.f, buttonHeight);

    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Text button;
        button.setFont(font);
        button.setString(labels[i]);
        button.setCharacterSize(20);
        button.setFillColor(sf::Color::White);
        button.setPosition(panelShape.getPosition().x + 10.f,
                           panelShape.getPosition().y + 200.f + i * (buttonHeight + 10.f));
        buttons.push_back(button);
    }
}

void SettingsPanel::toggleVisibility() {
    visible = !visible;
}

void SettingsPanel::handleInput(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonReleased) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        for (size_t i = 0; i < buttons.size(); ++i) {
            if (buttons[i].getGlobalBounds().contains(mousePos)) {
                if (i == 0) {
                    // Sobraz tła
                    std::string filepath = "../backgrounds/default.jpg"; //w przyszłości okno dialogowe
                    setBackgroundImage(filepath);
                } else if (i == 1) {
                    // kolor tła
                    setBackgroundColor(sf::Color::Red); //w przyszłości okno dialogowe
                    // kolor linii
                    setLineColor(sf::Color::Yellow); //w przyszłości okno color picker.
                } else if (i == 3) {
                    // reset
                    resetToDefault();
                }
            }
        }
    }
}

void SettingsPanel::update() {
    // aktualizacja suwakow
    sensitivitySlider.setPosition(
        panelShape.getPosition().x + 20.f,
        panelShape.getPosition().y + 130.f + sensitivitySlider.getSize().y / 2.f - 5.f
    );
    sensitivitySlider.setFillColor(sf::Color(
        static_cast<sf::Uint8>(sensitivity * 255),
        static_cast<sf::Uint8>((1.0f - sensitivity) * 255),
        0
    ));

    lineThicknessSlider.setPosition(
        panelShape.getPosition().x + 20.f,
        panelShape.getPosition().y + 170.f + lineThicknessSlider.getSize().y / 2.f - 5.f
    );
}

void SettingsPanel::draw(sf::RenderWindow& window) {
    if (!visible) return;

    window.draw(panelShape);
    window.draw(backgroundPreview);
    window.draw(sensitivitySlider);
    window.draw(lineThicknessSlider);

    for (const auto& button : buttons) {
        window.draw(button);
    }
}

void SettingsPanel::setBackgroundImage(const std::string& filepath) {
    if (backgroundTexture.loadFromFile(filepath)) {
        backgroundPreview.setTexture(&backgroundTexture);
        backgroundIsImage = true;
    } else {
        std::cerr << "Error loading background image: " << filepath << std::endl;
    }
}

void SettingsPanel::setBackgroundColor(const sf::Color& color) {
    backgroundPreview.setFillColor(color);
    backgroundIsImage = false;
}

void SettingsPanel::setLineColor(const sf::Color& color) {
    lineColor = color;
}

void SettingsPanel::resetToDefault() {
    setBackgroundColor(sf::Color::Black);
    setLineColor(sf::Color::White);
    sensitivity = 1.0f;
    lineThickness = 2.0f;
}

bool SettingsPanel::isVisible() const {
    return visible;
}
