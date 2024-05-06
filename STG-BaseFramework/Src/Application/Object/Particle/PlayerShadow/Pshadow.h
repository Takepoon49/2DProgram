#pragma once

#include "../ParticleBase.h"

class Player;

class PShadow : public ParticleBase
{
public:

	PShadow() {};
	~PShadow() {};

	void Init(std::shared_ptr<Player> _pair);
	void Update() override;
	void Draw() override;

private:

	std::shared_ptr<Player> m_pair;

	static const int	m_ImgSizeX = 128;
	static const int	m_ImgSizeY = 128;

};