#include "Pelota.h"

#define SCALE 100.0f

Pelota::Pelota(b2World& world, float x, float y, float radius) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / SCALE, y / SCALE);
    body = world.CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = radius / SCALE;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.9f;

    body->CreateFixture(&fixtureDef);

    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color::White);
}

void Pelota::update() {
    b2Vec2 pos = body->GetPosition();
    shape.setPosition(pos.x * SCALE, pos.y * SCALE);
}

void Pelota::draw(sf::RenderWindow& window) {
    update();
    window.draw(shape);
}

void Pelota::setPosition(const sf::Vector2f& pos) {
    body->SetTransform(b2Vec2(pos.x / SCALE, pos.y / SCALE), body->GetAngle());
    body->SetLinearVelocity(b2Vec2(0.f, 0.f));
}

sf::Vector2f Pelota::getPosition() {
    b2Vec2 pos = body->GetPosition();
    return sf::Vector2f(pos.x * SCALE, pos.y * SCALE);
}

b2Body* Pelota::getBody() {
    return body;
}

bool Pelota::contains(const sf::Vector2f& point) {
    sf::Vector2f pos = shape.getPosition();
    float dx = point.x - pos.x;
    float dy = point.y - pos.y;
    float distancia = std::sqrt(dx * dx + dy * dy);
    return distancia <= shape.getRadius();
}


bool Pelota::isMouseNear(const sf::Vector2f& mousePos, float threshold) {
    sf::Vector2f pos = getPosition();
    float dx = mousePos.x - pos.x;
    float dy = mousePos.y - pos.y;
    return std::sqrt(dx * dx + dy * dy) < threshold;
}