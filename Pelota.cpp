#include "Pelota.h"

Pelota::Pelota(b2World& world, float x, float y, float radius, bool esEstatica) {
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color::White);

    b2BodyDef bodyDef;
    bodyDef.position.Set(x / SCALE, y / SCALE);
    bodyDef.type = esEstatica ? b2_staticBody : b2_dynamicBody;
    body = world.CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = radius / SCALE;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 1.0f;
    fixtureDef.restitution = 0.6f;

    body->CreateFixture(&fixtureDef);
}

void Pelota::draw(sf::RenderWindow& window) {
    b2Vec2 pos = body->GetPosition();
    shape.setPosition(pos.x * SCALE, pos.y * SCALE);
    window.draw(shape);
}

b2Body* Pelota::getBody() {
    return body;
}

bool Pelota::contains(sf::Vector2f point) {
    return shape.getGlobalBounds().contains(point);
}
