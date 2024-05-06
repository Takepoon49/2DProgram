#pragma once

#include "../../../Object/Particle/ParticleBase.h"

class HLTrail : public ParticleBase
{
public:
	HLTrail();
	~HLTrail() {};

	void Init(Math::Vector2 _pos, float _deg, Math::Color _color);
	void Update() override;
	void Draw() override;

private:

	float	m_radian = 0.0f;
	float	m_speed = 0.0f;

	int		m_life = 16.0f;

	//ParticleType		m_type;

	static const int	m_ImgSizeX = 14;
	static const int	m_ImgSizeY = 14;

	Math::Rectangle		m_alphaRect;

};