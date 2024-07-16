#include <iostream>
// TODO Copy contructor sf::Vector2i --> Point i.e Point(sf::Vector2i)
struct Point {
  float x;
  float y;
  int color;
  int layer = 0;
  Point(float xx, float yy, int color = 0, int layer = 0)
      : x(xx), y(yy), color(color), layer(layer) {}
  friend bool operator==(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
  }
  friend bool operator<(const Point &a, const Point &b) {
    return a.x < b.x ? true : a.x == b.x ? a.y < b.y : false;
  }
  friend std::ostream &operator<<(std::ostream &os, const Point &p) {
    return os << p.x << std::endl << p.y << std::endl;
  }
  /*void operator=(Point &b) {
    this->x = b.x;
    this->y = b.y;
    this->color = b.color;
    this->layer = b.layer;
  }*/
  friend void operator>>(std::istream &os, Point &p) {
    os >> p.x;
    os >> p.y;
  }
};