#include "Skybox.h"
#include "../Window.h"

#define SB_VERTEX_SIZE (3 + 2)
#define SB_VERTEX(I,X,Y,Z,T,S) buffer[0 + I] = X; \
							   buffer[1 + I] = Y; \
							   buffer[2 + I] = Z; \
							   buffer[3 + I] = T; \
							   buffer[4 + I] = S; \
							   I += SB_VERTEX_SIZE;
#define SB_BOX(I) SB_VERTEX(I,-0.5f,-0.5f,-0.5f, 0.0f,        0.0f) /* BACK */ \
				  SB_VERTEX(I,-0.5f, 0.5f,-0.5f, 0.0f,        0.5f) \
				  SB_VERTEX(I, 0.5f, 0.5f,-0.5f, 1.0f / 3.0f, 0.5f) \
				  SB_VERTEX(I,-0.5f,-0.5f,-0.5f, 0.0f,        0.0f) \
				  SB_VERTEX(I, 0.5f,-0.5f,-0.5f, 1.0f / 3.0f, 0.0f) \
				  SB_VERTEX(I, 0.5f, 0.5f,-0.5f, 1.0f / 3.0f, 0.5f) \
				  SB_VERTEX(I,-0.5f,-0.5f, 0.5f, 2.0f / 3.0f, 0.5f) /* FRONT */ \
				  SB_VERTEX(I,-0.5f, 0.5f, 0.5f, 2.0f / 3.0f, 1.0f) \
				  SB_VERTEX(I, 0.5f, 0.5f, 0.5f, 1.0f,        1.0f) \
				  SB_VERTEX(I,-0.5f,-0.5f, 0.5f, 2.0f / 3.0f, 0.5f) \
				  SB_VERTEX(I, 0.5f,-0.5f, 0.5f, 1.0f,        0.5f) \
				  SB_VERTEX(I, 0.5f, 0.5f, 0.5f, 1.0f,        1.0f) \
				  SB_VERTEX(I,-0.5f, 0.5f,-0.5f, 1.0f / 3.0f, 0.0f) /* TOP */ \
				  SB_VERTEX(I,-0.5f, 0.5f, 0.5f, 1.0f / 3.0f, 0.5f) \
				  SB_VERTEX(I, 0.5f, 0.5f, 0.5f, 2.0f / 3.0f, 0.5f) \
				  SB_VERTEX(I,-0.5f, 0.5f,-0.5f, 1.0f / 3.0f, 0.0f) \
				  SB_VERTEX(I, 0.5f, 0.5f,-0.5f, 2.0f / 3.0f, 0.0f) \
				  SB_VERTEX(I, 0.5f, 0.5f, 0.5f, 2.0f / 3.0f, 0.5f) \
				  SB_VERTEX(I,-0.5f,-0.5f,-0.5f, 0.0f,        0.5f) /* BOTTOM */ \
				  SB_VERTEX(I,-0.5f,-0.5f, 0.5f, 0.0f,        1.0f) \
				  SB_VERTEX(I, 0.5f,-0.5f, 0.5f, 1.0f / 3.0f, 1.0f) \
				  SB_VERTEX(I,-0.5f,-0.5f,-0.5f, 0.0f,        0.5f) \
				  SB_VERTEX(I, 0.5f,-0.5f,-0.5f, 1.0f / 3.0f, 0.5f) \
				  SB_VERTEX(I, 0.5f,-0.5f, 0.5f, 1.0f / 3.0f, 1.0f) \
				  SB_VERTEX(I, 0.5f,-0.5f,-0.5f, 1.0f / 3.0f, 0.5f) /* RIGHT */ \
				  SB_VERTEX(I, 0.5f,-0.5f, 0.5f, 1.0f / 3.0f, 1.0f) \
				  SB_VERTEX(I, 0.5f, 0.5f, 0.5f, 2.0f / 3.0f, 1.0f) \
				  SB_VERTEX(I, 0.5f,-0.5f,-0.5f, 1.0f / 3.0f, 0.5f) \
				  SB_VERTEX(I, 0.5f, 0.5f,-0.5f, 2.0f / 3.0f, 0.5f) \
				  SB_VERTEX(I, 0.5f, 0.5f, 0.5f, 2.0f / 3.0f, 1.0f) \
				  SB_VERTEX(I,-0.5f,-0.5f,-0.5f, 2.0f / 3.0f, 0.0f) /* LEFT */ \
				  SB_VERTEX(I,-0.5f,-0.5f, 0.5f, 2.0f / 3.0f, 0.5f) \
				  SB_VERTEX(I,-0.5f, 0.5f, 0.5f, 1.0f,        0.5f) \
				  SB_VERTEX(I,-0.5f,-0.5f,-0.5f, 2.0f / 3.0f, 0.0f) \
				  SB_VERTEX(I,-0.5f, 0.5f,-0.5f, 1.0f,        0.0f) \
				  SB_VERTEX(I,-0.5f, 0.5f, 0.5f, 1.0f,        0.5f)

Skybox::Skybox(const char* name) {
	/* Init */
	int attrs[] = { 3, 2, 0 };
	texture = load_texture(name);
	shader = load_shader("SkyboxVertex.glsl", "SkyboxFragment.glsl");
	buffer = new float[6 * 6 * SB_VERTEX_SIZE];

	/* Load to buffer */
	int I = 0;
	SB_BOX(I);
	index = I;

	mesh = new Mesh(buffer, 36, attrs);
}
void Skybox::render(const Camera* cam) {
	/* Texture */
	texture->bind();

	/* Shader */
	shader->use();

	/* Shader uniforms */
	shader->uniformMatrix("projView", cam->getProjection() * cam->getView());
	shader->uniform3f("camPos", cam->position);
	shader->uniformVec2u("resolution", vec2(Window::width, Window::height));

	/* Draw */
	mesh->reload(buffer, 36);
	mesh->draw(GL_TRIANGLES);
}