/**
 * File: ImpulseSystem.h
 * Info: Ball collision resolution
 * Author: chlablak
 * Date: 2017-12-13
 */

#ifndef IMPULSESYSTEM_H
#define IMPULSESYSTEM_H

#include "System.h"
#include "Vec2.h"

class ImpulseSystem
  : public System
{
  public:

    virtual void apply(EntityManager& em)
    {

    }
};

#endif // IMPULSESYSTEM_H
