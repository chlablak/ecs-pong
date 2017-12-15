/**
 * File: ImpulseSystem.h
 * Info: Ball collision resolution
 * Author: chlablak
 * Date: 2017-12-14
 */

#ifndef IMPULSESYSTEM_H
#define IMPULSESYSTEM_H

#include "System.h"
#include "Vec2.h"

class ImpulseSystem
  : public System
{
  public:

    // Source: https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
    virtual void apply(EntityManager& em)
    {
      em.apply(Contact::MASK | Movement::MASK | Position::MASK,
        [&em](size_t id, components_t& c) {
          Contact& contact = std::get<Contact::ID>(c);
          Movement& move = std::get<Movement::ID>(c);
          Position& pos = std::get<Position::ID>(c);
          pos.coords += contact.penetration * contact.normal;
          move.velocity -= 2. * Vec2::dot_product(move.velocity, contact.normal) * contact.normal;
          move.velocity *= 1.002;
          em.unset<Contact>(id);
        });
    }
};

#endif // IMPULSESYSTEM_H
