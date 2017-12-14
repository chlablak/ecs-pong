/**
 * File: main.c
 * Info: main() function
 * Author: chlablak
 * Date: 2017-12-12
 */

#include <SFML/Graphics.hpp>
#include "SystemManager.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "GameSystem.h"
#include "MovementSystem.h"
#include "BoundSystem.h"
#include "CollisionSystem.h"
#include "ImpulseSystem.h"

int main()
{
  // Window's size
  constexpr size_t WINDOW_WIDTH = 400;
  constexpr size_t WINDOW_HEIGHT = 300;

  // Render window
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "ecs-pong",
                          sf::Style::Close | sf::Style::Titlebar);
  window.setVerticalSyncEnabled(true);
  window.setPosition({200, 600});

  // Systems
  SystemManager sys;
  sys.add(new InputSystem(window));
  sys.add(new BoundSystem());
  sys.add(new CollisionSystem());
  sys.add(new ImpulseSystem());
  sys.add(new MovementSystem());
  sys.add(new GameSystem(window));
  sys.add(new RenderSystem(window));

  // Starting entities
  EntityManager em;
  size_t id = em.add(); // upper wall
  em.set(id, Position{{0.5, 0.015}});
  em.set(id, Body{0.99, 0.01});
  id = em.add(); // bottom wall
  em.set(id, Position{{0.5, 0.985}});
  em.set(id, Body{0.99, 0.01});
  id = em.add(); // player bat
  em.set(id, Position{{0.05, 0.5}});
  em.set(id, Body{0.01, 0.1});
  em.set(id, Bound{{0.05, 0.08}, {0.05, 0.92}});
  em.set(id, Input{});
  id = em.add(); // bot bat
  em.set(id, Position{{0.95, 0.5}});
  em.set(id, Body{0.01, 0.1});
  em.set(id, Bound{{0.95, 0.08}, {0.95, 0.92}});
  em.set(id, AI{});

  // TODO debug
  id = em.add();
  em.set(id, Position{{0.01, 0.5}});
  em.set(id, Body{0.01, 0.94});
  id = em.add();
  em.set(id, Position{{0.99, 0.5}});
  em.set(id, Body{0.01, 0.94});

  // Main loop
  while (window.isOpen())
  {
    // Events
    sf::Event event;
    while (window.pollEvent(event))
    {
      // Closing window
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // Clear screen
    window.clear(sf::Color::Black);

    // Systems
    sys.apply(em);

    // Display
    window.display();
  }

  // The End
  return 0;
}
