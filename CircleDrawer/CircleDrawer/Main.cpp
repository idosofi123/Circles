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

    sf::View view(sf::FloatRect(-100, WIN_SIZE - 100, WIN_SIZE, -WIN_SIZE));
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

            sf::CircleShape circle;
            circle.setOutlineColor(sf::Color(114, 181, 185, 255));
            circle.setPointCount(500);
            circle.setOutlineThickness(1.5f);
            circle.setFillColor(sf::Color::Transparent);

            for (int i = 0, circleIndex; i <= 2 * n; i++) {

                circleIndex = (i % 2) ? (i + 1) / 2 : -i / 2;

                newPoint = simulation.GetVector(t, circleIndex);
                anchorPoint += newPoint;
                line[0] = line[1];
                line[1] = sf::Vertex(sf::Vector2f(anchorPoint.x, anchorPoint.y));

                window.draw(line, 2, sf::Lines);

                circle.setRadius(sqrt(pow(newPoint.x, 2) + pow(newPoint.y, 2)));
                circle.setOrigin(circle.getRadius(), circle.getRadius());
                circle.setPosition(anchorPoint.x, anchorPoint.y);
                window.draw(circle);
            }

            if (firstTravel) {
                drawing.append(sf::Vertex(sf::Vector2f(anchorPoint.x, anchorPoint.y), sf::Color::Yellow));
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