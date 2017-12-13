/**
 * File: SystemManager.h
 * Info: Manager for systems
 * Author: chlablak
 * Date: 2017-12-13
 */

#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <list>
#include <tuple>
#include "EntityManager.h"
#include "System.h"

class SystemManager
{
  public:

    ~SystemManager()
    {
      for(auto& [s, freq, start, del] : systems)
      {
        if(del)
          delete s;
        [[maybe_unused]] size_t freq_ = freq;
        [[maybe_unused]] bool start_ = start;
      }
    }

    // Add a new system in queue
    void add(System* s, size_t freq = 0, size_t start = 0, bool del = true)
    {
      systems.push_back({s, freq, start, del});
    }

    // Call each system
    void apply(EntityManager& em)
    {
      for(auto& [s, freq, start, del] : systems)
      {
        if(start-- <= 0)
        {
          s->apply(em);
          start = freq;
        }
        [[maybe_unused]] bool del_ = del;
      }
    }

  private:

    typedef std::tuple<System*, size_t, size_t, bool> system_t;

    std::list<system_t> systems;
};

#endif // SYSTEMMANAGER_H
