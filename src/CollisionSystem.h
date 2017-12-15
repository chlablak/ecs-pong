/**
 * File: CollisionSystem.h
 * Info: Collision detection system
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
              if(id1 != id2
                && std::holds_alternative<Body::Rectangle>(body2.shape)
                && !em.has<Fade>(id2))
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
                  Vec2 true_normal = Vec2::normalize(-difference);
                  Vec2 normal = true_normal;

                  // Collision with bat
                  if(em.has<Input>(id2) || em.has<AI>(id2))
                  {
                    normal = center.coords - aabb_center.coords;
                    normal.y = std::clamp(normal.y, -0.0125, 0.0125);
                    normal = Vec2::normalize(normal);
                  }

                  // Add the contact collision
                  em.set(id1, Contact{normal, true_normal, circle.radius - difference.length(), id2});

                  // Brick wall should fade out
                  if(em.has<Brick>(id2))
                    em.set(id2, Fade{-10, 255});
                }
              }
            });
        });
    }
};

#endif // COLLISIONSYSTEM_H
