#pragma once

// 継承元クラスのヘッダーはインクルード必須
#include "../EnemyBase.h"

class EnemyA :public EnemyBase
{
public:

	EnemyA() { Init(); }
	~EnemyA() {};

	void Update() override;
	void Init() override;

	void Test() { m_pos.x += 5.0f; };

	void ShootToPlayer(Math::Vector2 _pos);

	void SetTest();

	void SetMove(int _moveType);

private:

	//float Func01(float _y) { return -_y/4; }

	void Release() override;

	int m_frame;

};