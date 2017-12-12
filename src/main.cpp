#include <iostream>
#include "components.h"
#include "EntityManager.h"

int main()
{
  EntityManager em;
  size_t id = em.add();
  em.set(id, Body{2, 4});
  em.set(id, Position{0, 1});
  em.set(id, Input{});
  id = em.add();
  em.set(id, Body{2, 4});
  em.set(id, Position{2, 1});
  em.set(id, AI{});
  em.remove(0);
  id = em.add();
  em.set(id, Body{3, 3});
  em.set(id, Position{5, 5});
  id = em.add();
  em.set(id, Body{3, 3});
  em.set(id, Position{10, 10});
  em.dump();
  std::cout << (AI::MASK | Position::MASK) << std::endl;
  em.apply(AI::MASK | Position::MASK,
    [](size_t id, components_t& c) {
      Position& p = std::get<Position::ID>(c);
      std::cout << "id " << id << " is a bot with position ("
        << p.x << "," << p.y << ")" << std::endl;
    });
  return 0;
}
