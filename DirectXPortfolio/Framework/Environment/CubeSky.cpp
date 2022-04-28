#include "Framework.h"
#include "CubeSky.h"

CubeSky::CubeSky(wstring file)
{
	shader = new Shader(L"15_CubeSky.fx");

	//sphere = new MeshSphere(0.5f);
	sphere = new MeshRender(shader, new MeshSphere(0.5f));
	sphere->AddTransform();
	//sphere->GetTransform()->Scale(1000, 1000, 1000);

	wstring temp = L"../../_Textures/" + file;
	Check(D3DX11CreateShaderResourceViewFromFile
	(
		D3D::GetDevice(), temp.c_str(), NULL, NULL, &srv, NULL
	));

	sSrv = shader->AsSRV("SkyCubeMap");
}

CubeSky::~CubeSky()
{
	SafeDelete(shader);
	SafeDelete(sphere);
	SafeRelease(srv);
}

void CubeSky::Update()
{
	Vector3 position;
	Context::Get()->GetCamera()->Position(&position);

	sphere->GetTransform(0)->Position(position);
	sphere->UpdateTransforms();
}

void CubeSky::Render()
{
	sSrv->SetResource(srv);
	sphere->Render();
}
