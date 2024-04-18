#include "../../Scene/Scene.h"
#include "map.h"

void C_Map::Init()
{
	m_BackPos = { 0.0f, 0.0f };
	m_BackColor = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void C_Map::Update()
{
	m_BackMatrix = Math::Matrix::CreateTranslation(m_BackPos.x, m_BackPos.y, 0.0f);
}

void C_Map::Draw()
{
	DrawImgEX(m_BackMatrix, m_pImg0Tex, Math::Rectangle(0, 0, 1280, 720), m_BackColor);
}
