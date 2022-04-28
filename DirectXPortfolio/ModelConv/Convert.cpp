#include "stdafx.h"
#include "Convert.h"
#include "Converter.h"

void Convert::Initialize()
{
	//Airplane();
	//Tower();
	//Tank();
	Kachujin();
	//Megan();
	//Weapon();
}

void Convert::Airplane()
{
	Converter* conv = new Converter();
	conv->ReadFile(L"B787/Airplane.fbx");
	conv->ExportMaterial(L"B787/Airplane", false);
	conv->ExportMesh(L"B787/Airplane");

	SafeDelete(conv);
}

void Convert::Tower()
{
	Converter* conv = new Converter();
	conv->ReadFile(L"Tower/Tower.fbx");
	conv->ExportMaterial(L"Tower/Tower");
	conv->ExportMesh(L"Tower/Tower");

	SafeDelete(conv);
}

void Convert::Tank()
{
	Converter* conv = new Converter();
	conv->ReadFile(L"Tank/Tank.fbx");
	conv->ExportMaterial(L"Tank/Tank", false);
	conv->ExportMesh(L"Tank/Tank");

	SafeDelete(conv);
}

void Convert::Kachujin()
{
	Converter* conv = new Converter();
	conv->ReadFile(L"Kachujin/Mesh.fbx");
	conv->ExportMaterial(L"Kachujin/Mesh", false);
	conv->ExportMesh(L"Kachujin/Mesh");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Common/Idle.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Common/Idle");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Common/Running.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Common/Running");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Common/Jump.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Common/Jump");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Common/Hip_Hop_Dancing.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Common/Hip_Hop_Dancing");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Hand/Fight Idle.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Hand/Fight Idle");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Hand/Body Jab Cross.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Hand/Body Jab Cross");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Hand/Mma Kick.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Hand/Mma Kick");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Sword/Sword And Shield Idle.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Sword/Sword And Shield Idle");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Sword/Great Sword Casting.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Sword/Great Sword Casting");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Sword/Great Sword High Spin Attack.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Sword/Great Sword High Spin Attack");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Common/Big Hit To Head.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Common/Big Hit To Head");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Bow/Standing Aim Overdraw.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Bow/Standing Aim Overdraw");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Bow/Standing Aim Recoil.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Bow/Standing Aim Recoil");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Bow/Standing Draw Arrow.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Bow/Standing Draw Arrow");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Bow/Standing Disarm Bow.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Bow/Standing Disarm Bow");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Bow/Standing Equip Bow.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Bow/Standing Equip Bow");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Bow/Standing Aim Walk Back.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Bow/Standing Aim Walk Back");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Bow/Standing Aim Walk Forward.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Bow/Standing Aim Walk Forward");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Bow/Standing Aim Walk Left.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Bow/Standing Aim Walk Left");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Bow/Standing Aim Walk Right.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Bow/Standing Aim Walk Right");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Bow/Standing Run Forward.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Bow/Standing Run Forward");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Bow/Standing Walk Back.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Bow/Standing Walk Back");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Bow/Standing Walk Left.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Bow/Standing Walk Left");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Bow/Standing Walk Right.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Bow/Standing Walk Right");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Kachujin/Bow/Standing Idle 01.fbx");
	conv->ExportAnimClip(0, L"Kachujin/Bow/Standing Idle 01");
	SafeDelete(conv);


}

void Convert::Megan()
{
	Converter* conv = new Converter();
	conv->ReadFile(L"Megan/Mesh.fbx");
	conv->ExportMaterial(L"Megan/Mesh", false);
	conv->ExportMesh(L"Megan/Mesh");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Megan/Taunt.fbx");
	conv->ExportAnimClip(0, L"Megan/Taunt");
	SafeDelete(conv);

	conv = new Converter();
	conv->ReadFile(L"Megan/Dancing.fbx");
	conv->ExportAnimClip(0, L"Megan/Dancing");
	SafeDelete(conv);
}

void Convert::Weapon()
{
	vector<wstring> names;
	names.push_back(L"Cutter.fbx");
	names.push_back(L"Cutter2.fbx");
	names.push_back(L"Dagger_epic.fbx");
	names.push_back(L"Dagger_small.fbx");
	names.push_back(L"Katana.fbx");
	names.push_back(L"LongArrow.obj");
	names.push_back(L"LongBow.obj");
	names.push_back(L"Rapier.fbx");
	names.push_back(L"Sword.fbx");
	names.push_back(L"Sword2.fbx");
	names.push_back(L"Sword_epic.fbx");

	for (wstring name : names)
	{
		Converter* conv = new Converter();
		conv->ReadFile(L"Weapon/" + name);


		String::Replace(&name, L".fbx", L"");
		String::Replace(&name, L".obj", L"");

		conv->ExportMaterial(L"Weapon/" + name, false);
		conv->ExportMesh(L"Weapon/" + name);
		SafeDelete(conv);
	}
}
