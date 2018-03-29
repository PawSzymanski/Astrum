#include "ResourceManager.h"

ResourcesManager* ResourcesManager::instance = nullptr;

ResourcesManager::ResourcesManager() : gameplay_stage(vertCont), levelInfo("resources/levelData/level_4.cfg"), shipInfo("resources/levelData/ship_1.cfg"), 
										shipInfoMulti("resources/levelData/multi_ship_1.cfg"),
										areAllPlatfIncluded(false), isMouseButtonReleased(false), 
										areAllCargoSpaceIncluded(false), isGameOver(false), isPauseTime(false)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	
    window.create(sf::VideoMode(1366, 768, 32), "Astrum", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize, settings);

	window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);

    font.loadFromFile("resources/sansation.ttf");

    loadContainer();
	//game over buttons initialisation
	GOButton[0].init(font, 40, sf::Vector2f(8.75, 4), sf::Color::White, "Back", sf::Vector2f(0.4, 0.2));
	GOButton[1].init(font, 40, sf::Vector2f(8.75, 5), sf::Color::White, "Next", sf::Vector2f(0.4, 0.2));
	GOButton[2].init(font, 40, sf::Vector2f(8.75, 6), sf::Color::White, "Exit", sf::Vector2f(0.4, 0.2));
}

ResourcesManager::~ResourcesManager()
{
}

void ResourcesManager::loadContainer()
{
    std::map <std::string, sf::Color> sf_colors;
    sf_colors["BLACK"] = sf::Color::Black;
    sf_colors["RED"] = sf::Color::Red;
    sf_colors["MAGENTA"] = sf::Color::Magenta;
    sf_colors["CYAN"] = sf::Color::Cyan;
    sf_colors["BLUE"] = sf::Color::Blue;
    sf_colors["GREEN"] = sf::Color::Green;
    sf_colors["WHITE"] = sf::Color::White;
    sf_colors["YELLOW"] = sf::Color::Yellow;


    std::string dir("resources/parts/");
    std::vector < std::string > filenames = {
        "alien_body.cfg",
        "long_body.cfg",
        "cobra_body.cfg",
        "large_engine.cfg",
        "small_engine.cfg",
        "landing_legs.cfg",
        "crane.cfg",
        "wall.cfg",
		"wall1.cfg",
		"wall2.cfg",
		"wall3.cfg",
        "potato.cfg",
        "platform.cfg",
        "small_engine_fire.cfg",
        "explosion.cfg",
        "fire.cfg",
        "hook.cfg",
        "bomb.cfg",
		"faded_screen.cfg",
		"gun.cfg",
		"bullet.cfg",
		"shooting_camera.cfg",
		"sliding_doors.cfg",
		"square.cfg"
    };

    ConfigParser parser;

    for(auto & filename: filenames)
    {
        std::vector <sf::Vector2f> vert_vec;
        std::vector <sf::Vector2f> image_vec;
        std::string name;

        parser.load(dir+filename);
        parser.setSection("name");
        name = parser.getString();

        std::cout<<"NAME: "<<name<<std::endl;
        parser.setSection("vertex");

        while(!parser.EndOfSection())
        {
            sf::Vector2f v;
            v.x = parser.getFloat();
            v.y = parser.getFloat();
            std::cout<<v.x<<" "<<v.y<<std::endl;
            vert_vec.push_back(v);
        }

        if(parser.setSection("texCoords"))
        {
            while (!parser.EndOfSection())
            {
                sf::Vector2f v;
                v.x = parser.getFloat();
                v.y = parser.getFloat();

                std::cout<<v.x<<" "<<v.y<< " TEXTCOORDS" <<std::endl;
                image_vec.push_back(v);
            }
        }

        bool has_color = false;
        sf::Color color;
        if(parser.setSection("color"))
        {
            has_color = true;
            std::string c = parser.getString();
            if(sf_colors.find(c) == sf_colors.end())
            {
                std::cout<<"zły kolor w pliku"<<std::endl;
                assert(false);
            }
            color = sf_colors[c];
        }

        unsigned int vec_size = vert_vec.size();
        sf::VertexArray v_array(sf::TriangleFan, vec_size);
        for(int i=0; i<vec_size; ++i)
        {
            v_array[i].position = vert_vec[i];
            if(has_color)
                v_array[i].color = color;
            if(i<image_vec.size())
                v_array[i].texCoords = image_vec[i];
        }

        vertCont.addPoly(v_array, vec_size, name);
    }
	//loading texstures to container
	std::string texturePath("resources/graphics/"), textureName, vertexAssigned;

	parser.load("resources/graphics/image_info.cfg");
	parser.setSection("name");
    while (!parser.EndOfSection())
	{
		textureName = parser.getString();
        std::cout << std::endl<<" texture: " << textureName << " loaded " << std::endl;
        std::string partName = parser.getString();
        std::cout<<"partName: "<<partName<<std::endl;
		sf::Texture t;
		t.loadFromFile(texturePath + textureName);
        textureCont.addTexture(t, partName);
	}
	parser.load("resources/graphics/animations_info.cfg");
	while (!parser.EndOfSection())
	{
		float framesSpeed;
		std::string textureName = parser.getString();
        //std::cout << " anim: " << textureName << " loaded " << std::endl;
		sf::Vector2f frameSize;
		//x
		frameSize.x = parser.getFloat();
		//y
        //std::cout << " X: " << frameSize.x << " loaded " << std::endl;
		frameSize.y = parser.getFloat();
        //std::cout << " Y: " << frameSize.y << " loaded " << std::endl;
		framesSpeed = parser.getFloat();

		textureCont.addAnimation(textureName, frameSize, framesSpeed);
	}
}

ResourcesManager* ResourcesManager::getInstance()
{
	if (!instance) instance = new ResourcesManager();

	return instance;
}

ResourcesManager& ResourcesManager::getInstanceRef()
{
	return *getInstance();
}

void ResourcesManager::deleteInstance()
{
	delete instance;
}

std::string ResourcesManager::decodeOneLineDel(std::string &array)
{
	std::string message;
	while (array[0] != ';' && !array.empty())
	{
		message.push_back(array[0]);
		array.erase(0, 1);
	}
	array.erase(0, 1);
	return message;
}
//decodes first part of buffer 
std::string ResourcesManager::decodeOneLineRead(std::string arr)
{
	int i = 0;
	std::string message;
	while (!arr.empty() && arr[i] != ';')
	{
		message.push_back(arr[i]);
		++i;
	}
	return message;
}

