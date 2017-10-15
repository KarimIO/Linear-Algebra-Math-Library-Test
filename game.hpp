#ifndef GAME_HPP
#define GAME_HPP

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "camera.hpp"

class Game {
public:
	Game();
	void Run();
	~Game();
private:
	void Draw();

	Camera camera;
	
	GLFWwindow* window;
	
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	GLuint programID;

	GLuint wvpUniform;
	GLuint worldUniform;
};

#endif
