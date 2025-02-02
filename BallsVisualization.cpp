#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>

#define Width 650
#define Height 650

const float Gravity = 9.8f;
const float DeltaTime = 0.016f; // For 60 Frame Window
const float EnergyLossFactor = 0.5f;  // 50% energy loss per bounce
const int LifeTimeLimitSeconds = 10;

void PullEvents(sf::RenderWindow& window, std::vector<sf::CircleShape>& Balls, std::vector<float>& VelocitiesX, std::vector<float>& VelocitiesY, sf::CircleShape& ball, std::vector<std::chrono::steady_clock::time_point>& spawnTimes);

int main() {
    sf::RenderWindow* Window = new sf::RenderWindow(sf::VideoMode({ Width, Height }), "Doge Game");
    Window->setFramerateLimit(60);

    srand(time(0));

    // Balls
    sf::CircleShape Ball;
    Ball.setRadius(20);
    std::vector<sf::CircleShape> Balls;
    std::vector<float> VelocitiesY;
    std::vector<float> VelocitiesX;
    std::vector<std::chrono::steady_clock::time_point> spawnTimes;

    while (Window->isOpen()) {
        Window->clear(sf::Color::Black);
        PullEvents(*Window, Balls, VelocitiesX, VelocitiesY, Ball, spawnTimes);

        // Draw Balls and Move Downward
        for (size_t i = 0; i < Balls.size(); i++) {
            VelocitiesY[i] += Gravity * DeltaTime;
            sf::Vector2f Position = Balls[i].getPosition();
            Position.y += VelocitiesY[i];
            Position.x += VelocitiesX[i];

            // Collision between balls and Bottom 
            if (Position.y + Balls[i].getRadius() >= Window->getSize().y) {
                Position.y = Window->getSize().y - Balls[i].getRadius();
                VelocitiesY[i] = -VelocitiesY[i] * EnergyLossFactor;
            }

            // Collision between balls and Top 
            if (Position.y <= 0) {
                Position.y = 0;
                VelocitiesY[i] = -VelocitiesY[i] * EnergyLossFactor;
            }

            // Collision between balls and Right 
            if (Balls[i].getPosition().x + Balls[i].getRadius() >= Window->getSize().x) {
                Position.x = Window->getSize().x - Balls[i].getRadius();
                VelocitiesX[i] = -VelocitiesX[i] * EnergyLossFactor;
            }

            // Collision between balls and Left 
            if (Balls[i].getPosition().x <= 0) {
                Position.x = Balls[i].getRadius();
                VelocitiesX[i] = -VelocitiesX[i] * EnergyLossFactor;
            }

            // Collision between balls and each other 
            for (size_t j = i + 1; j < Balls.size(); j++) {
                float dx = Balls[j].getPosition().x - Balls[i].getPosition().x;
                float dy = Balls[j].getPosition().y - Balls[i].getPosition().y;
                float distance = std::sqrt(dx * dx + dy * dy);
                float overlap = (Balls[i].getRadius() + Balls[j].getRadius()) - distance;

                if (overlap > 0) {
                    float angle = std::atan2(dy, dx); // Angle between the two balls
                    float sin = std::sin(angle);
                    float cos = std::cos(angle);

                    // Move balls apart
                    Balls[i].move({ -overlap * cos / 2, -overlap * sin / 2 });
                    Balls[j].move({ overlap * cos / 2, overlap * sin / 2 });

                    // Swap velocities (simple elastic collision)
                    std::swap(VelocitiesX[i], VelocitiesX[j]);
                    std::swap(VelocitiesY[i], VelocitiesY[j]);
                }
            }

            Balls[i].setPosition(Position);
            Window->draw(Balls[i]);

            // Check if the ball lifetime exceeded the limit
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - spawnTimes[i]).count();

            if (elapsedSeconds >= LifeTimeLimitSeconds) {
                Balls.erase(Balls.begin() + i);
                VelocitiesX.erase(VelocitiesX.begin() + i);
                VelocitiesY.erase(VelocitiesY.begin() + i);
                spawnTimes.erase(spawnTimes.begin() + i);
                i--; // Adjust index after erasing
            }
        }

        Window->display();
    }

    delete Window;
    return 0;
}

void PullEvents(sf::RenderWindow& window, std::vector<sf::CircleShape>& Balls, std::vector<float>& VelocitiesX, std::vector<float>& VelocitiesY, sf::CircleShape& ball, std::vector<std::chrono::steady_clock::time_point>& spawnTimes) {
    while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();
    }

    // Creating balls
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        std::vector<sf::Color>Colors{ sf::Color::Red , sf::Color::Green , sf::Color::Blue };
        int randColor = rand() % 3;
        ball.setFillColor(Colors[randColor]);
        sf::Vector2i MousePosition = sf::Mouse::getPosition(window);
        ball.setPosition({ static_cast<float>(MousePosition.x) - ball.getRadius(), static_cast<float>(MousePosition.y) - ball.getRadius() });
        Balls.emplace_back(ball);
        VelocitiesX.emplace_back(0.0f);
        VelocitiesY.emplace_back(0.0f);
        spawnTimes.emplace_back(std::chrono::steady_clock::now()); // Record spawn time for the new ball
    }
}
