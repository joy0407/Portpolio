#pragma once

enum PlayerAnimationState
{
	MoveIdle = 0, PlayerMoveFoward, PlayerMoveBack, PlayerMoveLeft, PlayerMoveRight, PlayerMoveJump,
	FightHandIdle, FightHandJap, FightHandKick,
	FightSwordIdle, FightSwordCasting, FightSwordSpinAttack,
	FightBowIdle, FightBowMoveFoward, FightBowMoveBack, FightBowMoveLeft, FightBowMoveRight,
	FightBowGetArrow, FightBowAimArrow, FightBowFireArrow,
	FightSwordDashAttack
};

enum PlayerState
{
	PlayerIdle = 0, PlayerMove, PlayerAttack, PlayerHit
};

enum PlayerAttackType
{
	Hand = 0, Sword, LongBow
};

class Player
{
public:
	Player();
	~Player();

	void Update();
	void Render();
	
	Collider * GetCollider() { return colliderPlayer.collider; }
	Vector3 GetPosition() { Vector3 position; kachujin->GetTransform(0)->Position(&position); return position; }

private:

	void Kachujin();
	void Pass(UINT mesh, UINT model, UINT anim);

	void ChangeTexture(int index, ModelAnimator * main, Model * before, Model * change);

	void PlayAnimation();
	//
	void UpdateCollider();
	void Attack();
	void Move();
	void Swap();

	//
	void AttackHand();
	void AttackSword();
	void AttackLongBow();

private:
	Shader * shader;

	Model * weapon[3];
	Model * currentWeapon;
	ModelAnimator* kachujin = NULL;

	class Arrow * arrow;
	//ModelRender * arrow;
	//bool isArrowFire[3];

	PlayerState state;
	PlayerAttackType attackType;
	//float attackTime; // change actionTIme?
	float maxActionTime;
	float currentActionTime;
	int attackCount;

	PlayerAnimationState current;
	PlayerAnimationState next;
	int isPlayClip;

	struct ColliderDesc
	{
		Transform * Init;
		Collider * collider;
		Transform * colliderTransform;
	}colliderPlayer, colliderSword, colliderLeftHand, colliderRightHand, colliderRightFoot, colliderArrow[3];

	vector<ModelAnimator *> animators;
};

