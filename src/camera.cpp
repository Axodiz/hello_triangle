#include "camera.h"

void Camera::update(double xPosMouse, double yPosMouse)
{
	// get mouse position
	float xPos = (float)xPosMouse;
	float yPos = (float)yPosMouse;

	if(firstMouse){
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = yPos - lastY;
	lastX = xPos;
	lastY = yPos;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;

	front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	front.y = glm::sin(glm::radians(pitch));
	front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	front = glm::normalize(front);
}

void Camera::move(enum direction dir, float deltaTime){
	switch(dir){
	case FORWARD:
		if(noclip)
			position += speed * deltaTime * glm::vec3(front.x, 0.0f, front.z);
		else
			position += speed * deltaTime * front;
		break;
	case BACKWARD:
		if(noclip)
			position -= speed * deltaTime * glm::vec3(front.x, 0.0f, front.z);
		else
			position -= speed * deltaTime * front;
		break;
	case RIGHT:
		position += speed * deltaTime * glm::normalize(glm::cross(up, front));
		break;
	case LEFT:
		position -= speed * deltaTime * glm::normalize(glm::cross(up, front));
		break;
	default:
		break;
	}
}
