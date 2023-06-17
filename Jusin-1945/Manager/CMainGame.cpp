#include "framework.h"
#include "CMainGame.h"
#include "AbstractFactory.h"
#include "Collision.h"

CMainGame::CMainGame() : m_iScore(0)
{
	ZeroMemory(m_szScore, sizeof(m_szScore));
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
	dynamic_cast<CPlayer*>(m_ObjList[PLAYER].front())->Set_Enemy(&m_ObjList[MONSTER]);
	dynamic_cast<CPlayer*>(m_ObjList[PLAYER].front())->Set_Laser(&m_ObjList[LASER]);
	dynamic_cast<CPlayer*>(m_ObjList[PLAYER].front())->Set_Shield(&m_ObjList[SHIELD]);
	
	m_ObjList[MONSTER].push_back(CAbstractFactory<CMonster>::Create());
	
	//몬스터는 다이나믹 캐스팅 해야하긴 하는데 List 가져올 필요없이 플레이어 하나만 넣으면 될듯?
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
	CCollision::Collision_Sphere(m_ObjList[BULLET], m_ObjList[MONSTER]);
	CCollision::Collision_Rect(m_ObjList[LASER], m_ObjList[MONSTER]);

	for (size_t i = 0; i < OBJID_END; ++i) {
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}
}

void CMainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	for (size_t i = 0; i < OBJID_END; i++) {
		for (auto& iter : m_ObjList[i])
			iter->Render(m_hDC);
	}

	// 점수출력 -> 추후 scroe class 만들어서 추가
	wsprintf(m_szScore, L"Score : %d", m_iScore);
	TextOut(m_hDC, 50, 60, m_szScore, lstrlen(m_szScore));
}

void CMainGame::Release()
{
	for (size_t i = 0; i < OBJID_END; ++i) {
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

	ReleaseDC(g_hWnd, m_hDC);
}
