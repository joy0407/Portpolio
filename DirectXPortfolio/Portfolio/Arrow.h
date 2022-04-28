#pragma once
class Arrow
{
public:
	Arrow(bool hasArrow);
	~Arrow();

	void Update();
	void Render();

	void ActiveArrow(Vector3 startPosition, Vector3 direction);


private:

	void CreateArrow();
	void CheckCollider();
	void Pass(UINT mesh, UINT model, UINT anim);

	void UpdateCollider();

	

private:
	Shader * shader;

	ModelRender * arrow;
	Vector3 direction[3];
	bool isArrowFire[3];
	bool isPlayer;

	struct ColliderDesc
	{
		Transform * Init;
		Collider * collider;
		Transform * colliderTransform;
	}colliderArrow[3];
};

