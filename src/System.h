/**
 * File: System.h
 * Info: Base class for systems of ECS
 * Author: chlablak
 * Date: 2017-12-12
 */

#ifndef SYSTEM_H
#define SYSTEM_H

#include "EntityManager.h"

class System
{
  public:

    virtual ~System()
    {}

    // Apply the system on entities
    virtual void apply(EntityManager& em) = 0;
};

#endif // SYSTEM_H
