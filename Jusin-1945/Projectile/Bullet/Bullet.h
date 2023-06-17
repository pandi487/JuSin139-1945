#pragma once

#include "CObj.h"

class CBullet abstract : public CObj
{
public:
    CBullet();
    virtual ~CBullet();

public:
    void Set_Bulletinfo(float _fRadian, float _Xpos, float _Ypos);
    // 총알의 각도와 생성좌표를 설정해주는 함수
    void Set_Bulletinfo(float _Xpos, float _Ypos);
    // 라디안이 필요하지 않은 총알의 생성좌표 설정
};

