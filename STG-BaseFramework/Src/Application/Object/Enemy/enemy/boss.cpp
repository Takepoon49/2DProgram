#include "boss.h"
#include "../../../Scene/Scene.h"

Boss::Boss()
{

}

void Boss::Init()
{
	// ����
	m_rect = { 0, 128, 68, 92 };
	m_deg = 0.0f;
	m_scale = { 1.0f, 1.0f };

	m_flg = st_alive;
	m_pos = { 0.0f, 0.0f };
	m_move = { 0.0f, 0.0f };
	m_mat.Init();

	// ��������
	m_wingsRect = { 0, 128, 68, 92 };

	// ���̑��ϐ�
	m_nowAnim = { 0.0f, 0.0f };
	m_frame = 0;
	m_moveVec = Math::Vector2::Zero;
	m_rad = { 0.0f, 0.0f };

	m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void Boss::Update()
{
	SCENE.AddScore(1);
}

void Boss::Draw()
{

}
