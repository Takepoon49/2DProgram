#include "../../../Scene/Scene.h"
#include "bullet0.h"

C_Bullet0::C_Bullet0()
{
	m_AlphaRect = { 0, 0, 7, 19 };
	m_AddRect = { 7, 0, 7, 19 };

	m_flg = 0;
	
	m_pos = { 0.0f, 0.0f };
	m_move = { 0.0f, 0.0f };
	if (rand() % 2 == 0) m_scale = { 1.0f, 1.0f };
	else m_scale = { -1.0f, 1.0f };
	
	m_rad = { m_AlphaRect.width * m_scale.x / 2.0f,
				m_AlphaRect.height * m_scale.y / 2.0f };

	m_scale = { 1.0f, 1.0f };
	m_deg = 0.0f;

	m_mat.Init();

	m_color = C_GREEN;
	m_color = C_YELLOW;
	m_color = { 1.0f, 0.4f, 0.0f, 1.0f };
	m_color = { 0.0f, 0.8f, 0.8f, 1.0f };

	m_speed = { 0.0f, 24.0f };

	m_frame = 0;

	// �e
	m_shadow.pos = {};
	m_shadow.color = { 0.0f, 0.0f, 0.0f, 0.7f };
	m_shadow.mat.Init();
}

void C_Bullet0::Init()
{

}

void C_Bullet0::Update()
{
	switch (m_flg)
	{
	case 0:
		return;	//�������^�[��

	case 1:	// ���˂��ꂽ
		// ��ʊO����
		if (m_pos.y > scrTop || m_pos.y < scrBottom) { m_flg = 0; }
		break;
	case 2:
		m_move = m_emove;

		m_frame++;	// �J�E���g
		m_scale *= 1.15f;	// �g��

		if (m_frame < 2)
		{
			//�؂���͈͕ύX
			m_AlphaRect = { 0, 19, 14, 6 };
		}
		else
		{
			m_AlphaRect = { 14, 19, 14, 6 };
			m_scale = { 2.0f, 2.0f };
		}
		if (m_frame > 6)
		{
			m_flg = 0;
		}
		break;
	}

	m_pos += m_move;

	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.m = m_mat.Mix();

	// �e
	m_shadow.pos.x = m_pos.x + 16.0f;
	m_shadow.pos.y = m_pos.y - 32.0f;
	m_shadow.mat.s = Math::Matrix::CreateScale(m_scale.x * 0.8f, m_scale.y * 0.8f, 0.0f);
	m_shadow.mat.r = m_mat.r;
	m_shadow.mat.t = Math::Matrix::CreateTranslation(m_shadow.pos.x, m_shadow.pos.y, 0.0f);
	m_shadow.mat.Mix();
}

void C_Bullet0::Draw()
{
	switch (m_flg)
	{
	case 0:
		return;	// �������^�[��
	
	case 1:	// ���˒�
		DrawImg(m_mat.m, &m_tex, Math::Rectangle(m_AlphaRect.x, m_AlphaRect.y,
			m_AlphaRect.width, m_AlphaRect.height), 1.0f);

		D3D.SetBlendState(BlendMode::Add);

		DrawImgEX(m_mat.m, &m_tex, Math::Rectangle(m_AddRect.x, m_AddRect.y,
			m_AddRect.width, m_AddRect.height), m_color);

		D3D.SetBlendState(BlendMode::Alpha);
		break;

	case 2:	// ��������
		SHADER.m_spriteShader.SetMatrix(m_mat.m);
		SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_AlphaRect, &m_color);
		break;
	}

	// ���@�e
	DrawImgEX(m_shadow.mat.m, &m_tex, m_AlphaRect, m_shadow.color);
}

void C_Bullet0::Shot(Math::Vector2 a_pos)
{
	m_pos = a_pos;
	
	m_move = m_speed;

	m_flg = 1;

	m_emove = { Rnd() * 2.0f - 1.0f, -3.0f };
}