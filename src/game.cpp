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
sf::Color Game::colors[] = {sf::Color::White,   sf::Color::Blue,
    sf::Color::Cyan,    sf::Color::Green,
    sf::Color::Magenta, sf::Color::Red,
    sf::Color::Yellow};
bool newstroke = true;
void Game::event() {
    sf::Event event;
    static Point prev(0, 0, 0, 0);
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            // this->saveGame();
            window.close();
        }
        if(event.type == sf::Event::Resized){
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            width = event.size.width;
            height = event.size.height;
            window.setView(sf::View(visibleArea));
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            Point p(position.x, position.y, color);
            shape->onClick(prev, p, newstroke);
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            newstroke = true;
            shape->insert();
            event.type = sf::Event::Count; // Needed so ButtonReleased works correctly
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.scancode == sf::Keyboard::Scan::D){
                if(shape != &dot) newstroke = true;
                shape = &dot; }
            if (event.key.scancode == sf::Keyboard::Scan::R){
                if(shape != &rect) newstroke = true;
                shape = &rect;}
            if (event.key.scancode == sf::Keyboard::Scan::C){
                if(shape != &circle) newstroke = true;
                shape = &circle;}
            if (event.key.scancode == sf::Keyboard::Scan::L){
                if(shape != &line) newstroke = true;
                shape = &line;}
            if (event.key.scancode == sf::Keyboard::Scan::S){
                if(shape != &select) newstroke = true;
                shape = &select;static_cast<Shape_Select*>(shape)->clear();}
            if (event.key.scancode == sf::Keyboard::Scan::Up)
                incColor();
            if (event.key.scancode == sf::Keyboard::Scan::Down)
                decColor();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                    && sf::Keyboard::isKeyPressed(sf::Keyboard::Z)
                    &&  sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
                if(!stack_undo.empty()){ 
                    arr.push_back(stack_undo.top());
                    stack_undo.pop();
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                    && sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                if(!arr.empty()){
                    stack_undo.push(arr.back());
                    arr.pop_back();
                }
            }
        }
    }
}

void Game::draw() const {
    // Drwaing points
    /*for (auto &stroke : arr){
        for (auto &point : stroke->arr) {
            sf::Vertex dot(sf::Vector2f(point.x, point.y), colors[point.color]);
            window.draw(&dot, 1, sf::Points);
        }
		}*/
	sf::VertexArray va;
	
	for (auto &stroke : arr){
		for (auto &point : stroke->arr) {
			va.append(sf::Vertex(sf::Vector2f(point.x, point.y), colors[point.color]));
		}
	}

			window.draw(va);



		// Drawing overlay
		shape->drawOverlay(newstroke);
		// Drawing cursor
		sf::Vector2i position = sf::Mouse::getPosition(window);
		sf::Vertex dot(sf::Vector2f(position.x, position.y), colors[color]);
		window.draw(&dot, 1, sf::Points);
	}
	/*void Game::saveGame() const {
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
	  } // insert_pixel(Point(x, y, color));*/
	void Game::insert_pixel(Stroke *stroke, Point p) {
		if (p.x >= 0 && p.y >= 0 && p.x < width && p.y < height) {
			stroke->addPoint(p);
		}
	}
	void Game::clear_stack(){
		while(!stack_undo.empty()){
			delete stack_undo.top();
			stack_undo.pop();
		}
	}
	void Game::fill_line(Stroke* stroke, int x1, int y1, int x2, int y2) {
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
