/**
 * File: InputSystem.h
 * Info: Player input system
 * Author: chlablak
 * Date: 2017-12-13
 */

#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <SFML/Graphics.hpp>
#include "System.h"

class InputSystem
  : public System
{
  public:

    InputSystem(sf::RenderWindow& window)
      : window(window)
    {}

    virtual void apply(EntityManager& em)
    {
      // Player bat moves with the mouse
      em.apply(Input::MASK | Position::MASK,
        [this](size_t id, components_t& c) {
          Position& pos = std::get<Position::ID>(c);
          sf::Vector2i mouse = sf::Mouse::getPosition(window);
          sf::Vector2u size = window.getSize();
          pos.coords.x = (double)mouse.x / size.x;
          pos.coords.y = (double)mouse.y / size.y;
        });
    }

  private:

    sf::RenderWindow& window;
};

#endif // INPUTSYSTEM_H
