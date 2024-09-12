#include "../h/game.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include <iostream>
using namespace std;
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1024
#define FPS 60
#define DEBUGMODE 1
#define BENCHMARK 0
int main() {
  cout << "WSL~!" << endl;
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Scratcher");
  window.setMouseCursorVisible(false);
  window.setPosition(sf::Vector2i(100, 100));
  Game scratcher(window, WINDOW_WIDTH, WINDOW_HEIGHT);
  // scratcher.loadGame();
#if DEBUGMODE
  float fps;
  sf::Clock clock;
  sf::Time previousTime = clock.getElapsedTime();
  sf::Time currentTime;
#endif
#if BENCHMARK
  int counter = 0;
  int yrows = 1080;
  bool writeElapsedTimeOnce = false;
  sf::Clock totalTimeClock;
  sf::Time totalTimeBegin = totalTimeClock.getElapsedTime();
  sf::Time totalTimeElapsed;
#endif
  while (window.isOpen()) {
    // std::cout << "\b\b\b\b\b";
    window.clear();
    scratcher.event();
#if BENCHMARK
    if (counter < yrows) {
      scratcher.drawLine(0, counter, 1920, counter);
      counter++;
      totalTimeElapsed = totalTimeClock.getElapsedTime();
    } else if (!writeElapsedTimeOnce) {
      std::cout << "Benchmark time: "
                << (totalTimeElapsed.asSeconds() - totalTimeBegin.asSeconds())
                << std::endl;
      writeElapsedTimeOnce = true;
    }
#endif
    scratcher.draw();
#if DEBUGMODE
    currentTime = clock.getElapsedTime();
    fps = 1.0f / (currentTime.asSeconds() -
                  previousTime.asSeconds()); // the asSeconds returns a float
    scratcher.drawFPS(std::floor(fps));
    // std::string str = std::to_string(std::floor(fps));
    // std::cout
        // << str[0] << str[1] << str[2] << str[3]
        // << str[4]; // flooring it will make the frame rate a rounded number
    previousTime = currentTime;
#endif
    window.display();
  }

  // scratcher.saveGame();
  return 0;
}
