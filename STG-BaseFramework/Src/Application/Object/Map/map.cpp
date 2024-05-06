#include "../../Scene/Scene.h"
#include "map.h"

void Map::Init()
{
	m_BackPos = { 0.0f, 0.0f };
	m_BackColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_Rect = { 0, 0, 1280, 720*2 };

	m_scale = { 1.0f, 1.0f };
	m_deg = 0.0f;

	m_mat.Init();

	m_nowTex = 0;

	// ÉâÅ[ÉW
	m_largePos = { 0.0f, 0.0f };
	m_lScale = { 2.0f, 2.0f };
	m_lMat.Init();
	m_lColor = { 0.8f, 0.8f, 1.0f, 1.0f };
	m_lColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	//m_lRect = { 0, 16*144, 640, 360 };
	m_lRect = { 0, 16*134*3, 640, 360 };
}

void Map::Update()
{
	//m_BackPos.y -= 6.0f;
	//if (m_BackPos.y < -360.0f) m_BackPos.y = 360.0f;

	//m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	//m_mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_deg));
	//m_mat.t = Math::Matrix::CreateTranslation(m_BackPos.x, m_BackPos.y, 0.0f);
	//m_mat.Mix();

	//m_lRect.x -= 1;
	m_lRect.y -= 1;

	m_lMat.s = Math::Matrix::CreateScale(m_lScale.x, m_lScale.y, 0.0f);
	m_lMat.r = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(0.0f));
	m_lMat.t = Math::Matrix::CreateTranslation(m_largePos.x, m_largePos.y, 0.0f);
	m_lMat.Mix();
}

void Map::Draw()
{
	//SHADER.m_spriteShader.SetMatrix(m_mat.m);
	//SHADER.m_spriteShader.DrawTex(m_pImgTex[m_nowTex], 0, 0, &m_Rect, &m_BackColor);

	SHADER.m_spriteShader.SetMatrix(m_lMat.m);
	SHADER.m_spriteShader.DrawTex(m_pLargeMapTex, 0, 0, &m_lRect, &m_lColor);

	//ResetMatrix();
	//SHADER.m_spriteShader.DrawCircle(m_BackPos.x, m_BackPos.y, 20, &Math::Color(1, 0, 0, 1));
}
