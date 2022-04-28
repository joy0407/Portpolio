#include "pch.h"
#include "Monster.h"


Monster::Monster()
{
	for (int i = 0; i < 2; i++)
		currentActionTime[i] = 0;
}


Monster::~Monster()
{
}

void Monster::Update()
{
	for (int i = 0; i < 2; i++)
		currentActionTime[i] += Time::Delta();

	CheckState();

	Action();

	PlayAnimation();

	test->UpdateTransforms();
}

void Monster::Render()
{
	Pass(0, 1, 2);
}

void Monster::PlayHitAnimation(int index)
{
	//test->PlayClip(index, 1);
	state[index] = MonsterActionState::Hit;
	currentActionTime[index] = 0.0f;
	maxActionTime[index] = 2.0f;
	//next[index] = MonsterAnimationState::MonsterHit;
}

void Monster::Pass(UINT mesh, UINT model, UINT anim)
{
	for (ModelAnimator* temp : animators)
		temp->Pass(anim);
}

void Monster::CheckState()
{
	Vector3 playerPosition = BattleManager::GetInstance()->GetPlayer()->GetPosition();

	Vector3 monsterPosition;
	float length;
	for (int i = 0; i < 2; i++)
	{
		test->GetTransform(i)->Position(&monsterPosition);

		length = D3DXVec3Length(&(monsterPosition - playerPosition));

		if (currentActionTime[i] > maxActionTime[i])
		{
			state[i] = MonsterActionState::Idle;
		}

		if (state[i] != MonsterActionState::Hit)
		{
			if (length < 10)
			{
				state[i] = MonsterActionState::Fight;
			}
			else if (length < 50)
			{
				state[i] = MonsterActionState::Trace;
			}
			else
			{
				if (currentActionTime[i] > maxActionTime[i])
				{
					state[i] = MonsterActionState::Idle;

				}
			}
		}



	}
}

void Monster::Action()
{
	for (int i = 0; i < 2; i++)
	{
		switch (state[i])
		{
		case MonsterActionState::Idle:
			Idle(i);
			break;
		case MonsterActionState::Move:
			Move(i);
			break;
		case MonsterActionState::Fight:
			Attack(i);
			break;
		case MonsterActionState::Trace:
			Trace(i);
			break;
		case MonsterActionState::Hit:
			Hit(i);
			break;
		case MonsterActionState::Dead:
			Dead(i);
			break;
		default:
			break;
		}
	}

}
