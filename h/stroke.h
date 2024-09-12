#ifndef Stroke_h
#define Stroke_h
#include "game.h"
#include "point.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
#include <cmath>
class Stroke : public sf::Shape {
public:
  std::vector<Point> arr;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
      states.transform *= getTransform();
    for (size_t i = 0; i < arr.size() - 1; i++) {
      sf::Vector2f point1 = {arr[i].x, arr[i].y};
      sf::Vector2f point2 = {arr[i+1].x, arr[i+1].y};
      sf::Vertex vertices[4];
      sf::Vector2f direction = point2 - point1;
      sf::Vector2f unitDirection = direction/std::sqrt(direction.x*direction.x+direction.y*direction.y);
      sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

      sf::Vector2f offset = (10/2.f)*unitPerpendicular;

      vertices[0].position = point1 + offset;
      vertices[1].position = point2 + offset;
      vertices[2].position = point2 - offset;
      vertices[3].position = point1 - offset;;
      target.draw(vertices, 4, sf::Quads, states);
    }
  }
  sf::Vector2f getPoint(std::size_t index) const override {
    return sf::Vector2f(arr[index].x, arr[index].y);
  }
  std::size_t getPointCount() const override { return arr.size(); }
  ~Stroke() {}
  void addPoint(const Point &p) {
    arr.push_back(p);
    update();
  }
};

#endif
