#ifndef Stroke_h
#define Stroke_h
#include "game.h"
#include "point.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
class Stroke : public sf::Shape {
public:
  std::vector<Point> arr;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
      states.transform *= getTransform();
    for (int i = 0; i < arr.size() - 1; i++) {
      sf::VertexArray line_overlay(sf::LineStrip, 2);
      line_overlay[0].position = sf::Vector2f(arr[i].x, arr[i].y);
      line_overlay[0].color = Game::colors[arr[i].color];
      line_overlay[1].position = sf::Vector2f(arr[i + 1].x, arr[i + 1].y);
      line_overlay[1].color = Game::colors[arr[i].color];
      target.draw(line_overlay, states);
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
