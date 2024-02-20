#ifndef Game_Scratcher
#define Game_Scratcher
#include "point.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <set>
class Game {
private:
  sf::RenderWindow &window;
  std::set<Point> set; // ordered set
  int width;
  int height;

public:
  Game(sf::RenderWindow &window, int w, int h)
      : window(window), width(w), height(h) {}
  operator bool() { return window.isOpen(); }
  void clear() { window.clear(); }
  void event();
  void draw();
  void saveGame();
  void loadGame();
};

#endif