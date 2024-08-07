#include "../h/game.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include <iostream>
#include <string>
using namespace std;
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1024
#define FPS 60
#define DEBUGMODE
int main() {
  cout << "WSL~!" << endl;
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Scratcher");
  window.setPosition(sf::Vector2i(100, 100));
  Game scratcher(window, WINDOW_WIDTH, WINDOW_HEIGHT);
  // scratcher.loadGame();
#ifdef DEBUGMODE
  float fps;
  sf::Clock clock;
  sf::Time previousTime = clock.getElapsedTime();
  sf::Time currentTime;
#endif
  while (window.isOpen()) {
	  std::cout << "\b\b\b\b\b";
	  window.clear();
	  scratcher.event();
	  scratcher.draw();
	  window.display();
#ifdef DEBUGMODE
	  currentTime = clock.getElapsedTime();
	  fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
	  std::string str = std::to_string(std::floor(fps));
	  std::cout << str[0] << str[1] << str[2] << str[3] << str[4]; // flooring it will make the frame rate a rounded number
	  previousTime = currentTime;
#endif
  }
  // scratcher.saveGame();
  return 0;
}
