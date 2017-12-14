/**
 * File: CollisionSystem.h
 * Info: Ball collision detection
 * Author: chlablak
 * Date: 2017-12-13
 */

#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "System.h"
#include "Vec2.h"

class CollisionSystem
  : public System
{
  public:

    virtual void apply(EntityManager& em)
    {

    }
};

#endif // COLLISIONSYSTEM_H
