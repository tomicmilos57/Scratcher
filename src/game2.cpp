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
void Game::view_change() const {
  sf::View view = window.getDefaultView();
  view.setCenter(xcenter, ycenter);
  view.zoom(zoom);
  window.setView(view);
}
void Game::drawLine(int x, int y, int endx, int endy) {
  Point p1 = Point(x, y);
  Point p2 = Point(endx, endy);
  bool newstrk = true;
  line.onClick(p1, p2, newstrk);
  line.insert();
}
void Game::drawFPS(int fps) const {
  sf::Font font;
  sf::Vector2i mousepos = sf::Mouse::getPosition(window);
  sf::Vector2f position = window.mapPixelToCoords(mousepos);
  if (font.loadFromFile(
          "/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Medium.ttf")) {
    sf::View view = window.getDefaultView();
    window.setView(view);
    sf::Text coord;
    coord.setFont(font);
    coord.setString(std::to_string((int)position.x) + ", " +
                    std::to_string((int)position.y));
    coord.setCharacterSize(24);
    coord.setFillColor(colors[color]);
    sf::FloatRect pos = coord.getLocalBounds();
    /* coord.setPosition(
        (window.getSize().x + window.getPosition().x - pos.width) - 20,
        (window.getSize().y + window.getPosition().y - pos.height) - 40); */
    coord.setPosition(1920 - 20 - pos.width, 1024 - 20 - pos.height);
    window.draw(coord);
    sf::Text textfps;
    textfps.setFont(font);
    textfps.setString(std::to_string((int)fps));
    textfps.setCharacterSize(24);
    textfps.setFillColor(colors[color]);
    sf::FloatRect fpspos = textfps.getLocalBounds();
    textfps.setPosition((1920 - fpspos.width) - 20, 20);
    window.draw(textfps);

    view_change();
  } else {
    std::cout << "Error: Failed loading font from a file" << std::endl;
  }
}
