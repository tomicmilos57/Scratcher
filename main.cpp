#include "game.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
using namespace std;
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1024
#define FPS 60

int main() {
  cout << "WSL~!" << endl;
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Scratcher");
  window.setPosition(sf::Vector2i(100, 100));
  Game scratcher(window, WINDOW_WIDTH, WINDOW_HEIGHT);
  // scratcher.loadGame();
  while (window.isOpen()) {
    window.clear();
    scratcher.event();
    scratcher.draw();
    window.display();
  }
  // scratcher.saveGame();
  return 0;
}
