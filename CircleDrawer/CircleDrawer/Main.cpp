#include <iostream>
#include <SFML/Graphics.hpp>
#include "SVG/Path.h"
#include <sstream>
#include <string>
#include "Simulation.h"
#include <cmath>

int main() {

    int n;
    std::string svgPath;

    std::cout << "Path string of the SVG:" << std::endl;
    std::getline(std::cin, svgPath);

    std::cout << "Number of complementing circles (n >= 1):" << std::endl;
    std::cin >> n;

    std::shared_ptr<Path> path = std::make_shared<Path>(svgPath);

    Simulation simulation(n, path);

//  ----------------------------------------------------------------------
//  ----------------------------------------------------------------------

    const float WIN_SIZE = 800;

    const unsigned int FPS = 60;
    const float DT = 1 / static_cast<float>(FPS);
    const float ANIMATION_SECONDS = 7.0f;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 10;

    sf::RenderWindow window(sf::VideoMode(WIN_SIZE, WIN_SIZE), "Circle Drawer", sf::Style::Default, settings);

    sf::View view(sf::FloatRect(-100, -100, WIN_SIZE, WIN_SIZE));
    window.setView(view);

    sf::Event event;

    sf::Vertex yAxis[] = {
        sf::Vertex(sf::Vector2f(0, -WIN_SIZE), sf::Color::Green),
        sf::Vertex(sf::Vector2f(0, WIN_SIZE), sf::Color::Green)
    };

    sf::Vertex xAxis[] = {
        sf::Vertex(sf::Vector2f(-WIN_SIZE, 0), sf::Color::Green),
        sf::Vertex(sf::Vector2f(WIN_SIZE, 0), sf::Color::Green)
    };

    sf::VertexArray drawing;
    drawing.setPrimitiveType(sf::PrimitiveType::LinesStrip);

    // Prepare circle textures
    std::vector<sf::CircleShape> circleTextures(2 * n + 1);
    for (int i = 0; i < circleTextures.size(); i++) {
        Point circlePoint = simulation.GetVector(0, i - n);

        circleTextures[i].setRadius(sqrt(pow(circlePoint.x, 2) + pow(circlePoint.y, 2)));
        circleTextures[i].setOrigin(circleTextures[i].getRadius(), circleTextures[i].getRadius());
        circleTextures[i].setOutlineColor(sf::Color(114, 181, 185, 255));
        circleTextures[i].setPointCount(500);
        circleTextures[i].setOutlineThickness(1.5f);
        circleTextures[i].setFillColor(sf::Color::Transparent);
    }

    bool firstTravel = true;
    float t = 0;
    sf::Clock clock;
    float currentTime = clock.getElapsedTime().asSeconds(), newTime, frameTime, accumulator = 0;

    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (accumulator > DT) {

            t += accumulator / ANIMATION_SECONDS;

            if (t > 1) {
                t -= floor(t);
                firstTravel = false;
            }

            window.clear();

            window.draw(xAxis, 2, sf::Lines);
            window.draw(yAxis, 2, sf::Lines);

            Point anchorPoint{0, 0}, newPoint;

            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(anchorPoint.x, anchorPoint.y)),
                sf::Vertex(sf::Vector2f(anchorPoint.x, anchorPoint.y))
            };

            for (int i = 0, circleIndex; i <= 2 * n; i++) {

                circleIndex = (i % 2) ? (i + 1) / 2 : -i / 2;
                sf::CircleShape &currCircle = circleTextures[circleIndex + n];

                newPoint = simulation.GetVector(t, circleIndex);
                anchorPoint += newPoint;
                line[0] = line[1];
                line[1].position.x = anchorPoint.x;
                line[1].position.y = anchorPoint.y;

                window.draw(line, 2, sf::Lines);

                currCircle.setPosition(anchorPoint.x, anchorPoint.y);
                window.draw(currCircle);
            }

            if (firstTravel) {
                drawing.append(sf::Vertex(sf::Vector2f(anchorPoint.x, anchorPoint.y), sf::Color::Yellow));
                //drawing.append(sf::Vertex(sf::Vector2f(path->Interpolate(t).x, path->Interpolate(t).y), sf::Color::Red));
            }

            window.draw(drawing);

            window.display();
            accumulator = 0;
        }

        newTime = clock.getElapsedTime().asSeconds();
        accumulator += newTime - currentTime;
        currentTime = newTime;
    }

}