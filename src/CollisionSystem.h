/**
 * File: CollisionSystem.h
 * Info: Ball collision detection
 * Author: chlablak
 * Date: 2017-12-14
 */

#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "System.h"
#include "Vec2.h"

class CollisionSystem
  : public System
{
  public:

    // Source: https://learnopengl.com/#!In-Practice/2D-Game/Collisions/Collision-detection
    virtual void apply(EntityManager& em)
    {
      // On each moving body
      em.apply(Body::MASK | Movement::MASK | Position::MASK,
        [&em](size_t id1, components_t& c1) {
          // Versus all other body
          em.apply(Body::MASK | Position::MASK,
            [&](size_t id2, components_t& c2) {
              // We want only AABB
              Body& body2 = std::get<Body::ID>(c2);
              if(id1 != id2 && std::holds_alternative<Body::Rectangle>(body2.shape))
              {
                // Get center point circle first
                Position& center = std::get<Position::ID>(c1);
                // Calculate AABB info (center, half-extents)
                Body::Rectangle& aabb = std::get<Body::Rectangle>(body2.shape);
                Vec2 aabb_half_extents{aabb.width / 2., aabb.height / 2.};
                Position& aabb_center = std::get<Position::ID>(c2);
                // Get difference vector between both centers
                Vec2 difference = center.coords - aabb_center.coords;
                Vec2 clamped{difference};
                clamped.x = std::clamp(clamped.x, -aabb_half_extents.x, aabb_half_extents.x);
                clamped.y = std::clamp(clamped.y, -aabb_half_extents.y, aabb_half_extents.y);
                // Add clamped value to AABB_center and we get the value of box closest to circle
                Vec2 closest = aabb_center.coords + clamped;
                // Retrieve vector between center circle and closest point AABB and check if length <= radius
                difference = closest - center.coords;
                Body& body1 = std::get<Body::ID>(c1);
                Body::Circle& circle = std::get<Body::Circle>(body1.shape);
                if(difference.length_squared() < circle.radius * circle.radius)
                {
                  // Collision! Compute normal and penetration
                  em.set(id1, Contact{Vec2::normalize(-difference),
                                      circle.radius - difference.length(),
                                      id2});
                }
              }
            });
        });
    }
};

#endif // COLLISIONSYSTEM_H
