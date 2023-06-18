#include "Monster.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_iTeam = 2;
}

void CMonster::Change_Angle(){
	m_fAngle += 180.f;
}