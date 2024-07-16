#include "../h/game.h"
#include "../h/shape.h"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cmath>
#include <sys/select.h>

void Shape_Rect::onClick(Point& prev, Point& p, bool &newstroke){
    if (newstroke) {
        game->clear_stack();
        prev = p;
        newstroke = false;
    }
    rect_overlay->setSize(sf::Vector2f(p.x - prev.x, p.y - prev.y));
    rect_overlay->setPosition(prev.x,prev.y);
    rect_overlay->setOutlineColor(Game::colors[game->color]);
}
void Shape_Rect::drawOverlay(bool newstroke) const{
    if(!newstroke)game->window.draw(*rect_overlay);
}
void Shape_Rect::insert(){
    Stroke *stroke = new Stroke;
    game->arr.push_back(stroke);
    float x1 = rect_overlay->getPosition().x;
    float y1 = rect_overlay->getPosition().y;
    float width = rect_overlay->getSize().x;
    float height = rect_overlay->getSize().y;
    game->fill_line(stroke, x1,y1,x1+width,y1);
    game->fill_line(stroke, x1+width,y1,x1+width,y1+height);
    game->fill_line(stroke, x1+width,y1+height,x1,y1+height);
    game->fill_line(stroke, x1,y1+height,x1,y1);
}
void Shape_Dot::onClick(Point& prev, Point& p, bool &newstroke){
    static Stroke *stroke = new Stroke;
    if (newstroke) { // this could be improved
        game->clear_stack();
        prev = p;
        newstroke = false;
        stroke = new Stroke();
        game->arr.push_back(stroke);
    }
    game->fill_line(stroke, p.x, p.y, prev.x, prev.y);
    prev = p;
}
void Shape_Dot::drawOverlay(bool)const{}
void Shape_Dot::insert(){}
void Shape_Circle::onClick(Point& prev, Point& p, bool &newstroke){
    if (newstroke) {
        game->clear_stack();
        prev = p;
        newstroke = false;
    }
    float radius = sqrt((prev.x - p.x)*(prev.x - p.x) + (prev.y - p.y)*(prev.y - p.y));
    circle_overlay->setRadius(radius);//sf::Vector2f(p.x - prev.x, p.y - prev.y));
    circle_overlay->setPosition(prev.x - radius,prev.y - radius);
    circle_overlay->setOutlineColor(Game::colors[game->color]);
}
void Shape_Circle::drawOverlay(bool newstroke) const{
    if(!newstroke)game->window.draw(*circle_overlay);
}void Shape_Circle::insert(){
    Stroke *stroke = new Stroke;
    game->arr.push_back(stroke);
    float x1 = circle_overlay->getPosition().x;
    float y1 = circle_overlay->getPosition().y;
    float radius = circle_overlay->getRadius();
    drawCircle(stroke, x1+radius, y1+radius, radius);
}
void Shape_Circle::drawCircle(Stroke* stroke, int x, int y, int rad){
    float dp;       //initialising the descision parameter.
    int x1,y1;
    x1 = 0;            //initialisng the X,Y cordinates.
    y1 = rad;
    dp = 3 - 2*rad;
    while(x1<=y1)
    {
        if(dp<=0)
            dp += (4 * x1) + 6;
        else
        {
            dp += 4*(x1-y1)+10;
            y1--;
        }
        x1++;
        drawEightPoints(stroke, x,y,x1,y1);
    }  
}
void Shape_Circle::drawEightPoints(Stroke* stroke, int xc, int yc, int x, int y){
    stroke->addPoint(Point(x+xc, y+yc, game->color));
    stroke->addPoint(Point(x+xc, -y+yc, game->color));
    stroke->addPoint(Point(-x+xc, -y+yc, game->color));
    stroke->addPoint(Point(-x+xc, y+yc, game->color));

    stroke->addPoint(Point(y+xc, x+yc, game->color));
    stroke->addPoint(Point(y+xc, -x+yc, game->color));
    stroke->addPoint(Point(-y+xc, -x+yc, game->color));
    stroke->addPoint(Point(-y+xc, x+yc, game->color));
}
void Shape_Line::onClick(Point& prev, Point& p, bool &newstroke){
    if (newstroke) {
        game->clear_stack();
        prev = p;
        newstroke = false;
    }
    line_overlay[0].position = sf::Vector2f(prev.x, prev.y);
    line_overlay[0].color  = Game::colors[game->color];
    line_overlay[1].position = sf::Vector2f(p.x, p.y);
    line_overlay[1].color = Game::colors[game->color];
}
void Shape_Line::drawOverlay(bool newstroke) const{
    if(!newstroke)game->window.draw(line_overlay, 2, sf::Lines);
}
void Shape_Line::insert(){
	Stroke *stroke = new Stroke;
	game->arr.push_back(stroke);
	game->fill_line(stroke, line_overlay[0].position.x, line_overlay[0].position.y,
			line_overlay[1].position.x, line_overlay[1].position.y);
}
void Shape_Select::onClick(Point& prev, Point& p, bool &newstroke){
	if(!phase2){
		if (newstroke) {
			game->clear_stack();
			prev = p;
			newstroke = false;
		}
		select_overlay->setSize(sf::Vector2f(p.x - prev.x, p.y - prev.y));
		select_overlay->setPosition(prev.x,prev.y);
	}
	else{
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
			if(!(p.x >= beginx 
						&& p.x <= endx
						&& p.y >= beginy
						&& p.y <= endy)){
				phase2 = false;
				clear();
			}
			prev = p;
		}else{
			auto dx = p.x - prev.x;
			auto dy = p.y - prev.y;
			prev = p;
			auto oldPos = select_overlay->getPosition();
			select_overlay->setPosition(oldPos.x + dx, oldPos.y + dy);
			for(Stroke* stroke : container){
				for(Point& p : stroke->arr){
					p.x += dx;
					p.y += dy;
				}
			}
		}
	}
}
void Shape_Select::drawOverlay(bool newstroke) const{
	game->window.draw(*select_overlay);
}
void Shape_Select::insert(){
	if(!phase2){
		for(auto stroke : game->arr){
			if(stroke_inside_select(stroke)){
				//std::cout << "Match" << std::endl;
				container.insert(stroke);
				phase2 = true;
			}else{
				//std::cout << "Not_match" << std::endl;
			}
		}
		if(!phase2) clear();
	}else{
		//implement undo for select_mode
	}
}
bool Shape_Select::stroke_inside_select(Stroke* stroke){
	//std::cout << "Xbegin: "<< select_overlay->getPosition().x << " Xend: " << select_overlay->getPosition().x + select_overlay->getSize().x
	//	<< " Ybegin: " << select_overlay->getPosition().y << " Yend: " << select_overlay->getPosition().y + select_overlay->getSize().y << std::endl;
	auto startx = select_overlay->getPosition().x;
	auto starty = select_overlay->getPosition().y;
	auto width = startx + select_overlay->getSize().x;
	auto height = starty + select_overlay->getSize().y;
	auto beginx = std::min(startx, width);
	auto endx = std::max(startx, width);
	auto beginy = std::min(starty, height);
	auto endy = std::max(starty, height);
	for(auto& p : stroke->arr){
		if(!(p.x >= beginx 
					&& p.x <= endx
					&& p.y >= beginy
					&& p.y <= endy)){
			return false;
		}
	}
	return true;
}
void Shape_Select::clear(){
	select_overlay->setPosition(sf::Vector2f(0,0));
	select_overlay->setSize(sf::Vector2f(0,0));
	phase2 = false;
	container.clear();
}
