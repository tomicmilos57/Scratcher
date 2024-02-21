#include "game.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <fstream>
#include <iostream>
sf::Color Game::colors[] = {
    sf::Color::White,   sf::Color::Blue, sf::Color::Cyan,  sf::Color::Green,
    sf::Color::Magenta, sf::Color::Red,  sf::Color::Yellow};

void Game::event() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      // this->saveGame();
      window.close();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2i position = sf::Mouse::getPosition(window);
      sf::CircleShape circle;
      circle.setPosition(position.x, position.y);
      circle.setRadius(radius);
      for (size_t i = 0; i < circle.getPointCount(); i++) {
        auto point = circle.getPoint(i);
        Point p(point.x + position.x - radius, point.y + position.y - radius,
                color);
        if (p.x >= 0 && p.y >= 0 && p.x < width && p.y < height) {
          set.insert(p);
          // std::cout << p.x << " " << p.y << std::endl;
        }
      }
    }
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.scancode == sf::Keyboard::Scan::PageUp)
        incRadius();
      if (event.key.scancode == sf::Keyboard::Scan::PageDown)
        decRadius();
      if (event.key.scancode == sf::Keyboard::Scan::Up)
        incColor();
      if (event.key.scancode == sf::Keyboard::Scan::Down)
        decColor();
    }
  }
}

void Game::draw() const {

  // Drwaing points
  for (auto &point : set) {
    sf::Vertex dot(sf::Vector2f(point.x, point.y), colors[point.color]);
    window.draw(&dot, 1, sf::Points);
  }
  // Drawing cursor
  sf::CircleShape cursor;
  cursor.setRadius(radius);
  cursor.setOrigin(radius, radius);
  cursor.setFillColor(colors[color]);
  sf::Vector2i position = sf::Mouse::getPosition(window);
  cursor.setPosition(position.x, position.y);
  window.draw(cursor);
}
void Game::saveGame() const {
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
