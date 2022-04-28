#include "stdafx.h"
#include "CubeSkyDemo.h"
#include "Viewer/Freedom.h"
#include "Environment/CubeSky.h"
#include "Environment/Terrain.h"

void CubeSkyDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(23, 0, 0);
	Context::Get()->GetCamera()->Position(0, 32, -67);
	((Freedom *)Context::Get()->GetCamera())->Speed(100, 2);


	shader = new Shader(L"14_Mesh.fx");

	Transform * transform = NULL;
	cube = new MeshRender(shader, new MeshCube());
	transform = cube->AddTransform();
	transform->Position(0, 5, 0);
	transform->Scale(20, 10, 20);

	grid = new MeshRender(shader, new MeshGrid(5, 5));
	transform = grid->AddTransform();
	transform->Scale(20, 1, 20);

	cylinder = new MeshRender(shader, new MeshCylinder(0.5f, 3.0f, 20, 20));
	sphere = new MeshRender(shader, new MeshSphere(0.5f, 20, 20));
	for (UINT i = 0; i < 5; i++)
	{
		//cylinder = new MeshCylinder(shader, 0.5f, 3.0f, 20, 20);
		cylinder->AddTransform();
		cylinder->GetTransform(i)->Position(-30, 6, -15.0f + (float)i * 15.0f);
		cylinder->GetTransform(i)->Scale(5, 5, 5);
		//cylinder[i * 2]->DiffuseMap(L"Bricks.png");

		//cylinder[i * 2 + 1] = new MeshCylinder(shader, 0.5f, 3.0f, 20, 20);
		//cylinder[i * 2 + 1]->GetTransform()->Position(30, 6, -15.0f + (float)i * 15.0f);
		cylinder->AddTransform();
		cylinder->GetTransform(i + 1)->Position(-30, 6, -15.0f + (float)i * 15.0f);
		cylinder->GetTransform(i + 1)->Scale(5, 5, 5);
		//cylinder[i * 2 + 1]->DiffuseMap(L"Bricks.png");


		//sphere[i * 2] = new MeshSphere(shader, 0.5f, 20, 20);
		sphere->AddTransform();
		sphere->GetTransform(i)->Position(-30, 15.5f, -15.0f + (float)i * 15.0f);
		sphere->GetTransform(i)->Scale(5, 5, 5);
		//sphere[i * 2]->DiffuseMap(L"Wall.png");

		//sphere[i * 2 + 1] = new MeshSphere(shader, 0.5f, 20, 20);
		sphere->AddTransform();
		sphere->GetTransform(i + 1)->Position(30, 15.5f, -15.0f + (float)i * 15.0f);
		sphere->GetTransform(i + 1)->Scale(5, 5, 5);
		//sphere[i * 2 + 1]->DiffuseMap(L"Wall.png");
	}
	cylinder->UpdateTransforms();
	sphere->UpdateTransforms();

	sky = new CubeSky(L"Environment/GrassCube1024.dds");

	terrainShader = new Shader(L"11_Terrain.fx");
	terrain = new Terrain(terrainShader, L"Terrain/Gray256.png");
	terrain->BaseMap(L"Terrain/Dirt3.png");
}

void CubeSkyDemo::Destroy()
{
	
}

void CubeSkyDemo::Update()
{
	sky->Update();
	terrain->Update();

	cube->Update();
	grid->Update();
	cylinder->Update();
	sphere->Update();
}

void CubeSkyDemo::Render()
{
	sky->Render();

	cylinder->Render();

	sphere->Render();

	cube->Render();
	grid->Render();

	terrain->Render();
}