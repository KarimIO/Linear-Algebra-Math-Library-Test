#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "game.hpp"

#define THROW_ERROR(s) throw std::runtime_error(s);

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		THROW_ERROR("Failed to open shader.\n");
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *message,
	void *userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "--------------- \nDebug message (" << id << "): " << message << "\n";

	switch (source)
	{
		case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
		case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
		case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << "\n";

	switch (type)
	{
		case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
		case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
		case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
		case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
		case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
		case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << "\n";

	switch (severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
		case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
		case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << "\n\n";
}

Game::Game() {
	if( !glfwInit() ) {
		THROW_ERROR("Could not load GLFW\n");
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For Mac
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // No old OGL
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	window = glfwCreateWindow( 1024, 768, "Linear Algebra", NULL, NULL);
	if( window == NULL ){
	    glfwTerminate();
		THROW_ERROR("Could not create window\n");
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	if (gl3wInit())
		THROW_ERROR("Could not load GL3W\n");

	if (!gl3wIsSupported(3, 3))
		THROW_ERROR("OpenGL 3.3 not supported\n");

	/*GLint flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback((GLDEBUGPROC)glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
	else {
		printf("No debug\n");
	}*/

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
			glGetString(GL_SHADING_LANGUAGE_VERSION));

	objects_.reserve(3);

	const Vector3 triangle[] = {
		Vector3(-1.0f, -1.0f, 0.0f),
		Vector3(0.0f,  1.0f, 0.0f),
		Vector3(1.0f, -1.0f, 0.0f)
	};
	
	objects_.push_back(Object(triangle, 3));
	objects_.push_back(Object(triangle, 3, Vector3(0,0,-2), Vector3(2), Vector3(0)));

	const Vector3 box[] = {
		// Back
		Vector3(-1.0f, -1.0f, -1.0f),
		Vector3(-1.0f,  1.0f, -1.0f),
		Vector3( 1.0f, -1.0f, -1.0f),
		Vector3(-1.0f,  1.0f, -1.0f),
		Vector3( 1.0f, -1.0f, -1.0f),
		Vector3( 1.0f,  1.0f, -1.0f),

		// Front
		Vector3(-1.0f, -1.0f, 1.0f),
		Vector3(-1.0f,  1.0f, 1.0f),
		Vector3( 1.0f, -1.0f, 1.0f),
		Vector3(-1.0f,  1.0f, 1.0f),
		Vector3( 1.0f, -1.0f, 1.0f),
		Vector3( 1.0f,  1.0f, 1.0f),
		
		// Right
		Vector3(-1.0f, -1.0f, -1.0f),
		Vector3(-1.0f, -1.0f,  1.0f),
		Vector3(-1.0f,  1.0f, -1.0f),
		Vector3(-1.0f, -1.0f,  1.0f),
		Vector3(-1.0f,  1.0f, -1.0f),
		Vector3(-1.0f,  1.0f,  1.0f),
		
		// Left
		Vector3( 1.0f, -1.0f, -1.0f),
		Vector3( 1.0f, -1.0f,  1.0f),
		Vector3( 1.0f,  1.0f, -1.0f),
		Vector3( 1.0f, -1.0f,  1.0f),
		Vector3( 1.0f,  1.0f, -1.0f),
		Vector3( 1.0f,  1.0f,  1.0f),

		// Bottom
		Vector3(-1.0f, -1.0f, -1.0f),
		Vector3(-1.0f, -1.0f,  1.0f),
		Vector3( 1.0f, -1.0f, -1.0f),
		Vector3(-1.0f, -1.0f,  1.0f),
		Vector3( 1.0f, -1.0f, -1.0f),
		Vector3( 1.0f, -1.0f,  1.0f),

		// Top
		Vector3(-1.0f, 1.0f, -1.0f),
		Vector3(-1.0f, 1.0f,  1.0f),
		Vector3( 1.0f, 1.0f, -1.0f),
		Vector3(-1.0f, 1.0f,  1.0f),
		Vector3( 1.0f, 1.0f, -1.0f),
		Vector3( 1.0f, 1.0f,  1.0f)
	};

	objects_.push_back(Object(box, sizeof(box)/sizeof(box[0]), Vector3(0), Vector3(8)));

	const GLfloat quads[] = {
		-1.0f, -1.0f,
		-1.0f,  1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f
	};

	glGenVertexArrays(1, &quadvao);
	glBindVertexArray(quadvao);
	glGenBuffers(1, &quadvbo);
	glBindBuffer(GL_ARRAY_BUFFER, quadvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quads), quads, GL_STATIC_DRAW);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   2,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
		
	glGenFramebuffers(1, &fbo_);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

	glGenTextures(1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 1024, 768, 0, GL_RGBA, GL_FLOAT, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	
	glGenTextures(1, &depth_texture_);
	glBindTexture(GL_TEXTURE_2D, depth_texture_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, 1024.0f, 768.0f, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture_, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint buffers[] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, buffers);	

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		THROW_ERROR("Framebuffer Failed!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(33.0f/255.0f, 66.0f/255.0f, 99.0f/255.0f, 1.0);
	
	mainProgram = LoadShaders( "shaders/main_vert.glsl", "shaders/main_frag.glsl" );
	
	vpUniform = glGetUniformLocation(mainProgram, "perspectiveView");
	worldUniform = glGetUniformLocation(mainProgram, "world");
	
	postProgram = LoadShaders( "shaders/post_vert.glsl", "shaders/post_frag.glsl" );
	
	depth_uniform_ = glGetUniformLocation(postProgram, "depthTex");
	color_uniform_ = glGetUniformLocation(postProgram, "colorTex");
	selector_uniform_ = glGetUniformLocation(postProgram, "selector");
	view_uniform_ = glGetUniformLocation(postProgram, "view");
	proj_uniform_ = glGetUniformLocation(postProgram, "proj");
	selector_ = 0;

	glEnable(GL_DEPTH_TEST);
	
	std::cout << "Game successfully Initialized!" << std::endl;
}

void Game::Draw() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(mainProgram);

	// SetMatrix: TargetLocation, Count, IsRowMajor, Source
	Matrix world(1.0f);
	Matrix vp = camera.getProj() * camera.getView();
	glUniformMatrix4fv(vpUniform, 1, true, vp.getMatrix());
	
	for (Object &o : objects_) {
		o.Draw(worldUniform);
	}
}

void Game::PostStage() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(postProgram);

	glUniform1i(color_uniform_, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_);

	glUniform1i(depth_uniform_, 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depth_texture_);

	glUniform1ui(selector_uniform_, selector_);

	glUniformMatrix4fv(proj_uniform_, 1, true, camera.getProj().getMatrix());
	glUniformMatrix4fv(view_uniform_, 1, true, camera.getView().getMatrix());

	glBindVertexArray(quadvao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

bool keyPressed = false;

void Game::Update(double time) {
	// Get Movement offset = (key1-key2)*delta_time
	double x = ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) - (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)) * time;
	double y = ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) - (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)) * time;
	double z = ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) - (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)) * time;
	
	const double hx = 1024.0f/2.0f;
	const double hy =  768.0f/2.0f;

	double mx, my;
	glfwGetCursorPos(window, &mx, &my);
	mx = (mx-hx)*time;
	my = (my-hy)*time;
	glfwSetCursorPos(window, hx, hy);

	// Move the camera
	camera.Move(Vector3(x, y, z), mx, my);

	objects_[0].SetPosition(0, sin(glfwGetTime()) * 4, 4);
	objects_[1].SetScale(Vector3(cos(glfwGetTime()) * 2, sin(glfwGetTime()) * 2, 1));
	
	if (keyPressed == false && glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		keyPressed = true;
		selector_ = (selector_+1)%4;
	}
	else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE) {
		keyPressed = false;
	}
}
	
void Game::Run() {
	double start_time = glfwGetTime(), end_time;
	do {
		end_time = glfwGetTime();
		Update(end_time-start_time);
		start_time = end_time;

		Draw();
		PostStage();

		// Swap buffers
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	while((glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS) && (glfwWindowShouldClose(window) == false) );
}

Game::~Game() {
	glfwTerminate();
}
