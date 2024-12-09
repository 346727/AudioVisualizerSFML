#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>

class SettingsPanel {
public:
    SettingsPanel(const sf::Vector2f& position, const sf::Vector2f& size);

    // Metody do zarzadzania user input
    void toggleVisibility();
    void handleInput(const sf::Event& event, sf::RenderWindow& window);
    void update();
    void draw(sf::RenderWindow& window);

    // ustwawienia
    void setBackgroundImage(const std::string& filepath);
    void setBackgroundColor(const sf::Color& color);
    void setLineColor(const sf::Color& color);
    void resetToDefault();

    // dostępy
    bool isVisible() const;

private:
    sf::RectangleShape panelShape;
    sf::RectangleShape backgroundPreview;
    sf::Color backgroundColor;
    sf::Color lineColor;

    std::vector<sf::Text> buttons;
    sf::Font font;

    bool visible;
    bool backgroundIsImage;
    sf::Texture backgroundTexture;

    // Suwaki i opcje
    float sensitivity;
    float lineThickness;
    sf::RectangleShape sensitivitySlider;
    sf::RectangleShape lineThicknessSlider;

    // Helper metody
    void createButtons();
    void updateSliders(sf::RenderWindow& window);
    void applyBackground();
};

#endif // SETTINGSPANEL_H
