#ifndef Stroke_h
#define Stroke_h
#include "game.h"
#include "point.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
#include <cmath>
#include <math.h>
#define PARAM 100
class Stroke : public sf::Shape {
public:
  std::vector<Point> arr;
  Point firstPoint;
  Point prev;
  sf::RenderTexture texture;
  sf::Color color;
  int radius;
  int left = 0, right = 0, up = 0, down = 0;
  Stroke(Point p, int r, sf::Color color) : prev(p), radius(r/2), color(color){
    firstPoint = p;
    left = p.x - PARAM*radius;
    right = p.x + PARAM*radius;
    up = p.y - PARAM*radius;
    down = p.y + PARAM*radius;
    texture.create(right - left, down - up);
  }
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    states.transform *= getTransform();
    sf::Sprite sprite(texture.getTexture());
    sprite.setPosition(this->getPosition().x + left, this->getPosition().y + up);
    target.draw(sprite);
  }
  sf::Vector2f getPoint(std::size_t index) const override {
    //return {0,0};
    return sf::Vector2f(arr[index].x, arr[index].y);
  }
  std::size_t getPointCount() const override { /*return 0;*/ return arr.size(); }
  ~Stroke() {}
  void addPoint(const Point &p) {
    bool changed = false;
    if(p.x - radius < left){ left = p.x - PARAM*radius; changed = true;}
    if(p.x + radius > right){ right = p.x + PARAM*radius; changed = true;}
    if(p.y - radius < up){ up = p.y - PARAM*radius; changed = true;}
    if(p.y + radius > down){ down = p.y + PARAM*radius; changed = true;}


    if(changed){
      arr.push_back(p);
      texture.create(right - left, down - up);
      for (size_t i = 1; i < arr.size(); i++) {
        this->drawline(arr[i - 1].x - left, down - arr[i - 1].y, arr[i].x - left, down - arr[i].y);
      }
    }
    else{
        if(arr.size() > 0)this->drawline(arr.back().x - left, down - arr.back().y, p.x - left, down - p.y);
        arr.push_back(p);
    }
    //if(!firstPoint)drawline(prev.x, prev.y, p.x, p.y);
    prev = p;
    //firstPoint = true;
    update();
  }

private:
  inline void drawCircle(int x, int y){
    static sf::CircleShape circle;
    circle.setFillColor(color);
    circle.setOutlineThickness(1);
    circle.setRadius(radius); // sf::Vector2f(p.x - prev.x, p.y - prev.y));
    circle.setPosition(x - radius, y - radius);
    circle.setOutlineColor(color);
    //target.draw(circle);  
    texture.draw(circle);
  }
  void drawline(int x1, int y1, int x2, int y2){
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
      drawCircle(x, y);
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
        drawCircle(x, y);
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
      drawCircle(x, y);
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
        drawCircle(x, y);
      }
    }
  }  
};

#endif
