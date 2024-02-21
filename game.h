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
  int radius = 10;

public:
  Game(sf::RenderWindow &window, int w, int h)
      : window(window), width(w), height(h) {}
  operator bool() { return window.isOpen(); } // excess
  void clear() const { window.clear(); }
  void event();
  void draw() const;
  void saveGame() const;
  void loadGame();
  void incRadius() { radius < 20 ? radius += 1 : 20; }
  void decRadius() { radius > 1 ? radius -= 1 : 1; }
};

#endif