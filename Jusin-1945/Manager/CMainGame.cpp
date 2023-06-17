#include "framework.h"
#include "CMainGame.h"
#include "AbstractFactory.h"

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

	//m_ObjList[PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	
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

	wsprintf(m_szScore, L"Score : %d", m_iScore);
	TextOut(m_hDC, 50, 60, m_szScore, lstrlen(m_szScore));
}

void CMainGame::Release()
{
	for (size_t i = 0; i < OBJID_END; ++i) {
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}
