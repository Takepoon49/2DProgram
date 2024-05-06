#pragma once

#include "../ParticleBase.h"

class Scene;

class Explosion : public ParticleBase
{
public:

	Explosion();
	~Explosion() override {};

	void Init(ParticleType _type, Math::Vector2 _pos);
	void Update() override;
	void Draw() override;

private:

	static const int m_ImgSizeX = 32;
	static const int m_ImgSizeY = 32;

	Math::Vector2	m_wsSize;
	MathSet			m_wsMat;
	Math::Rectangle	m_wsRect;
	float			m_wsAlpha;
};