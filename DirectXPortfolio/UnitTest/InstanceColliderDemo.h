#pragma once
#include "Systems/IExecute.h"

class InstanceColliderDemo : public IExecute
{
public:
	virtual void Initialize() override;
	virtual void Ready() override {}
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override {}
	virtual void Render() override;
	virtual void PostRender() override {}
	virtual void ResizeScreen() override {}

private:
	void Mesh();
	void Airplane();
	void Kachujin();

	//void AddPointLights();
	//void AddSpotLights();
	//void AddCapsuleLights();

	void Pass(UINT mesh, UINT model, UINT anim);

private:
	Shader* shader;

	class CubeSky* sky;


	Material* floor;
	Material* stone;
	Material* brick;
	Material* wall;

	MeshRender* sphere;
	MeshRender* cylinder;
	MeshRender* cube;
	MeshRender* grid;


	ModelRender* airplane = NULL;

	Model* weapon;
	ModelAnimator* kachujin = NULL;
	
	struct ColliderDesc
	{
		Transform * Init;
		Collider * collider;
		Transform * colliderTransform;
	}collider[4];
	
	// test code
	//MeshRender * temp;
	//Collider * colider;
	//Transform * transform;
	//
	vector<MeshRender *> meshes;
	vector<ModelRender *> models;
	vector<ModelAnimator *> animators;
};