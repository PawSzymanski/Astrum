#include "render_system.h"
#include "ResourceManager.h"


render_system::render_system(sf::RenderWindow &window) : win(window)
{
	//if (!engineTexture.loadFromFile("resources/graphics/engine1.png"))
	{
	//	std::cout << "NIE £ADUJE OBRAZKA" << std::endl;
	}
	//renderStates.texture(&engineTexture);
}

void render_system::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	Position::Handle pos;
	Circle::Handle circ;
	Line::Handle line;
	Transform::Handle trans;
	VertexArray::Handle vArray;
	Joint::Handle joint;
	//std::cout << "render gameplpay, entity size: " << en.size() << std::endl;

	for (auto entity : en.entities_with_components(vArray, trans))
	{

		//TUTAJ SIE ZMIENI JAK WSZYSTKIE ENTITY BEDA MIA£Y TEXTURY NARAZI BEDZIE TAK
		if (entity.has_component<isEngine>())
		{

			trans = entity.component<Transform>();
			//sf::BlendMode noBlending = sf::BlendNone;
			sf::RenderStates renderStates;
			auto texture = ResourcesManager::getInstanceRef().textureCont.getTexture("small_engine");

			renderStates.texture = &texture;
			renderStates.transform = trans->trans;
			
			vArray->vert[0].texCoords = sf::Vector2f(0, 0);
			vArray->vert[1].texCoords = sf::Vector2f(30, 0);
			vArray->vert[2].texCoords = sf::Vector2f(30, 20);
			vArray->vert[3].texCoords = sf::Vector2f(0, 20);

			win.draw(vArray->vert, renderStates);
		}
		else
		{
			win.draw(vArray->vert, trans->trans);
		}

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
	}

	for (auto entity : en.entities_with_components(line))
	{
		win.draw(line->line);
	}
}
render_system::~render_system()
{
}
