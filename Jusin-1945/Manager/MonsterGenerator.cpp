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

        // ���� Ÿ�̸�
        if (0 == m_dwTimers[CREATE])
        {
            Create_Monster(m_dwTimers[CREATE]);
        }
    }

	return OBJ_NOEVENT;
}

void CMonsterGenerator::Late_Update(void)
{
	// WAVE Ÿ���� �� ������ ��� ���Ͱ� ����� �ı�
	if (WAVE == m_eType)
	{
		if (!m_MonsterObsList.empty() && nullptr != m_MainGame_MonsterList)
		{
			// ���� ���ӿ��� �����Ǵ� ���� ����Ʈ�� ����
			// ���� ������ �ִ� ���Ͱ� �����Ǿ����� Ȯ���Ѵ�.
			for (auto iter = m_MonsterObsList.begin(); iter != m_MonsterObsList.end();)
			{
				auto iterFound = find_if(m_MainGame_MonsterList->begin(), m_MainGame_MonsterList->end(), [&iter](CObj* obj) {
					return (*iter == obj);
					});
				
				// �����Ǿ��ٰ� �Ǵ��ϸ� ����Ʈ���� �����Ѵ�.
				if (iterFound == m_MainGame_MonsterList->end())
				{
					iter = m_MonsterObsList.erase(iter);
				}
				else
					++iter;
			}
		}

		// ���� ������ �տ� �ֱ� ������, ��� ����Ʈ�� ������� �����⸦ ���δ�.
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

	// MONSTER_CREATE_INFO�� ���� ���� ����
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

	// ������ ���� �����ϱ�
	m_MonsterCreateList.pop_front();

	// ���� ���� �����̸� Ÿ�̸ӿ� ���
	if (!m_MonsterCreateList.empty())
	{
		m_dwTimers[CREATE] = m_MonsterCreateList.front().dwTime;
	}
	// ���� �� ��ȯ������ �����ϱ�
	else if (INSTANT == m_eType)
		m_bDead = true;
}