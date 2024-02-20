#include <iostream>
// TODO Copy contructor sf::Vector2i --> Point i.e Point(sf::Vector2i)
struct Point {
  float x;
  float y;
  Point(float xx, float yy) : x(xx), y(yy) {}
  friend bool operator==(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
  }
  friend bool operator<(const Point &a, const Point &b) {
    return a.x < b.x ? true : a.x == b.x ? a.y < b.y : false;
  }
  friend std::ostream &operator<<(std::ostream &os, const Point &p) {
    return os << p.x << std::endl << p.y << std::endl;
  }

  friend void operator>>(std::istream &os, Point &p) {
    os >> p.x;
    os >> p.y;
  }
};