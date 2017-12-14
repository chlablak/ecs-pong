/**
 * File: components.h
 * Info: Defines all components for the ECS
 * Author: chlablak
 * Date: 2017-12-12
 */

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <variant>
#include <bitset>
#include <tuple>
#include "Vec2.h"

struct Body;
struct Position;
struct Input;
struct AI;
struct Movement;
struct Bound;
struct Contact;

// Components collection (in correct order)
using components_t =
  std::tuple<Body, Position, Input, AI, Movement, Bound, Contact>;

// Mask type
using mask_t = std::bitset<std::tuple_size_v<components_t>>;

// Body (physics and graphics)
// (Position XY is on the center of mass)
struct Body
{
  // Each component has its ID (must follow order of components_t)
  // The mask is deduced from the ID
  static constexpr size_t ID{0};
  static constexpr mask_t MASK{1 << ID};

  // Body can be a circle or a rectangle
  struct Circle
  {
    double radius;
  };

  struct Rectangle
  {
    double width;
    double height;
  };

  // fields
  std::variant<Circle, Rectangle> shape;

  // constructors for confort
  Body(double radius = 0.)
    : shape{Circle{radius}}
  {}

  Body(double width, double height)
    : shape{Rectangle{width, height}}
  {}
}; // struct Body

// Position XY (domain is [0;1])
struct Position
{
  static constexpr size_t ID{1};
  static constexpr mask_t MASK{1 << ID};

  // fields
  Vec2 coords;
};

// Tag for the player bat
struct Input
{
  static constexpr size_t ID{2};
  static constexpr mask_t MASK{1 << ID};
};

// Tag for the AI bat
struct AI
{
  static constexpr size_t ID{3};
  static constexpr mask_t MASK{1 << ID};
};

// Movement XY
struct Movement
{
  static constexpr size_t ID{4};
  static constexpr mask_t MASK{1 << ID};

  // fields
  Vec2 velocity;
};

// AABB bounds, for low-cost collision between bats and walls
struct Bound
{
  static constexpr size_t ID{5};
  static constexpr mask_t MASK{1 << ID};

  // fields
  Vec2 min;
  Vec2 max;
};

// Collision occured
struct Contact
{
  static constexpr size_t ID{6};
  static constexpr mask_t MASK{1 << ID};

  // fields
  Vec2 normal;
  double penetration;
  size_t with;
};

#endif // COMPONENTS_H
