/**
 * File: RenderSystem.h
 * Info: Rendering system
 * Author: chlablak
 * Date: 2017-12-12
 */

#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SFML/Graphics.hpp>
#include "System.h"

class RenderSystem
  : public System
{
  public:

    RenderSystem(sf::RenderWindow& window)
      : window(window)
    {}

    virtual void apply(EntityManager& em)
    {
      em.apply(Body::MASK | Position::MASK,
        [this](size_t id, components_t& c) {
          Body const& body = std::get<Body::ID>(c);
          Position const& pos = std::get<Position::ID>(c);
          sf::Vector2u size = window.getSize();

          // If we have a circle
          if(std::holds_alternative<Body::Circle>(body.body))
          {
            Body::Circle const& circle = std::get<Body::Circle>(body.body);
            size_t r = circle.radius * std::min(size.x, size.y) / 2.f;
            sf::CircleShape shape(r);
            shape.setPosition(pos.x * size.x - r, pos.y * size.y - r);
            window.draw(shape);
          }

          // Else if we have a rectangle
          else if(std::holds_alternative<Body::Rectangle>(body.body))
          {
            Body::Rectangle const& rect = std::get<Body::Rectangle>(body.body);
            sf::RectangleShape shape({rect.width * size.x, rect.height * size.y});
            shape.setPosition((pos.x - rect.width / 2.f) * size.x,
                              (pos.y - rect.height / 2.f) * size.y);
            window.draw(shape);
          }
        });
    }

  private:

    sf::RenderWindow& window;
};

#endif // RENDERSYSTEM_H
