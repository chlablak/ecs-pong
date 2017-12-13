/**
 * File: GameSystem.h
 * Info: Game system (new balls, scores, menu)
 * Author: chlablak
 * Date: 2017-12-13
 */

#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include <random>
#include <ctime>
#include "System.h"

class GameSystem
  : public System
{
  public:

    GameSystem()
      : gen(std::time(nullptr))
      , dis(-0.01f, 0.01f)
    {}

    virtual void apply(EntityManager& em)
    {
      size_t count = 0;
      em.apply(Position::MASK | Movement::MASK,
        [&](size_t id, components_t& c) {
          Position const& pos = std::get<Position::ID>(c);
          if(pos.x > -0.1f && pos.x < 1.1f && pos.y > -0.1f && pos.y < 1.1f)
            ++count;
          else
          {
            --count;
            em.remove(id);
          }
        });
      if(count == 0)
      {
        size_t id = em.add();
        em.set(id, Body{0.02f});
        em.set(id, Position{0.5f, 0.5f});
        em.set(id, Movement{dis(gen), dis(gen)});
      }
    }

  private:

    std::mt19937 gen;
    std::uniform_real_distribution<float> dis;
};

#endif // GAMESYSTEM_H
