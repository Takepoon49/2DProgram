#include "H-Laser.h"

void HLaser::Init()
{
	for (int i = 0; i < MaxNum; i++)
	{
		m_pos[i] = {};
		m_deg[i] = 0.0f;
		m_mat[i].Init();
		m_color[i] = { 1.0f, 1.0f, 1.0f, 1.0f };
	}
	m_size = { 1.0f, 1.0f };
	m_rect = { 28, 0, 14, 14 };
	m_flg = 0;
}

void HLaser::Update(Math::Vector2 _pos)
{
	for (int i = 0; i < MaxNum; i++)
	{
		CalcMove(_pos, i);

		m_pos[i] += m_move[i];

		m_mat->s = Math::Matrix::CreateScale(m_size.x, m_size.y, 0.0f);
		m_mat->r = Math::Matrix::CreateRotationZ(DegToRad(m_deg[i]));
		m_mat->t = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0.0f);
		m_mat->Mix();
	}
}

void HLaser::Draw()
{
	if (!m_flg) return;

	for (int i = 0; i < MaxNum; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat[i].m);
		SHADER.m_spriteShader.DrawTex(m_pTex, 0, 0, &m_rect, &m_color[i]);
	}
}

void HLaser::CalcMove(Math::Vector2 _tpos, int _num)
{
	Math::Vector2 c_pos;
	c_pos.x = _tpos.x - m_pos[_num].x;
	c_pos.y = _tpos.y - m_pos[_num].y;
	float radian = atan2(c_pos.y, c_pos.x);

	m_move[_num].x = cos(radian) * 6.0f;
	m_move[_num].y = sin(radian) * 6.0f;
}

void HLaser::Release()
{

}
