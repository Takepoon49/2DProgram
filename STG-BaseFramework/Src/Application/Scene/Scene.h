#pragma once

typedef unsigned int UINT;

#include "../utility.h"

#include "../Object/Player/player.h"

#include "../Object/Enemy/enemy.h"

#include "../Object/Attack/Beam/beam0.h"

#include "../Object/Attack/Bullet/bullet0.h"

#include "../Object/Map/map.h"

#include "../Object/Item/item.h"

#include "../Object/Hit/Hit.h"

class EnemyBase;

enum SceneType
{
	S_Title,
	S_Game1,
	S_Scene2,
	S_End
};

class Scene
{
private:

	bool abool;

	// �V�[���Ǘ��p�ϐ�
	SceneType nowScene;
	char nowSceneStr[100] = "";
	Math::Color SceneFadeColor;

	// �f�o�b�O
	bool	m_debugFlg = 0;
	int		m_debugNowPage = 0;

	// �L�[�t���O
	bool keyFlg[key_End];

	// �}�E�X���W�֘A
	bool bGetMousePos = true;

	//�t���[����
	int frame;

	// �v���C���[
	C_Player	m_player;
	KdTexture	m_playerTex;

	// �e
	KdTexture	m_bullet0Tex;
	
	C_Beam0		m_beam;
	int			beamNum;
	float		beamDeg;

	// �A�C�e��
	std::vector<C_Item*> m_itemList;
	std::vector <C_Item*>::iterator m_itemIt;
	KdTexture	m_itemTex;

	// �G�l�~�[
	C_Enemy		m_enemy;
	KdTexture	m_enemyTex;

	// �G�̉ϒ��̌p��
	std::vector<EnemyBase*>	m_enemyAList;
	std::vector <EnemyBase*>::iterator m_enemyAIt;
	//std::shared_ptr<EnemyBase>	m_enemyA;

	// �}�b�v
	C_Map		m_map;
	KdTexture	m_mapTex;

	// ��
	KdTexture	m_MaruTex;

	// �����蔻��
	C_Hit		m_hit;

public:
	
	// �f�o�b�O
	bool GetDebugFlg() { return m_debugFlg; }

	// �L�[�t���O
	bool GetKeyFlg(int num) { return keyFlg[num]; }
	void SetKeyFlg(int num, bool tf) { keyFlg[num] = tf; }

	// �����ݒ�
	void Init();
	void InitGame1();

	// ���
	void Release();
	void ReleaseGame1();

	// �X�V����
	void Update();
	void CheckGame1Vec();
	void UpdateGame1();

	// �`�揈��
	void Draw2D();
	void DrawGame1();

	void DrawString(SceneType nowScene);
	void DrawFilledMaru(float x, float y, float rad, Math::Color);

	// �Q�b�^�[
	C_Player* GetPlayer() { return &m_player; }

	C_Beam0* GetBeam() { return &m_beam; }
	
	C_Enemy* GetEnemy() { return &m_enemy; }
	
	C_Item* GetItem(int num) { return m_itemList[num]; }
	
	C_Map* GetMap() { return &m_map; }

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
