#ifndef shape_h
#define shape_h
// #include "point.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <set>
#include "line.h"
#include "point.h"
class Game;
class Stroke;
class Shape { // Abstract class
protected:
  Game *game;
  Shape(Game *g) : game(g) {}

public:
  virtual void onClick(Point &prev, Point &p, bool &newstroke) {}
  virtual void drawOverlay(bool) const {}
  virtual void insert() {}
};
class Shape_Dot : public Shape {
public:
  Shape_Dot(Game *g) : Shape(g) {}
  void onClick(Point &prev, Point &p, bool &newstroke);
  void drawOverlay(bool) const;
  void insert();
};

class Shape_Rect : public Shape {
private:
  sf::RectangleShape *rect_overlay;

public:
  Shape_Rect(Game *g) : Shape(g) {}
  void onClick(Point &prev, Point &p, bool &newstroke);
  void drawOverlay(bool) const;
  void insert();
  // Destructor
};
class Shape_Circle : public Shape {
private:
  sf::CircleShape *circle_overlay;

public:
  Shape_Circle(Game *g) : Shape(g) {
    circle_overlay = new sf::CircleShape();
    circle_overlay->setFillColor(sf::Color(0, 0, 0, 0));
    circle_overlay->setOutlineThickness(1);
  }
  void onClick(Point &prev, Point &p, bool &newstroke);
  void drawOverlay(bool) const;
  void insert();
};
class Shape_Line : public Shape {
private:
  sfLine *line;
public:
  Shape_Line(Game *g) : Shape(g) {}
  void onClick(Point &prev, Point &p, bool &newstroke);
  void drawOverlay(bool) const;
  void insert();
};
class Shape_Select : public Shape {
private:
  sf::RectangleShape *select_overlay;
  std::set<sf::Shape *> container;
  bool phase2 = false;

public:
  Shape_Select(Game *g) : Shape(g) {
    select_overlay = new sf::RectangleShape();
    select_overlay->setFillColor(sf::Color(75, 255, 255, 128));
    // select_overlay->setOutlineColor(sf::Color(0,0,128,128));
    // select_overlay->setOutlineThickness(1);
  }
  void onClick(Point &prev, Point &p, bool &newstroke);
  void drawOverlay(bool) const;
  void insert();
  void clear();

private:
  bool stroke_inside_select(sf::Shape *);
};
#endif
