#include "game.h"
#include <fstream>
#include <iostream>

void Game::event() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      // this->saveGame();
      window.close();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // oneliner
      sf::Vector2i position = sf::Mouse::getPosition(window);
      Point p(position.x, position.y);
      if (p.x >= 0 && p.y >= 0 && p.x < width && p.y < height) {
        set.insert(p);
        std::cout << p.x << " " << p.y << std::endl;
      }
    }
  }
}

void Game::draw() {
  for (auto &point : set) {
    sf::Vertex dot(sf::Vector2f(point.x, point.y), sf::Color::White);
    window.draw(&dot, 1, sf::Points);
  }
  window.display();
}
void Game::saveGame() {
  std::cout << "Saving game" << std::endl;
  std::ofstream savefile("save.txt");
  for (auto &point : set) {
    std::cout << point.x << ' ' << point.y << std::endl;
    savefile << point;
  }
  return;
}
void Game::loadGame() {
  std::ifstream savefile("save.txt");
  while (!savefile.eof()) {
    Point *p = new Point(0, 0); // memleak
    savefile >> *p;
    std::cout << "Loading " << p->x << ' ' << p->y << std::endl;
    set.insert(*p);
  }
  return;
}