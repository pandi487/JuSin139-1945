#include "framework.h"
#include "CMainGame.h"

CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
}

void CMainGame::Update()
{
	for (size_t i = 0; i < OBJID_END; i++) {

	}
}

void CMainGame::Late_Update()
{
}

void CMainGame::Render()
{
}

void CMainGame::Release()
{
}
