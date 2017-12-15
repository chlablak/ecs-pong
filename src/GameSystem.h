/**
 * File: GameSystem.h
 * Info: Game system (new balls, scores, menu)
 * Author: chlablak
 * Date: 2017-12-13
 */

#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>
#include "System.h"

class GameSystem
  : public System
{
  public:

    GameSystem(sf::RenderWindow& window)
      : window(window)
      , gen(std::time(nullptr))
      , dis(-0.01, 0.01)
      , scores{0, 0}
    {
      sf::Vector2u size = window.getSize();
      font.loadFromFile("BebasNeue.otf"); // can fail
      text.setFont(font);
      text.setCharacterSize(size.y / 10);
      text.setStyle(sf::Text::Bold);
      text.setString("0  0");
      text.setOrigin(text.getLocalBounds().width / 2, 0);
      text.setPosition(size.x / 2, size.y / 16);
    }

    virtual void apply(EntityManager& em)
    {
      size_t count = 0;
      em.apply(Position::MASK | Movement::MASK,
        [&](size_t id, components_t& c) {
          Position const& pos = std::get<Position::ID>(c);
          if(  pos.coords.x > -0.1 && pos.coords.x < 1.1
            && pos.coords.y > -0.1 && pos.coords.y < 1.1)
          {
            ++count;
          }
          else
          {
            em.remove(id);
            if(pos.coords.x < 0.)
              ++scores.second;
            else
              ++scores.first;
            text.setString(std::to_string(scores.first)
                           + "  " + std::to_string(scores.second));
            text.setOrigin(text.getLocalBounds().width / 2, 0);
          }
        });
      size_t id = -1;
      for(size_t i = 0; i < 2 - count; ++i)
      {
        id = em.add();
        em.set(id, Body{0.015f});
        em.set(id, Position{0.5f, 0.5f});
        em.set(id, Movement{dis(gen), dis(gen)});
      }
      window.draw(text);
    }

  private:

    sf::RenderWindow& window;
    std::mt19937 gen;
    std::uniform_real_distribution<double> dis;
    std::pair<size_t, size_t> scores;
    sf::Font font;
    sf::Text text;
};

#endif // GAMESYSTEM_H
