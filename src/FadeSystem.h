/**
 * File: FadeSystem.h
 * Info: Fade in/out system
 * Author: chlablak
 * Date: 2017-12-15
 */

#ifndef FADESYSTEM_H
#define FADESYSTEM_H

#include "System.h"

class FadeSystem
  : public System
{
  public:

    virtual void apply(EntityManager& em)
    {
      // Fade by modifying alpha color
      em.apply(Body::MASK | Fade::MASK,
        [&em](size_t id, components_t& c) {
          Body& body = std::get<Body::ID>(c);
          Fade& fade = std::get<Fade::ID>(c);
          fade.alpha += fade.diff;
          fade.alpha = std::clamp(fade.alpha, 0, 255);
          body.color.a = fade.alpha

          // Fade in complete, remove Fade component
          if(fade.alpha == 255)
            em.unset<Fade>(id);
        });
    }
};

#endif // FADESYSTEM_H
