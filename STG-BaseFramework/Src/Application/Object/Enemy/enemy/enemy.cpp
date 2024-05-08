#include "enemy.h"
#include "../../../Scene/Scene.h"
#include "../../../Object/Player/Player.h"

void Enemy::Init(int _flg, int _stime)
{
	m_objType = ObjType::Enemy;

	// 行動パターン決定
	m_movePtn = _flg;
	m_frame2 = 0;

	//m_shotTime = rand() % (2 * 30) + 30;
	m_shotTime = _stime;

	// ロックオン
	m_Lock.flg = false;
	m_Lock.frame = 0.0f;
	m_Lock.color = { 1.0f, 0.5f, 0.0f, 0.8f };
	m_Lock.mat.Init();
	m_Lock.rect = Math::Rectangle(100, 0, 70, 70);

	m_hp = 4;

	// 描画関連
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

	// 影
	m_shadow.pos = {};
	m_shadow.mat.Init();
	m_shadow.color = { 0.0f, 0.0f, 0.0f, 0.5f };
}

void Enemy::Update(Math::Vector2 ppos)
{
	//if (m_flg == st_dead) return;

	// 弾のフラグチェック＆削除
	//m_pOwner->DeleteBullet1();

	// 自機に向ける
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

	// UI更新
	if (m_Lock.flg > 0)
	{
		m_Lock.color = { 1.0f, 0.5f + fabs(sin(DegToRad(m_frame * 12.0f)))*0.5f, 0.0f, 0.8f };

		m_Lock.mat.s = Math::Matrix::CreateScale(0.90f, 0.90f, 0.00f);
		m_Lock.mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_frame));
		m_Lock.mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
		m_Lock.mat.Mix();
	}

	// 行動パターン通りに移動量を決定
	UpdateMovePattern();

	// 移動処理
	m_pos += m_move;

	// 画面外処理
	if (m_pos.x < scrLeft - 200.0f || m_pos.x > scrRight + 200.0f || 
		m_pos.y < scrBottom - 200.0f || m_pos.y > scrTop + 200.0f)
	{
		m_hp = 0;
	}

	// 生存中の処理
	if (m_hp >= 1 && (m_flg & BaseBitState::st_alive))
	{
		// 弾発射
		if (m_frame % m_shotTime == 0)
		{
			m_pOwner->CreateBullet1(m_pos, m_deg);
		}
	}

	// 死んだときの処理
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

	// 行列作成
	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	m_mat.r = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg + 90.0f));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.m = m_mat.s * m_mat.r * m_mat.t;

	// 影
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

	// 自機影描画
	SHADER.m_spriteShader.SetMatrix(m_shadow.mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_AlphaRect, &m_shadow.color);

	// 自機描画
	SHADER.m_spriteShader.SetMatrix(m_mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_AlphaRect, &m_color);

	// UI描画
	if (m_Lock.flg > 0)
	{
		SHADER.m_spriteShader.SetMatrix(m_Lock.mat.m);
		SHADER.m_spriteShader.DrawTex(m_pUITex, 0, 0, &m_Lock.rect, &m_Lock.color);
	}

	if (m_pOwner->GetDebugFlg())
	{
		// デバッグ
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
	case ep_stop:	// デバッグ用、動かないやつ
		m_move = { 0.0f, 0.0f };
		break;

	case ep_d1:	// 左右にsinカーブで移動
		m_frame2++;

		m_pos.x += cos(DirectX::XMConvertToRadians(m_frame2 * 1.5f)) * 6.0f;
		//m_pos.y += sin(DirectX::XMConvertToRadians(m_frame*1.5f)) * 2.0f;
		
		break;

	case ep_d2:	// ぐるぐる回る敵
		m_frame2++;

		//m_pos.x += cos(DirectX::XMConvertToRadians(m_frame2 * 1.5f)) * 3.0f;
		m_pos.y += sin(DirectX::XMConvertToRadians(m_frame2 * 1.5f)) * 6.0f;
		break;

	case ep_1:	// 下→左
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

	case ep_2:	// 下→右 
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

	case ep_3:	// 左から右
		m_move.x = 4.0f;
		/*if (m_pos.x > scrRight + 32.0f)
		{
			m_pos.x = scrLeft - 32.0f;
		}*/
		break;
		
	case ep_4:	// 右から左
		m_move.x = -4.0f;
		/*if (m_pos.x < scrLeft - 32.0f)
		{
			m_pos.x = scrRight + 32.0f;
		}*/
		break;

	case ep_5:	// 上から下に停止、その後下
		
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

	case ep_6:	// 左から右 ( 早め )
		m_move.x = 4.0f;
		m_move.y = -1.8f;
		break;

	case ep_7:	// 右から左 ( 早め )
		m_move.x = -4.0f;
		m_move.y = -1.8f;
		break;

	case ep_8:	// 左から右＋上から下
		m_move.x = 1.0f;
		m_move.y = -1.8f;
		break;

	case ep_9:	// 右から左＋上から下
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