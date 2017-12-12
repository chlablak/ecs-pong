/**
 * File: EntityManager.h
 * Info: Entities manager for the ECS
 * Author: chlablak
 * Date: 2017-12-12
 */

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <functional>
#include "components.h"

class EntityManager
{
  public:

    typedef std::function<void(size_t, components_t&)> function_t;

    // Return the first empty entity's ID
    size_t add()
    {
      size_t id = 0;
      for(; id < std::size(masks); ++id)
      {
        if(masks[id] == 0)
          return id;
      }
      masks.push_back(0);
      components.push_back(components_t{});
      return id;
    }

    // Remove an entity, takes the entity's ID
    void remove(size_t id)
    {
      masks[id] = 0;
    }

    // Set a component on an entity
    template<typename Component>
    void set(size_t id, Component const& component)
    {
      std::get<Component::ID>(components[id]) = component;
      masks[id] |= Component::MASK;
    }

    // Apply a function on each entity matching a defined mask
    void apply(mask_t const& mask, function_t const& f)
    {
      for(size_t id = 0; id < std::size(masks); ++id)
      {
        if((masks[id] & mask) == mask)
          f(id, components[id]);
      }
    }

  private:

    // Each entity has a mask and associated components
    std::vector<mask_t> masks;
    std::vector<components_t> components;
}; // class EntityManager

#endif // ENTITYMANAGER_H
