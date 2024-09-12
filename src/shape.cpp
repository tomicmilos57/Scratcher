#include "../h/shape.h"
#include "../h/game.h"
#include "../h/stroke.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

void Shape_Rect::onClick(Point &prev, Point &p, bool &newstroke) {
  if (newstroke) {
    game->clear_stack();
    prev = p;
    newstroke = false;
  }
  rect_overlay = new sf::RectangleShape();
  rect_overlay->setFillColor(sf::Color(0, 0, 0, 0));
  rect_overlay->setOutlineThickness(1);
  rect_overlay->setSize(sf::Vector2f(p.x - prev.x, p.y - prev.y));
  rect_overlay->setPosition(prev.x, prev.y);
  rect_overlay->setOutlineColor(Game::colors[game->color]);
}
void Shape_Rect::drawOverlay(bool newstroke) const {
  if (!newstroke)
    game->window.draw(*rect_overlay);
}
void Shape_Rect::insert() { game->arr.push_back(rect_overlay); }
void Shape_Dot::onClick(Point &prev, Point &p, bool &newstroke) {
  static Stroke *stroke = new Stroke;
  if (newstroke) { // this could be improved
    game->clear_stack();
    prev = p;
    newstroke = false;
    stroke = new Stroke();
    game->arr.push_back(stroke);
  }
  // game->fill_line(stroke, p.x, p.y, prev.x, prev.y);
  stroke->addPoint(p);
  prev = p;
}
void Shape_Dot::drawOverlay(bool) const {}
void Shape_Dot::insert() {}
void Shape_Circle::onClick(Point &prev, Point &p, bool &newstroke) {
  if (newstroke) {
    game->clear_stack();
    prev = p;
    newstroke = false;
  }
  float radius =
      sqrt((prev.x - p.x) * (prev.x - p.x) + (prev.y - p.y) * (prev.y - p.y));
  circle_overlay = new sf::CircleShape();
  circle_overlay->setFillColor(sf::Color(0, 0, 0, 0));
  circle_overlay->setOutlineThickness(1);
  circle_overlay->setRadius(
      radius); // sf::Vector2f(p.x - prev.x, p.y - prev.y));
  circle_overlay->setPosition(prev.x - radius, prev.y - radius);
  circle_overlay->setOutlineColor(Game::colors[game->color]);
}
void Shape_Circle::drawOverlay(bool newstroke) const {
  if (!newstroke)
    game->window.draw(*circle_overlay);
}
void Shape_Circle::insert() { game->arr.push_back(circle_overlay); }

void Shape_Line::onClick(Point &prev, Point &p, bool &newstroke) {
  if (newstroke) {
    game->clear_stack();
    prev = p;
    newstroke = false;
  }
  line_overlay[0].position = sf::Vector2f(prev.x, prev.y);
  line_overlay[0].color = Game::colors[game->color];
  line_overlay[1].position = sf::Vector2f(p.x, p.y);
  line_overlay[1].color = Game::colors[game->color];
  this->color = game->color;
}
void Shape_Line::drawOverlay(bool newstroke) const {
  if (!newstroke)
    game->window.draw(line_overlay, 2, sf::Lines);
}
void Shape_Line::insert() {
  Stroke *stroke = new Stroke;
  Point p1(line_overlay[0].position.x, line_overlay[0].position.y, color);
  Point p2(line_overlay[1].position.x, line_overlay[1].position.y, color);
  stroke->addPoint(p1);
  stroke->addPoint(p2);
  game->arr.push_back(stroke);
}
void Shape_Select::onClick(Point &prev, Point &p, bool &newstroke) {
  if (!phase2) {
    if (newstroke) {
      game->clear_stack();
      prev = p;
      newstroke = false;
    }
    select_overlay->setSize(sf::Vector2f(p.x - prev.x, p.y - prev.y));
    select_overlay->setPosition(prev.x, prev.y);
  } else {
    if (newstroke) {
      newstroke = false;
      auto startx = select_overlay->getPosition().x;
      auto starty = select_overlay->getPosition().y;
      auto width = startx + select_overlay->getSize().x;
      auto height = starty + select_overlay->getSize().y;
      auto beginx = std::min(startx, width);
      auto endx = std::max(startx, width);
      auto beginy = std::min(starty, height);
      auto endy = std::max(starty, height);
      if (!(p.x >= beginx && p.x <= endx && p.y >= beginy && p.y <= endy)) {
        phase2 = false;
        clear();
      }
      prev = p;
    } else {
      auto dx = p.x - prev.x;
      auto dy = p.y - prev.y;
      prev = p;
      auto oldPos = select_overlay->getPosition();
      select_overlay->setPosition(oldPos.x + dx, oldPos.y + dy);
      for (sf::Shape *elem : container) {
        elem->move(dx, dy);
      }
    }
  }
}
void Shape_Select::drawOverlay(bool newstroke) const {
  game->window.draw(*select_overlay);
}
void Shape_Select::insert() {
  if (!phase2) {
    for (auto &stroke : game->arr) {
      if (stroke_inside_select(stroke)) {
        // std::cout << "Match" << std::endl;
        container.insert(stroke);
        phase2 = true;
      } else {
        // std::cout << "Not_match" << std::endl;
      }
    }
    if (!phase2)
      clear();
  } else {
    // implement undo for select_mode
  }
}
bool Shape_Select::stroke_inside_select(sf::Shape *elem) {
  // std::cout << "Xbegin: "<< select_overlay->getPosition().x << " Xend: " <<
  // select_overlay->getPosition().x + select_overlay->getSize().x
  //	<< " Ybegin: " << select_overlay->getPosition().y << " Yend: " <<
  // select_overlay->getPosition().y + select_overlay->getSize().y << std::endl;
  auto startx = select_overlay->getPosition().x;
  auto starty = select_overlay->getPosition().y;
  auto width = startx + select_overlay->getSize().x;
  auto height = starty + select_overlay->getSize().y;
  auto beginx = std::min(startx, width);
  auto endx = std::max(startx, width);
  auto beginy = std::min(starty, height);
  auto endy = std::max(starty, height);
  int startposx = elem->getPosition().x;
  int startposy = elem->getPosition().y;
  for (size_t i = 0; i < elem->getPointCount(); i++) {
    if (!(startposx + elem->getPoint(i).x >= beginx &&
          startposx + elem->getPoint(i).x <= endx &&
          startposy + elem->getPoint(i).y >= beginy &&
          startposy + elem->getPoint(i).y <= endy)) {
      return false;
    }
  }
  return true;
}
void Shape_Select::clear() {
  select_overlay->setPosition(sf::Vector2f(0, 0));
  select_overlay->setSize(sf::Vector2f(0, 0));
  phase2 = false;
  container.clear();
}
