/**
 * File: main.c
 * Info: main() function
 * Author: chlablak
 * Date: 2017-12-12
 */

#include <SFML/Graphics.hpp>
#include "RenderSystem.h"
#include "InputSystem.h"
#include "GameSystem.h"
#include "MovementSystem.h"
#include "SystemManager.h"

int main()
{
  // Window's size
  constexpr size_t WINDOW_WIDTH = 800;
  constexpr size_t WINDOW_HEIGHT = 600;

  // Render window
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "ecs-pong",
                          sf::Style::Close | sf::Style::Titlebar);
  window.setVerticalSyncEnabled(true);
  window.setPosition({200, 200});

  // Systems
  SystemManager sys;
  sys.add(new RenderSystem(window));
  sys.add(new InputSystem(window));
  sys.add(new GameSystem());
  sys.add(new MovementSystem());

  // Starting entities
  EntityManager em;
  size_t id = em.add(); // upper wall
  em.set(id, Position{0.5f, 0.01f});
  em.set(id, Body{0.99f, 0.01f});
  id = em.add(); // bottom wall
  em.set(id, Position{0.5f, 0.99f});
  em.set(id, Body{0.99f, 0.01f});
  id = em.add(); // player bat
  em.set(id, Position{0.05f, 0.5f});
  em.set(id, Body{0.01f, 0.1f});
  em.set(id, Input{});
  id = em.add(); // bot bat
  em.set(id, Position{0.95f, 0.5f});
  em.set(id, Body{0.01f, 0.1f});
  em.set(id, AI{});

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
