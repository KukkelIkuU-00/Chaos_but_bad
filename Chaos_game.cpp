#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;
using namespace sf;

// VARIABLES
static const float ikkuna = 900.0;
static int seed_num = 5;
static float lerp_num = 0.61803398875;
static float radius = ikkuna / 2 - 25.0;
static int density = 100000;
static int alpha = 255;

float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

/*
SIERPINSKI TRIANGLE:
    seed_num = 3
    lerp_num = 0.5
PENTAGONAL N-FLAKE:
    seed_num = 5
    lerp_num = 1/phi = 0.61803398875
HEXA N_FLAKE:
    seed_num = 6
    lerp_num = 2/3
HEPTA N-FLAKE:
    seed_num = 7
    lerp_num = 0.69
OCTA N-FLAKE:
    seed_num = 8
    lerp_num = 0.71
*/

int main()
{
    int rand_number = int(ikkuna) + 1;
    Vector2f current(float(rand() % rand_number), float(rand() % rand_number));

    // Window render and particle
    RenderWindow window(VideoMode(ikkuna, ikkuna), "Chaos game", Style::Close | Style::Titlebar);
    View view(Vector2f(ikkuna / 2, ikkuna / 2), Vector2f(ikkuna, ikkuna));

    // lista kulma pisteistä
    VertexArray vertex(Points, seed_num);
    for (int i = 0; i < seed_num; i++) {
        float angle = i * (2 * M_PI) / seed_num;
        angle -= M_PI / 2;
        vertex[i].position = Vector2f(cos(angle) * radius, sin(angle) * radius);
        vertex[i].position += Vector2f(ikkuna/2, ikkuna/2);
        vertex[i].color = Color::Magenta;
    }

    // Main pisteet
    VertexArray points(Points, density);
    for (int i = 0; i < density; i++) {
        Vector2f next_corner(vertex[rand() % seed_num].position);
        points[i].position = Vector2f(lerp(current.x, next_corner.x, lerp_num), lerp(current.y, next_corner.y, lerp_num));
        points[i].color = Color(0, 255, 0, alpha);
        current = points[i].position;
    }

    // Main loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

	// zoomia
        if (Keyboard::isKeyPressed(Keyboard::Z)) {
            view.zoom(0.999f);
        } else if (Keyboard::isKeyPressed(Keyboard::X)) {
            view.zoom(1.001f);
        }

	// alkeellista liikkumista, pitäisi muuttaa hiirellä liikutettavaksi
        if(Keyboard::isKeyPressed(Keyboard::Key::A)) {
            view.move(-0.1f, 0.0f);
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::D)) {
            view.move(0.1f, 0.0f);
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::W)) {
            view.move(0.0f, -0.1f);
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::S)) {
            view.move(0.0f, 0.1f);
        }

        window.clear();
        window.setView(view);
        window.draw(vertex);
        window.draw(points);
        window.display();
    }
    return 0;
}