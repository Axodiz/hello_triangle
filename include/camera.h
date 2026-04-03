#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum direction{
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT
};

class Camera{
public:
	// constructor set position
	Camera(float xPos, float yPos, float zPos)
		: position(glm::vec3(xPos, yPos, zPos))
	{};

	// update camera front
	void update(double xPosMouse, double yPosMouse);
	// update camera position
	void move(enum direction dir, float deltaTime);
	// change noclip mode
	void changeMode() {noclip = !noclip;}
	
	// getters
	const glm::vec3 getPosition() const {return position;}
	const glm::vec3 getFront() const {return front;}
	const glm::vec3 getUp() const {return up;}
	const float getFov() const {return fov;}
private:
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	// angles of rotation;
	float pitch = 0.0f;
	float yaw = 90.0f;
	float roll = 0.0f;
	
	float speed = 2.5f;
	float fov = 45.0f;
	float lastX = 0.0f;
	float lastY = 0.0f;
	float sensitivity = 0.1f;

	bool firstMouse = true;
	bool noclip = true;
};

#endif
