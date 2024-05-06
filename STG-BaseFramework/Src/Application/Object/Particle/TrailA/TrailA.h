#pragma once

#include "../../../Object/Particle/ParticleBase.h"

class TrailA : public ParticleBase
{
public:

	TrailA();
	~TrailA() {};

	void Init(Math::Vector2 _pos);
	void Update() override;
	void Draw() override;



private:

	std::shared_ptr<BaseObject> m_pair;

	static const int m_ImgSizeX = 32;
	static const int m_ImgSizeY = 32;

};