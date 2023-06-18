#include "MonsterGenMng_Stage1.h"

#include "Manager/MonsterGenerator.h"
#include "Manager/CMainGame.h"
#include "AbstractFactory.h"

CMonsterGenMng_Stage1::CMonsterGenMng_Stage1()
{
}

CMonsterGenMng_Stage1::~CMonsterGenMng_Stage1()
{
}

void CMonsterGenMng_Stage1::Initialize(void)
{
	m_dwTimers.resize(TIMER_FOR_END);
	for (auto& timer : m_dwTimers)
		timer = 1;

	m_MainGame_GeneratorList = &CMainGame::Get_Instance().Get_ObjList()[MANAGER];
	m_MainGame_MonsterList = &CMainGame::Get_Instance().Get_ObjList()[MONSTER];
}

int CMonsterGenMng_Stage1::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Timers();

	// 생성 타이머
	if (0 == m_dwTimers[CREATE])
	{
		Test();
	}

	return OBJ_NOEVENT;
}

void CMonsterGenMng_Stage1::Late_Update(void)
{
}

void CMonsterGenMng_Stage1::Release(void)
{
}

void CMonsterGenMng_Stage1::Test()
{
	m_GeneratorList.push_back(dynamic_cast<CMonsterGenerator*>(CAbstractFactory<CMonsterGenerator>::Create()));
	for (int i = 0; i < 1000; ++i)
	{
		int randomX = (rand() % (WINCX - 200)) + 100;
		DWORD randomTime = rand() % 10 + 1;
		m_GeneratorList.back()->Add_Monster({ randomTime, { randomX, 0 }, 10, 0 });
	}
}