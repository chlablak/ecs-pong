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
      components.push_back(components_t());
      return id;
    }

    // Remove an entity
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

    // Unset a component on an entity
    template<typename Component>
    void unset(size_t id)
    {
      masks[id] &= ~Component::MASK;
    }

    // Check if an entity has a component
    template<typename Component>
    bool has(size_t id) const
    {
      return (masks[id] & Component::MASK).any();
    }

    // Apply a function on each entity matching a defined mask
    void apply(mask_t const& mask,
               std::function<void(size_t, components_t&)> const& f)
    {
      apply([&](mask_t const& m) { return (mask & m) == mask; }, f);
    }

    // Apply a function on each entity validating the predicate
    void apply(std::function<bool(mask_t const& mask)> const& p,
               std::function<void(size_t, components_t&)> const& f)
    {
      for(size_t id = 0; id < std::size(masks); ++id)
      {
        if(p(masks[id]))
          f(id, components[id]);
      }
    }

  private:

    // Each entity has a mask and associated components
    std::vector<mask_t> masks;
    std::vector<components_t> components;
}; // class EntityManager

#endif // ENTITYMANAGER_H
