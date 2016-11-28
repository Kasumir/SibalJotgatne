// Monster.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "Monster.h"


// Monster

IMPLEMENT_DYNAMIC(Monster, CWnd)

Monster::Monster(int x, int y) // 몬스터 생성. 매개변수로 원하는 위치에 생성.
{
	pos.x = x;
	pos.y = y;
	m_visible = TRUE;
}

Monster::~Monster()
{
}


BEGIN_MESSAGE_MAP(Monster, CWnd)
END_MESSAGE_MAP()



// Monster 메시지 처리기입니다.




void Monster::MoveState()//돌아다니다가 유저를 인식하면 쫓아감
{
	int random1, random2;
	random1 = rand() % 2;
	random2 = rand() % 20 + 1;

	/* 
	블록에 안에서만 좌우로 돌아다니는 경우
	if(random == 0)
		for(int i=0;i<random2;i++)
			pos.x += 8;
	else
		for(int i=0;i<random2;i++)
			pos.x -= 8;
	
	블록에서 떨어졌을 경우인 친구들.
	pos.y += 16;
	pos.y -= 16;
	
	if( 캐릭터객체 어떻게 생성하지? 캐릭터객체.좌표 +- 15 < = 몬스터객체 좌표. 10 ) if문 4개로 쫓아가는거 구현
	
	*/
	
}


void Monster::StopState()//게임대기상태나 캐릭터에게 공격당해서 갇혀있는 상태
{
	pos.x = pos.x;
	pos.y = pos.y;

	/*
	if(게임이 켜져있는 상태 && 캐릭터랑 부딪힌다면)
	몬스터 소멸

	*/
}
