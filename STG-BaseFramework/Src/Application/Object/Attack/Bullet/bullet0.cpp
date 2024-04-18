#include "../../../Scene/Scene.h"
#include "bullet0.h"

C_Bullet0::C_Bullet0()
{
	m_pTex = nullptr;

	m_AlphaRect = { 0, 0, 7, 19 };
	m_AddRect = { 7, 0, 7, 19 };

	m_flg = 0;
	
	m_pos = { 0.0f, 0.0f };
	m_move = { 0.0f, 0.0f };
	m_scale = { 1.0f, 1.0f };
	m_rad = { m_AlphaRect.width * m_scale.x / 2.0f,
				m_AlphaRect.height * m_scale.y / 2.0f };

	m_deg = 0.0f;

	m_mat.Init();

	m_color = C_GREEN;

	m_speed = { 0.0f, 27.0f };
}

C_Bullet0::~C_Bullet0()
{

}

void C_Bullet0::Init()
{

}

void C_Bullet0::Update()
{
	if (m_flg == 0) return;	// ‘ŠúƒŠƒ^[ƒ“

	// ‰æ–ÊŠO”»’è
	if (m_pos.y > scrTop || m_pos.y < scrBottom) { m_flg = 0; }

	m_pos += m_move;

	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.m = m_mat.Mix();
}

void C_Bullet0::Draw()
{
	if (m_flg == 0) return;

	DrawImg(m_mat.m, m_pTex, Math::Rectangle(m_AlphaRect.x, m_AlphaRect.y,
											 m_AlphaRect.width, m_AlphaRect.height), 1.0f);

	D3D.SetBlendState(BlendMode::Add);

	DrawImgEX(m_mat.m, m_pTex, Math::Rectangle(m_AddRect.x, m_AddRect.y,
												m_AddRect.width, m_AddRect.height), m_color);

	D3D.SetBlendState(BlendMode::Alpha);
}

void C_Bullet0::Shot(Math::Vector2 a_pos)
{
	m_pos = a_pos;
	
	m_move = m_speed;

	m_flg = 1;
}

void C_Bullet0::Hit()
{
	m_flg = 0;
}

const bool C_Bullet0::GetFlg()
{
	return m_flg;
}

const Math::Vector2 C_Bullet0::GetPos()
{
	return m_pos;
}

const Math::Vector2 C_Bullet0::GetRad()
{
	return m_rad;
}

const HitStruct C_Bullet0::GetObj()
{
	HitStruct obj;
	obj.pos = m_pos;
	obj.rad = m_rad;
	obj.flg = m_flg;

	return HitStruct(obj);
}
