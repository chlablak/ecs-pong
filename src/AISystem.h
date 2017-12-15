/**
 * File: AISystem.h
 * Info: AI movement system
 * Author: chlablak
 * Date: 2017-12-15
 */

#ifndef AISYSTEM_H
#define AISYSTEM_H

#include "System.h"

class AISystem
  : public System
{
  public:

    virtual void apply(EntityManager& em)
    {
      danger = {0., 0.5};

      // Find the prior danger
      em.apply(Movement::MASK | Position::MASK,
        [this](size_t id, components_t& c) {
          Movement& move = std::get<Movement::ID>(c);
          if(move.velocity.x > 0.)
          {
            Position& pos = std::get<Position::ID>(c);
            if(pos.coords.x > danger.x)
              danger = pos.coords;
          }
        });

      // Move the AI bat to the right position
      em.apply(AI::MASK | Position::MASK,
        [this](size_t id, components_t& c) {
          Position& pos = std::get<Position::ID>(c);
          if(std::abs(pos.coords.y - danger.y) > 0.02)
            pos.coords.y += pos.coords.y < danger.y ? 0.01 : -0.01;
        });
    }

  private:

    Vec2 danger;
};

#endif // AISYSTEM_H
