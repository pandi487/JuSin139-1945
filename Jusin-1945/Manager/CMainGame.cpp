#include "framework.h"
#include "CMainGame.h"
#include "AbstractFactory.h"
#include "Collision.h"
#include "Stage/MonsterGenMng_Stage1.h"

CMainGame CMainGame::g_pInstance;

CMainGame::CMainGame() : m_iTime(0)
{
	ZeroMemory(m_szTime, sizeof(m_szTime));
	ZeroMemory(m_szName, sizeof(m_szName));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	m_ObjList[PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	dynamic_cast<CPlayer*>(m_ObjList[PLAYER].front())->Set_Bullet(&m_ObjList[BULLET]);
	dynamic_cast<CPlayer*>(m_ObjList[PLAYER].front())->Set_Target(&m_ObjList[MONSTER]);
	dynamic_cast<CPlayer*>(m_ObjList[PLAYER].front())->Set_Laser(&m_ObjList[LASER]);
	dynamic_cast<CPlayer*>(m_ObjList[PLAYER].front())->Set_Shield(&m_ObjList[SHIELD]);
	dynamic_cast<CPlayer*>(m_ObjList[PLAYER].front())->Set_Mini(&m_ObjList[MINIAIRPLANE]);

	m_ObjList[MONSTER].push_back(CAbstractFactory<CMonster_TypeA>::Create(0,0,225));
	
	//몬스터는 다이나믹 캐스팅 해야a하긴 하는데 List 가져올 필요없이 플레이어 하나만 넣으면 될듯?
	if (m_ObjList[MANAGER].empty())
	{
		m_ObjList[MANAGER].push_back(CAbstractFactory<CMonsterGenMng_Stage1>::Create());
	}

	m_ObjList[MOUSE].push_back(CAbstractFactory<CMouse>::Create());
}


void CMainGame::Update()
{
	for (size_t i = 0; i < OBJID_END; i++) {
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();) {
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult) {
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CMainGame::Late_Update()
{
	// 충돌처리
	CCollision::Collision_Sphere(m_ObjList[BULLET], m_ObjList[PLAYER]);
	CCollision::Collision_Sphere(m_ObjList[BULLET], m_ObjList[MONSTER]);
	CCollision::Collision_Sphere(m_ObjList[BULLET], m_ObjList[MINIAIRPLANE]);
	CCollision::Collision_Rect(m_ObjList[LASER], m_ObjList[BULLET]);
	CCollision::Collision_Rect(m_ObjList[LASER], m_ObjList[MONSTER]);
	CCollision::Collision_Sphere(m_ObjList[SHIELD], m_ObjList[MONSTER]);
	CCollision::Collision_Sphere(m_ObjList[SHIELD], m_ObjList[BULLET]);


	for (size_t i = 0; i < OBJID_END; ++i) {
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}
}

void CMainGame::Render()
{
	if (m_dwTime + 1000 <= GetTickCount()) {
		m_dwTime = GetTickCount();
		m_iTime++;
	}

	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	for (size_t i = 0; i < OBJID_END; i++) {
		for (auto& iter : m_ObjList[i])
			iter->Render(m_hDC);
	}

	// 시간 출력
	wsprintf(m_szTime, L"Time : %d", m_iTime);
	TextOut(m_hDC, 50, 40, m_szTime, lstrlen(m_szTime));

	// 게임 이름
	wsprintf(m_szName, L"139기 1차 팀과제");
	TextOut(m_hDC, 430, 40, m_szName, lstrlen(m_szName));
	
}

void CMainGame::Release()
{
	for (size_t i = 0; i < OBJID_END; ++i) {
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

	ReleaseDC(g_hWnd, m_hDC);
}
