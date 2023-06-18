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
		timer = 200;

	m_MainGame_GeneratorList = &CMainGame::Get_Instance().Get_ObjList()[MANAGER];
	m_MainGame_MonsterList = &CMainGame::Get_Instance().Get_ObjList()[MONSTER];

    Phase_1();
	Phase_2();
	Phase_3();
	Phase_4();
	Phase_5();
	Phase_Boss();
}

int CMonsterGenMng_Stage1::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Timers();

	// 생성 타이머
	if (0 == m_dwTimers[CREATE])
	{
        if (!m_GeneratorList.empty())
        {
		    m_GeneratorList.front()->Set_StartCreate();
        }
	}

    if (m_GeneratorList.front()->Get_Dead())
    {
        m_GeneratorList.pop_front();

        if (!m_GeneratorList.empty())
        {
            m_GeneratorList.front()->Set_StartCreate();
        }
    }

	return OBJ_NOEVENT;
}

void CMonsterGenMng_Stage1::Late_Update(void)
{
    if (m_GeneratorList.empty())
        m_bDead = true;
}

void CMonsterGenMng_Stage1::Release(void)
{
}

void CMonsterGenMng_Stage1::Phase_1()
{
    CMonsterGenerator* pGenerator = dynamic_cast<CMonsterGenerator*>(CAbstractFactory<CMonsterGenerator>::Create());
	m_GeneratorList.push_back(pGenerator);
    m_GeneratorList.back()->Set_Type(CMonsterGenerator::GENERATOR_TYPE::WAVE);
	for (int i = 0; i < 25; ++i)
	{
		int randomX = (rand() % (WINCX - 280)) + 140;
		DWORD randomTime = rand() % 10 + 30;
		m_GeneratorList.back()->Add_Monster({ randomTime, { randomX, 0 }, 10, CMonsterGenerator::MONSTER_TYPE::NORMAL });
	}
}

void CMonsterGenMng_Stage1::Phase_2()
{
	CMonsterGenerator* pGenerator = dynamic_cast<CMonsterGenerator*>(CAbstractFactory<CMonsterGenerator>::Create());
	m_GeneratorList.push_back(pGenerator);
    m_GeneratorList.back()->Set_Type(CMonsterGenerator::GENERATOR_TYPE::WAVE);
    for (int i = 0; i < 25; ++i)
	{
		int randomX = (rand() % (WINCX - 280)) + 140;
		DWORD randomTime = rand() % 10 + 30;
		m_GeneratorList.back()->Add_Monster({ randomTime, { randomX, 0 }, 10, CMonsterGenerator::MONSTER_TYPE::NORMAL });
	}
}

void CMonsterGenMng_Stage1::Phase_3()
{
	CMonsterGenerator* pGenerator = dynamic_cast<CMonsterGenerator*>(CAbstractFactory<CMonsterGenerator>::Create());
	m_GeneratorList.push_back(pGenerator);
    m_GeneratorList.back()->Set_Type(CMonsterGenerator::GENERATOR_TYPE::WAVE);

    pGenerator->Add_Monster({ 60, { WINCX / 2, 0 }, 10, CMonsterGenerator::MONSTER_TYPE::BOSS });
}

void CMonsterGenMng_Stage1::Phase_4()
{
	CMonsterGenerator* pGenerator = dynamic_cast<CMonsterGenerator*>(CAbstractFactory<CMonsterGenerator>::Create());
	m_GeneratorList.push_back(pGenerator);
    m_GeneratorList.back()->Set_Type(CMonsterGenerator::GENERATOR_TYPE::WAVE);

    pGenerator->Add_Monster({ 60, { WINCX / 2, 0 }, 10, CMonsterGenerator::MONSTER_TYPE::BOSS });
}

void CMonsterGenMng_Stage1::Phase_5()
{
	CMonsterGenerator* pGenerator = dynamic_cast<CMonsterGenerator*>(CAbstractFactory<CMonsterGenerator>::Create());
	m_GeneratorList.push_back(pGenerator);
    m_GeneratorList.back()->Set_Type(CMonsterGenerator::GENERATOR_TYPE::WAVE);

    pGenerator->Add_Monster({ 60, { WINCX / 2, 0 }, 10, CMonsterGenerator::MONSTER_TYPE::BOSS });
}

void CMonsterGenMng_Stage1::Phase_Boss()
{
	CMonsterGenerator* pGenerator = dynamic_cast<CMonsterGenerator*>(CAbstractFactory<CMonsterGenerator>::Create());
	m_GeneratorList.push_back(pGenerator);
    m_GeneratorList.back()->Set_Type(CMonsterGenerator::GENERATOR_TYPE::WAVE);

    pGenerator->Add_Monster({ 60, { WINCX / 2, 0 }, 10, CMonsterGenerator::MONSTER_TYPE::BOSS });
}