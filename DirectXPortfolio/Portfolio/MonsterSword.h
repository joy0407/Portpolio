#pragma once

class MonsterSword : public Monster
{
public:
	MonsterSword();
	~MonsterSword();

	void Update() override;
	void Render() override;

protected:
	// Monster��(��) ���� ��ӵ�
	virtual void PlayAnimation() override;

	virtual void Idle(int index) override;
	virtual void Move(int index) override;
	virtual void Attack(int index) override;
	virtual void Trace(int index) override;
	virtual void Hit(int index) override;
	virtual void Dead(int index) override;
};

