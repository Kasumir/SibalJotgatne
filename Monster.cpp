// Monster.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "Monster.h"



// Monster

IMPLEMENT_DYNAMIC(Monster, CWnd)

Monster::Monster() // 몬스터 생성. 매개변수로 원하는 위치에 생성.
{
	jumpcount = 6;
	m_UDstate = DOWN;
	m_LRstate = STOP;
	LRcount = 0;
}

Monster::~Monster()
{
	m_visible = FALSE;
}


BEGIN_MESSAGE_MAP(Monster, CWnd)
END_MESSAGE_MAP()



// Monster 메시지 처리기입니다.




void Monster::MoveState()//돌아다니다가 유저를 인식하면 쫓아감
{
	int random1;
	random1 = rand() % 100;

if(LRcount == 0)
	if (random1%2 == 0 && random1 != 0) // 몬스터가 랜덤으로 돌아다님. 근데 점프 횟수를 더 적게.
	{
		m_LRstate = LEFT;
		LRcount++;
	}
	else if (random1%2 == 1)
	{
		m_LRstate = RIGHT;
		LRcount++;
	}
	else  if(random1 == 0)// 랜덤으로 점프
	{
		for (; jumpcount<6; jumpcount++)
			m_UDstate = UP;
	}

	if (LRcount == 1000)
		LRcount = 0;
	
	//if( 1차 충돌판정시 쫓아감. (1차 충돌판정 : 몬스터가 캐릭터를 인식하는 범위))

	switch (m_UDstate) {
	case STOP:
		pos.y += 0;
		break;
	case UP:
		pos.y -= 16;
		jumpcount = 0;
		break;
	case DOWN:
		pos.y += 16;
		break;
	}
	switch (m_LRstate) {
	case STOP:
		pos.x += 0;
		break;
	case LEFT:
			pos.x -= 8; 
		break;
	case RIGHT:
			pos.x += 8;
		break;
	}
	
}


void Monster::StopState()//게임대기상태나 캐릭터에게 공격당해서 갇혀있는 상태
{
	m_LRstate = STOP;
	m_UDstate = STOP;
	pos.x += 0;
	pos.y += 0;

	/*
	if(게임이 켜져있는 상태 && 캐릭터랑 부딪힌다면)
	몬스터 소멸

	*/
}


void Monster::check()
{
	POSITION p;
	CPoint pos;
	int count = 0;
	for (p = Tile_list.GetHeadPosition(); p != NULL;) // 모든 벽돌에 대해 돎.
	{
		pos = Tile_list.GetNext(p);
		if (m_UDstate == DOWN) // 떨어지다가 땅에 붙도록.
		{
			if (pos.x > pos.x - M_SIZE && pos.x < pos.x + B_SIZE && pos.y > pos.y - M_SIZE && pos.y < pos.y - M_SIZE + B_SIZE / 2)
			{
				m_UDstate = STOP;
				pos.y = pos.y - M_SIZE;
			}
		}
		else if (m_UDstate == STOP) // 밑에 벽돌이 있는지 없는지 검사.
			if (!(pos.x > pos.x - M_SIZE && pos.x < pos.x + B_SIZE && pos.y > pos.y - M_SIZE && pos.y < pos.y - M_SIZE + B_SIZE / 2))
				count++;//밑에 모든 벽돌이 없는지 검사.
	}
	if (count == Tile_list.GetCount())
		m_UDstate = DOWN; // 타일숫자 = 검사한 숫자 -> 떨어짐.
	if (jumpcount == 6) // 점프가 6번 프레임 만큼 돌고 떨어짐.
		m_UDstate = DOWN;
}


void Monster::MonsterDie()
{
	m_visible = FALSE;
}

void Monster::MonsterCreate(int x, int y)
{
	m_visible = TRUE;
	pos.x = x;
	pos.y = y;
}
