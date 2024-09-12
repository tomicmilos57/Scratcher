#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <cmath>

class sfLine : public sf::Shape {
public:
  float thickness;
  sf::Color color;
  sfLine(const sf::Vector2f &point1) : point1(point1) {}
  void secondPoint(const sf::Vector2f &point2) {
    sf::Vector2f direction = point2 - point1;
    sf::Vector2f unitDirection =
        direction /
        std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

    sf::Vector2f offset = (thickness / 2.f) * unitPerpendicular;

    vertices[0].position = point1 + offset;
    vertices[1].position = point2 + offset;
    vertices[2].position = point2 - offset;
    vertices[3].position = point1 - offset;

    for (int i = 0; i < 4; ++i)
      vertices[i].color = color;
  }
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    states.transform *= getTransform();
    target.draw(vertices, 4, sf::Quads, states);
  }
  sf::Vector2f getPoint(std::size_t index) const override {
    return sf::Vector2f(vertices[index].position.x, vertices[index].position.y);
  }
  std::size_t getPointCount() const override { return 4; }

private:
  sf::Vertex vertices[4];
  sf::Vector2f point1;
};
