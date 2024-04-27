#include "../../Scene/Scene.h"
#include "player.h"

void Player::Init()
{
	// �L�[�t���O
	for (auto& i : keyFlg)
	{
		i = false;
	}

	// �ǔ����[�U�[
	m_hLaser.Init();

	// ���@
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

	// �V�[�J�[
	m_spos		= { 0.0f, 0.0f };
	m_sscale	= { 0.75f, 0.75f };
	m_sdeg		= 0.0f;
	m_sColor	= { 0.8f, 0.9f, 0.8f, 1.0f };
	m_seekerFlg = false;

	// �E�F�u(A)
	m_webA.flg = false;
	m_webA.pos = {};
	m_webA.size = 0.0f;
	m_webA.sizeXAdd = 0.0f;
	m_webA.degAdd = 0.0f;
	m_webA.degMove = 0.0f;

	// �E�F�u(B)
	m_webB.flg = false;
	m_webB.pos = {};
	m_webB.size = 0.0f;
	m_webB.sizeXAdd = 0.0f;
	m_webB.degAdd = 0.0f;
	m_webB.degMove = 0.0f;

	// �e
	m_shootTime = 0;
	m_shootFlg = 0;

	// �f�o�b�O
	m_DebugColor = C_GREEN;
}

void Player::CheckVec()
{
	// ���b�N�I��
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

	// �e
	std::vector<C_Bullet0*>::iterator _it;
	_it = m_bulletList.begin();	// �ϒ��z��̐擪�A�h���X���i�[
	while (_it != m_bulletList.end())
	{
		const int bAlive = (*_it)->GetFlg();
		if (bAlive == 0)
		{
			delete (*_it);
			_it = m_bulletList.erase(_it);	// �����폜���č폜���锠�̎��̃A�h���X���C�e���[�^�[�Ɋi�[
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

	// �ړ�����
	if (GetKey(VK_UP)) m_move.y = +m_speed.y;

	if (GetKey(VK_DOWN)) m_move.y = -m_speed.y;

	if (GetKey(VK_LEFT))
	{
		if (m_webB.size >= 100)
		{
			if (m_webB.degAdd < 35.0f) m_webB.degAdd += 1.5f;
		}

		m_move.x = -m_speed.x;			// �ړ��ʁF��

		m_nowAnim.x = 8.0f;				// �X���F��
	}
	else if (GetKey(VK_RIGHT))
	{
		if (m_webB.size >= 100)
		{
			if (m_webB.degAdd > -35.0f) m_webB.degAdd -= 1.5f;
		}

		m_move.x = +m_speed.x;			// �ړ��ʁF�E
		
		m_nowAnim.x = 1.0f;				// �X�� : �E
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
		m_nowAnim.x = 0;			// �X���F�Ȃ�
		//m_ownAlphaRect.x = 0;
	}

	// �[����
	if (m_pos.x + m_move.x > scrRight - m_rad.x || m_pos.x + m_move.x < scrLeft + m_rad.x) m_move.x = 0;
	if (m_pos.y + m_move.y > scrTop - m_rad.y || m_pos.y + m_move.y < scrBottom + m_rad.y) m_move.y = 0;
	
	// �ړ��ʍ���
	m_pos += m_move;

	// �E�F�u�X�V
	// A
	m_webA.degMove = m_frame * 1.25f;
	if (m_webA.degMove >= 360.0f) m_webA.degMove -= 360.0f;
	m_webA.pos = m_pos;

	// B
	m_webB.degMove = m_frame * 1.25f;
	if (m_webB.degMove >= 360.0f) m_webB.degMove -= 360.0f;
	m_webB.pos = { m_pos.x + cos(DegToRad(90 + m_webB.degAdd))* m_webB.size * 2.25f,
					m_pos.y + sin(DegToRad(90 + m_webB.degAdd)) * m_webB.size* 2.25f };

	//								 size() : ���݂̔z��v�f��
	for (UINT b = 0; b < m_bulletList.size(); b++)
	{
		m_bulletList[b]->Update();
	}

	// �V�[�J�[
	//UpdateSeeker();

	// �s��쐬
	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.m = m_mat.s * m_mat.r * m_mat.t;

	CheckVec();
}

void Player::Draw()
{
	//�s��̏����� (�}�`�`��̑O�ɏ���)
	SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixIdentity());

	// �g�U�^
	DrawWebA();

	// �W���^
	DrawWebB();

	// �W���^�̓����蔻��\��(��)
	//SHADER.m_spriteShader.DrawBox(m_pos.x, m_pos.y + m_webB.size, m_webB.size + m_webB.sizeXAdd, m_webB.size, &Math::Color(1.0f, 0.0f, 0.0f, 0.3f), true);

	// ���@
	DrawImgEX(m_mat.m, &m_tex, Math::Rectangle(
		m_ownAlphaRect.width * m_nowAnim.x, m_ownAlphaRect.height * m_nowAnim.y,
		m_ownAlphaRect.width,				m_ownAlphaRect.height					), m_color);

	// �V�[�J�[
	//DrawSeeker();

	// �e
	for (UINT b = 0; b < m_bulletList.size(); b++)
	{
		m_bulletList[b]->Draw();
	}

	// === �ȉ��f�o�b�O ==============
	
	// ���@�����蔻��
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
	float gapDeg = 360.0f / 8.0f;	// ���W�p�`

	for (deg = 0; deg < 360; deg += gapDeg)	// ���W�񃋁[�v
	{
		// ���݂̒��_
		a = cos(DegToRad(deg + m_webB.degMove)) * (m_webB.size + m_webB.sizeXAdd*2.0f);
		b = sin(DegToRad(deg + m_webB.degMove)) * (m_webB.size/2.0f);

		degNext = deg + gapDeg;	// ���̒��_���v�Z
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
	// �ʏ�V���b�g
	if (GetKey('Z'))
	{
		if (m_shootFlg == 0)
		{
			m_shootFlg = 1;
		}
	}

	// �Q�A�V���b�g
	if (GetKey(VK_SHIFT))
	{
		if (m_shootFlg == 0)
		{
			m_shootFlg = 2;
		}
	}

	// �R�A�V���b�g
	if (GetKey('A'))
	{
		if (m_shootFlg == 0)
		{
			m_shootFlg = 3;
		}
	}

	// �e�쐬
	switch (m_shootFlg)
	{
	case 1:	// �P��
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
	case 2:	// �Q��
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
	case 3:	// �Q��
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

	// �E�F�u�W�J
	// �g�U�^
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
	// �W���^
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
