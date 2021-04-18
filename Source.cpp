#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#define mapWidth 25
#define mapHeight 25

using std::cout;
using std::endl;
using key = sf::Keyboard;

int innerWidth = 800, innerHeight = 600;
//map created in Ascii mapper
const int worldMap[mapWidth][mapHeight] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1,1},
	{1,0,0,0,1,0,3,0,0,4,4,0,0,4,0,0,4,0,0,4,0,0,4,0,1},
	{1,0,0,0,1,0,3,0,0,4,4,0,0,4,0,0,4,0,0,4,0,0,4,0,1},
	{1,0,0,0,1,0,3,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,1,0,3,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,3,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,3,0,0,4,0,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
	{1,1,0,1,0,0,3,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
	{1,1,0,1,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,3,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1},
	{1,1,0,1,1,1,3,0,0,0,3,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
	{1,1,0,0,0,1,3,0,0,0,3,2,0,0,0,0,0,0,0,0,0,0,0,2,1},
	{1,1,0,1,0,1,3,0,0,0,3,2,0,0,0,0,0,0,0,0,0,0,0,2,1},
	{1,1,0,0,0,1,3,0,3,3,3,2,0,2,2,2,2,2,0,2,2,2,0,2,1},
	{1,1,0,1,1,1,0,0,0,0,0,2,0,2,0,0,0,2,0,0,0,2,0,2,1},
	{1,1,0,1,0,0,0,0,2,2,2,2,0,2,0,0,0,2,0,0,0,2,0,2,1},
	{1,1,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,2,2,2,2,2,0,2,1},
	{1,1,0,1,0,0,0,0,1,0,0,1,2,2,0,0,0,0,0,0,0,2,0,2,1},
	{1,1,0,1,0,0,0,0,1,0,0,1,2,2,0,0,0,0,0,0,0,2,0,2,1},
	{1,1,0,1,0,0,0,0,1,0,0,1,2,2,0,0,0,0,0,0,0,2,0,2,1},
	{1,1,0,1,1,1,1,1,1,0,0,1,2,2,0,0,0,0,0,0,0,2,0,2,1},
	{1,1,0,0,0,0,0,0,9,0,0,1,2,2,0,0,0,0,0,0,0,0,0,2,1},
	{1,1,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};


sf::Vector2f matrix_rotation(sf::Vector2f vec, float value) {

	return sf::Vector2f(
		vec.x * std::cos(value) - vec.y * std::sin(value),
		vec.x * std::sin(value) + vec.y * std::cos(value)
	);

}

void setResolution()
{
	int usr;
	cout << "1)1920x1200,2)800x600"<<endl<<"usr:";
	std::cin >> usr;
	if(usr == 1)
	{
		innerWidth = 1920;
		innerHeight = 1200;
	}else
	{
		innerWidth = 800;
		innerHeight = 600;
	}
}


int main()
{	
	setResolution();
	bool hasFocus = true;
	sf::RenderWindow app(sf::VideoMode(innerWidth - 1, innerHeight), "Raycasting live from visual studio");
	sf::Event ev;
	sf::Clock clock;
	sf::Time fps;


	app.setFramerateLimit(60);
	app.setVerticalSyncEnabled(true);
	app.setSize(sf::Vector2u(innerWidth, innerHeight));


	sf::Vector2f position(2.0f, 2.0f);
	sf::Vector2f direction(0.0f, 1.0f);
	sf::Vector2f plane(-0.66f, 0.0f);

	sf::RectangleShape floor;
	floor.setFillColor(sf::Color::Red);
	floor.setPosition(0, innerHeight / 2);
	floor.setSize(sf::Vector2f(innerWidth, innerHeight / 2));

	while (app.isOpen())
	{

		while (app.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				app.close();
				break;
			case sf::Event::LostFocus:
				hasFocus = false;
				break;
			case sf::Event::GainedFocus:
				hasFocus = true;
				break;
			default:
				break;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))app.close();
		}
		app.clear(sf::Color(199, 199, 199));
		app.draw(floor);
		for (int x = 0; x < innerWidth; x++)
		{//start of raycasting\\
			
			double camX = 2 * x / double(innerWidth) - 1;
			sf::Vector2f rayDirection;
			sf::Vector2f rayPosition;
			sf::Vector2f mapPosition;
			sf::Vector2f sideDistance;
			sf::Vector2f deltaDistance;
			double perpWallDist;
			int stepX, stepY, side, hit = 0;

			rayPosition.x = position.x;
			rayPosition.y = position.y;

			rayDirection.x = direction.x + plane.x * camX;
			rayDirection.y = direction.y + plane.y * camX;

			mapPosition.x = int(rayPosition.x);
			mapPosition.y = int(rayPosition.y);

			deltaDistance.x = std::sqrt(1 + (rayDirection.y * rayDirection.y) / (rayDirection.x * rayDirection.x));
			deltaDistance.y = std::sqrt(1 + (rayDirection.x * rayDirection.x) / (rayDirection.y * rayDirection.y));


			if (rayDirection.x < 0)
			{
				stepX = -1;
				sideDistance.x = (position.x - mapPosition.x) * deltaDistance.x;
			}
			else
			{
				stepX = 1;
				sideDistance.x = (mapPosition.x + 1 - position.x) * deltaDistance.x;
			}
			if (rayDirection.y < 0)
			{
				stepY = -1;
				sideDistance.y = (position.y - mapPosition.y) * deltaDistance.y;
			}
			else
			{
				stepY = 1;
				sideDistance.y = (mapPosition.y + 1 - position.y) * deltaDistance.y;
			}

			//sending ray until it hits the wall
			while (hit == 0)
			{
				if (sideDistance.x < sideDistance.y)
				{
					sideDistance.x += deltaDistance.x;
					mapPosition.x += stepX;
					side = 0;
				}
				else
				{
					sideDistance.y += deltaDistance.y;
					mapPosition.y += stepY;
					side = 1;
				}

				if (worldMap[int(mapPosition.x)][int(mapPosition.y)] > 0) hit = 1;
			}

			if (side == 0)perpWallDist = (mapPosition.x - position.x + (1 - stepX) / 2) / rayDirection.x;
			else perpWallDist = (mapPosition.y - position.y + (1 - stepY) / 2) / rayDirection.y;

			int lineHeight = (int)(innerHeight / perpWallDist);

			int drawStart = -lineHeight / 2 + innerHeight / 2;
			if (drawStart < 0) drawStart = 0;
			int drawEnd = lineHeight / 2 + innerHeight / 2;
			if (drawEnd >= innerHeight) drawEnd = innerHeight - 1;

			sf::Color clr;

			switch (worldMap[int(mapPosition.x)][int(mapPosition.y)])
			{
			case 1: clr = sf::Color::White; break;
			case 2: clr = sf::Color::Cyan; break;
			case 3: clr = sf::Color::Green; break;
			case 4: clr = sf::Color::Magenta; break;
			case 9: clr = sf::Color::Yellow; break;
			default: clr = sf::Color::Yellow;  break;
			}

			if (side == 1) {
				clr = sf::Color(clr.r / 2, clr.g / 2, clr.b / 2);
			}

			if (worldMap[int(position.x)][int(position.y)] == 9) app.close();

			sf::Vertex line[2] =
			{
					sf::Vertex(sf::Vector2f(x, drawStart), clr),
					sf::Vertex(sf::Vector2f(x, drawEnd), clr)
			};

			app.draw(line, 2, sf::Lines);

			//-------------------MOVEMENT--------------------------\\
				

			fps = clock.getElapsedTime();
			float dt = clock.restart().asSeconds();
			clock.restart();
			double moveSpeed = fps.asSeconds() * 5;
			double rotSpeed = fps.asSeconds() * 3;
			if (hasFocus) {
				if (key::isKeyPressed(key::W) || key::isKeyPressed(key::Up))
				{
					if (worldMap[int(position.x + direction.x * moveSpeed)][int(position.y)] == false) position.x += direction.x * moveSpeed;
					if (worldMap[int(position.x)][int(position.y + direction.x * moveSpeed)] == false) position.y += direction.y * moveSpeed;

				}
				else if (key::isKeyPressed(key::S) || key::isKeyPressed(key::Down))
				{
					if (worldMap[int(position.x - direction.x * moveSpeed)][int(position.y)] == false) position.x -= direction.x * moveSpeed;
					if (worldMap[int(position.x)][int(position.y - direction.x * moveSpeed)] == false) position.y -= direction.y * moveSpeed;
				}
				if (key::isKeyPressed(key::A) || key::isKeyPressed(key::Left))
				{
					double oldDirX = direction.x;
					direction.x = direction.x * cos(-rotSpeed) - direction.y * sin(-rotSpeed);
					direction.y = oldDirX * sin(-rotSpeed) + direction.y * cos(-rotSpeed);
					double oldPlaneX = plane.x;
					plane.x = plane.x * cos(-rotSpeed) - plane.y * sin(-rotSpeed);
					plane.y = oldPlaneX * sin(-rotSpeed) + plane.y * cos(-rotSpeed);

				}
				else if (key::isKeyPressed(key::D) || key::isKeyPressed(key::Right))
				{
					double oldDirX = direction.x;
					direction.x = direction.x * cos(rotSpeed) - direction.y * sin(rotSpeed);
					direction.y = oldDirX * sin(rotSpeed) + direction.y * cos(rotSpeed);
					double oldPlaneX = plane.x;
					plane.x = plane.x * cos(rotSpeed) - plane.y * sin(rotSpeed);
					plane.y = oldPlaneX * sin(rotSpeed) + plane.y * cos(rotSpeed);
				}
			}
		}//end of raycasting
		app.display();
	}
	return EXIT_SUCCESS;
}
