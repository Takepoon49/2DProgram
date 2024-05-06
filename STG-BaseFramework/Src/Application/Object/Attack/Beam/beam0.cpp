#include "../../../Scene/Scene.h"
#include "beam0.h"

C_Beam0::C_Beam0()
{
}

void C_Beam0::Init()
{
	for (int i = 0; i < MaxNum; i++)
	{
		m_pos[i] = { 0.0f, 0.0f };

		m_mat[i].s = Math::Matrix::Identity;
		m_mat[i].r = Math::Matrix::Identity;
		m_mat[i].t = Math::Matrix::Identity;
		m_mat[i].m = m_mat[i].s * m_mat[i].r * m_mat[i].t;
	}

	m_deg = 0.0f;
	m_size = { 1.3f, 1.3f };
	m_color = { 1.0f, 1.0f, 1.0f, 0.7f };
	m_color = { 0.77f, 0.46f, 1.0f, 1.0f };
}

void C_Beam0::Update(int aNum, float aDeg)
{
	if (aNum > MaxNum) aNum = MaxNum;

	m_deg = aDeg;

	for (int i = 0; i < aNum; i++)
	{
		m_pos[i].x = 0.0f + cos(DegToRad(m_deg)) * (i * 3.5f * m_size.x);
		m_pos[i].y = 0.0f + sin(DegToRad(m_deg)) * (i * 3.5f * m_size.y);

		m_mat[i].s = Math::Matrix::CreateScale(m_size.x, m_size.y, 0.0f);
		m_mat[i].r = Math::Matrix::CreateRotationZ(DegToRad(m_deg + 90));
		m_mat[i].t = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0.0f);
		m_mat[i].m = m_mat[i].s * m_mat[i].r * m_mat[i].t;
	}
}

void C_Beam0::Draw(int aNum)
{
	D3D.SetBlendState(BlendMode::Alpha);

	if (aNum > MaxNum) aNum = MaxNum;

	for (int i = 0; i < aNum; i++)
	{
		DrawImgEX(m_mat[i].m, m_pTex, Math::Rectangle(28, 0, 14, 14), m_color);
	}

	D3D.SetBlendState(BlendMode::Alpha);
}
