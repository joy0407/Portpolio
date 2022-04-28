#include "pch.h"
#include "Player.h"


Player::Player()
{
	shader = new Shader(L"27_Animation.fx");

	Kachujin();

	BattleManager::GetInstance()->SetPlayer(this);
}


Player::~Player()
{
}

void Player::Update()
{
	currentActionTime += Time::Delta();

	UpdateCollider();

	Attack();

	Move();

	Swap();

	PlayAnimation();

	arrow->Update();
	kachujin->Update();

}

void Player::Render()
{
	Pass(0, 1, 2);
	arrow->Render();
	kachujin->Render();

	colliderPlayer.collider->Render(Color(0, 1, 0, 1));
}

void Player::Kachujin()
{
	kachujin = new ModelAnimator(shader);
	kachujin->ReadMaterial(L"Kachujin/Mesh");
	kachujin->ReadMesh(L"Kachujin/Mesh");

	//Common
	kachujin->ReadClip(L"Kachujin/Common/Idle");
	kachujin->ReadClip(L"Kachujin/Common/Running");
	kachujin->ReadClip(L"Kachujin/Common/Jump");
	kachujin->ReadClip(L"Kachujin/Common/Hip_Hop_Dancing");

	//Hand
	kachujin->ReadClip(L"Kachujin/Hand/Fight Idle");
	kachujin->ReadClip(L"Kachujin/Hand/Body Jab Cross");
	kachujin->ReadClip(L"Kachujin/Hand/Mma Kick");

	//Sword
	kachujin->ReadClip(L"Kachujin/Sword/Sword And Shield Idle");
	kachujin->ReadClip(L"Kachujin/Sword/Great Sword Casting");
	kachujin->ReadClip(L"Kachujin/Sword/Great Sword High Spin Attack");
	
	//Bow
	//kachujin->ReadClip(L"Kachujin/Bow/Standing Equip Bow");
	//kachujin->ReadClip(L"Kachujin/Bow/Standing Disarm Bow");
	//
	//kachujin->ReadClip(L"Kachujin/Bow/Standing Run Forward");
	//kachujin->ReadClip(L"Kachujin/Bow/Standing Walk Back");
	//kachujin->ReadClip(L"Kachujin/Bow/Standing Walk Left");
	//kachujin->ReadClip(L"Kachujin/Bow/Standing Walk Right");
	//
	//kachujin->ReadClip(L"Kachujin/Bow/Standing Aim Walk Back");
	//kachujin->ReadClip(L"Kachujin/Bow/Standing Aim Walk Forward");
	//kachujin->ReadClip(L"Kachujin/Bow/Standing Aim Walk Left");
	//kachujin->ReadClip(L"Kachujin/Bow/Standing Aim Walk Right");
	//
	//kachujin->ReadClip(L"Kachujin/Bow/Standing Aim Overdraw");
	//kachujin->ReadClip(L"Kachujin/Bow/Standing Aim Recoil");
	//kachujin->ReadClip(L"Kachujin/Bow/Standing Draw Arrow");
	//
	//kachujin->ReadClip(L"Kachujin/Bow/Standing Idle 01");
	
	kachujin->MakeTexture(0);

	Transform attachTransform;
	attachTransform.Position(-10, 0, -10);
	attachTransform.Scale(1.0f, 1.0f, 1.0f);
	attachTransform.RotationDegree(0, 0, 0);
	
	weapon[0] = new Model();
	weapon[0]->ReadMaterial(L"Weapon/Sword");
	weapon[0]->ReadMesh(L"Weapon/Sword");
	
	currentWeapon = weapon[0];
	kachujin->GetModel()->Attach(shader, weapon[0], 35, &attachTransform);
	kachujin->MakeTexture(1);
	
	weapon[1] = new Model();
	weapon[1]->ReadMaterial(L"Weapon/LongBow");
	weapon[1]->ReadMesh(L"Weapon/LongBow");
	
	attachTransform.Position(10, -4, 0);
	attachTransform.Scale(5.0f, 5.0f, 5.0f);
	attachTransform.RotationDegree(-90, 90, 0);
	kachujin->GetModel()->Distach(currentWeapon);
	currentWeapon = weapon[1];
	kachujin->GetModel()->Attach(shader, weapon[1], 11, &attachTransform);
	kachujin->MakeTexture(2);
	
	ChangeTexture(1, kachujin, currentWeapon, weapon[0]);
	kachujin->SetAttachBoneIndex(35);
	attackType = PlayerAttackType::Sword;

	Transform* transform = NULL;

	transform = kachujin->AddTransform();
	transform->Position(-25, 0, -30);
	transform->Scale(0.075f, 0.075f, 0.075f);
	kachujin->PlayClip(0, 0, 1.0f);

	kachujin->UpdateTransforms();

	animators.push_back(kachujin);

	arrow = new Arrow(true);

	colliderPlayer.Init = new Transform();
	colliderPlayer.Init->Scale(80, 150, 80);
	colliderPlayer.Init->Position(0, 100, 0);
	colliderPlayer.colliderTransform = new Transform();
	colliderPlayer.collider = new Collider(colliderPlayer.colliderTransform, colliderPlayer.Init);

	colliderSword.Init = new Transform();
	colliderSword.Init->Scale(10, 10, 120);
	colliderSword.Init->Position(-10, 0, -60);
	colliderSword.colliderTransform = new Transform();
	colliderSword.collider = new Collider(colliderSword.colliderTransform, colliderSword.Init);
	
	colliderRightFoot.Init = new Transform();
	colliderRightFoot.Init->Scale(30, 30, 30);
	colliderRightFoot.Init->Position(0, 0, 0);
	colliderRightFoot.colliderTransform = new Transform();
	colliderRightFoot.collider = new Collider(colliderRightFoot.colliderTransform, colliderRightFoot.Init);

	colliderLeftHand.Init = new Transform();
	colliderLeftHand.Init->Scale(30, 30, 30);
	colliderLeftHand.Init->Position(0, 0, 0);
	colliderLeftHand.colliderTransform = new Transform();
	colliderLeftHand.collider = new Collider(colliderLeftHand.colliderTransform, colliderLeftHand.Init);

	colliderRightHand.Init = new Transform();
	colliderRightHand.Init->Scale(30, 30, 30);
	colliderRightHand.Init->Position(0, 0, 0);
	colliderRightHand.colliderTransform = new Transform();
	colliderRightHand.collider = new Collider(colliderRightHand.colliderTransform, colliderRightHand.Init);

	//attackType = PlayerAttackType::Sword;
	attackCount = 0;
	currentActionTime = 0.0f;
	maxActionTime = 0.0f;
	isPlayClip = 0;

	current = PlayerAnimationState::MoveIdle;
	next = PlayerAnimationState::MoveIdle;
}

void Player::Pass(UINT mesh, UINT model, UINT anim)
{
	for (ModelAnimator* temp : animators)
		temp->Pass(anim);
}

void Player::ChangeTexture(int index, ModelAnimator * main, Model * before, Model * change)
{
	Transform attachTransform;
	

	if (index != 2)
	{
		//attachTransform.Position(-10, 0, -10);
		//attachTransform.Scale(1.0f, 1.0f, 1.0f);
		//attachTransform.RotationDegree(0, 0, 0);
	}
	else
	{
		//attachTransform.Position(100.0f, 0, 0);
		//attachTransform.Scale(15.0f, 15.0f, 15.0f);
		//attachTransform.RotationDegree(-90, 90, 0);
	}

	if (before != NULL)
	{
		main->GetModel()->Distach(before);
	}


	if (change != NULL)
	{
		main->GetModel()->Attach(shader, change, 35, &attachTransform);
		currentWeapon = change;
	}
	else
	{
		currentWeapon = NULL;
	}

	main->ChangeTexture(index);
}

void Player::PlayAnimation()
{
	if (current == next)
		return;

	switch (next)
	{
	case PlayerAnimationState::MoveIdle:
		kachujin->PlayClip(0, 0);
		break;
	case PlayerAnimationState::PlayerMoveFoward:
		kachujin->PlayClip(0, 1);
		break;
	case PlayerAnimationState::PlayerMoveBack:
		kachujin->PlayClip(0, 1);
		break;
	case PlayerAnimationState::PlayerMoveLeft:
		kachujin->PlayClip(0, 1);
		break;
	case PlayerAnimationState::PlayerMoveRight:
		kachujin->PlayClip(0, 1);
		break;
	case PlayerAnimationState::PlayerMoveJump:
		kachujin->PlayClip(0, 2);
		break;
	case PlayerAnimationState::FightHandIdle:
		kachujin->PlayClip(0, 4, 1.0f, 0.3f);
		break;
	case PlayerAnimationState::FightHandJap:
		kachujin->PlayClip(0, 5, 1.0f, 0.3f);
		break;
	case PlayerAnimationState::FightHandKick:
		kachujin->PlayClip(0, 6, 1.0f, 0.3f);
		break;
	case PlayerAnimationState::FightSwordIdle:
		kachujin->PlayClip(0, 7, 1.0f, 0.3f);
		break;
	case PlayerAnimationState::FightSwordCasting:
		kachujin->PlayClip(0, 8, 1.0f, 0.3f);
		break;
	case PlayerAnimationState::FightSwordSpinAttack:
		kachujin->PlayClip(0, 9, 1.0f, 0.3f);
		break;
	case PlayerAnimationState::FightBowIdle:
		kachujin->PlayClip(0, 23, 1.0f, 0.3f);
		break;
	case PlayerAnimationState::FightBowMoveFoward:
		kachujin->PlayClip(0, 12, 1.0f, 0.3f);
		break;
	case PlayerAnimationState::FightBowMoveBack:
		kachujin->PlayClip(0, 13, 1.0f, 0.3f);
		break;
	case PlayerAnimationState::FightBowMoveLeft:
		kachujin->PlayClip(0, 14, 1.0f, 0.3f);
		break;
	case PlayerAnimationState::FightBowMoveRight:
		kachujin->PlayClip(0, 15, 1.0f, 0.3f);
		break;
	case PlayerAnimationState::FightBowAimArrow:
		kachujin->PlayClip(0, 20, 1.0f, 0.3f);
		break;
	case PlayerAnimationState::FightBowFireArrow:
		kachujin->PlayClip(0, 21, 1.0f, 0.3f);
		break;
	case PlayerAnimationState::FightBowGetArrow:
		kachujin->PlayClip(0, 22, 1.0f, 0.3f);
		break;
	case PlayerAnimationState::FightSwordDashAttack:
		kachujin->PlayClip(0, 8, 1.0f, 0.3f);
		break;
	default:
		kachujin->PlayClip(0, 0);
	}

	current = next;
	
}

void Player::UpdateCollider()
{
	Matrix attach;

	if (attackType == PlayerAttackType::Hand)
	{
		kachujin->SetAttachBoneIndex(63);
		kachujin->CalculateAttachBoneIndex();
		attach = kachujin->GetAttachTransform(0);
		colliderRightFoot.collider->GetTransform()->World(attach);
		colliderRightFoot.collider->Update();

		kachujin->SetAttachBoneIndex(11);
		kachujin->CalculateAttachBoneIndex();
		attach = kachujin->GetAttachTransform(0);
		colliderLeftHand.collider->GetTransform()->World(attach);
		colliderLeftHand.collider->Update();

		kachujin->SetAttachBoneIndex(35);
		kachujin->CalculateAttachBoneIndex();
		attach = kachujin->GetAttachTransform(0);
		colliderRightHand.collider->GetTransform()->World(attach);
		colliderRightHand.collider->Update();
	}
	else if (attackType == PlayerAttackType::Sword)
	{
		kachujin->SetAttachBoneIndex(35);
		kachujin->CalculateAttachBoneIndex();
		attach = kachujin->GetAttachTransform(0);
		colliderSword.collider->GetTransform()->World(attach);
		colliderSword.collider->Update();
	}
	else if (attackType == PlayerAttackType::LongBow)
	{

	}
	
	Matrix matrix = kachujin->GetTransform(0)->World();

	colliderPlayer.collider->GetTransform()->World(matrix);
	colliderPlayer.collider->Update();
	
}

void Player::Attack()
{
	if (attackType == PlayerAttackType::Hand)
		AttackHand();
	else if (attackType == PlayerAttackType::Sword)
		AttackSword();
	else if (attackType == PlayerAttackType::LongBow)
		AttackLongBow();
}

void Player::Move()
{
	Vector3 Position;
	Vector3 Forward;
	Vector3 Right;
	Vector3 Rotation;

	Transform * transform = kachujin->GetTransform(0);

	transform->Position(&Position);
	transform->RotationDegree(&Rotation);
	Forward = transform->Forward();
	Right = transform->Right();

	if (Keyboard::Get()->Down(VK_SPACE))
	{
		next = PlayerAnimationState::PlayerMoveJump;
		currentActionTime = 0.0f;
		maxActionTime = 2.0f;
	}
	else
	{
		if (currentActionTime > maxActionTime)
		{
			if (attackType == PlayerAttackType::Hand)
			{
				next = PlayerAnimationState::FightHandIdle;

			}
			else if (attackType == PlayerAttackType::Sword)
			{
				next = PlayerAnimationState::FightSwordIdle;

			}
			else if (attackType == PlayerAttackType::LongBow)
			{
				next = PlayerAnimationState::FightBowIdle;

			}
			else
			{
				next = PlayerAnimationState::MoveIdle;
			}
			attackCount = 0;

		}

	}

	D3DXVec3Normalize(&Forward, &Forward);

	if (next == PlayerAnimationState::FightSwordDashAttack)
	{
		next = PlayerAnimationState::FightSwordDashAttack;
		if (current == PlayerAnimationState::FightSwordDashAttack)
		{
			Position -= Forward * Time::Delta() * 10;
		}
	}
		
	else
	{
		if (Keyboard::Get()->Press('A'))
		{
			if (attackType == PlayerAttackType::LongBow)
				next = PlayerAnimationState::FightBowMoveLeft;
			else
				next = PlayerAnimationState::PlayerMoveFoward;
		}
		else if (Keyboard::Get()->Press('D'))
		{
			if (attackType == PlayerAttackType::LongBow)
				next = PlayerAnimationState::FightBowMoveRight;
			else
				next = PlayerAnimationState::PlayerMoveFoward;
		}

		if (Keyboard::Get()->Press('W'))
		{
			if (attackType == PlayerAttackType::LongBow)
				next = PlayerAnimationState::FightBowMoveFoward;
			else
				next = PlayerAnimationState::PlayerMoveFoward;
		}
		else if (Keyboard::Get()->Press('S'))
		{
			if (attackType == PlayerAttackType::LongBow)
				next = PlayerAnimationState::FightBowMoveBack;
			else
				next = PlayerAnimationState::PlayerMoveFoward;
		}

		if (Keyboard::Get()->Press('W'))
		{
			Position -= Forward * Time::Delta() * 10;
		}
		else if (Keyboard::Get()->Press('S'))
		{
			Position += Forward * Time::Delta() * 10;
		}

		if (Keyboard::Get()->Press('A'))
		{
			Rotation.y -= 100 * Time::Delta();
		}
		else if (Keyboard::Get()->Press('D'))
		{
			Rotation.y += 100 * Time::Delta();
		}
	}








	transform->Position(Position);
	transform->RotationDegree(Rotation);

	kachujin->UpdateTransforms();
}

void Player::Swap()
{
	if (Keyboard::Get()->Down('1'))
	{
		attackType = PlayerAttackType::Hand;
		ChangeTexture(0, kachujin, currentWeapon, NULL);
	}
	else if (Keyboard::Get()->Down('2'))
	{
		attackType = PlayerAttackType::Sword;
		ChangeTexture(1, kachujin, currentWeapon, weapon[0]);
	}
	else if (Keyboard::Get()->Down('3'))
	{
		attackType = PlayerAttackType::LongBow;
		ChangeTexture(2, kachujin, currentWeapon, weapon[1]);
	}
}

void Player::AttackHand()
{
	if (Mouse::Get()->Down(0))
	{
		attackCount++;
		attackCount = attackCount % 2;

		next = (PlayerAnimationState)(attackCount + 6);
		currentActionTime = 0.0f;
		maxActionTime = 2.0f;
	}

	if (Mouse::Get()->Down(1))
	{
		if (current == PlayerAnimationState::FightHandJap)
		{
			next = PlayerAnimationState::FightHandKick;
			currentActionTime = 0.0f;
			maxActionTime = 2.0f;
		}

	}

	bool isHit = false;

	if (currentActionTime < maxActionTime)
	{
		vector<Monster*>& list = BattleManager::GetInstance()->GetMonsterList();

		for (int i = 0; i < list.size(); i++)
		{
			vector<ColliderDesca>& col = list[i]->GetCollider();
			for (int j = 0; j < col.size(); j++)
			{
				if (colliderRightFoot.collider->IsIntersect(col[j].collider))
				{
					isHit = true;
					list[i]->PlayHitAnimation(j);
				}


			}

			if (isHit == true)
			{
				colliderLeftHand.collider->Render(Color(1, 0, 0, 1));
				colliderRightHand.collider->Render(Color(1, 0, 0, 1));
				colliderRightFoot.collider->Render(Color(1, 0, 0, 1));
			}
				
			else
			{
				colliderLeftHand.collider->Render(Color(0, 1, 0, 1));
				colliderRightHand.collider->Render(Color(0, 1, 0, 1));
				colliderRightFoot.collider->Render(Color(0, 1, 0, 1));
			}
				
		}


	}
}

void Player::AttackSword()
{

	if (Mouse::Get()->Down(0))
	{
		attackCount++;
		attackCount = attackCount % 2;

		next = (PlayerAnimationState)(attackCount + 9);
		currentActionTime = 0.0f;
		maxActionTime = 2.0f;
	}

	if (Mouse::Get()->Down(1))
	{
		if (current == PlayerAnimationState::PlayerMoveFoward)
		{
			next = PlayerAnimationState::FightSwordDashAttack;
			currentActionTime = 0.0f;
			maxActionTime = 2.0f;
		}

		if (current == PlayerAnimationState::FightSwordCasting)
		{
			next = PlayerAnimationState::FightSwordSpinAttack;
			currentActionTime = 0.0f;
			maxActionTime = 2.0f;
		}

	}

	bool isHit = false;

	if (currentActionTime < maxActionTime)
	{
		vector<Monster*>& list = BattleManager::GetInstance()->GetMonsterList();
		
		for (int i = 0; i < list.size(); i++)
		{
			vector<ColliderDesca>& col = list[i]->GetCollider();
			for (int j = 0; j < col.size(); j++)
			{
				if (colliderSword.collider->IsIntersect(col[j].collider))
				{
					isHit = true;
					list[i]->PlayHitAnimation(j);
				}

					
			}

			if (isHit == true)
				colliderSword.collider->Render(Color(1, 0, 0, 1));
			else
				colliderSword.collider->Render(Color(0, 1, 0, 1));
		}


	}
}

void Player::AttackLongBow()
{
	if (Mouse::Get()->Down(0))
	{
		attackCount++;

		next = PlayerAnimationState::FightBowAimArrow;

		currentActionTime = 0.0f;
		maxActionTime = 2.0f;
	}

	if (attackCount > 0 && Mouse::Get()->Up(0))
	{
		next = PlayerAnimationState::FightBowFireArrow;

		Vector3 position;
		Vector3 direction;

		kachujin->GetTransform(0)->Position(&position);
		direction = kachujin->GetTransform(0)->Forward();

		arrow->ActiveArrow(position, direction);

		currentActionTime = 0.0f;
		maxActionTime = 2.0f;
	}
}
