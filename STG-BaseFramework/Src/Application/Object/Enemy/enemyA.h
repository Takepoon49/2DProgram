#pragma once

// 継承元クラスのヘッダーはインクルード必須
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