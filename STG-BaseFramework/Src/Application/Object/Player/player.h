#pragma once
#include "../Attack/Bullet/bullet0.h"

struct LockOn
{
	Math::Vector2	pos;
	bool			bActive;
};

class Scene;

class C_Player
{
public:

	C_Player() {}
	~C_Player() {}

	void Init();
	void CheckVec();
	void Update();
	void Draw();
	
	// �V�[�J�[
	void UpdateSeeker();
	void DrawSeeker();

	// �Z�b�^�[
	void SetPlayerTex(KdTexture* a_pTex) { m_pTex = a_pTex; }

	void SetPDeg(float deg) { m_deg = deg; }

	// �Q�b�^�[
	float GetPDeg() { return m_deg; }

	// �e
	void CreateBullet(Math::Vector2 a_pos, bool a_num);
	
	int GetBulletNum() { return m_bulletList.size(); }
	
	bool GetBulletFlg(int num) { return m_bulletList[num]->GetFlg(); }
	
	HitStruct GetBulletObj(int num) { return m_bulletList[num]->GetObj(); }
	
	void SetBullet0Tex(KdTexture* a_pTex) { m_pBullet0Tex = a_pTex; }
	void SetBulletFlg(int num, bool a_bActive) { m_bulletList[num]->SetFlg(a_bActive); }

	void SetOwner(Scene* a_pOwner) { m_pOwner = a_pOwner; }

	HitStruct GetObj();		// ���@�����蔻��p
	HitStruct GetSeekObj();	// �V�[�J�[�����蔻��p

private:

	Scene* m_pOwner;

	KdTexture* m_pTex;

	keynum KeyNum;

	// ���@
	UINT			m_flg;					// ��ԊǗ��t���O

	Math::Rectangle	m_ownAlphaRect;			// �؂���͈�

	Math::Vector2	m_pos;					// ���W
	Math::Vector2	m_move;					// �ړ���
	Math::Vector2	m_speed;				// �ړ��ʂɓ����l
	Math::Vector2	m_scale;				// �g�嗦
	Math::Vector2	m_rad;					// �[�Ƃ̓����蔻��p���a
	float			m_Hrad;					// �e�Ƃ̓����蔻��p���a
	float			m_deg;					// �p�x
	MathSet			m_mat;					// �s��
	Math::Color		m_color;				// �F
	Math::Color		m_DebugColor;			// �f�o�b�O�p�F

	// �V�[�J�[
	UINT				m_SImgPosX = 100;
	UINT				m_SImgPosY = 106;
	static const int	m_SImgSizeX = 100;
	static const int	m_SImgSizeY = 100;
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
	std::vector<C_Bullet0*>::iterator it;

	float m_bulletTime;


	// �E�F�u
	UINT			webMode;	// 0:�g�U�^ 1:�W���^

	// �g�U�^�E�F�u (A)
	bool			Aflg;		// 
	float			Aradius;		// 
	
	// �W���^�E�F�u (B)
	bool			Bflg;		// 
	float			Bsize;	// 


	bool GetKeyFlg(int num);
	void SetKeyFlg(int num, bool tf);
};