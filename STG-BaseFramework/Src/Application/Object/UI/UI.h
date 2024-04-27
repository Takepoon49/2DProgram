#pragma once

class Scene;

class UI
{
public:

	UI() {};
	~UI() {};

	void Init();
	void Update();
	void Draw();

	void SetTexture0(KdTexture* _pTex) { m_pTex0 = _pTex; }
	void SetOwner(Scene* _pOwner) { m_pOwner = _pOwner; }

private:

	Scene* m_pOwner;

	KdTexture* m_pTex0;
};