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

struct Body;
struct Position;
struct Input;
struct AI;
struct Movement;
struct Bound;

// Components collection (in correct order)
typedef std::tuple<Body, Position, Input, AI, Movement, Bound> components_t;

// Mask type and no component mask
typedef std::bitset<std::tuple_size_v<components_t>> mask_t;

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
    float radius;
  };

  struct Rectangle
  {
    float width;
    float height;
  };

  // fields
  std::variant<Circle, Rectangle> body;

  // constructors for confort
  Body(float radius = 0.f)
    : body{Circle{radius}}
  {}

  Body(float width, float height)
    : body{Rectangle{width, height}}
  {}
}; // struct Body

// Position XY (domain is [0;1])
struct Position
{
  static constexpr size_t ID{1};
  static constexpr mask_t MASK{1 << ID};

  // fields
  float x;
  float y;
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
  float dx;
  float dy;
};

// AABB bounds, for low-cost collision between bats and walls
struct Bound
{
  static constexpr size_t ID{5};
  static constexpr mask_t MASK{1 << ID};

  // fields
  float minx;
  float maxx;
  float miny;
  float maxy;
};

#endif // COMPONENTS_H
