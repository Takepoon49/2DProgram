#pragma once

#include "../../../Object/Particle/ParticleBase.h"

class ShockWave : public ParticleBase
{
public:

	ShockWave();
	~ShockWave() {};

	void Init(Math::Vector2 _pos);
	void Update() override;
	void Draw() override;

private:

	Math::Rectangle m_rect2;
	MathSet m_mat2;

	//static const int m_smokeMax = 40;

	//struct st_smoke
	//{
	//	Math::Vector2	pos;
	//	Math::Vector2	move;
	//	MathSet			mat;
	//	float			scale;
	//	float			alpha;
	//}m_smoke[m_smokeMax];
};