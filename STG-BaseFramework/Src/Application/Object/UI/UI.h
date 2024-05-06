#pragma once

#include "../../utility.h"

class Scene;

class UI
{
public:

	UI() {};
	~UI() {};

	void Init();
	void Update();
	void Draw();
	void DrawStr();

	void SetTexture0(KdTexture* _pTex) { m_pTex0 = _pTex; }
	void SetPlayerTex(std::string _dir) { m_playerTex.Load(_dir); }
	void SetOwner(Scene* _pOwner) { m_pOwner = _pOwner; }

private:

	Scene* m_pOwner;

	KdTexture*	m_pTex0;

	char text[100] = "";
	
	// ���@�A�C�R���p
	KdTexture		m_playerTex;
	Math::Vector2	m_playerPos;
	MathSet			m_playerMat;

	// �c�@�̐��\��
	Math::Vector2 m_playerNumPos;

	// �ً}����Q�[�W
	float			m_moveVal;
	float			m_moveValMax;
	Math::Vector2	m_moveGagePos;
	Math::Vector2	m_moveGageSize;
	MathSet			m_moveFrameMat;
	MathSet			m_moveGageMat;
	Math::Color		m_moveFrameColor;
	Math::Color		m_moveGageColor;

};