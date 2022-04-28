#include "pch.h"
#include "MainScene.h"
#include "Viewer/Freedom.h"
#include "Environment/CubeSky.h"
#include "Player.h"


MainScene::MainScene()
{
	Context::Get()->GetCamera()->RotationDegree(23, 0, 0);
	//Context::Get()->GetCamera()->RotationDegree(90, 0, 0);
	Context::Get()->GetCamera()->Position(0, 32, -67);
	//Context::Get()->GetCamera()->Position(-25, 51, -31);
	((Freedom *)Context::Get()->GetCamera())->Speed(20, 2);

	shader = new Shader(L"27_Animation.fx");

	//Create Object
	sky = new CubeSky(L"Environment/GrassCube1024.dds");

	CreateGrid();
	CreatePlayer();
	CreateMonster();
}


MainScene::~MainScene()
{
}

void MainScene::Initialize()
{
}

void MainScene::Destroy()
{
}

void MainScene::Update()
{
	sky->Update();

	grid->Update();

	player->Update();
	monster->Update();
}

void MainScene::Render()
{
	sky->Render();

	Pass(0, 1, 2);

	floor->Render();
	grid->Render();

	player->Render();
	monster->Render();
}

void MainScene::CreateGrid()
{
	floor = new Material(shader);
	floor->DiffuseMap("Floor.png");

	Transform* transform = NULL;

	grid = new MeshRender(shader, new MeshGrid(5, 5));
	transform = grid->AddTransform();
	transform->Position(0, 0, 0);
	transform->Scale(12, 1, 12);

	grid->UpdateTransforms();

	meshes.push_back(grid);
}

void MainScene::CreatePlayer()
{
	player = new Player();
}

void MainScene::CreateMonster()
{
	monster = new MonsterSword();
}

void MainScene::Pass(UINT mesh, UINT model, UINT anim)
{
	for (MeshRender* temp : meshes)
		temp->Pass(mesh);
}
