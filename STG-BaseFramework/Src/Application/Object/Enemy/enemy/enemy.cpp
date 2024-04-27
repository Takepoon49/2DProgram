#include "../../../Scene/Scene.h"
#include "enemy.h"

void C_Enemy::Init()
{
	// ロックオン
	m_Lock.flg = false;
	m_Lock.frame = 0.0f;
	m_Lock.color = { 1.0f, 0.5f, 0.0f, 0.8f };
	m_Lock.mat.Init();
	m_Lock.rect = Math::Rectangle(100, 0, 70, 70);

	m_hp = 2;

	m_pos = { 200.0f, 100.0f };
	m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_color = { 0.8f, 0.5f, 0.5f, 1.0f };
	m_dColor = C_RED;
	m_deg = 0.0f;
	m_scale = { 0.7f, 0.7f };
	//m_rad = { m_ImgSizeX * m_scale.x, m_ImgSizeY * m_scale.y };
	m_rad = { m_AlphaRect.width * m_scale.x, m_AlphaRect.height * m_scale.y };
	m_rad /= 2.75f;

	m_flg = st_alive;
	m_frame = 0;
}

void C_Enemy::Update(Math::Vector2 ppos)
{
	// 弾のフラグチェック＆削除
	DeleteBullet1();

	Math::Vector2 Cpos = {};
	Cpos.x = ppos.x - m_pos.x;
	Cpos.y = ppos.y - m_pos.y;

	float Cradian = atan2(Cpos.y, Cpos.x);
	m_deg = DirectX::XMConvertToDegrees(Cradian);

	m_frame++;
	if (m_frame >= 360) m_frame = 0;

	// UI更新
	if (m_Lock.flg)
	{
		m_Lock.color = { 1.0f, 0.5f + fabs(sin(DegToRad(m_frame * 12.0f)))*0.5f, 0.0f, 0.8f };

		m_Lock.mat.s = Math::Matrix::CreateScale(0.90f, 0.90f, 0.00f);
		m_Lock.mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_frame));
		m_Lock.mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
		m_Lock.mat.Mix();
	}

	if (m_hp <= 0)
	{
		//m_flg = st_dead;
		SetRndPos();
		m_hp = 2;
	}

	switch (m_flg)
	{
	case BaseBitState::st_dead:
		//m_scale = { 0.1f, 0.1f };
		//return;
		break;
	case BaseBitState::st_alive:

		break;
	case BaseBitState::st_stat1:
		m_deg = -30.0f;
		break;
	}

	// 弾発射
	if (m_frame % 30 == 0)
	{
		CreateBullet1();
	}
	// 弾更新
	for (auto& obj : m_bulletList)
	{
		obj->Update();
	}

	// 行列作成
	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	//m_mat.r = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	m_mat.r = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg + 90.0f));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.m = m_mat.s * m_mat.r * m_mat.t;
}

void C_Enemy::Draw()
{
	if (m_flg == st_dead) return;

	// 自機描画
	SHADER.m_spriteShader.SetMatrix(m_mat.m);
	SHADER.m_spriteShader.DrawTex(m_pTex, 0, 0, &m_AlphaRect, &m_color);

	// UI描画
	if (m_Lock.flg)
	{
		SHADER.m_spriteShader.SetMatrix(m_Lock.mat.m);
		SHADER.m_spriteShader.DrawTex(m_pUITex, 0, 0, &m_Lock.rect, &m_Lock.color);
	}

	// 弾更新
	for (auto& obj : m_bulletList)
	{
		obj->Draw();
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

void C_Enemy::SetRndPos()
{
	//m_pos = { Rnd() * (1280.0f + m_rad.x) - (640.0f - m_rad.x), 
	//			Rnd() * (360.0f + m_rad.y) - (360.0f - m_rad.y) };

	m_pos = { Rnd() * (1280.0f - m_rad.x) - (640.0f - m_rad.x), 
			Rnd() * (360.0f - m_rad.y) };

	m_flg = st_alive;
}

void C_Enemy::DeleteBullet1()
{
	m_bulletIt = m_bulletList.begin();	// 可変長配列の先頭アドレスを格納
	while (m_bulletIt != m_bulletList.end())
	{
		const int bAlive = (*m_bulletIt)->GetFlg();
		if (bAlive == 0)
		{
			delete (*m_bulletIt);
			m_bulletIt = m_bulletList.erase(m_bulletIt);	// 箱を削除して削除する箱の次のアドレスをイテレーターに格納
		}
		else
		{
			m_bulletIt++;
		}
	}
}

void C_Enemy::CreateBullet1()
{
	Bullet1* temp = new Bullet1();
	temp->Init();
	temp->SetTexture(m_pBullet1Tex);
	temp->SetOwner(m_pOwner);
	temp->Shot(m_pos, m_deg, 1);
	m_bulletList.push_back(temp);
}

void C_Enemy::CreateExplosion()
{
	Explosion* temp = new Explosion();
	temp->Init(0, m_pos);
	temp->SetTexture(m_pParticleTex);
	temp->SetOwner(m_pOwner);
}

void C_Enemy::DeleteExplosion()
{

}

HitStruct C_Enemy::GetObj()
{
	HitStruct objTemp;
	objTemp.pos = m_pos;
	objTemp.rad = m_rad;
	objTemp.flg = m_flg;
	return objTemp;
}
