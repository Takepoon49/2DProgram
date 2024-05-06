#pragma once

#include "../../../Object/Particle/ParticleBase.h"

class LightH : public ParticleBase
{
public:

	LightH();
	~LightH() {};

	void Init(std::shared_ptr<BaseObject> _pair, int _type);
	void Update();
	void Draw() override;



private:

	std::shared_ptr<BaseObject> m_pair;

	static const int m_ImgSizeX = 32;
	static const int m_ImgSizeY = 32;

};