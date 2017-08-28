#include "animations_system.h"
#include "ResourceManager.h"
/*
*
*
*  Author: Pawe³ Szymañski
*/

animations_system::animations_system()
{
}

void animations_system::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	AdditionalAnim::Handle animationH;
	for (auto ent : en.entities_with_components<AdditionalAnim>())
	{
		animationH = ent.component<AdditionalAnim>();
		animationH->wholeTime += animationH->clock.getElapsedTime();
		animationH->time += animationH->clock.restart();
		
		if(!animationH.valid()) //do we need it ?
		return;

		if (animationH->animate)
		{
			if (animationH->time.asSeconds() > (1.0f / animationH->fps))
			{
				animationH->time = sf::Time::Zero;
				
				std::string nameOfAnim = animationH->nameOfAnim;
				sf::Vector2f framesSize = ResourcesManager::getInstanceRef().textureCont.getAnimationFrameSize(nameOfAnim);
				int amountFramesX = (*animationH->texture).getSize().x / framesSize.x;
				int amountFramesY = (*animationH->texture).getSize().y / framesSize.y;

				++(animationH->frame_x);
				animationH->frame_y = (animationH->frame_x >= amountFramesX) ? (animationH->frame_y + 1) : animationH->frame_y;
				animationH->frame_y = (animationH->frame_y >= amountFramesY) ? 0 : animationH->frame_y;
				animationH->frame_x = (animationH->frame_x >= amountFramesX) ? 0 : animationH->frame_x;

				sf::VertexArray & array = animationH->v_array;
				array[0].texCoords = sf::Vector2f(animationH->frame_x *  framesSize.x, animationH->frame_y * framesSize.y);
				array[1].texCoords = sf::Vector2f(animationH->frame_x * framesSize.x, animationH->frame_y * framesSize.y + framesSize.y);
				array[2].texCoords = sf::Vector2f(animationH->frame_x * framesSize.x + framesSize.x, animationH->frame_y * framesSize.y + framesSize.y);
				array[3].texCoords = sf::Vector2f(animationH->frame_x * framesSize.x + framesSize.x, animationH->frame_y * framesSize.y);
                //std::cout << (*animationH->texture).getSize().x << " " << framesSize.x << std::endl;
                
				//std::cout << "ANIM " << nameOfAnim <<  std::endl;
			}
		}
		else
		{
			//niepotrzebny kod?
			//sf::VertexArray & array = animationH->v_array;
			///array[0].texCoords = sf::Vector2f(0, 0);
			////array[1].texCoords = sf::Vector2f(0, 0);
			//array[2].texCoords = sf::Vector2f(0, 0);
			//array[3].texCoords = sf::Vector2f(0, 0);

			//or this 
			//ent.remove<AdditionalAnim>();
		}
	}
}


animations_system::~animations_system()
{
}
