#include "../../Scene/Scene.h"
#include "map.h"

void C_Map::Init()
{
	m_BackPos = { 0.0f, 0.0f };
	m_BackColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_Rect = { 0, 0, 1280, 720*2 };

	m_scale = { 1.0f, 1.0f };
	m_deg = 0.0f;

	m_mat.Init();

	m_nowTex = 0;
}

void C_Map::Update()
{
	m_BackPos.y -= 2.5f;
	if (m_BackPos.y < -360.0f) m_BackPos.y = 360.0f;

	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_BackPos.x, m_BackPos.y, 0.0f);
	m_mat.Mix();
}

void C_Map::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat.m);
	SHADER.m_spriteShader.DrawTex(m_pImgTex[m_nowTex], 0, 0, &m_Rect, &m_BackColor);

	//ResetMatrix();
	//SHADER.m_spriteShader.DrawCircle(m_BackPos.x, m_BackPos.y, 20, &Math::Color(1, 0, 0, 1));
}
