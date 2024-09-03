#include "../h/game.h"
Game::Game(sf::RenderWindow &window, int w, int h)
    : window(window), width(w), height(h), rect(this), dot(this), circle(this),
      line(this), select(this) {
  xcenter = (float)w / 2;
  ycenter = (float)h / 2;
  view_change();
}
void Game::insert_pixel(Stroke *stroke, const Point &p) {
  stroke->addPoint(p);
}
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
  std::cout << "zoom: " << zoom << std::endl;
}
#include <math.h>
void Game::fill_line(Stroke *stroke, int x1, int y1, int x2, int y2) {
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
    insert_pixel(stroke, Point(x, y, color));
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
      insert_pixel(stroke, Point(x, y, color));
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
    insert_pixel(stroke, Point(x, y, color));
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
      insert_pixel(stroke, Point(x, y, color));
    }
  }
}
