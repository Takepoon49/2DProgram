#pragma once

#include "../BaseObject.h"

class Scene;

class ParticleBase : public BaseObject
{
public:
	ParticleBase();
	~ParticleBase() {};

	void Init(ParticleType _type, Math::Vector2 _pos);
	void Update() override;
	void Draw() override;

protected:

	void Release() override;

	ParticleType		m_type;

	int					m_life = 0;

	static const int	m_ImgSizeX = 64;
	static const int	m_ImgSizeY = 64;
};