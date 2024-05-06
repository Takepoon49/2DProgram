#pragma once

#include "../../BaseObject.h"

//class Scene;

class HLaser : public BaseObject
{
public:

	HLaser() {};
	~HLaser() {};

	void Init(Math::Vector2 _pos, float _deg);
	void Update() override;
	void Draw() override;

	float CalcMove(Math::Vector2 _pos, int _num);

	float CalcTgtDeg(Math::Vector2 _pos);
	float CalcOwnDeg(Math::Vector2 _pos);

	void SetTgtDeg(float _deg) { m_tgtDeg = _deg; }
	void SetTarget(std::shared_ptr<BaseObject> _tgt) { m_target = _tgt; }

private:

	void Release();

	// ÇΩÅ[Ç∞Ç¡Ç∆óp
	std::shared_ptr<BaseObject> m_target;

	int m_rndTime;

	float m_radian = 0.0f;
	float m_speed = 0.0f;

	static const int	m_ImgSizeX = 14;
	static const int	m_ImgSizeY = 14;

	float m_tgtDeg = 0.0f;
};