#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <cmath>
#include "Pelota.h"

#define SCALE 100.0f

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ejercicio 2");
    window.setFramerateLimit(60);

    b2Vec2 gravity(0.f, 0.0f);
    b2World world(gravity);

    // Crear pelotas
    Pelota p1(world, 300, 300, 25);
    Pelota p2(world, 500, 300, 25);
    Pelota* pelotaSeleccionada = nullptr;

    // Crear bordes del mundo
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.f, 0.f);
    b2Body* ground = world.CreateBody(&groundBodyDef);

    b2EdgeShape edge;
    b2FixtureDef edgeFixture;
    edgeFixture.shape = &edge;

    // Piso
    edge.SetTwoSided(b2Vec2(0, 6), b2Vec2(8, 6));
    ground->CreateFixture(&edgeFixture);
    // Techo
    edge.SetTwoSided(b2Vec2(0, 0), b2Vec2(8, 0));
    ground->CreateFixture(&edgeFixture);
    // Izquierda
    edge.SetTwoSided(b2Vec2(0, 0), b2Vec2(0, 6));
    ground->CreateFixture(&edgeFixture);
    // Derecha
    edge.SetTwoSided(b2Vec2(8, 0), b2Vec2(8, 6));
    ground->CreateFixture(&edgeFixture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Cerrar ventana
            if (event.type == sf::Event::Closed)
                window.close();

            // Mouse presionado
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (p1.contains(mousePos))
                    pelotaSeleccionada = &p1;
                else if (p2.contains(mousePos))
                    pelotaSeleccionada = &p2;
            }

            // Mouse soltado
            if (event.type == sf::Event::MouseButtonReleased) {
                pelotaSeleccionada = nullptr;
            }
        }

        // Mover pelota con el mouse
        if (pelotaSeleccionada && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            b2Vec2 newPos(mousePos.x / SCALE, mousePos.y / SCALE);
            pelotaSeleccionada->getBody()->SetTransform(newPos, 0);
            pelotaSeleccionada->getBody()->SetLinearVelocity(b2Vec2(0, 0));  // Detener momento acumulado
        }

        // Aplicar fuerza tipo resorte (Hooke)
        b2Vec2 pos1 = p1.getBody()->GetWorldCenter();
        b2Vec2 pos2 = p2.getBody()->GetWorldCenter();
        b2Vec2 delta = pos2 - pos1;
        float distancia = delta.Length();
        float longitudReposo = 2.0f;
        float extension = distancia - longitudReposo;

        if (distancia != 0) {
            delta.Normalize();
            float k = 20.0f; // rigidez del resorte
            b2Vec2 fuerza = -k * extension * delta;
            p1.getBody()->ApplyForceToCenter(-fuerza, true);
            p2.getBody()->ApplyForceToCenter(fuerza, true);
        }

        world.Step(1.f / 60.f, 8, 3);

        window.clear(sf::Color::Black);
        p1.draw(window);
        p2.draw(window);

        // Dibujar línea del resorte
        sf::Vertex resorteLinea[] = {
            sf::Vertex(sf::Vector2f(p1.getBody()->GetPosition().x * SCALE, p1.getBody()->GetPosition().y * SCALE), sf::Color::Green),
            sf::Vertex(sf::Vector2f(p2.getBody()->GetPosition().x * SCALE, p2.getBody()->GetPosition().y * SCALE), sf::Color::Green)
        };
        window.draw(resorteLinea, 2, sf::Lines);


        window.display();
    }

    return 0;
}