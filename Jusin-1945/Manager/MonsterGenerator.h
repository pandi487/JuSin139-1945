#pragma once

#include "CObj.h"

typedef struct _MONSTER_CREATE_INFO
{
	// 상대시간 값 (딜레이)
	DWORD	dwTime;
	// 몬스터 위치
	POINT	ptPosition;
	// 몬스터 체력
	int		iHP;
	// 몬스터 종류
	int		iType;
}MONSTER_CREATE_INFO;

/*
* 몬스터를 딜레이 값을 기준으로 생성하고 파괴되는 클래스
* MonsterGenerateManager에서 추가되어 관리되는 클래스이다.
*/

class CMonsterGenerator : public CObj
{
public:
	CMonsterGenerator();
	virtual ~CMonsterGenerator();

public:
	// CObj을(를) 통해 상속됨
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
	// INSTANT	: 적을 모두 소환하면 삭제 됨.
	// WAVE		: 모든 적이 죽어야 삭제 됨.
	enum GENERATOR_TYPE	{ INSTANT, WAVE, GENERATOR_TYPE_END };

protected:
	// 몬스터 정보 저장
	list<MONSTER_CREATE_INFO>		m_MonsterCreateList;

	// 몬스터 감시 리스트 (WAVE용)
	list<CObj*>		m_MonsterObsList;

	GENERATOR_TYPE	m_eType = INSTANT;

	// 메인 게임에 추가하기 위한 포인터
	list<CObj*>* m_MainGame_MonsterList = nullptr;

protected:
    bool m_bStart_Create = false;

public:
	void Set_MonsterList(list<CObj*>* value) { m_MainGame_MonsterList = value; }

	// 몬스터 정보를 추가하기
	void Add_Monster(MONSTER_CREATE_INFO value)
	{
		m_MonsterCreateList.push_back(value);
	}

    void Set_Type(GENERATOR_TYPE value) { m_eType = value; }

    void Set_StartCreate() { m_bStart_Create = true; }
};

