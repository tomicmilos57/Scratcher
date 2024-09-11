#include "../h/game.h"
#include "../h/stroke.h"
#include <SFML/System/Vector2.hpp>
Game::Game(sf::RenderWindow &window, int w, int h)
    : window(window), width(w), height(h), rect(this), dot(this), circle(this),
      line(this), select(this) {
  xcenter = (float)w / 2;
  ycenter = (float)h / 2;
  view_change();
}
void Game::insert_pixel(Stroke *stroke, const Point &p) { stroke->addPoint(p); }
void Game::clear_stack() {
  while (!stack_undo.empty()) {
    delete stack_undo.top();
    stack_undo.pop();
  }
}
void Game::view_change() {
  sf::View view = window.getDefaultView();
  view.setCenter(xcenter, ycenter);
  view.zoom(zoom);
  window.setView(view);
}
