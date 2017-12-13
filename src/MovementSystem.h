/**
 * File: MovementSystem.h
 * Info: Player input system
 * Author: chlablak
 * Date: 2017-12-13
 */

#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include <SFML/Graphics.hpp>
#include "System.h"

class MovementSystem
  : public System
{
  public:

    virtual void apply(EntityManager& em)
    {
      em.apply(Movement::MASK | Position::MASK,
        [this](size_t id, components_t& c) {
          Position& pos = std::get<Position::ID>(c);
          Movement const& dpos = std::get<Movement::ID>(c);
          pos.x += dpos.dx;
          pos.y += dpos.dy;
        });
    }
};

#endif // MOVEMENTSYSTEM_H
