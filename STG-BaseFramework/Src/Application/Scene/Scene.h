#pragma once

#include "../utility.h"

#include "../Object/Attack/Beam/beam0.h"	// �r�[��

#include "../Object/Attack/Bullet/bullet0.h"	// �e

#include "../Object/Item/item.h"	// �A�C�e��

#include "../Hit/Hit.h"	// �����蔻��

class Player;
class HLaser;
class PlayerAB;

class Bullet1;
class Bomb;

class Enemy;
class Boss;

class ParticleBase;

class Explosion;


class Map;

class UI;

enum class SceneType
{
	Title,
	Game1,
	Result
};

class Scene
{
private:

	// �^�[�Q�b�g
	int m_targetNum;

	// �V�[���Ǘ��p�ϐ�
	SceneType nowScene;
	char nowSceneStr[100] = "";
	Math::Color SceneFadeColor;

	// �f�o�b�O
	bool	m_bShowDebugWindow = false;
	bool	m_debugFlg = 0;
	int		m_debugNowPage = 0;

	// �}�E�X���W�֘A
	bool m_bGetMousePos = true;
	POINT m_mousePos;

	// �t���[����
	int m_frame = 0;

	// �^�C�g��
	Math::Matrix m_titleMat;	// �s�� 
	KdTexture m_titleTex0;		// Press Enter
	KdTexture m_titleTex1;		// Ray Seeker
	KdTexture m_titleTex2;		// �E�̂��

	// �v���C���[
	std::shared_ptr<Player> m_player;

	// �v���C���[�̒e
	KdTexture	m_bullet0Tex;
	C_Beam0		m_beam;
	int			beamNum;
	float		beamDeg;
	//std::shared_ptr<PlayerAB> m_abParticle;	// ���@�p�A�t�^�[�o�[�i�[
	std::vector<std::shared_ptr<PlayerAB>> m_abParticleList;

	// �{��
	std::shared_ptr<Bomb>	m_bomb;
	std::vector<std::shared_ptr<Bomb>>	m_bombList;

	// �G�̒e
	// �e
	std::vector<std::shared_ptr<Bullet1>>			m_bulletList;
	std::vector<std::shared_ptr<Bullet1>>::iterator m_bulletIt;
	KdTexture* m_pBullet1Tex;

	// �ǔ����[�U�[
	std::vector<std::shared_ptr<HLaser>>	m_hLaserList;

	// �A�C�e��
	std::vector<std::shared_ptr<C_Item>>	m_itemList;
	KdTexture	m_itemTex;

	// �G�l�~�[
	std::vector<std::shared_ptr<Enemy>>		m_enemyList;
	KdTexture	m_enemyTex;

	// �{�X
	std::shared_ptr<Boss>					m_boss;
	KdTexture								m_bossTex;

	// �p�[�e�B�N��
	std::vector<std::shared_ptr<ParticleBase>>	m_particleList;	// �S�p�[�e�B�N���̃��X�g
	KdTexture	m_particleTex;

	// �}�b�v
	std::shared_ptr<Map>	m_map;
	KdTexture				m_mapTex[3];

	// UI
	std::shared_ptr<UI>		m_UI;
	KdTexture				m_UITex;

	// ��
	KdTexture	m_MaruTex;

	// �����蔻��
	C_Hit		m_hit;

public:

	// �c�@
	int m_playerLife = 3;

	// �{��
	int			m_bombNum = 0;

	// �X�R�A
	int m_score;
	void AddScore(int _num) { m_score += _num; }

	// �t���O
	bool	m_gameOverFlg = false;	// �Q�[���I�[�o�[
	bool	keyFlg[k_end];			// �L�[�t���O
	bool	AddBlend = true;		// ���Z����
	float	LightHSize = 1.8f;		// �ǔ��e�̌��̃T�C�Y

	// �f�o�b�O
	bool GetDebugFlg() { return m_debugFlg; }

	// �����ݒ�
	void Init();
	// �X�V����
	void Update();
	// �`�揈��
	void Draw2D();
	// ���
	void Release();

	// �^�C�g��
	void InitTitle();
	void UpdateTitle();
	void DrawTitle();
	void ReleaseTitle();
	
	// �Q�[���P
	void InitGame1();
	void CheckGame1Vec();
	void UpdateGame1();
	void DrawGame1();
	void ReleaseGame1();

	// ���U���g
	void InitResult();
	void UpdateResult();
	void DrawResult();
	void ReleaseResult();

	void DrawString(SceneType nowScene);
	void DrawFilledMaru(float x, float y, float rad, Math::Color);

	// �G�o���p
	void UpdateEnemyTL();

	// �f�o�b�O�p
	void UpdateDebugEnemy();
	void DebugKey1();
	void DebugKey2();
	void DebugKey3();

	// �e�֘A
	void DeleteBullet1();
	void CreateBullet1(Math::Vector2 _pos, float _deg);

	// �Q�b�^�[
	int	GetTargetNum() { return m_targetNum; }
	int GetLockOnNum();
	int GetPlayerLife() { return m_playerLife; }
	float GetPlayerRollVal();
	float GetPlayerRollValMax();
	Math::Vector2 GetPlayerNowAnim();
	Math::Color GetPlayerDColor();
	std::shared_ptr<Player> GetPlayer() { return m_player; }

	// �Z�b�^�[
	void SetAllLock(int _flg);

	// �|�C���^�֘A
	void CreateEnemy(Math::Vector2 _pos, int _flg);		// �G�o�� (���ς���)
	void CreateEnemy1(Math::Vector2 _pos, int _flg);	// �G�o�� (�����Ղꂢ)

	void CreateBoss(Math::Vector2 _pos, int _flg);		// �{�X�o��
	void ResetBoss();									// �{�X�N���A

	void CreateItem(Math::Vector2 _pos, int _flg);		// �A�C�e���o�� 
	void CreateHLaser(Math::Vector2 _pos, float _deg);	// �ǔ����[�U�[�o��
	void ShotBomb(Math::Vector2 _ppos, int _flg);		// �{������

	void EraseAll();

	// �p�[�e�B�N��
	void CreateLightH(std::shared_ptr<BaseObject> _pair, int _type);			// �ǔ����[�U�[�̌�
	void CreateHLTrail(Math::Vector2 _pos, float _deg, Math::Color _color);		// �ǔ����[�U�[�̋O��
	void CreateParticle(ParticleType _type, Math::Vector2 _pos);				// �H
	void CreateExplosionA(ParticleType _type, Math::Vector2 _pos);				// ����
	//void CreateLightH(std::shared_ptr<HLaser> _pair);							// �H
	void CreatePlayerAB(std::shared_ptr<BaseObject> _obj);						// �v���C���[AB
	void CreatePShadow(Math::Vector2 _pos);										// �v���C���[�����ړ����̉e
	void MakeShockWave(Math::Vector2 _pos);										// �Ռ��g
	void CreateMSLTrail(Math::Vector2 _pos);									// �~�T�C���̋O��

	void DrawPlayerAB();

	C_Beam0* GetBeam() { return &m_beam; }

	C_Hit* GetHit() { return &m_hit; }

	// GUI����
	void ImGuiUpdate();

private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()