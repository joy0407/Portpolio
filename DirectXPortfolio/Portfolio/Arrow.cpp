#include "pch.h"
#include "Arrow.h"


Arrow::Arrow(bool hasArrow)
	:isPlayer(hasArrow)
{
	shader = new Shader(L"27_Animation.fx");

	CreateArrow();
}


Arrow::~Arrow()
{
}

void Arrow::Update()
{
	
	UpdateCollider();
	CheckCollider();

	arrow->UpdateTransforms();
	arrow->Update();
}

void Arrow::Render()
{
	Pass(0, 1, 2);

	arrow->Render();
}

void Arrow::CreateArrow()
{
	arrow = new ModelRender(shader);
	arrow->ReadMaterial(L"Weapon/LongArrow");
	arrow->ReadMesh(L"Weapon/LongArrow");

	Transform * transform;
	for (int i = 0; i < 3; i++)
	{
		transform = arrow->AddTransform();
		transform->RotationDegree(90, 0, 0);
		transform->Scale(0.5f, 0.5f, 0.5f);
	}



	for (int i = 0; i < 3; i++)
	{
		colliderArrow[i].Init = new Transform();
		colliderArrow[i].Init->Scale(5, 10, 5);
		colliderArrow[i].Init->Position(0, 0, 0);
		colliderArrow[i].colliderTransform = new Transform();
		colliderArrow[i].collider = new Collider(colliderArrow[i].colliderTransform, colliderArrow[i].Init);
	}
}

void Arrow::CheckCollider()
{
	for (int k = 0; k < 3; k++)
	{
		if (isArrowFire[k] == true)
		{
			bool isHit = false;
			if(isPlayer == false)
			{
				// need to test
				Player * player = BattleManager::GetInstance()->GetPlayer();

				if (colliderArrow[k].collider->IsIntersect(player->GetCollider()))
				{
					colliderArrow[k].collider->Render(Color(1, 0, 0, 1));
				}
				else
				{
					colliderArrow[k].collider->Render(Color(0, 1, 0, 1));
				}
			}
			else
			{
				vector<Monster*>& list = BattleManager::GetInstance()->GetMonsterList();

				for (int i = 0; i < list.size(); i++)
				{
					vector<ColliderDesca>& col = list[i]->GetCollider();
					for (int j = 0; j < col.size(); j++)
					{
						if (colliderArrow[k].collider->IsIntersect(col[j].collider))
						{
							isHit = true;
							list[i]->PlayHitAnimation(j);
						}


					}

					if (isHit == true)
						colliderArrow[k].collider->Render(Color(1, 0, 0, 1));
					else
						colliderArrow[k].collider->Render(Color(0, 1, 0, 1));

				}
			}
		}
	}
}

void Arrow::Pass(UINT mesh, UINT model, UINT anim)
{
	arrow->Pass(model);
}

void Arrow::UpdateCollider()
{
	for (int i = 0; i < 3; i++)
	{
		Vector3 position;
		arrow->GetTransform(i)->Position(&position);
		position -= direction[i] * Time::Delta() * 10;
		arrow->GetTransform(i)->Position(position);
	}

	for (int i = 0; i < 3; i++)
	{
		Matrix matrix = arrow->GetTransform(i)->World();
		colliderArrow[i].collider->GetTransform()->World(matrix);
		colliderArrow[i].collider->Update();
	}
}

void Arrow::ActiveArrow(Vector3 startPosition, Vector3 direction)
{
	float angle = atan2(direction.z, -direction.x) - Math::PI / 2;

	for (int i = 0; i < 3; i++)
	{
		if (isArrowFire[i] == false)
		{
			isArrowFire[i] = true;
			arrow->GetTransform(i)->Position(startPosition.x, 10, startPosition.z);
			arrow->GetTransform(i)->Rotation(Math::PI / 2, angle, 0);
			this->direction[i] = direction;
			break;
		}
	}
}
