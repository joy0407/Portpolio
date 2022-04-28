#pragma once

enum MonsterAnimationState
{
	Default = 0, MonsterMoveLeft, MonsterMoveRight, MonsterMoveFoward, MonsterMoveBack,
	FightWeaponIdle, FightWeaponUse,
	FightWeaponGetArrow, FightWeaponWeaponAimArrow, FightWeaponBowFireArrow,
	TraceMoveForward, TraceMoveBack, TraceLeft, TraceRight,
	MonsterHit, MonsterDead
};

enum MonsterActionState
{
	Idle = 0, Move, Fight, Trace, Hit, Dead
};

struct ColliderDesca
{
	Transform * Init;
	Collider * collider;
	Transform * colliderTransform;
};

class Monster
{
public:
	Monster();
	virtual ~Monster();

	virtual void Update();
	virtual void Render();

	vector<ColliderDesca>&  GetCollider() { return collidertemp; }

	void PlayHitAnimation(int index);

protected:
	void Pass(UINT mesh, UINT model, UINT anim);

	void CheckState();
	void Action();
	virtual void PlayAnimation() = 0;
	
	virtual void Idle(int index) = 0;
	virtual void Move(int index) = 0;
	virtual void Attack(int index) = 0;
	virtual void Trace(int index) = 0;
	virtual void Hit(int index) = 0;
	virtual void Dead(int index) = 0;

	

protected:
	Shader * shader;

	ModelAnimator * test;

	ColliderDesca collider[2];// , collidertemp[1];

	MonsterActionState state[2];

	MonsterAnimationState currnet[2];
	MonsterAnimationState next[2];

	float maxActionTime[2];
	float currentActionTime[2];

	Vector3 moveDirection[2];

	vector<ModelAnimator *> animators;
	vector<ColliderDesca> collidertemp;
};

