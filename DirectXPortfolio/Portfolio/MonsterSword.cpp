#include "pch.h"
#include "MonsterSword.h"


MonsterSword::MonsterSword()
	:Monster()
{
	shader = new Shader(L"27_Animation.fx");

	test = new ModelAnimator(shader);
	test->ReadMaterial(L"Kachujin/Mesh");
	test->ReadMesh(L"Kachujin/Mesh");

	//Common
	test->ReadClip(L"Kachujin/Common/Idle");
	test->ReadClip(L"Kachujin/Common/Big Hit To Head");
	test->ReadClip(L"Kachujin/Sword/Great Sword High Spin Attack");

	Transform attachTransform;
	attachTransform.Position(-10, 0, -10);
	attachTransform.Scale(1.0f, 1.0f, 1.0f);

	Model * weapon = new Model();
	weapon->ReadMaterial(L"Weapon/Sword");
	weapon->ReadMesh(L"Weapon/Sword");

	
	test->GetModel()->Attach(shader, weapon, 35, &attachTransform);

	test->MakeTexture(0);


	

	Transform* transform = NULL;

	transform = test->AddTransform();
	transform->Position(50, 0, -30);
	transform->Scale(0.075f, 0.075f, 0.075f);
	test->PlayClip(0, 0, 1.0f);

	transform = test->AddTransform();
	transform->Position(0, 0, 0);
	transform->Scale(0.075f, 0.075f, 0.075f);
	test->PlayClip(0, 0, 1.0f);

	test->UpdateTransforms();

	animators.push_back(test);

	for (UINT i = 0; i < 2; i++)
	{
		collider[i].Init = new Transform();
		collider[i].Init->Scale(10, 10, 120);
		collider[i].Init->Position(-10, 0, -60);
		collider[i].colliderTransform = new Transform();
		collider[i].collider = new Collider(collider[i].colliderTransform, collider[i].Init);
	}

	for (UINT i = 0; i < 2; i++)
	{
		ColliderDesca temp;
		temp.Init = new Transform();
		temp.Init->Scale(80, 150, 80);
		temp.Init->Position(0, 100, 0);
		temp.colliderTransform = test->GetTransform(i);
		temp.collider = new Collider(temp.colliderTransform, temp.Init);

		collidertemp.push_back(temp);
	}

	BattleManager::GetInstance()->AddMonster(this);
}


MonsterSword::~MonsterSword()
{
}

void MonsterSword::Update()
{
	Super::Update();

	test->Update();

	for (int i = 0; i < 2; i++)
	{
		test->SetAttachBoneIndex(35);
		test->CalculateAttachBoneIndex();
		Matrix attach = test->GetAttachTransform(i);
		collider[i].collider->GetTransform()->World(attach);
		collider[i].collider->Update();
	}


	for(int i=0;i<collidertemp.size();i++)
		collidertemp[i].collider->Update();

}

void MonsterSword::Render()
{
	Super::Render();

	test->Render();

	collider[0].collider->Render(Color(0, 1, 0, 1));
	collidertemp[0].collider->Render(Color(0, 1, 0, 1));

	collider[1].collider->Render(Color(0, 1, 0, 1));
	collidertemp[1].collider->Render(Color(0, 1, 0, 1));
}

void MonsterSword::PlayAnimation()
{
	for (int i = 0; i < 2; i++)
	{
		if (currnet[i] == next[i])
			continue;

		switch (next[i])
		{
		case MonsterAnimationState::Default:
			test->PlayClip(i, 0, 1.0f, 0.2f);
			maxActionTime[i] = 2.0f;
			break;
		case MonsterAnimationState::MonsterHit:
			test->PlayClip(i, 1, 1.0f, 0.2f);
			maxActionTime[i] = 2.0f;
			break;
		case MonsterAnimationState::FightWeaponUse:
			test->PlayClip(i, 2, 1.0f, 0.2f);
			maxActionTime[i] = 2.0f;
			break;
		default:
			break;
		}

		currentActionTime[i] = 0.0f;
		currnet[i] = next[i];
	}

}

void MonsterSword::Idle(int index)
{
	next[index] = MonsterAnimationState::Default;
}

void MonsterSword::Move(int index)
{
}

void MonsterSword::Attack(int index)
{
	next[index] = MonsterAnimationState::FightWeaponUse;

	bool isHit = false;

	//if (currentActionTime[index] < maxActionTime[index])
	{
		Collider * collider1 = BattleManager::GetInstance()->GetPlayer()->GetCollider();

		if (collider[index].collider->IsIntersect(collider1))
		{
			isHit = true;
			
		}

		if (isHit == true)
			collider[index].collider->Render(Color(1, 0, 0, 1));
		else
			collider[index].collider->Render(Color(0, 1, 0, 1));


	}
}

void MonsterSword::Trace(int index)
{
	next[index] = MonsterAnimationState::Default;

	Vector3 playerPosition, position;
	
	playerPosition = BattleManager::GetInstance()->GetPlayer()->GetPosition();
	test->GetTransform(index)->Position(&position);

	moveDirection[index] = playerPosition - position;

	D3DXVec3Normalize(&moveDirection[index], &moveDirection[index]);

	position += moveDirection[index] * 5 * Time::Delta();

	test->GetTransform(index)->Position(position);

	float angle = atan2(moveDirection[index].z, -moveDirection[index].x) + Math::PI / 2;

	test->GetTransform(index)->Rotation(0, angle, 0);

}

void MonsterSword::Hit(int index)
{
	next[index] = MonsterAnimationState::MonsterHit;
}

void MonsterSword::Dead(int index)
{
}
