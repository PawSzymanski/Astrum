#include "render_system.h"



render_system::render_system(sf::RenderWindow &window) : win(window)
{

}

void render_system::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	Position::Handle pos;
	Circle::Handle circ;
	Line::Handle line;
	Transform::Handle trans;
	VertexArray::Handle vArray;
	Joint::Handle joint;

	//win.clear(sf::Color::Blue);
	//std::cout << "render gameplpay, entity size: " << en.size() << std::endl;
	for (auto entity : en.entities_with_components(vArray, trans))
	{
		win.draw(vArray->vert, trans->trans);
		//std::cout << "array disp  "<< vArray->vert.getVertexCount();
	}
	for (auto entity : en.entities_with_components(circ, pos, line, trans))
	{
		sf::CircleShape c_shape;
		c_shape.setFillColor(circ->color);
		c_shape.setPosition(pos->pos);
		c_shape.setRadius(circ->r);
		c_shape.setOrigin(sf::Vector2f(circ->r, circ->r));
		win.draw(c_shape);
		win.draw(line->line, trans->trans);
		//std::cout << "cir disp";
	}
	for (auto entity : en.entities_with_components(line))
	{
		//std::cout << "line" << std::endl;
		win.draw(line->line);
		//std::cout << "line disp";
	}
}
render_system::~render_system()
{
}
