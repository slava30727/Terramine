#include "defines.cpp"

#ifdef _RELEASE
#	include <windows.h>
#endif

#include <math.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"
#include "Window.h"
#include "Camera.h"
#include "Player.h"
#include "EventHandler.h"

#include "Voxels/voxel.h"
#include "Voxels/Chunk.h"
#include "Voxels/Chunks.h"
#include "Voxels/Terrarian.h"

#include "Graphics/Shader.h"
#include "Graphics/Skybox.h"
#include "Graphics/Texture.h"
#include "Graphics/LineBatch.h"
#include "Graphics/VoxelRenderer.h"
#include "Graphics/MasterHandler.h"

#include "GUI/Text.h"
#include "GUI/GUIHandler.h"

MAIN {
	CONSOLE_LOG("Initializing window...\t");
		if (Window::init(WIDTH, HEIGHT, "Terramine") == -1) {
			system("pause");
			return -1;
		}
	CONSOLE_LOG("DONE\n");

	/* Systems init */
	Events::init();
	Text::init();
	MasterHandler::init();

	CONSOLE_LOG("OpenGL predefines...\t")
		glcall(glClearColor(0.61f, 0.86f, 1.0f, 1.0f));
		glcall(glEnable(GL_MULTISAMPLE));
		glcall(glEnable(GL_BLEND));
		glcall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		glcall(glLineWidth(2.0f));
	CONSOLE_LOG("DONE\n");

	while (!Window::isClosed()) {
		if (Events::justPressed(GLFW_KEY_T)) Events::toggleCursor();
		if (Events::justPressed(GLFW_KEY_ESCAPE)) {
			MasterHandler::gui->current = pauseMenu;
			Events::toggleCursor();
		}

		MasterHandler::updateAll();
		MasterHandler::render();

		Window::swapBuffers();
		Events::pullEvents();
	}

	CONSOLE_LOG("Terminating systems...\t");
	MasterHandler::terminate();
	Events::terminate();
	Window::terminate();
	CONSOLE_LOG("DONE\n");

#	ifndef _RELEASE
		system("pause");
#	endif
	return 0;
}

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}
bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "OpenGL error : " << error << ' ' << function << " : " << line << std::endl;
		return false;
	}
	return true;
}
