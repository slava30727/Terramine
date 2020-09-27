#include "Camera.h"

void Camera::updateVectors() {
#ifdef COMFORT_CAM
	frontCam = vec3(rotation * vec4(0.0f, 0.0f, -1.0f, 1.0f));
	frontMove = vec3(frontCam.x, 0.0f, frontCam.z);
	frontMove = normalize(frontMove);
#else
	frontCam = vec3(rotation * vec4(0.0f, 0.0f, -1.0f, 1.0f));
	frontMove = frontCam;
#endif
	right = vec3(rotation * vec4(1.0f, 0.0f,  0.0f, 1.0f));
	up    = vec3(vec4(0.0f, 1.0f,  0.0f, 1.0f));
}
Camera::Camera(vec3 position, float fov) : position(position), fov(fov), rotation(1.0f) {
	updateVectors();
}
mat4 Camera::getProjection() const {
	float aspect = (float)Window::width / (float)Window::height;
	return glm::perspective(fov, aspect, 0.15f, 1000.0f);
}
mat4 Camera::getView() const {
	return glm::lookAt(position, position + frontCam, up);
}
void Camera::rotate(float x, float y, float z) {
	//rotation = glm::rotate(rotation, z, vec3(0.0f, 0.0f, 1.0f));
	rotation = glm::rotate(rotation, y, vec3(0.0f, 1.0f, 0.0f));
	rotation = glm::rotate(rotation, x, vec3(1.0f, 0.0f, 0.0f));

	updateVectors();
}