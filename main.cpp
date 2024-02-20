#include "game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
using namespace std;
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 60

int main() {
  cout << "WSL~!" << endl;
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Scratcher");
  Game scratcher(window, WINDOW_WIDTH, WINDOW_HEIGHT);
  // scratcher.loadGame();
  while (window.isOpen()) {
    window.clear();
    scratcher.event();
    scratcher.draw();
    window.display();
  }
  scratcher.saveGame();
  return 0;
}
