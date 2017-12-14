/**
 * File: ImpulseSystem.h
 * Info: Ball collision resolution
 * Author: chlablak
 * Date: 2017-12-13
 */

#ifndef IMPULSESYSTEM_H
#define IMPULSESYSTEM_H

#include <iostream> // TODO debug
#include "System.h"
#include "Vec2.h"

class ImpulseSystem
  : public System
{
  public:

    virtual void apply(EntityManager& em)
    {
      em.apply(Contact::MASK | Movement::MASK | Position::MASK,
        [&em](size_t id, components_t& c) {
          Contact& contact = std::get<Contact::ID>(c);
          Movement& move = std::get<Movement::ID>(c);
          Position& pos = std::get<Position::ID>(c);
          std::cout << "CONTACT(" << id << ") -> " << contact.normal << "; "
                    << contact.penetration << "; " << contact.with << std::endl;
          // TODO
          em.unset<Contact>(id);
        });
    }
};

#endif // IMPULSESYSTEM_H
