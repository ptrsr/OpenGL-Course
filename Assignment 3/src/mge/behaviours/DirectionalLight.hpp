#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "mge\behaviours\AbstractBehaviour.hpp"

class DirectionalLight : public AbstractBehaviour
{
public:
	DirectionalLight();
	~DirectionalLight();

	virtual void update(float pStep);

protected:
private:

};

#endif // !DIRECTIONALLIGHT_H