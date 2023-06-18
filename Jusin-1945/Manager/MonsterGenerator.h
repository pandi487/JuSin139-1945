#pragma once

#include "CObj.h"

typedef struct _MONSTER_CREATE_INFO
{
	// ���ð� �� (������)
	DWORD	dwTime;
	// ���� ��ġ
	POINT	ptPosition;
	// ���� ü��
	int		iHP;
	// ���� ����
	int		iType;
}MONSTER_CREATE_INFO;

/*
* ���͸� ������ ���� �������� �����ϰ� �ı��Ǵ� Ŭ����
* MonsterGenerateManager���� �߰��Ǿ� �����Ǵ� Ŭ�����̴�.
*/

class CMonsterGenerator : public CObj
{
public:
	CMonsterGenerator();
	virtual ~CMonsterGenerator();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override {}
	virtual void Release(void) override;
    virtual void Collide(CObj& _rDst) override {}

private:
	void Create_Monster(DWORD& _timer);

public:
	enum TIMER_FOR { CREATE, TIMER_END };
	enum MONSTER_TYPE { NORMAL, SPEED, BOSS, MONSTER_TYPE_END };
	// INSTANT	: ���� ��� ��ȯ�ϸ� ���� ��.
	// WAVE		: ��� ���� �׾�� ���� ��.
	enum GENERATOR_TYPE	{ INSTANT, WAVE, GENERATOR_TYPE_END };

protected:
	// ���� ���� ����
	list<MONSTER_CREATE_INFO>		m_MonsterCreateList;

	// ���� ���� ����Ʈ (WAVE��)
	list<CObj*>		m_MonsterObsList;

	GENERATOR_TYPE	m_eType = INSTANT;

	// ���� ���ӿ� �߰��ϱ� ���� ������
	list<CObj*>* m_MainGame_MonsterList = nullptr;

protected:
    bool m_bStart_Create = false;

public:
	void Set_MonsterList(list<CObj*>* value) { m_MainGame_MonsterList = value; }

	// ���� ������ �߰��ϱ�
	void Add_Monster(MONSTER_CREATE_INFO value)
	{
		m_MonsterCreateList.push_back(value);
	}

    void Set_Type(GENERATOR_TYPE value) { m_eType = value; }

    void Set_StartCreate() { m_bStart_Create = true; }
};

