#ifndef OBIT_H
#define ORBIT_H

#include "SFML/Graphics.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"

class OrbitBehaviour : public AbstractBehaviour
{
	public:
		glm::vec2 _pitchRange = glm::vec2(-90.0f, 90.0f);
		float _yawRotSpeed = 1.0f;

		OrbitBehaviour(sf::Window * pWindow, GameObject * pTarget);

		virtual void update(float pStep);

	private:
		GameObject * _target;
		sf::Window * _window;

		glm::vec2 _mousePos;
		float _distance;

		glm::mat4 Orbit(GameObject * pTarget);

		OrbitBehaviour(const OrbitBehaviour&);
		OrbitBehaviour& operator=(const OrbitBehaviour&);
};

#endif //ORBIT_H
