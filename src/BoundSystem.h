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
        [this](size_t id, components_t& c) {
          Position& p = std::get<Position::ID>(c);
          Bound const& b = std::get<Bound::ID>(c);
          if(p.x < b.minx)
            p.x = b.minx;
          else if(p.x > b.maxx)
            p.x = b.maxx;
          if(p.y < b.miny)
            p.y = b.miny;
          else if(p.y > b.maxy)
            p.y = b.maxy;
        });
    }
};

#endif // BOUNDSYSTEM_H
