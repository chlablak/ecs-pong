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

    // (can be easily optimized)
    virtual void apply(EntityManager& em)
    {
      em.apply(Body::MASK | Position::MASK,
        [this](size_t id, components_t& c) {
          Body const& body = std::get<Body::ID>(c);
          Position const& pos = std::get<Position::ID>(c);
          sf::Vector2u size = window.getSize();

          // If we have a circle
          if(std::holds_alternative<Body::Circle>(body.shape))
          {
            Body::Circle const& circle = std::get<Body::Circle>(body.shape);
            size_t r = circle.radius * std::min(size.x, size.y) / 2.;
            sf::CircleShape shape(r);
            shape.setPosition(pos.coords.x * size.x - r, pos.coords.y * size.y - r);
            window.draw(shape);
          }

          // Else if we have a rectangle
          else if(std::holds_alternative<Body::Rectangle>(body.shape))
          {
            Body::Rectangle const& rect = std::get<Body::Rectangle>(body.shape);
            sf::RectangleShape shape({(float)(rect.width * size.x),
                                      (float)(rect.height * size.y)});
            shape.setPosition((pos.coords.x - rect.width / 2.) * size.x,
                              (pos.coords.y - rect.height / 2.) * size.y);
            window.draw(shape);
          }
        });
    }

  private:

    sf::RenderWindow& window;
};

#endif // RENDERSYSTEM_H
