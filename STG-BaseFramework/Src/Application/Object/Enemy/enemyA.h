#pragma once

// �p�����N���X�̃w�b�_�[�̓C���N���[�h�K�{
#include "EnemyBase.h"

class EnemyA :public EnemyBase
{
public:

	EnemyA() { Init(); }
	~EnemyA() { Release(); }

	void Update() override;
	void Init() override;

private:

	void Release() override;

};