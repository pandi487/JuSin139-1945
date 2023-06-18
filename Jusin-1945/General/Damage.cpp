#include "Damage.h"

CDamage::CDamage()
{
}

CDamage::~CDamage()
{
}

void CDamage::Apply_Damage(CObj& _Dst, CObj& _Src)
{
	// 플레이어와 총알 충돌 -> 플레이어 체력 감소
	
	// 플레이어와 몬스터 충돌 -> 플레이어와 몬스터 체력 감소
	
	// 보스와 총알 충돌 -> 보스 체력 감소
}
