#include <glm.hpp>
#include "mge/behaviours/OrbitBehaviour.hpp"
#include "mge/core/GameObject.hpp"

#define PI 3.141592653589f

OrbitBehaviour::OrbitBehaviour(sf::Window * pWindow, GameObject * pTarget)
{
	_window = pWindow;
	_target = pTarget;
	_distance = 6;
}

void OrbitBehaviour::update(float pStep)
{
	
	_owner->setTransform(Orbit(_target));

}

glm::mat4 OrbitBehaviour::Orbit(GameObject * pTarget)
{
	sf::Vector2f mouseDelta = (sf::Vector2f)_window->getSize() / 2.0f - (sf::Vector2f)sf::Mouse::getPosition();
	_mousePos += glm::vec2(mouseDelta.x * _yawRotSpeed, mouseDelta.y) / 300;
	_mousePos = glm::vec2(_mousePos.x, glm::clamp(_mousePos.y, _pitchRange.x * (PI / 180.f), _pitchRange.y * (PI / 180.f)));
	sf::Mouse::setPosition((sf::Vector2i)_window->getSize() / 2);

	glm::tmat4x4<float, glm::precision::highp> transform = glm::tmat4x4< float, glm::precision::highp>();

	transform = glm::rotate(transform, _mousePos.x, glm::tvec3<float, glm::precision::highp>(0, 1, 0));
	transform = glm::rotate(transform, _mousePos.y, glm::tvec3<float, glm::precision::highp>(1, 0, 0));
	transform = glm::translate(transform, glm::vec3(0, 0, _distance));

	return pTarget->getTransform() * transform;
}
