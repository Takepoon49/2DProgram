#include "enemyA.h"

void EnemyA::Update()
{
	m_frame++;
	//if (m_frame > 90)
	//{
	//	m_move = { 0.0f, 0.0f };
	//	if (m_frame > 120)
	//	{
	//		if (m_pos.x > 0)
	//		{
	//			m_move = { +3.0f, -1.0f };
	//		}
	//		else
	//		{
	//			m_move = { -3.0f, -1.0f };
	//		}
	//	}
	//}

	if (m_pos.y < 0.0f)
	{
		if (m_pos.x > 0)
		{
			m_move = { +3.0f, -1.0f };
		}
		else
		{
			m_move = { -3.0f, -1.0f };
		}
	}

	m_pos += m_move;

	if (m_pos.y < scrBottom - m_rad.y)
	{
		m_flg = st_dead;
	}

	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.Mix();
}

void EnemyA::Init()
{
	m_tex.Load("Data/Texture/Enemy/enemy0.png");

	m_frame = 0;

	m_rect = { 0, 0, 115, 106 };

	m_hp = 2;
	m_flg = st_alive;
	m_pos = {};
	//m_pos = { Rnd() * 1280.0f - 640.0f, 0.0f + Rnd() * 200.0f };
	//m_pos = { rand() % (1280 - (int)m_rad.x*2) - (640 - m_rad.x), scrTop + m_rad.y };	// -640 + rad.x ` +640 - rad.x
	m_pos = { Rnd() * (640.0f - m_rad.x)*2 - (640 - m_rad.x), scrTop + m_rad.y};	// -640 + rad.x ` +640 - rad.x

	m_move = { 0.0f, -4.0f };
	m_scale = { 0.7f, 0.7f };
	m_rad = { m_rect.width * m_scale.x, m_rect.height * m_scale.y };
	m_rad /= 2.0f;
	m_deg = 0.0f;
	m_mat.Init();
	m_color = C_BLUE;
	m_color = { 0.8f, 0.5f, 0.5f, 1.0f };

	m_speed = {};
}

void EnemyA::ShootToPlayer(Math::Vector2 _pos)
{
	Math::Vector2 c_pos;
	c_pos.x = _pos.x - m_pos.x;
	c_pos.y = _pos.y - m_pos.y;
	float radian = atan2(c_pos.y, c_pos.x);

	m_move.x = cos(radian) * 3.0f;
	m_move.y = sin(radian) * 3.0f;
}

void EnemyA::SetTest()
{
	m_move = { 0.0f, 0.0f };
	m_pos = { Rnd() * 1280.0f + 64.0f - 640.0f - 64.0f, 300 };
}

void EnemyA::SetMove(int _moveType)
{
	switch (_moveType)
	{
	case 0:
		m_move = { 0.0f, 3.0f };	
		break;
	case 1:
		
		break;
	case 2:
		
		break;
	case 3:
		
		break;
	case 4:
		
		break;
	}
}

void EnemyA::Release()
{
	m_tex.Release();
}
