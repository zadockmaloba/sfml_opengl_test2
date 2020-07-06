#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/GLU.h>
#include <EGL/egl.h>
#include <iostream>

static const sf::Vector2i WIN_SIZE{ 1080,720 };
void gameLoop(sf::RenderWindow* win);

/*--------------------------------------------------------------------------------
  ---            SFML project by Zadock Maloba                                 ---
  ---                                                                          ---
  ---   E-mail: malobazadock@gmail.com || Tweeter: @Zadock_254                 ---
  --------------------------------------------------------------------------------
*/


int main()
{
	sf::RenderWindow win(sf::VideoMode(WIN_SIZE.x,WIN_SIZE.y, 32), "SFML/OpenGL", sf::Style::Close | sf::Style::Resize);
	gameLoop(&win);
}

void gameLoop(sf::RenderWindow* win)
{
	win->setVerticalSyncEnabled(true);
	//Declare objects not meant to be in the Loop here...
	float positions[9] = {
		-0.5f,0.5f,0.0f,
		 0.0f,0.5f,0.0f,
		 0.5f,-0.5f,0.5f,
	};
	float cube_vert[9] = {
		-0.5f,0.5f,0.0f,
		 0.0f,0.5f,0.0f,
		 0.5f,-0.5f,0.5f,
	};
	glewInit();
	unsigned int buffer;
	unsigned int bufA ;
	glGenBuffers(1, &bufA);
	glBindBuffer(GL_ARRAY_BUFFER, bufA);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), cube_vert, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	sf::Clock Clock;

	//Decl_Objs
	while (win->isOpen())
	{
		float angle = Clock.getElapsedTime().asMilliseconds();
		win->clear();
		//Draw Game Objects Here...
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//Draw_Objs

		//Event Loop ...
		sf::Event evnts;
		while (win->pollEvent(evnts))
		{
			if (evnts.type == sf::Event::Closed) win->close();
			if (evnts.type == sf::Event::Resized) glViewport(0,0,win->getSize().x,win->getSize().y) ;
			if (evnts.type == sf::Event::KeyPressed)
			{
				if(evnts.key.code == sf::Keyboard::Left)glRotatef( 10, 0, 1, 0);
				if (evnts.key.code == sf::Keyboard::Right)glRotatef(10, 0, -1, 0);
				if (evnts.key.code == sf::Keyboard::Up)glRotatef(10, 1, 0, 0);
				if (evnts.key.code == sf::Keyboard::Down)glRotatef(10, -1, 0, 0);
			}
		}//Event_loop
		//glRotatef(-(int)angle%10, 1, 0, 1);
		win->display();
	}
}
