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
	void Update(double time);
	void Draw();
	void PostStage();

	Camera camera;
	
	GLFWwindow* window;
	
	GLuint fbo_;
	GLuint depth_texture_;

	GLuint trivao;
	GLuint quadvao;
	GLuint trivbo;
	GLuint quadvbo;

	GLuint mainProgram;
	GLuint postProgram;

	GLuint vpUniform;
	GLuint worldUniform;
	GLuint depth_uniform_;
};

#endif
