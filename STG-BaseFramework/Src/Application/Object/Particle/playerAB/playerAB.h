#pragma once

#include "../ParticleBase.h"

class Scene;
class Player;

class PlayerAB : public ParticleBase
{
public:

	PlayerAB();
	~PlayerAB() override {};

	void Init();
	void Update() override;
	void Draw() override;

	void SetPlayer(std::shared_ptr<BaseObject> _pair) { m_player = _pair; }

private:

	std::shared_ptr<BaseObject> m_player;

	static const int m_ImgSizeX = 32;
	static const int m_ImgSizeY = 32;

	Math::Rectangle		m_shadowRect;

	//KdTexture*		m_pTex;

	//int				m_type;

	//Math::Vector2		m_nowAnim;
	//Math::Rectangle	m_rect;

	//int				m_flg;
	//int				m_frame;

	//Math::Vector2		m_pos;
	//Math::Vector2		m_move;
	//Math::Vector2		m_scale;
	//float				m_deg;
	//MathSet			m_mat;
	//Math::Color		m_color;

};