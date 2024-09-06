#ifndef Stroke_h
#define Stroke_h
#include "game.h"
#include "point.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
class Stroke : public sf::Drawable {
public:
  std::vector<Point> arr;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    for (int i = 0; i < arr.size() - 1; i++) {
      sf::VertexArray line_overlay(sf::LineStrip, 2);
      line_overlay[0].position = sf::Vector2f(arr[i].x, arr[i].y);
      line_overlay[0].color = Game::colors[arr[i].color];
      line_overlay[1].position = sf::Vector2f(arr[i + 1].x, arr[i + 1].y);
      line_overlay[1].color = Game::colors[arr[i].color];
      target.draw(line_overlay, states);
    }
  }
  ~Stroke(){}
  void addPoint(const Point &p) { arr.push_back(p); }
};

#endif
