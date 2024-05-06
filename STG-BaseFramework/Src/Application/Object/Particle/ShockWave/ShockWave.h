#pragma once

#include "../../BaseObject.h"

class ShockWave : public BaseObject
{
public:

	ShockWave();
	~ShockWave() {};

	void Init(Math::Vector2 _pos);
	void Update();
	void Draw();

private:



};