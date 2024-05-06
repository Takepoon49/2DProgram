#include "../../Scene/Scene.h"
#include "item.h"

void C_Item::Init()
{
	m_pos = { 0.0f, 0.0f };
	m_move = { 0.0f, 0.0f };
	m_rad = 0.0f;
	m_color = { 1.0f, 1.0f, 1.0f, 1.0f };

	m_rect = { 0, 0, 0, 0 };

	m_flg = BaseBitState::st_dead;
}

void C_Item::Update()
{
	if (m_flg == BaseBitState::st_dead) return;

	m_pos += m_move;

	if (m_pos.y < scrBottom - m_rad) m_flg = BaseBitState::st_dead;

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
}

void C_Item::Draw()
{
	if (m_flg == BaseBitState::st_dead) return;

	DrawImgEX(m_mat, m_pTex, m_rect, m_color);
}

void C_Item::Drop(Math::Vector2 a_pos, bool type)
{
	switch (type)
	{
	case 0:	// powerUp
		m_rad = 20.0f;
		m_rect = { 0, 0, 32, 32 };
		break;
	
	case 1:	// score
		m_rad = 15.0f;
		m_rect = { 0, 0, 32, 32 };
		break;
	}

	m_pos = a_pos;
	m_move = { 0.0f, -6.0f };
	m_flg = 1;
}

void C_Item::SetFlg(UINT a_alive)
{
	m_flg = a_alive;
}

HitStruct C_Item::GetObj()
{
	HitStruct objTemp;	

	objTemp.pos = m_pos;
	objTemp.rad = { m_rad, m_rad };
	objTemp.flg = m_flg;

	return objTemp;
}
