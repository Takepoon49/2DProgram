#pragma once

#include "../BaseObject.h"
#include "../Attack/Bullet/bullet0.h"
#include "../Attack/H-Laser/H-Laser.h"

struct LockOn
{
	Math::Vector2	pos;
	bool			bActive;
};

class Player :public BaseObject
{
public:

	Player();
	~Player()override { Release(); };

	void Init() override;
	void CheckVec();
	void Update() override;
	void Draw() override;

	// �ړ�����
	void UpdateMove();	// X + �����L�[�Ń��[�����O
	void UpdateMove1();	// �����L�[��x�����Ń��[�����O�i�v�j

	// �E�F�u
	void DrawWebA();
	void DrawWebB();

	Math::Color GetDebugColor() { return m_DebugColor; }
	
	// �V�[�J�[
	void UpdateSeeker();
	void DrawSeeker();

	// �U���n
	void UpdateAttack();

	// �Z�b�^�[
	// �؂���͈�
	void SetNowAnimY(int _animY) { m_nowAnim.y = (int)_animY; }
	// ���@�F
	void SetPColor(Math::Color _color) { m_color = _color; }

	//void SetPlayerTex(KdTexture* a_pTex) { m_pTex = a_pTex; }
	void SetBullet0Tex(KdTexture* a_pTex) { m_pBullet0Tex = a_pTex; }
	void SetPDeg(float deg) { m_deg = deg; }

	// �Q�b�^�[
	float GetPDeg() { return m_deg; }

	// �e
	void CreateBullet(Math::Vector2 a_pos);
	void CreateBullet(float _x, float _y);

	int GetBulletNum() { return m_bulletList.size(); }
	int GetBulletFlg(int num) { return m_bulletList[num]->GetFlg(); }

	int GetShootTime() { return m_shootTime; }
	int GetShootFlg() { return m_shootFlg; }

	HitStruct GetBulletObj(int num) { return m_bulletList[num]->GetObj(); }

	//void SetBullet0Tex(KdTexture* a_pTex) { m_pBullet0Tex = a_pTex; }
	void SetBulletFlg(int num, int _flg) { m_bulletList[num]->SetFlg(_flg); }

	void SetOwner(Scene* a_pOwner) { m_pOwner = a_pOwner; }

	HitStruct GetObj();		// ���@�����蔻��p
	HitStruct GetSeekObj();	// �V�[�J�[�����蔻��p

	HitStruct GetWebBObj();

	int GetRollFlg() { return m_roll.flg; }
	float GetRollFrame1() { return m_roll.frame1; }

	float GetFrame0() { return m_frame; }

private:

	Scene* m_pOwner;

	struct webStruct
	{
		bool			flg;
		Math::Vector2	pos;
		float			size;
		float			sizeXAdd;
		float			degMove;
		float			degAdd;
	};

	// �g�U�^�E�F�u (A)
	webStruct m_webA;

	//�W���^�E�F�u (B)
	webStruct m_webB;

	// �L�[�t���O
	bool keyFlg[k_end];

	// ���@
	// �ړ����x
	float m_moveSpd = 7.5f;

	Math::Rectangle	m_ownAlphaRect;			// �؂���͈�
	Math::Vector2	m_nowAnim;

	float			m_frame;

	Math::Vector2	m_speed;				// �ړ��ʂɓ����l
	float			m_Hrad;					// �e�Ƃ̓����蔻��p���a
	Math::Color		m_DebugColor;			// �f�o�b�O�p�F

	// ���[�����O
	struct Roll
	{
		int		flg;		// �׸�
		Dir		dir;		// ����
		float	frame1;		// ���͗p�t���[��
		float	frame2;		// ���͗p�t���[��
		float	move;		// �ړ��ʃv���X�p
		int		cnt;		// �L�[�̃J�E���g�p
	}m_roll;

	// �e
	Math::Vector2	m_shadowPos;
	Math::Color		m_shadowColor;
	MathSet			m_shadowMat;

	// �V�[�J�[
	int						m_SImgPosX = 0;
	int						m_SImgPosY = 128 * 2;

	static const int	m_SImgSizeX = 128;
	static const int	m_SImgSizeY = 128;

	Math::Vector2		m_spos;			// ���W
	Math::Vector2		m_sscale;		// �傫��
	float				m_sdeg;			// �p�x
	MathSet				m_seekerMat;	// �s��
	Math::Color			m_sColor;		// �F
	bool				m_seekerFlg;	// �t���O

	// ���b�N�I��
	std::vector<LockOn*> m_pLockList;
	std::vector<LockOn*>::iterator m_pLockIt;

	// �e(�ϒ�)
	KdTexture* m_pBullet0Tex;
	std::vector<C_Bullet0*> m_bulletList;

	int		m_shootFlg;
	int		m_shootTime;

	// �ǔ����[�U�[
	HLaser	m_hLaser;
};