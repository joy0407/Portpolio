#include "stdafx.h"
#include "InstanceColliderDemo.h"
#include "Viewer/Freedom.h"
#include "Environment/CubeSky.h"

void InstanceColliderDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(23, 0, 0);
	Context::Get()->GetCamera()->Position(0, 32, -67);
	((Freedom *)Context::Get()->GetCamera())->Speed(20, 2);


	shader = new Shader(L"27_Animation.fx");

	sky = new CubeSky(L"Environment/GrassCube1024.dds");

	Mesh();
	Airplane();
	Kachujin();

	//AddPointLights();
	//AddSpotLights();
	//AddCapsuleLights();

	//Transform * transform = NULL;
	//cube = new MeshRender(shader, new MeshCube());
	//transform = cube->AddTransform();
	//transform->Position(0, 5, 0);
	//transform->Scale(20, 10, 20);
	////cube->DiffuseMap(L"Stones.png");
	//
	//grid = new MeshRender(shader, new MeshGrid(5, 5));
	//transform = grid->AddTransform();
	//transform->Scale(20, 1, 20);
	////grid->DiffuseMap(L"Floor.png");
	//
	//
	//cylinder = new MeshRender(shader, new MeshCylinder(0.5f, 3.0f, 20, 20));
	//sphere = new MeshRender(shader, new MeshSphere(0.5f, 20, 20));
	//for (UINT i = 0; i < 5; i++)
	//{
	//	//cylinder = new MeshCylinder(shader, 0.5f, 3.0f, 20, 20);
	//	cylinder->AddTransform();
	//	cylinder->GetTransform(i)->Position(-30, 6, -15.0f + (float)i * 15.0f);
	//	cylinder->GetTransform(i)->Scale(5, 5, 5);
	//	//cylinder[i * 2]->DiffuseMap(L"Bricks.png");
	//
	//	//cylinder[i * 2 + 1] = new MeshCylinder(shader, 0.5f, 3.0f, 20, 20);
	//	//cylinder[i * 2 + 1]->GetTransform()->Position(30, 6, -15.0f + (float)i * 15.0f);
	//	cylinder->AddTransform();
	//	cylinder->GetTransform(i)->Position(-30, 6, -15.0f + (float)i * 15.0f);
	//	cylinder->GetTransform(i)->Scale(5, 5, 5);
	//	//cylinder[i * 2 + 1]->DiffuseMap(L"Bricks.png");
	//
	//
	//	//sphere[i * 2] = new MeshSphere(shader, 0.5f, 20, 20);
	//	sphere->AddTransform();
	//	sphere->GetTransform(i)->Position(-30, 15.5f, -15.0f + (float)i * 15.0f);
	//	sphere->GetTransform(i)->Scale(5, 5, 5);
	//	//sphere[i * 2]->DiffuseMap(L"Wall.png");
	//
	//	//sphere[i * 2 + 1] = new MeshSphere(shader, 0.5f, 20, 20);
	//	sphere->AddTransform();
	//	sphere->GetTransform(i)->Position(30, 15.5f, -15.0f + (float)i * 15.0f);
	//	sphere->GetTransform(i)->Scale(5, 5, 5);
	//	//sphere[i * 2 + 1]->DiffuseMap(L"Wall.png");
	//}
	//
	//terrainShader = new Shader(L"11_Terrain.fx");
	//terrain = new Terrain(terrainShader, L"Terrain/Gray256.png");
	//terrain->BaseMap(L"Terrain/Dirt3.png");

	//temp = new MeshRender(shader, new MeshCube());
	//Transform* t = temp->AddTransform();
	//t->Position(-27, 10, -35);
	//t->Scale(1, 1, 1);
	//transform = new Transform();
	//colider = new Collider(transform);
}

void InstanceColliderDemo::Destroy()
{
	
}

void InstanceColliderDemo::Update()
{
	sky->Update();

	sphere->Update();
	cylinder->Update();
	cube->Update();
	grid->Update();

	airplane->Update();
	
	kachujin->Update();
	
	
	for (int i = 0; i < 4; i++)
	{
		Matrix attach = kachujin->GetAttachTransform(i);
		collider[i].collider->GetTransform()->World(attach);
		collider[i].collider->Update();
	}

	//colider->GetTransform()->World(temp->GetTransform(0)->World());
	//colider->Update();
}

void InstanceColliderDemo::Render()
{
	//sky->Pass(11);
	sky->Render();

	Pass(0, 1, 2);

	wall->Render();
	sphere->Render();

	brick->Render();
	cylinder->Render();

	stone->Render();
	cube->Render();

	floor->Render();
	grid->Render();

	airplane->Render();

	kachujin->Render();

	//bool col = false;
	for (int i = 0; i < 4; i++)
	{
		collider[i].collider->Render(Color(0, 1, 0, 1));

		//if (colider->IsIntersect(collider[i].collider))
		//	col = true;
	}

	//colider->Render(col != true ? Color(0, 1, 0, 1) : Color(1, 0, 0, 1));
}

void InstanceColliderDemo::Mesh()
{
	//Create Material
	{
		floor = new Material(shader);
		floor->DiffuseMap("Floor.png");
		//floor->SpecularMap("Floor_Specular.png");
		//floor->NormalMap("Floor_Normal.png");
		//floor->Specular(1, 1, 1, 20);

		stone = new Material(shader);
		stone->DiffuseMap("Stones.png");
		//stone->SpecularMap("Stones_Specular.png");
		//stone->NormalMap("Stones_Normal.png");
		//stone->Specular(1, 1, 1, 20);

		brick = new Material(shader);
		brick->DiffuseMap("Bricks.png");
		//brick->SpecularMap("Bricks_Specular.png");
		//brick->NormalMap("Bricks_Normal.png");
		//brick->Specular(1, 0.3f, 0.3f, 20);

		wall = new Material(shader);
		wall->DiffuseMap("Wall.png");
		//wall->SpecularMap("Wall_Specular.png");
		//wall->NormalMap("Wall_Normal.png");
		//wall->Specular(1, 1, 1, 20);
	}

	//Create Mesh
	{
		Transform* transform = NULL;

		cube = new MeshRender(shader, new MeshCube());
		transform = cube->AddTransform();
		transform->Position(0, 5, 0);
		transform->Scale(20, 10, 20);

		grid = new MeshRender(shader, new MeshGrid(5, 5));
		transform = grid->AddTransform();
		transform->Position(0, 0, 0);
		transform->Scale(12, 1, 12);

		cylinder = new MeshRender(shader, new MeshCylinder(0.5f, 3.0f, 20, 20));
		sphere = new MeshRender(shader, new MeshSphere(0.5f, 20, 20));
		for (UINT i = 0; i < 5; i++)
		{
			transform = cylinder->AddTransform();
			transform->Position(-30, 6, -15.0f + (float)i * 15.0f);
			transform->Scale(5, 5, 5);

			transform = cylinder->AddTransform();
			transform->Position(30, 6, -15.0f + (float)i * 15.0f);
			transform->Scale(5, 5, 5);


			transform = sphere->AddTransform();
			transform->Position(-30, 15.5f, -15.0f + (float)i * 15.0f);
			transform->Scale(5, 5, 5);

			transform = sphere->AddTransform();
			transform->Position(30, 15.5f, -15.0f + (float)i * 15.0f);
			transform->Scale(5, 5, 5);
		}
	}

	sphere->UpdateTransforms();
	cylinder->UpdateTransforms();
	cube->UpdateTransforms();
	grid->UpdateTransforms();

	meshes.push_back(sphere);
	meshes.push_back(cylinder);
	meshes.push_back(cube);
	meshes.push_back(grid);
}

void InstanceColliderDemo::Airplane()
{
	airplane = new ModelRender(shader);
	airplane->ReadMaterial(L"B787/Airplane");
	airplane->ReadMesh(L"B787/Airplane");

	Transform* transform = airplane->AddTransform();
	transform->Position(2.0f, 9.91f, 2.0f);
	transform->Scale(0.004f, 0.004f, 0.004f);
	airplane->UpdateTransforms();

	models.push_back(airplane);
}

void InstanceColliderDemo::Kachujin()
{
	weapon = new Model();
	weapon->ReadMaterial(L"Weapon/Sword");
	weapon->ReadMesh(L"Weapon/Sword");

	kachujin = new ModelAnimator(shader);
	kachujin->ReadMaterial(L"Kachujin/Mesh");
	kachujin->ReadMesh(L"Kachujin/Mesh");
	kachujin->ReadClip(L"Kachujin/Idle");
	kachujin->ReadClip(L"Kachujin/Running");
	kachujin->ReadClip(L"Kachujin/Jump");
	kachujin->ReadClip(L"Kachujin/Hip_Hop_Dancing");

	Transform attachTransform;

	attachTransform.Position(-10, 0, -10);
	attachTransform.Scale(1.0f, 1.0f, 1.0f);

	kachujin->GetModel()->Attach(shader, weapon, 35, &attachTransform);


	Transform* transform = NULL;

	transform = kachujin->AddTransform();
	transform->Position(-25, 0, -30);
	transform->Scale(0.075f, 0.075f, 0.075f);
	kachujin->PlayClip(0, 0, 1.0f);

	transform = kachujin->AddTransform();
	transform->Position(-10, 0, -30);
	transform->Scale(0.075f, 0.075f, 0.075f);
	kachujin->PlayClip(1, 1, 1.0f);

	transform = kachujin->AddTransform();
	transform->Position(10, 0, -30);
	transform->Scale(0.075f, 0.075f, 0.075f);
	kachujin->PlayClip(2, 2, 0.75f);

	transform = kachujin->AddTransform();
	transform->Position(25, 0, -30);
	transform->Scale(0.075f, 0.075f, 0.075f);
	kachujin->PlayClip(3, 3, 0.75f);

	kachujin->UpdateTransforms();

	animators.push_back(kachujin);

	for (UINT i = 0; i < 4; i++)
	{
		collider[i].Init = new Transform();
		collider[i].Init->Scale(10, 10, 120);
		collider[i].Init->Position(-10, 0, -60);
		collider[i].colliderTransform = new Transform();
		collider[i].collider = new Collider(collider[i].colliderTransform, collider[i].Init);
	}

}

//oid InstanceColliderDemo::AddPointLights()
//
//	PointLight light;
//	light =
//	{
//	   Color(0.0f, 0.0f, 0.0f, 1.0f),
//	   Color(0.0f, 0.0f, 1.0f, 1.0f),
//	   Color(0.0f, 0.0f, 0.7f, 1.0f),
//	   Vector3(-25, 10, -30), 5.0f, 0.9f
//	};
//	Context::Get()->AddPointLight(light);
//
//	PointLight light2;
//	light2 =
//	{
//	   Color(0.0f, 0.0f, 0.0f, 1.0f),
//	   Color(1.0f, 0.2f, 0.3f, 1.0f),
//	   Color(0.0f, 0.0f, 0.0f, 1.0f),
//	   Vector3(25, 10, -30), 10.0f, 0.3f
//	};
//	Context::Get()->AddPointLight(light2);
//
//
//oid InstanceColliderDemo::AddSpotLights()
//
//	SpotLight light;
//	light =
//	{
//	   Color(0.3f, 1.0f, 0.0f, 1.0f),
//	   Color(0.7f, 1.0f, 0.0f, 1.0f),
//	   Color(0.3f, 1.0f, 0.0f, 1.0f),
//	   Vector3(-10, 20, -30), 21.0f,
//	   Vector3(0, -1, 0), 56.0f, 0.9f
//	};
//	Context::Get()->AddSpotLight(light);
//
//	light =
//	{
//	   Color(0.2f, 1.0f, 0.15f, 1.0f),
//	   Color(0.2f, 1.0f, 0.15f, 1.0f),
//	   Color(0.2f, 1.0f, 0.15f, 1.0f),
//	   Vector3(10, 30, -30), 31.0f,
//	   Vector3(0, -1, 0), 56.0f, 0.9f
//	};
//	Context::Get()->AddSpotLight(light);
//
//
//oid InstanceColliderDemo::AddCapsuleLights()
//
//	CapsuleLight light;
//	light =
//	{
//	   Color(0.0f, 0.8f, 1.0f, 1.0f),
//	   Color(0.0f, 0.8f, 1.0f, 1.0f),
//	   Color(0.0f, 1.0f, 1.0f, 1.0f),
//	   Vector3(-18, 16, -17), 7.2f,
//	   Vector3(1, 0, 0), 18.0f, 0.9f
//	};
//	Context::Get()->AddCapsuleLight(light);
//
//
//	light =
//	{
//	   Color(0.0f, 0.0f, 0.0f, 1.0f),
//	   Color(0.75f, 0.0f, 0.0f, 1.0f),
//	   Color(1.0f, 1.0f, 0.0f, 1.0f),
//	   Vector3(-20.0f, 1, -40), 20.0f,
//	   Vector3(1, 0, 0), 40.0f, 0.8f
//	};
//	Context::Get()->AddCapsuleLight(light);
//

void InstanceColliderDemo::Pass(UINT mesh, UINT model, UINT anim)
{
	for (MeshRender* temp : meshes)
		temp->Pass(mesh);

	for (ModelRender* temp : models)
		temp->Pass(model);

	for (ModelAnimator* temp : animators)
		temp->Pass(anim);
}