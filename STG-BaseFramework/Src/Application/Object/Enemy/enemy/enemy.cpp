#include "enemy.h"
#include "../../../Scene/Scene.h"
#include "../../../Object/Player/Player.h"

void Enemy::Init(int _flg, int _stime)
{
	m_objType = ObjType::Enemy;

	// �s���p�^�[������
	m_movePtn = _flg;
	m_frame2 = 0;

	//m_shotTime = rand() % (2 * 30) + 30;
	m_shotTime = _stime;

	// ���b�N�I��
	m_Lock.flg = false;
	m_Lock.frame = 0.0f;
	m_Lock.color = { 1.0f, 0.5f, 0.0f, 0.8f };
	m_Lock.mat.Init();
	m_Lock.rect = Math::Rectangle(100, 0, 70, 70);

	m_hp = 4;

	// �`��֘A
	m_nowAnimX = 0;

	m_pos = { 200.0f, 100.0f };
	m_move = { 0.0f, 0.0f };

	switch(rand() % 3)
	{
	case 0:
		m_color = { 0.3f, 0.4f, 0.3f, 1.0f };
		break;
	case 1:
		m_color = { 0.7f, 0.7f, 0.7f, 1.0f };
		break;
	case 2:
		m_color = { 0.3f, 0.3f, 0.3f, 1.0f };
		break;
	}

	m_dColor = C_RED;
	m_deg = 180.0f + 90.0f;
	m_scale = { 0.65f, 0.65f };
	//m_rad = { m_ImgSizeX * m_scale.x, m_ImgSizeY * m_scale.y };
	m_rad = { m_AlphaRect.width * m_scale.x, m_AlphaRect.height * m_scale.y };
	m_rad /= 2.75f;

	m_flg = st_alive;
	m_frame = 0;

	// �e
	m_shadow.pos = {};
	m_shadow.mat.Init();
	m_shadow.color = { 0.0f, 0.0f, 0.0f, 0.5f };
}

void Enemy::Update(Math::Vector2 ppos)
{
	//if (m_flg == st_dead) return;

	// �e�̃t���O�`�F�b�N���폜
	//m_pOwner->DeleteBullet1();

	// ���@�Ɍ�����
	if (m_pOwner->GetPlayerHitFlg())
	{
		Math::Vector2 Cpos = {};
		Cpos.x = ppos.x - m_pos.x;
		Cpos.y = ppos.y - m_pos.y;

		float Cradian = atan2(Cpos.y, Cpos.x);
		m_deg = DirectX::XMConvertToDegrees(Cradian);
	}

	m_frame++;
	if (m_frame % 3 == 0)
	{
		m_nowAnimX++;
		if (m_nowAnimX > 1) m_nowAnimX = 0;

		m_AlphaRect = { 128 * m_nowAnimX, 0, 128, 128 };
		//m_AlphaRect = { 256 + 256 * m_nowAnimX, 0, 256, 128 };
	}

	// UI�X�V
	if (m_Lock.flg > 0)
	{
		m_Lock.color = { 1.0f, 0.5f + fabs(sin(DegToRad(m_frame * 12.0f)))*0.5f, 0.0f, 0.8f };

		m_Lock.mat.s = Math::Matrix::CreateScale(0.90f, 0.90f, 0.00f);
		m_Lock.mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_frame));
		m_Lock.mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
		m_Lock.mat.Mix();
	}

	// �s���p�^�[���ʂ�Ɉړ��ʂ�����
	UpdateMovePattern();

	// �ړ�����
	m_pos += m_move;

	// ��ʊO����
	if (m_pos.x < scrLeft - 200.0f || m_pos.x > scrRight + 200.0f || 
		m_pos.y < scrBottom - 200.0f || m_pos.y > scrTop + 200.0f)
	{
		m_hp = 0;
	}

	// �������̏���
	if (m_hp >= 1 && (m_flg & BaseBitState::st_alive))
	{
		// �e����
		if (m_frame % m_shotTime == 0)
		{
			m_pOwner->CreateBullet1(m_pos, m_deg);
		}
	}

	// ���񂾂Ƃ��̏���
	if (m_hp <= 0 && m_flg & BaseBitState::st_alive)
	{
		//m_flg = st_dead;
		//SetRndPos();
		//m_hp = 2;
		SCENE.CreateExplosionA(ParticleType::ExplosionA, m_pos);

		m_flg = BaseBitState::st_stat1;
		m_frame = 0;
	}

	if (m_flg & BaseBitState::st_stat1)
	{
		m_color.w -= 1.0f / (3 * 3);

		if (m_frame > 3 * 3)
		{
			m_flg = BaseBitState::st_dead;
			m_pOwner->m_score += 200;
		}
	}

	// �s��쐬
	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	m_mat.r = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg + 90.0f));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.m = m_mat.s * m_mat.r * m_mat.t;

	// �e
	m_shadow.pos.x = m_pos.x + 14.0f;
	m_shadow.pos.y = m_pos.y - 28.0f;
	m_shadow.mat.s = Math::Matrix::CreateScale(m_scale.x * 0.7f, m_scale.y * 0.7f, 0.0f);
	m_shadow.mat.r = m_mat.r;
	m_shadow.mat.t = Math::Matrix::CreateTranslation(m_shadow.pos.x, m_shadow.pos.y, 0.0f);
	m_shadow.mat.Mix();
}

void Enemy::Draw()
{
	if (m_flg == st_dead) return;

	// ���@�e�`��
	SHADER.m_spriteShader.SetMatrix(m_shadow.mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_AlphaRect, &m_shadow.color);

	// ���@�`��
	SHADER.m_spriteShader.SetMatrix(m_mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_AlphaRect, &m_color);

	// UI�`��
	if (m_Lock.flg > 0)
	{
		SHADER.m_spriteShader.SetMatrix(m_Lock.mat.m);
		SHADER.m_spriteShader.DrawTex(m_pUITex, 0, 0, &m_Lock.rect, &m_Lock.color);
	}

	if (m_pOwner->GetDebugFlg())
	{
		// �f�o�b�O
		ResetMatrix();
		m_dColor = C_RED;
		KdShaderManager::GetInstance().m_spriteShader.DrawBox
			(m_pos.x, m_pos.y, m_rad.x, m_rad.y, &m_dColor, false);
	}
}

void Enemy::UpdateMovePattern()
{	
	switch (m_movePtn)
	{
	case ep_stop:	// �f�o�b�O�p�A�����Ȃ����
		m_move = { 0.0f, 0.0f };
		break;

	case ep_d1:	// ���E��sin�J�[�u�ňړ�
		m_frame2++;

		m_pos.x += cos(DirectX::XMConvertToRadians(m_frame2 * 1.5f)) * 6.0f;
		//m_pos.y += sin(DirectX::XMConvertToRadians(m_frame*1.5f)) * 2.0f;
		
		break;

	case ep_d2:	// ���邮����G
		m_frame2++;

		//m_pos.x += cos(DirectX::XMConvertToRadians(m_frame2 * 1.5f)) * 3.0f;
		m_pos.y += sin(DirectX::XMConvertToRadians(m_frame2 * 1.5f)) * 6.0f;
		break;

	case ep_1:	// ������
		m_frame2++;
		if (m_frame <= 1)
		{
			m_move = { 0.0f, -3.0f };
		}
		if (m_frame == 50)
		{
			m_move = { -2.0f, -0.5f };
		}
		break;

	case ep_2:	// �����E 
		m_frame2++;
		if (m_frame <= 1)
		{
			m_move = { 0.0f, -3.0f };
		}
		if (m_frame == 80)
		{
			m_move = { +2.0f, -0.5f };
		}
		break;

	case ep_3:	// ������E
		m_move.x = 4.0f;
		/*if (m_pos.x > scrRight + 32.0f)
		{
			m_pos.x = scrLeft - 32.0f;
		}*/
		break;
		
	case ep_4:	// �E���獶
		m_move.x = -4.0f;
		/*if (m_pos.x < scrLeft - 32.0f)
		{
			m_pos.x = scrRight + 32.0f;
		}*/
		break;

	case ep_5:	// �ォ�牺�ɒ�~�A���̌㉺
		
		if (m_frame < 60)
		{
			m_move.y = -3.0f;
		}
		if (m_frame > 60 && m_frame < 60 * 4)
		{
			m_move.x = 0.0f;
			m_move.y = 0.0f;
		}
		else if (m_frame > 60 * 4)
		{
			m_move.y = -2.0f;
		}
		break;

	case ep_6:	// ������E ( ���� )
		m_move.x = 4.0f;
		m_move.y = -1.8f;
		break;

	case ep_7:	// �E���獶 ( ���� )
		m_move.x = -4.0f;
		m_move.y = -1.8f;
		break;

	case ep_8:	// ������E�{�ォ�牺
		m_move.x = 1.0f;
		m_move.y = -1.8f;
		break;

	case ep_9:	// �E���獶�{�ォ�牺
		m_move.x = -1.0f;
		m_move.y = -1.8f;
		break;

	case ep_10:

		break;

	default:
		break;
	}
}

void Enemy::SetRndPos()
{
	//m_pos = { Rnd() * (1280.0f + m_rad.x) - (640.0f - m_rad.x), 
	//			Rnd() * (360.0f + m_rad.y) - (360.0f - m_rad.y) };

	m_pos = { Rnd() * (1280.0f - m_rad.x) - (640.0f - m_rad.x), 
			Rnd() * (360.0f - m_rad.y) };

	m_flg = st_alive;
}