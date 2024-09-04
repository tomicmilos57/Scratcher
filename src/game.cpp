#include "../h/game.h"
#include "../h/shape.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <math.h>
#include <sys/select.h>
sf::Color Game::colors[] = {
    sf::Color::White,   sf::Color::Blue, sf::Color::Cyan,  sf::Color::Green,
    sf::Color::Magenta, sf::Color::Red,  sf::Color::Yellow};
void Game::event() {
  sf::Event event;
  static Point prev(0, 0, 0);
  view_change(); // Without this line, mouse and view are not aligned in
                 // beginning
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      // this->saveGame();
      window.close();
    }
    if (event.type == sf::Event::Resized) {
      sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
      width = event.size.width;
      height = event.size.height;
      window.setView(sf::View(visibleArea));
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2i mousepos = sf::Mouse::getPosition(window);
      sf::Vector2f position = window.mapPixelToCoords(mousepos);
      Point p(position.x, position.y, color);
      shape->onClick(prev, p, newstroke);
    }
    if (event.type == sf::Event::MouseButtonReleased) {
      newstroke = true;
      shape->insert();
      event.type = sf::Event::Count; // Needed so ButtonReleased works correctly
    }
    if (event.type == sf::Event::MouseWheelMoved &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
      if (event.mouseWheel.delta < 0) {
        if (zoom < 2.5)
          zoom += 0.1;
        view_change();
      } else if (event.mouseWheel.delta > 0) {
        if (zoom > 0.2)
          zoom -= 0.1;
        view_change();
      }
    } else if (event.type == sf::Event::MouseWheelMoved &&
               sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
      if (event.mouseWheel.delta < 0) {
        xcenter += 50;
        view_change();
      } else if (event.mouseWheel.delta > 0) {
        xcenter -= 50;
        view_change();
      }
    } else if (event.type == sf::Event::MouseWheelMoved) {
      if (event.mouseWheel.delta < 0) {
        ycenter += 50;
        view_change();
      } else if (event.mouseWheel.delta > 0) {
        ycenter -= 50;
        view_change();
      }
    }
    if (event.key.scancode == sf::Keyboard::Scan::R &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
      xcenter = (float)width / 2;
      ycenter = (float)height / 2;
      zoom = 1;
      view_change();
    }
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.scancode == sf::Keyboard::Scan::D) {
        if (shape != &dot)
          newstroke = true;
        shape = &dot;
      }
      if (event.key.scancode == sf::Keyboard::Scan::R) {
        if (shape != &rect)
          newstroke = true;
        shape = &rect;
      }
      if (event.key.scancode == sf::Keyboard::Scan::C) {
        if (shape != &circle)
          newstroke = true;
        shape = &circle;
      }
      if (event.key.scancode == sf::Keyboard::Scan::L) {
        if (shape != &line)
          newstroke = true;
        shape = &line;
      }
      if (event.key.scancode == sf::Keyboard::Scan::S) {
        if (shape != &select)
          newstroke = true;
        shape = &select;
        static_cast<Shape_Select *>(shape)->clear();
      }
      if (event.key.scancode == sf::Keyboard::Scan::Up)
        incColor();
      if (event.key.scancode == sf::Keyboard::Scan::Down)
        decColor();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
          sf::Keyboard::isKeyPressed(sf::Keyboard::Z) &&
          sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        if (!stack_undo.empty()) {
          arr.push_back(stack_undo.top());
          stack_undo.pop();
        }
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
                 sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        if (!arr.empty()) {
          stack_undo.push(arr.back());
          arr.pop_back();
        }
      }
    }
  }
}

void Game::draw() const {
  sf::VertexArray va;
  for (auto &stroke : arr) {
    for (auto &point : stroke->arr) {
      va.append(
          sf::Vertex(sf::Vector2f(point.x, point.y), colors[point.color]));
    }
  }

  window.draw(va);

  // Drawing overlay
  shape->drawOverlay(newstroke);
  // Drawing cursor
  sf::Vector2i mousepos = sf::Mouse::getPosition(window);
  sf::Vector2f position = window.mapPixelToCoords(mousepos);
  sf::Vertex dot(sf::Vector2f(position.x, position.y), colors[color]);
  window.draw(&dot, 1, sf::Points);
}