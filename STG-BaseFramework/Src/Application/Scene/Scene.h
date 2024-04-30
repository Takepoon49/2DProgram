#pragma once

#include "../utility.h"

#include "../Object/Attack/Beam/beam0.h"	// �r�[��

#include "../Object/Attack/Bullet/bullet0.h"	// �e

#include "../Object/Item/item.h"	// �A�C�e��

#include "../Object/Hit/Hit.h"	// �����蔻��


class Player;
class C_Enemy;
class EnemyBase;
class EnemyA;
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

	// �V�[���Ǘ��p�ϐ�
	SceneType nowScene;
	char nowSceneStr[100] = "";
	Math::Color SceneFadeColor;

	// �f�o�b�O
	bool	m_bShowDebugWindow = false;
	bool	m_debugFlg = 0;
	int		m_debugNowPage = 0;

	// �}�E�X���W�֘A
	bool bGetMousePos = true;
	// �t���[����
	int frame;
	// �X�R�A
	int	m_score;

	// �v���C���[
	std::shared_ptr<Player>		m_player;
	int			m_playerNowAnimY = 0;
	Math::Color m_playerColor = C_WHITE;

	// �e
	KdTexture	m_bullet0Tex;
	C_Beam0		m_beam;
	int			beamNum;
	float		beamDeg;

	// �A�C�e��
	std::vector<std::shared_ptr<C_Item>>	m_itemList;
	KdTexture	m_itemTex;

	// �G�l�~�[
	std::vector<std::shared_ptr<C_Enemy>>	m_enemyList;
	KdTexture	m_enemyTex;

	// �G�̉ϒ��̌p��
	std::vector<std::shared_ptr<EnemyA>>	m_enemyAList;

	// �p�[�e�B�N��
	KdTexture	m_particleTex;

	// �}�b�v
	std::shared_ptr<Map>	m_map;
	KdTexture	m_mapTex[2];

	// UI
	std::shared_ptr<UI>		m_UI;
	KdTexture	m_UITex;

	// ��
	KdTexture	m_MaruTex;

	// �����蔻��
	C_Hit		m_hit;

public:
	
	// �L�[�t���O
	bool keyFlg[255];

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

	// �|�C���^�֘A
	void CreateEnemy(int _flg);

	// (���̂�)�Q�b�^�[��...�����͗ǂ��z��������...
	//Player* GetPlayer() { return &m_player; }

	C_Beam0* GetBeam() { return &m_beam; }
	
	//C_Enemy* GetEnemy() { return m_enemy; }
	
	//C_Item* GetItem(int num) { return m_itemList[num]; }
	
	//Map* GetMap() { return &m_map; }

	C_Hit* GetHit() { return &m_hit; }

	//UI* GetUI() { return &m_UI; }

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