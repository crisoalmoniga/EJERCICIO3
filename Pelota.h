#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Pelota {
public:
    Pelota(b2World& world, float x, float y, float radius);

    void update();
    void draw(sf::RenderWindow& window);
    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition();
    b2Body* getBody();

    bool isMouseNear(const sf::Vector2f& mousePos, float threshold = 30.0f);
    bool contains(const sf::Vector2f& point);


private:
    b2Body* body;
    sf::CircleShape shape;
};
