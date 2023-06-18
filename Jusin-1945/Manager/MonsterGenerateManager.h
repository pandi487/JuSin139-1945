#pragma once

#include "CObj.h"
#include "MonsterGenerator.h"

/*
* ���� �����ϴ� MonsterGenerator�� �����ϰ� ����ð�����
* MonsterGenerator�� �� �����⸦ �۵���Ű�� Ŭ����
* Ÿ�̸Ӵ� ���� ���۰� ���ÿ� �۵��Ǹ�, Ư�� Ÿ�ֿ̹� ����Ʈ�� Ư�� �����⸦ �����Ͽ� �۵���Ų��.
*/

class CMonsterGenerateManager abstract : public CObj
{
public:
	enum { };
public:
	CMonsterGenerateManager();
	virtual ~CMonsterGenerateManager();

public:
	enum TIMER_FOR { CREATE, TIMER_FOR_END };

protected:
	// ���� ������ ����
	list<CMonsterGenerator*>		m_GeneratorList;

	// ������ ����ϱ� ���� ������
	list<CObj*>* m_MainGame_GeneratorList;

	// ���� ���ӿ� �߰��ϱ� ���� ������
	list<CObj*>* m_MainGame_MonsterList;

public:
	void Set_GeneratorList(list<CObj*>* value) { m_MainGame_GeneratorList = value; }
	void Set_MonsterList(list<CObj*>* value) { m_MainGame_MonsterList = value; }
};