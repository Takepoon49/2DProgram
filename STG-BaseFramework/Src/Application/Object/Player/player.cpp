#include "../../Scene/Scene.h"
#include "player.h"

void Player::Init()
{
	// キーフラグ
	for (auto& i : keyFlg)
	{
		i = false;
	}

	// 追尾レーザー
	m_hLaser.Init();

	// 自機
	m_rect = {};
	m_ownAlphaRect = { 0, 0, 128, 128 };
	m_nowAnim = { 0.0f, 0.0f };

	m_flg	= false;
	m_pos	= { 0.0f, -200.0f };
	m_move	= { 0.0f, 0.0f };
	m_speed = { 7.5f, 7.5f };
	m_scale	= { 0.70f, 0.70f };
	m_scale	= { 0.70f, 0.70f };
	m_rad	= { m_ownAlphaRect.width * m_scale.x, m_ownAlphaRect.height * m_scale.y };
	m_rad	= { m_rad.x / 3.0f, m_rad.y / 2.5f };
	m_Hrad	= 15.0f;
	m_deg	= 0.0f;
	m_color	= { 0.15f, 0.95f, 0.15f, 1.0f };
	m_color	= { 0.70f, 0.70f, 0.70f, 1.0f };
	//m_color	= { 0.1f, 0.80f, 0.80f, 1.0f };

	// シーカー
	m_spos		= { 0.0f, 0.0f };
	m_sscale	= { 0.75f, 0.75f };
	m_sdeg		= 0.0f;
	m_sColor	= { 0.8f, 0.9f, 0.8f, 1.0f };
	m_seekerFlg = false;

	// ウェブ(A)
	m_webA.flg = false;
	m_webA.pos = {};
	m_webA.size = 0.0f;
	m_webA.sizeXAdd = 0.0f;
	m_webA.degAdd = 0.0f;
	m_webA.degMove = 0.0f;

	// ウェブ(B)
	m_webB.flg = false;
	m_webB.pos = {};
	m_webB.size = 0.0f;
	m_webB.sizeXAdd = 0.0f;
	m_webB.degAdd = 0.0f;
	m_webB.degMove = 0.0f;

	// 弾
	m_shootTime = 0;
	m_shootFlg = 0;

	// デバッグ
	m_DebugColor = C_GREEN;
}

void Player::CheckVec()
{
	// ロックオン
	m_pLockIt = m_pLockList.begin();
	while (m_pLockIt != m_pLockList.end())
	{
		const bool bAlive = (*m_pLockIt)->bActive;
		if (!bAlive)
		{
			delete (*m_pLockIt);
			m_pLockIt = m_pLockList.erase(m_pLockIt);
		}
		else
		{
			m_pLockIt++;
		}
	}

	// 弾
	std::vector<C_Bullet0*>::iterator _it;
	_it = m_bulletList.begin();	// 可変長配列の先頭アドレスを格納
	while (_it != m_bulletList.end())
	{
		const int bAlive = (*_it)->GetFlg();
		if (bAlive == 0)
		{
			delete (*_it);
			_it = m_bulletList.erase(_it);	// 箱を削除して削除する箱の次のアドレスをイテレーターに格納
		}
		else
		{
			_it++;
		}
	}
}

void Player::Update()
{
	m_frame++;
	if (m_frame >= 360) m_frame = 0;

	m_DebugColor = { 1.0f, 0.5f + (fabs(sin(DirectX::XMConvertToRadians(m_frame * 7)))) * 0.5f, 0.0f, 0.8f };
	//m_DebugColor = { 1.0f, 0.0f, 0.6f + (fabs(sin(DirectX::XMConvertToRadians(m_frame * 15)))) * 0.4f, 0.6f };
	//m_DebugColor = { sin(DegToRad(m_frame * 6)), sin(DegToRad(180 + m_frame * 6)), 1.0f, 0.8f};
	//m_DebugColor = { sin(DegToRad(m_frame * 5)), sin(DegToRad(180 + m_frame * 5)), 1.0f, 1.0f};
	//m_DebugColor = { 0.0f, 1.0f, 1.0f, 1.0f };

	m_move = { 0.0f, 0.0f };

	UpdateAttack();

	// 移動入力
	if (GetKey(VK_UP)) m_move.y = +m_speed.y;

	if (GetKey(VK_DOWN)) m_move.y = -m_speed.y;

	if (GetKey(VK_LEFT))
	{
		if (m_webB.size >= 100)
		{
			if (m_webB.degAdd < 35.0f) m_webB.degAdd += 1.5f;
		}

		m_move.x = -m_speed.x;			// 移動量：左

		m_nowAnim.x = 8.0f;				// 傾き：左
	}
	else if (GetKey(VK_RIGHT))
	{
		if (m_webB.size >= 100)
		{
			if (m_webB.degAdd > -35.0f) m_webB.degAdd -= 1.5f;
		}

		m_move.x = +m_speed.x;			// 移動量：右
		
		m_nowAnim.x = 1.0f;				// 傾き : 右
	}
	else if (GetKey('G'))
	{
		if (m_frame % 2 == 0)
		{
			m_nowAnim.x += 2.0f;
			if (m_nowAnim.x > 8.0f) m_nowAnim.x = 0.0f;
		}
	}
	else
	{
		m_nowAnim.x = 0;			// 傾き：なし
		//m_ownAlphaRect.x = 0;
	}

	// 端判定
	if (m_pos.x + m_move.x > scrRight - m_rad.x || m_pos.x + m_move.x < scrLeft + m_rad.x) m_move.x = 0;
	if (m_pos.y + m_move.y > scrTop - m_rad.y || m_pos.y + m_move.y < scrBottom + m_rad.y) m_move.y = 0;
	
	// 移動量合成
	m_pos += m_move;

	// ウェブ更新
	// A
	m_webA.degMove = m_frame * 1.25f;
	if (m_webA.degMove >= 360.0f) m_webA.degMove -= 360.0f;
	m_webA.pos = m_pos;

	// B
	m_webB.degMove = m_frame * 1.25f;
	if (m_webB.degMove >= 360.0f) m_webB.degMove -= 360.0f;
	m_webB.pos = { m_pos.x + cos(DegToRad(90 + m_webB.degAdd))* m_webB.size * 2.25f,
					m_pos.y + sin(DegToRad(90 + m_webB.degAdd)) * m_webB.size* 2.25f };

	//								 size() : 現在の配列要素数
	for (UINT b = 0; b < m_bulletList.size(); b++)
	{
		m_bulletList[b]->Update();
	}

	// シーカー
	//UpdateSeeker();

	// 行列作成
	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.m = m_mat.s * m_mat.r * m_mat.t;

	CheckVec();
}

void Player::Draw()
{
	//行列の初期化 (図形描画の前に書く)
	SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixIdentity());

	// 拡散型
	DrawWebA();

	// 集中型
	DrawWebB();

	// 集中型の当たり判定表示(仮)
	//SHADER.m_spriteShader.DrawBox(m_pos.x, m_pos.y + m_webB.size, m_webB.size + m_webB.sizeXAdd, m_webB.size, &Math::Color(1.0f, 0.0f, 0.0f, 0.3f), true);

	// 自機
	DrawImgEX(m_mat.m, &m_tex, Math::Rectangle(
		m_ownAlphaRect.width * m_nowAnim.x, m_ownAlphaRect.height * m_nowAnim.y,
		m_ownAlphaRect.width,				m_ownAlphaRect.height					), m_color);

	// シーカー
	//DrawSeeker();

	// 弾
	for (UINT b = 0; b < m_bulletList.size(); b++)
	{
		m_bulletList[b]->Draw();
	}

	// === 以下デバッグ ==============
	
	// 自機当たり判定
	if (m_pOwner->GetDebugFlg())
	{
		ResetMatrix();
		//m_DebugColor = C_RED;
		DrawMaru(m_pos.x, m_pos.y, m_rad.x, &m_DebugColor, false);
		DrawMaru(m_pos.x, m_pos.y, m_Hrad, &m_DebugColor, false);
		SHADER.m_spriteShader.DrawBox((int)m_pos.x, (int)m_pos.y, (int)m_rad.x, (int)m_rad.y, &m_DebugColor, false);
	}
}

void Player::DrawWebA()
{
	float a = 0.0f, b = 0.0f, deg = 0.0f;
	float aNext = 0.0f, bNext = 0.0f, degNext = 0.0f;

	float a2[2] = {};
	float b2[2] = {};

	float gapDeg = 360.0f / 8.0f;

	for (deg = 0; deg < 360; deg += gapDeg)
	{
		a = cos(DegToRad(deg + m_webA.degMove)) * (m_webA.size);
		b = sin(DegToRad(deg + m_webA.degMove)) * (m_webA.size / 4.0f);

		degNext = deg + gapDeg;
		aNext = cos(DegToRad(degNext + m_webA.degMove)) * (m_webA.size);
		bNext = sin(DegToRad(degNext + m_webA.degMove)) * (m_webA.size / 4.0f);

		SHADER.m_spriteShader.DrawLine(m_webA.pos.x + a, m_webA.pos.y + b,
			m_webA.pos.x + aNext, m_webA.pos.y + bNext, &m_DebugColor);

		if (deg < 180*2)
		{
			SHADER.m_spriteShader.DrawLine(m_webA.pos.x + a, m_webA.pos.y + b,
				m_webA.pos.x + a, m_webA.pos.y + b + 30, &m_DebugColor);
		}

		if (deg == 0.0f)
		{
			a2[0] = a;
			b2[0] = b;
		}
		if (deg == 180.0f)
		{
			a2[1] = a;
			b2[1] = b;
		}
	}
	
	for (int i = 0; i < 2; i++)
	{
		SHADER.m_spriteShader.DrawCircle(m_webA.pos.x + a2[i], m_webA.pos.y + b2[i], 10, &m_DebugColor, false);
	}

	SHADER.m_spriteShader.DrawLine(m_webA.pos.x + a2[0], m_webA.pos.y + b2[0],
									m_webA.pos.x + a2[1], m_webA.pos.y + b2[1], &m_DebugColor);	

	float size2 = (a2[0]);

	for (deg = 0; deg < 360; deg += gapDeg)
	{
		//a = cos(DegToRad(deg + m_webA.degMove)) * fabs(a2[0] - m_webA.pos.x);
		//b = sin(DegToRad(deg + m_webA.degMove)) * fabs(a2[0] - m_webA.pos.x);

		a = cos(DegToRad(deg)) * size2;
		b = sin(DegToRad(deg)) * m_webA.size;

		degNext = deg + gapDeg;
		aNext = cos(DegToRad(degNext)) * size2;
		bNext = sin(DegToRad(degNext)) * m_webA.size;

		SHADER.m_spriteShader.DrawLine(m_webA.pos.x + a, m_webA.pos.y + b,
			m_webA.pos.x + aNext, m_webA.pos.y + bNext, &m_DebugColor);
	}
}

void Player::DrawWebB()
{
	float a = 0.0f , b = 0.0f, deg = 0.0f;
	float aNext = 0.0f, bNext = 0.0f, degNext = 0.0f;
	float gapDeg = 360.0f / 8.0f;	// ←８角形

	for (deg = 0; deg < 360; deg += gapDeg)	// ←８回ループ
	{
		// 現在の頂点
		a = cos(DegToRad(deg + m_webB.degMove)) * (m_webB.size + m_webB.sizeXAdd*2.0f);
		b = sin(DegToRad(deg + m_webB.degMove)) * (m_webB.size/2.0f);

		degNext = deg + gapDeg;	// 次の頂点を計算
		aNext = cos(DegToRad(degNext + m_webB.degMove)) * (m_webB.size + m_webB.sizeXAdd*2.0f);
		bNext = sin(DegToRad(degNext + m_webB.degMove)) * (m_webB.size/2.0f);

		SHADER.m_spriteShader.DrawLine(m_webB.pos.x + a, m_webB.pos.y + b, 
										m_webB.pos.x + aNext, m_webB.pos.y + bNext, &m_DebugColor);

		//if ((int)deg % 45 == 0)
		{
			SHADER.m_spriteShader.DrawLine(m_pos.x, m_pos.y, m_webB.pos.x + a, m_webB.pos.y + b, &m_DebugColor);
		}
	}
}

void Player::UpdateSeeker()
{
	m_spos.x = m_pos.x;
	m_spos.y = m_pos.y + 300.0f;

	m_seekerMat.s = Math::Matrix::CreateScale(m_sscale.x, m_sscale.y, 0.0f);
	m_seekerMat.r = Math::Matrix::CreateRotationZ(DegToRad(m_sdeg));
	m_seekerMat.t = Math::Matrix::CreateTranslation(m_spos.x, m_spos.y, 0.0f);
	m_seekerMat.m = m_seekerMat.s * m_seekerMat.r * m_seekerMat.t;
}

void Player::DrawSeeker()
{
	DrawImgEX(m_seekerMat.m, &m_tex, Math::Rectangle(m_SImgPosX, m_SImgPosY, m_SImgSizeX, m_SImgSizeY), m_sColor);
}

void Player::UpdateAttack()
{
	// 通常ショット
	if (GetKey('Z'))
	{
		if (m_shootFlg == 0)
		{
			m_shootFlg = 1;
		}
	}

	// ２連ショット
	if (GetKey(VK_SHIFT))
	{
		if (m_shootFlg == 0)
		{
			m_shootFlg = 2;
		}
	}

	// ３連ショット
	if (GetKey('A'))
	{
		if (m_shootFlg == 0)
		{
			m_shootFlg = 3;
		}
	}

	// 弾作成
	switch (m_shootFlg)
	{
	case 1:	// １列
		if (m_shootTime % 3 == 0 && m_shootTime < 3*3)
		{
			CreateBullet(m_pos.x, m_pos.y);
		}
		m_shootTime++;
		if (m_shootTime >= 3*6)
		{
			m_shootFlg = 0;
			m_shootTime = 0;
		}
		break;
	case 2:	// ２列
		if (m_shootTime % 3 == 0 && m_shootTime < 3 * 3)
		{
			CreateBullet(m_pos.x - 12.0f, m_pos.y);
			CreateBullet(m_pos.x + 12.0f, m_pos.y);
		}
		m_shootTime++;
		if (m_shootTime >= 3 * 6)
		{
			m_shootFlg = 0;
			m_shootTime = 0;
		}
		break;
	case 3:	// ２列
		if (m_shootTime % 3 == 0 && m_shootTime < 3 * 3)
		{
			CreateBullet(m_pos.x +  0.0f, m_pos.y + 6.0f);
			CreateBullet(m_pos.x - 14.0f, m_pos.y);
			CreateBullet(m_pos.x + 14.0f, m_pos.y);
		}
		m_shootTime++;
		if (m_shootTime >= 3 * 6)
		{
			m_shootFlg = 0;
			m_shootTime = 0;
		}
		break;
	}

	// ウェブ展開
	// 拡散型
	if (GetKey('X'))
	{
		if (m_webA.size <= 300.0f)
		{
			m_webA.size += 12.0f;
		}
	}
	else
	{
		if (m_webA.size > 0.0f)
		{
			m_webA.size -= 18.0f;

		}
		else
		{
			m_webA.size = 0.0f;
		}
	}
	// 集中型
	if (GetKey('C'))
	{
		if (m_webB.size <= 250.0f) m_webB.size += 5.0f;
		//if (m_webB.size <= 150.0f) m_webB.size += 5.0f;
		
		if (m_webB.size >= 250.0f)
		//if (m_webB.size >= 150.0f)
		{
			if (m_webB.sizeXAdd <= 135.0f)
			{
				m_webB.sizeXAdd += 5.0f;
			}
		}
	}
	else
	{
		if (m_webB.size > 0.0f)
		{
			m_webB.size -= 18.0f;
			m_webB.sizeXAdd = 0.0f;
		}
		else
		{
			m_webB.size = 0.0f;
			m_webB.sizeXAdd = 0.0f;
			m_webB.degAdd = 0;
		}
	}

	if (m_webB.size <= 0.0f)
	{
		m_webB.flg = false;
	}
	else
	{
		m_webB.flg = true;
	}
}

void Player::CreateBullet(Math::Vector2 a_pos)
{
	C_Bullet0* tempBullet = new C_Bullet0();
	tempBullet->Init();
	tempBullet->SetTexture(m_pBullet0Tex);
	tempBullet->Shot(a_pos);
	m_bulletList.push_back(tempBullet);
}

void Player::CreateBullet(float _x, float _y)
{
	C_Bullet0* tempBullet = new C_Bullet0();
	tempBullet->Init();
	tempBullet->SetTexture(m_pBullet0Tex);
	tempBullet->Shot({_x, _y});
	m_bulletList.push_back(tempBullet);
}

HitStruct Player::GetObj()
{
	HitStruct objTemp;

	objTemp.pos = m_pos;
	objTemp.rad = m_rad;
	objTemp.flg = m_flg;

	return objTemp;
}

HitStruct Player::GetSeekObj()
{
	HitStruct tempObj;
	tempObj.pos = m_spos;
	tempObj.rad = { m_SImgSizeX * m_sscale.x, m_SImgSizeY * m_sscale.y };
	tempObj.flg = m_seekerFlg;

	return tempObj;
}

HitStruct Player::GetWebBObj()
{
	HitStruct obj;
	obj.pos = { m_pos.x, m_pos.y + m_webB.size };
	obj.rad = { m_webB.size + m_webB.sizeXAdd, m_webB.size };
	obj.flg = m_webB.flg;

	return HitStruct(obj);
}
