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
    AdditionalAnim::Handle anim;
    PolyName::Handle nameHandle;
	//std::cout << "render gameplpay, entity size: " << en.size() << std::endl;

    for (auto entity : en.entities_with_components(vArray, trans, nameHandle))
	{

        if (ResourcesManager::getInstanceRef().textureCont.isTexture(nameHandle->name))
		{
			trans = entity.component<Transform>();
			//sf::BlendMode noBlending = sf::BlendNone;
			sf::RenderStates renderStates;
            auto &texture = ResourcesManager::getInstanceRef().textureCont.getTexture(nameHandle->name);

			renderStates.texture = &texture;
			renderStates.transform = trans->trans;
			
			win.draw(vArray->vert, renderStates);
        }
		else
		{
			win.draw(vArray->vert, trans->trans);
		}

	}

    for(auto entity : en.entities_with_components(trans, anim))
    {
        sf::RenderStates states;
        states.texture = anim->texture;
        states.transform = trans->trans;
		states.transform.translate(anim->transVector);
        win.draw(anim->v_array, states);
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

	if (ResourcesManager::getInstanceRef().areAllPlatfIncluded || ResourcesManager::getInstanceRef().isGameOver)
	{
		int i = 0;
		for (auto & button : ResourcesManager::getInstanceRef().GOButton)
		{

			sf::RenderStates states, states2;

			
			states2.transform.translate(sf::Vector2f(8.15, 3.9 + i));
			states2.transform.scale(sf::Vector2f(0.01, 0.01));
			

			win.draw(button.rect, states);
			win.draw(button.text, states2);
			++i;
		}
	}
}
render_system::~render_system()
{
}
