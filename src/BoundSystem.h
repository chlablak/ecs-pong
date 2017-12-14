/**
 * File: BoundSystem.h
 * Info: Player input system
 * Author: chlablak
 * Date: 2017-12-13
 */

#ifndef BOUNDSYSTEM_H
#define BOUNDSYSTEM_H

#include "System.h"

class BoundSystem
  : public System
{
  public:

    virtual void apply(EntityManager& em)
    {
      em.apply(Bound::MASK | Position::MASK,
        [](size_t id, components_t& c) {
          Position& p = std::get<Position::ID>(c);
          Bound const& b = std::get<Bound::ID>(c);
          if(p.coords.x < b.min.x)
            p.coords.x = b.min.x;
          else if(p.coords.x > b.max.x)
            p.coords.x = b.max.x;
          if(p.coords.y < b.min.y)
            p.coords.y = b.min.y;
          else if(p.coords.y > b.max.y)
            p.coords.y = b.max.y;
        });
    }
};

#endif // BOUNDSYSTEM_H
