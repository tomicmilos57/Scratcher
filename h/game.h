#ifndef Game_Scratcher
#define Game_Scratcher
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include "shape.h"
#include <iostream>
#include <set>
#include <stack>
class Point;
class DrawableTransformable : public sf::Drawable, public sf::Transformable {};
class Game {
private:
  sf::RenderWindow &window;
  std::vector<sf::Shape *> arr;
  std::stack<sf::Shape  *> stack_undo;
  int width;
  int height;
  float zoom = 1;
  float xcenter;
  float ycenter;
  bool newstroke = true;
  Shape_Rect rect;
  Shape_Dot dot;
  Shape_Circle circle;
  Shape_Line line;
  Shape_Select select;
  Shape *shape = &dot;
  int color = 0;
  static sf::Color colors[];
  static Point prev;

public:
  Game(sf::RenderWindow &window, int w, int h);
  void event();
  void draw() const;


  void drawLine(int x, int y, int endx, int endy);
private:
  void saveGame() const;
  void loadGame();
  void incColor() { color < 6 ? color += 1 : color = 0; }
  void decColor() { color > 0 ? color -= 1 : color = 6; }
  void insert_pixel(Stroke *, const Point&);
  void fill_line(Stroke *, int, int, int, int);
  void clear_stack();
  void view_change();
  friend Shape_Rect;
  friend Shape_Dot;
  friend Shape_Circle;
  friend Shape_Line;
  friend Shape_Select;
  friend Stroke;
};

#endif
