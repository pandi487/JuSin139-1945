#include "CObj.h"
#include "CMainGame.h"
#include "MonsterGenerator.h"
#include "AbstractFactory.h"
#include "Unit/GameObject.h"
#include "Monster/Monster.h"
#include "Monster/Monster_TypeA.h"

CMonsterGenerator::CMonsterGenerator()
{
}

CMonsterGenerator::~CMonsterGenerator()
{
}

void CMonsterGenerator::Initialize(void)
{
	m_dwTimers.resize(TIMER_END);
	for (auto& timer : m_dwTimers)
		timer = 1;

	m_MainGame_MonsterList = &CMainGame::Get_Instance().Get_ObjList()[MONSTER];
    CMainGame::Get_Instance().Get_ObjList()[GENERATOR].push_back(this);
}

int CMonsterGenerator::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

    if (m_bStart_Create)
    {
        __super::Update_Timers();

        // 생성 타이머
        if (0 == m_dwTimers[CREATE])
        {
            Create_Monster(m_dwTimers[CREATE]);
        }
    }

	return OBJ_NOEVENT;
}

void CMonsterGenerator::Late_Update(void)
{
	// WAVE 타입일 때 생성한 모든 몬스터가 사망시 파괴
	if (WAVE == m_eType)
	{
		if (!m_MonsterObsList.empty() && nullptr != m_MainGame_MonsterList)
		{
			// 메인 게임에서 관리되는 몬스터 리스트에 대해
			// 현재 가지고 있는 몬스터가 삭제되었는지 확인한다.
			for (auto iter = m_MonsterObsList.begin(); iter != m_MonsterObsList.end();)
			{
				auto iterFound = find_if(m_MainGame_MonsterList->begin(), m_MainGame_MonsterList->end(), [&iter](CObj* obj) {
					return (*iter == obj);
					});
				
				// 삭제되었다고 판단하면 리스트에서 제거한다.
				if (iterFound == m_MainGame_MonsterList->end())
				{
					iter = m_MonsterObsList.erase(iter);
				}
				else
					++iter;
			}
		}

		// 삭제 동작이 앞에 있기 때문에, 모든 리스트가 비워지면 생성기를 죽인다.
		if (m_MonsterObsList.empty())
		{
			m_bDead = true;
		}
	}
}

void CMonsterGenerator::Release(void)
{
	
}

void CMonsterGenerator::Create_Monster(DWORD& _timer)
{
	if (nullptr == m_MainGame_MonsterList || m_MonsterCreateList.empty())
		return;

	MONSTER_CREATE_INFO* pMonsterInfo = &m_MonsterCreateList.front();

	// MONSTER_CREATE_INFO를 토대로 몬스터 생성
	switch (pMonsterInfo->iType)
	{
	case NORMAL:
		m_MainGame_MonsterList->push_back(
			CAbstractFactory<CMonster_TypeA>::Create(pMonsterInfo->ptPosition.x, pMonsterInfo->ptPosition.y)
			);
		break;
	case SPEED:
		m_MainGame_MonsterList->push_back(
			CAbstractFactory<CMonster_TypeA>::Create(pMonsterInfo->ptPosition.x, pMonsterInfo->ptPosition.y)
			);
		break;
	case BOSS:
		m_MainGame_MonsterList->push_back(
			CAbstractFactory<CMonster_TypeA>::Create(pMonsterInfo->ptPosition.x, pMonsterInfo->ptPosition.y)
			);
		break;
	}
    CGameObject* pGameObj = dynamic_cast<CGameObject*>(m_MainGame_MonsterList->back());
    pGameObj->Get_StatusInfo().fMaxHP = (float)pMonsterInfo->iHP;
    pGameObj->Get_StatusInfo().fMaxHP = (float)pMonsterInfo->iHP;

	// 생성된 것은 제외하기
	m_MonsterCreateList.pop_front();

	// 다음 적의 딜레이를 타이머에 등록
	if (!m_MonsterCreateList.empty())
	{
		m_dwTimers[CREATE] = m_MonsterCreateList.front().dwTime;
	}
	// 전부 다 소환했으면 삭제하기
	else if (INSTANT == m_eType)
		m_bDead = true;
}