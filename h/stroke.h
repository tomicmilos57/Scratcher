#ifndef Stroke_h
#define Stroke_h
#include "game.h"
#include "point.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
#include <cmath>
#include <math.h>
class Stroke : public sf::Shape {
public:
  std::vector<Point> arr;
  sf::Color color;
  int radius;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    states.transform *= getTransform();
    for (size_t i = 1; i < arr.size(); i++) {
      this->drawline(arr[i - 1].x, arr[i - 1].y, arr[i].x, arr[i].y, target);
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
private:
  void drawCircle(int x, int y, sf::RenderTarget& target) const{
    sf::CircleShape circle;
    circle.setFillColor(sf::Color(0, 0, 0, 0));
    circle.setOutlineThickness(5);
    circle.setRadius(radius); // sf::Vector2f(p.x - prev.x, p.y - prev.y));
    circle.setPosition(x - radius, y - radius);
    circle.setOutlineColor(color);
    target.draw(circle);  
  }
  void drawline(int x1, int y1, int x2, int y2, sf::RenderTarget &target) const{
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = x2 - x1;
    dy = y2 - y1;
    dx1 = fabs(dx);
    dy1 = fabs(dy);
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;
    if (dy1 <= dx1) {
      if (dx >= 0) {
        x = x1;
        y = y1;
        xe = x2;
      } else {
        x = x2;
        y = y2;
        xe = x1;
      }
      drawCircle(x, y, target);
      for (i = 0; x < xe; i++) {
        x = x + 1;
        if (px < 0) {
          px = px + 2 * dy1;
        } else {
          if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
            y = y + 1;
          } else {
            y = y - 1;
          }
          px = px + 2 * (dy1 - dx1);
        }
        drawCircle(x, y, target);
      }
    } else {
      if (dy >= 0) {
        x = x1;
        y = y1;
        ye = y2;
      } else {
        x = x2;
        y = y2;
        ye = y1;
      }
      drawCircle(x, y, target);
      for (i = 0; y < ye; i++) {
        y = y + 1;
        if (py <= 0) {
          py = py + 2 * dx1;
        } else {
          if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
            x = x + 1;
          } else {
            x = x - 1;
          }
          py = py + 2 * (dx1 - dy1);
        }
        drawCircle(x, y, target);
      }
    }
  }  
};

#endif
