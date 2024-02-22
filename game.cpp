#include "game.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <fstream>
#include <iostream>
#include <math.h>
sf::Color Game::colors[] = {sf::Color::White,   sf::Color::Blue,
                            sf::Color::Cyan,    sf::Color::Green,
                            sf::Color::Magenta, sf::Color::Red,
                            sf::Color::Yellow}; //, sf::Color::Black
bool newstroke = true;
void Game::event() {
  sf::Event event;

  static Point prev(0, 0, 0, 0);
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      // this->saveGame();
      window.close();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2i position = sf::Mouse::getPosition(window);
      Point p(position.x, position.y, color);
      if (newstroke) { // this could be improved
        prev = p;
        newstroke = false;
      }
      insert_pixel(p);
      fill_line(p.x, p.y, prev.x, prev.y);
      prev = p;
    }
    if (event.type == sf::Event::MouseButtonReleased) {
      newstroke = true;
      layer++;
      event.type = sf::Event::Count; // Needed so ButtonReleased works correctly
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
      /*if (event.key.scancode == sf::Keyboard::Scan::Delete)
        color = 7; // Black SHOULD ACCTUALY REMOVE FROM SET*/
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
  savefile.close();
  return;
}
void Game::loadGame() {
  std::ifstream savefile("save.txt");
  while (!savefile.eof()) {     // getline(myfile,line)
    Point *p = new Point(0, 0); // memleak
    savefile >> *p;
    std::cout << "Loading " << p->x << ' ' << p->y << std::endl;
    set.insert(*p);
  }
  savefile.close();
  return;
} // insert_pixel(Point(x, y, color));
void Game::fill_line(int x1, int y1, int x2, int y2) {
  int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
  dx = x2 - x1;
  dy = y2 - y1;
  dx1 = fabs(dx);
  dy1 = fabs(dy);
  px = 2 * dy1 - dx1;
  py = 2 * dx1 - dy1;
  if (dy1 <= dx1) {
    if (dx >= 0) {
      x = x1;
      y = y1;
      xe = x2;
    } else {
      x = x2;
      y = y2;
      xe = x1;
    }
    insert_pixel(Point(x, y, color));
    for (i = 0; x < xe; i++) {
      x = x + 1;
      if (px < 0) {
        px = px + 2 * dy1;
      } else {
        if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
          y = y + 1;
        } else {
          y = y - 1;
        }
        px = px + 2 * (dy1 - dx1);
      }
      insert_pixel(Point(x, y, color));
    }
  } else {
    if (dy >= 0) {
      x = x1;
      y = y1;
      ye = y2;
    } else {
      x = x2;
      y = y2;
      ye = y1;
    }
    insert_pixel(Point(x, y, color));
    for (i = 0; y < ye; i++) {
      y = y + 1;
      if (py <= 0) {
        py = py + 2 * dx1;
      } else {
        if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
          x = x + 1;
        } else {
          x = x - 1;
        }
        py = py + 2 * (dx1 - dy1);
      }
      insert_pixel(Point(x, y, color));
    }
  }
}

void Game::insert_pixel(Point p) {
  if (p.x >= 0 && p.y >= 0 && p.x < width && p.y < height) {
    set.insert(p);
  }
}

/*sf::Vector2i position = sf::Mouse::getPosition(window);
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
}*/