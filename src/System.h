/**
 * File: System.h
 * Info: Base class for systems of ECS
 * Author: chlablak
 * Date: 2017-12-12
 */

#ifndef SYSTEM_H
#define SYSTEM_H

#include "EntityManager.h"
#include "components.h"

class System
{
  public:

    // Apply the system on entities
    void apply(EntityManager& em)
    {
      em.apply(mask(), [this](size_t id, components_t& c) { action(id, c); });
    }

    // action() applies on entity specified by mask()
    virtual mask_t mask() const = 0;
    virtual void action(size_t id, components_t& c) = 0;
};

#endif // SYSTEM_H
