#pragma once
#include "Systems/IExecute.h"

class MainScene : public IExecute
{
public:
	MainScene();
	~MainScene();

	// IExecute을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Ready() override {}
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override {}
	virtual void Render() override;
	virtual void PostRender() override {}
	virtual void ResizeScreen() override {}

private:
	void CreateGrid();
	void CreatePlayer();
	void CreateMonster();

	void Pass(UINT mesh, UINT model, UINT anim);

private:
	Shader * shader;

	class CubeSky* sky;

	Material* floor;
	MeshRender * grid;

	class Player * player;
	class Monster * monster;

	vector<MeshRender *> meshes;
};

