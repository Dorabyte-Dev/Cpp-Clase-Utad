#include <cstdio>

class CEntity
{
protected:
	const char* name;
	int x;
	int y;
	int health;
public:
	CEntity(const char* _name, int _x, int _y)
		: name{_name}
		, x{_x}
		, y{_y}
	{
		health = 0;
		printf("CEntity(%s)\n", name);
	}
	virtual ~CEntity()
	{
		printf("~CEntity(%s)\n", name);
	}
	void Move(int iDX, int iDY)
	{
		x += iDX;
		y += iDY;
	}
	void TakeDamage(int iDamage)
	{
		health -= iDamage;
		if(health < 0)
		{
			health = 0;
		}
	}
	bool IsAlive()
	{
		return health != 0;
	}
	void Print()
	{
		printf("%s en (%d,%d) con %d de vida\n", name, x, y, health);
	}
	virtual void Update()
	{

	}
};

class CPlayer : public CEntity
{
private:
	int score;

public:
	CPlayer(const char* _name, int _x, int _y) : CEntity(_name, _x, _y)
	{
		score = 0;
		health = 100;
		printf("CPlayer(%s)\n", name);
	}
	virtual ~CPlayer() override
	{
		printf("~CPlayer(%s)\n", name);
	}

	virtual void Update() override
	{
		Move(1, 0);
		AddScore(1);
	}

	void AddScore(int _score)
	{
		score += _score;
	}

	void Heal(int _healAmount)
	{
		if(IsAlive())
		{
			health += _healAmount;
			if(health > 100)
			{
				health = 100;
			}
		}
	}
};

class CEnemy : public CEntity
{
private:
	int damage;
	CEntity* target;
public:
	CEnemy(const char* _name, int _x, int _y, int _damage) : CEntity(_name, _x, _y)
	{
		health = 30;
		target = nullptr;
		damage = _damage;
		printf("CEnemy(%s)\n", name);
	}
	virtual ~CEnemy() override
	{
		printf("~CEnemy(%s)\n", name);
	}
	virtual void Update() override
	{
		Move(-1, 0);
		if(target != nullptr)
		{
			Attack(*target);
		}
	}

	void SetTarget(CEntity* _pTarget)
	{
		target = _pTarget;
	}
	void Attack(CEntity& _rOther)
	{
		_rOther.TakeDamage(damage);
	}
};

class CTurret : public CEnemy
{
public :
	CTurret(const char* _name, int _x, int _y, int _damage) : CEnemy(_name, _x, _y, _damage)
	{
		health = 50;
	}
};


int main()
{
	CEntity* pPlayer = new CPlayer("Heroe", 0, 0);
	CEntity* pOrc = new CEnemy("Orco", 5, 0, 25);
	CEntity* pGoblin = new CEnemy("Trasgo", 8, 3, 15);
	CEntity* pTurret = new CTurret("Turret", 10, 2, 5);

	static_cast<CEnemy*>(pOrc)->SetTarget(pPlayer);
	static_cast<CEnemy*>(pGoblin)->SetTarget(pPlayer);
	static_cast<CEnemy*>(pTurret)->SetTarget(pOrc);

	/*oPlayer.Move(2, 1);
	oOrc.Attack(oPlayer);
	oOrc.Attack(oPlayer);
	oPlayer.Print();
	oGoblin.Attack(oOrc);
	oGoblin.Attack(oOrc);
	if(!oOrc.IsAlive())
	{
		oPlayer.AddScore(10);
	}*/

	CEntity* tEntities[] = { pPlayer, pOrc, pGoblin, pTurret };

	for(int iTurn = 1; iTurn <= 3; ++iTurn)
	{
		for(CEntity* pEntity : tEntities)
			pEntity->Update(); 
		for(CEntity* pEntity : tEntities)
			pEntity->Print();
	}
	for(CEntity* pEntity : tEntities)
		delete pEntity;
		
}