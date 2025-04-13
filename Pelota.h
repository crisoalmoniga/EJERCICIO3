#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#define SCALE 100.0f

class Pelota {
public:
    Pelota(b2World& world, float x, float y, float radius, bool esEstatica = false);

    void draw(sf::RenderWindow& window);
    b2Body* getBody();
    bool contains(sf::Vector2f point);

private:
    b2Body* body;
    sf::CircleShape shape;
};
