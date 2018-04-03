/*
 *  partsmanager.cpp
 *
 *  Created: 2017-07-09
 *   Author: Patryk Wojtanowski modified by Pawe³ Szymañski
 */
#include "partsmanager.h"
#include "ResourceManager.h"

PartsManager::PartsManager()
{

}

void PartsManager::init()
{
    latch_part = nullptr;
    mouse_pos = sf::Vector2f(0,0);

    body_trans = sf::Transform();
    body_trans.translate(650, 500);
    body_trans.scale(200,200);
    good_place = false;

    std::string &dir = ResourcesManager::getInstanceRef().shipInfo;

    ConfigParser parser;
    assert(parser.load(dir));
    if(parser.setSection("body_info"))
    {
        current_body_name = parser.getString();
        current_body = &(ResourcesManager::getInstanceRef().vertCont.getPoly(current_body_name));
        current_normals = &(ResourcesManager::getInstanceRef().vertCont.getNormals(current_body_name));

        std::cout<<"current body: "<<current_body_name<<std::endl;
    }

    if(parser.setSection("parts_info"))
    {
        while(!parser.EndOfSection())
        {
            Part new_part;
            sf::Vector2f pos;

            new_part.name = parser.getString();
            pos.x =  parser.getFloat();
            pos.y = parser.getFloat();
            sf::Vector2f npos = body_trans * pos;
            new_part.pos = npos;
            new_part.rot = parser.getFloat();
            new_part.key = parser.getString();
			new_part.partId = parser.getFloat();//<- id part

            new_part.normals = &(ResourcesManager::getInstanceRef().vertCont.getNormals(new_part.name));
            new_part.v_array = &(ResourcesManager::getInstanceRef().vertCont.getPoly(new_part.name));

            std::cout<<"textures size: "<<ResourcesManager::getInstanceRef().vertCont.textures.size()<<std::endl;

            std::cout<<new_part.name<< " is texture = ";
            //if(new_part.name == "small_engine" ||new_part.name == "large_engine")
             //   {
				new_part.texture = &(ResourcesManager::getInstanceRef().textureCont.getTexture(new_part.name));
            //    std::cout<<"true"<<std::endl;}
            //else
            //    {new_part.texture = nullptr;
           //     std::cout<<"false"<<std::endl;}

            new_part.trans = sf::Transform();
            new_part.trans.translate(npos);
            new_part.trans.rotate(new_part.rot);
            new_part.trans.scale(200,200);

			//ResourcesManager::getInstanceRef().
            parts.push_back(new_part);
        }
    }
}

bool PartsManager::is_body_set()
{
    return (current_body);
}

void PartsManager::set_body(const std::string &name)
{
   // if(parts.size() > 0)
   //     return;
	//std::cout << "poszlo" << std::endl;
    current_body_name = name;
    current_body = &(ResourcesManager::getInstanceRef().vertCont.getPoly(name));
    current_normals = &(ResourcesManager::getInstanceRef().vertCont.getNormals(name));
}

void PartsManager::loadPartFromFile(std::string dir)
{
	ConfigParser pars;
	pars.load(dir);
	if (!pars.setSection("body_info"))
		return;
	set_body(pars.getString());

	parts.clear();

	Part part;
	if (!pars.setSection("parts_info"))
		return;

	while (!pars.EndOfSection())
	{
		std::cout << "loaded!!!!" << std::endl;
		part.name.clear();
		part.name = pars.getString();
		part.v_array = &(ResourcesManager::getInstanceRef().vertCont.getPoly(part.name));
		part.texture = &(ResourcesManager::getInstanceRef().textureCont.getTexture(part.name));
		part.pos.x = 200 * pars.getFloat() + 650;
		part.pos.y = 200 * pars.getFloat() + 500;
		part.rot = pars.getFloat();
		part.key = pars.getString();
		pars.getFloat(); //<-id part
		sf::Transform trans;

		part.trans = {	1,0,0,
						0,1,0,
						0,0,1 };

		part.trans.translate(part.pos);
		part.trans.rotate(part.rot);

		part.trans.scale(sf::Vector2f(200, 200));

		part.normals = &(ResourcesManager::getInstanceRef().vertCont.getNormals(part.name));

		parts.push_back(part);
	}
}

void PartsManager::add_part(const std::string &name)
{
    if(latch_part)
        return;

    sf::VertexArray &temp = ResourcesManager::getInstanceRef().vertCont.getPoly(name);
    std::vector <sf::Vector2f> &temp_normals = ResourcesManager::getInstanceRef().vertCont.getNormals(name);

    Part new_part(name, temp, temp_normals);

    std::cout<<new_part.name<< " is texture = ";
   // if(new_part.name == "small_engine" ||new_part.name == "large_engine")
   //     {
		new_part.texture = &(ResourcesManager::getInstanceRef().textureCont.getTexture(name));
  //    std::cout<<"true"<<std::endl;}
   // else
   //     {new_part.texture = nullptr;
   //     std::cout<<"false"<<std::endl;}

    parts.push_back(new_part);

    latch_part =  &(parts.at( parts.size() -1 ));
}

void PartsManager::saveShip(const std::string &dir)
{
    std::vector < std::vector <std::string> > body_data, parts_data;
    ConfigCreator creator;

    body_data.resize(1);
    body_data.at(0).push_back(current_body_name);

    creator.addSection("body_info", body_data);
	int partID = 0;
    for( Part & part: parts)
    {
        std::stringstream posx, posy, rot;
        sf::Vector2f pos = body_trans.getInverse() * part.pos;
        posx<<pos.x;
        posy<<pos.y;
        rot<<part.rot;
        std::vector < std::string > temp = {
            part.name,
            posx.str(),
            posy.str(),
            rot.str(),
            part.key,
			std::to_string(partID)
        };

        parts_data.push_back(temp);
		++partID;
    }

    creator.addSection("parts_info", parts_data);
    creator.setDir(dir);
    creator.create();
}

Part *PartsManager::findClicked()
{
    for(auto & part: parts)
    {
        sf::VertexArray& v_array = *(part.v_array);
        std::vector<sf::Vector2f> &normals = *(part.normals);
        unsigned int size = normals.size();

        sf::Vector2f pos = part.trans.getInverse() * mouse_pos;
        float best_distance = -FLT_MAX;

        for(unsigned int i=0 ; i <size; ++i)
        {
            sf::Vector2f normal =  normals.at(i);
            sf::Vector2f vert_to_point = pos - v_array[i].position;
            float dist = dot(normal,vert_to_point);
            best_distance = (dist > best_distance)? dist: best_distance;
        }

        if(best_distance < 0.0f)
            return &part;
    }

    return nullptr;
}

void PartsManager::input(sf::Event ev)
{
    if(ev.type == sf::Event::MouseMoved)
    {
        mouse_pos = sf::Vector2f(ev.mouseMove.x, ev.mouseMove.y);

        if(latch_part)
        {
            latch_part->pos = sf::Vector2f(ev.mouseMove.x - ev.mouseMove.x%10, ev.mouseMove.y - ev.mouseMove.y%10);
            latch_part->trans = sf::Transform();
            latch_part->trans.translate(latch_part->pos);
            latch_part->trans.scale(200, 200);
            latch_part->trans.rotate(latch_part->rot);
        }
    }
    else if(ev.type == sf::Event::MouseWheelScrolled && latch_part)
    {
        latch_part->rot += ev.mouseWheelScroll.delta * 10;
        latch_part->trans.rotate(ev.mouseWheelScroll.delta * 10);
    }
    else if( ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Delete && latch_part)
    {
        for(auto iter = parts.begin(); iter < parts.end(); ++iter)
        {
            if(&(*iter) == latch_part)
            {
                parts.erase(iter);
                break;
            }
        }

        latch_part = nullptr;
    }
    else if( ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left)
    {
        if(latch_part && good_place)
            latch_part = nullptr;
        else if(!latch_part)
        {
            Part * clicked = findClicked();
            latch_part = (clicked)? clicked : nullptr;
        }
    }
    else if( ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Right)
    {
        Part * clicked = findClicked();
        assigner.assign(clicked);
    }

    assigner.input(ev);

    if(!current_body || !latch_part)
        return;

    const unsigned int size = current_body->getVertexCount();
    const sf::Vector2f pos = body_trans.getInverse() * latch_part->pos;

    sf::Vector2f best_normal;
    float best_distance = -FLT_MAX;

    for(unsigned int i=0 ; i <size; ++i)
    {
        sf::Vector2f normal =  current_normals->at(i);
        sf::Vector2f vert_to_point = pos - (*current_body)[i].position;
        float dist = dot(normal,vert_to_point);
        bool good = dist > best_distance;
        best_distance = (good)? dist: best_distance;
        best_normal = (good)? normal : best_normal;
    }

    good_place = best_distance < 0.1f;
    if(good_place)
    {
        latch_part->pos += -best_normal * best_distance *200.0f;
        latch_part->trans = sf::Transform();
        latch_part->trans.translate(latch_part->pos);
        latch_part->trans.scale(200, 200);
        latch_part->trans.rotate(latch_part->rot);
    }

    for(unsigned int i=0; i<size; i++)
    {
        sf::Vector2f vert = (*current_body)[i].position;
        float dist = distance(vert, pos);
        if(dist < 0.1f)
        {
            latch_part->pos += vert;//body_trans * vert;
            latch_part->trans = sf::Transform();
            latch_part->trans.translate(latch_part->pos);
            latch_part->trans.scale(200, 200);
            latch_part->trans.rotate(latch_part->rot);
        }
    }

}

void PartsManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (current_body)
	{
		sf::RenderStates renderStates;

		renderStates.texture = &ResourcesManager::getInstanceRef().textureCont.getTexture(current_body_name);
		renderStates.transform = body_trans;
		target.draw(*current_body, renderStates);
	}
	int liczba = 0;
    for(auto &p: parts)
    {
		//std::cout << " number of parts : " << liczba++ << std::endl;
		//system("pause");
        sf::Vertex line[2]
        {
            sf::Vertex(p.trans * sf::Vector2f(0,0), sf::Color::White),
            sf::Vertex(p.trans * sf::Vector2f(0,0.4f), sf::Color::White)
        };

        sf::RenderStates renderStates;

        renderStates.texture = p.texture;
        renderStates.transform = p.trans;

        target.draw(*(p.v_array), renderStates);
        target.draw(line,2,sf::Lines);

        sf::Text key;
        key.setCharacterSize(32);
        key.setFillColor(sf::Color::White);
        key.setFont(ResourcesManager::getInstanceRef().font);
        key.setPosition(p.pos- sf::Vector2f(16,16));
        key.setString(p.key);
        target.draw(key);
    }

    target.draw(assigner);
}

void PartsManager::release()
{
    current_body = nullptr;
    current_normals = nullptr;
    latch_part = nullptr;

    good_place = false;
    assigner.release();

    mouse_pos = sf::Vector2f(0,0);
    current_body_name = std::string();
    parts.clear();
}
