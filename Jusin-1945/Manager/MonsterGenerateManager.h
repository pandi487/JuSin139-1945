#pragma once

#include "CObj.h"
#include "MonsterGenerator.h"

/*
* 적을 생성하는 MonsterGenerator를 저장하고 절대시간으로
* MonsterGenerator의 적 생성기를 작동시키는 클래스
* 타이머는 게임 시작과 동시에 작동되며, 특정 타이밍에 리스트의 특정 생성기를 생성하여 작동시킨다.
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
	// 몬스터 생성기 저장
	list<CMonsterGenerator*>		m_GeneratorList;

	// 생성기 등록하기 위한 포인터
	list<CObj*>* m_MainGame_GeneratorList;

	// 메인 게임에 추가하기 위한 포인터
	list<CObj*>* m_MainGame_MonsterList;

public:
	void Set_GeneratorList(list<CObj*>* value) { m_MainGame_GeneratorList = value; }
	void Set_MonsterList(list<CObj*>* value) { m_MainGame_MonsterList = value; }
};