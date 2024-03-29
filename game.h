#ifndef Game_Scratcher
#define Game_Scratcher
#include "point.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <set>
class Game {
private:
  sf::RenderWindow &window;
  std::set<Point> set;
  int width;
  int height;
  int radius = 1;
  int color = 0;
  int layer = 1;
  static sf::Color colors[];

public:
  Game(sf::RenderWindow &window, int w, int h)
      : window(window), width(w), height(h) {}
  void event();
  void draw() const;
  void saveGame() const;
  void loadGame();
  void incRadius() { radius < 20 ? radius += 1 : 20; }
  void decRadius() { radius > 1 ? radius -= 1 : 1; }
  void incColor() { color < 6 ? color += 1 : color = 0; }
  void decColor() { color > 0 ? color -= 1 : color = 6; }

private:
  void insert_pixel(Point);
  void fill_line(int, int, int, int);
};

#endif