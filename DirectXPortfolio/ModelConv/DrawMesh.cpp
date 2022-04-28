#include "stdafx.h"
#include "DrawMesh.h"
#include "Viewer/Freedom.h"

void DrawMesh::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(23, 0, 0);
	Context::Get()->GetCamera()->Position(0, 3, -20);
	((Freedom *)Context::Get()->GetCamera())->Speed(20, 2);

	shader = new Shader(L"27_Mesh.fx");

	gridMaterial = new Material(shader);
	gridMaterial->DiffuseMap(L"White.png");
	grid = new MeshRender(shader, new MeshGrid());
	grid->AddTransform()->Scale(10, 1, 2);
	grid->UpdateTransforms();

	cubeMaterial = new Material(shader);
	cubeMaterial->DiffuseMap(L"Box.png");
	cube = new MeshRender(shader, new MeshCube());

	
		for (float x = -100; x <= 100; x += 5.0f)
		{
			Transform* transform = cube->AddTransform();

			transform->Position(Vector3(x, 0.5f * 0.25f, 0));
			transform->RotationDegree(0, Math::Random(-180.0f, 180.0f), 0);
			transform->Scale(0.25, 0.25, 0.25);
		}
	
	cube->UpdateTransforms();

}

void DrawMesh::Update()
{
	grid->Update();
	cube->Update();
	
}

void DrawMesh::Render()
{
	gridMaterial->Render();
	grid->Render();

	cubeMaterial->Render();
	cube->Render();
}


