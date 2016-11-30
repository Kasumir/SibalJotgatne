// Monster.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "Monster.h"



// Monster

IMPLEMENT_DYNAMIC(Monster, CWnd)

Monster::Monster() // ���� ����. �Ű������� ���ϴ� ��ġ�� ����.
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



// Monster �޽��� ó�����Դϴ�.




void Monster::MoveState()//���ƴٴϴٰ� ������ �ν��ϸ� �Ѿư�
{
	int random1;
	random1 = rand() % 100;

if(LRcount == 0)
	if (random1%2 == 0 && random1 != 0) // ���Ͱ� �������� ���ƴٴ�. �ٵ� ���� Ƚ���� �� ����.
	{
		m_LRstate = LEFT;
		LRcount++;
	}
	else if (random1%2 == 1)
	{
		m_LRstate = RIGHT;
		LRcount++;
	}
	else  if(random1 == 0)// �������� ����
	{
		for (; jumpcount<6; jumpcount++)
			m_UDstate = UP;
	}

	if (LRcount == 1000)
		LRcount = 0;
	
	//if( 1�� �浹������ �Ѿư�. (1�� �浹���� : ���Ͱ� ĳ���͸� �ν��ϴ� ����))

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


void Monster::StopState()//���Ӵ����³� ĳ���Ϳ��� ���ݴ��ؼ� �����ִ� ����
{
	m_LRstate = STOP;
	m_UDstate = STOP;
	pos.x += 0;
	pos.y += 0;

	/*
	if(������ �����ִ� ���� && ĳ���Ͷ� �ε����ٸ�)
	���� �Ҹ�

	*/
}


void Monster::check()
{
	POSITION p;
	CPoint pos;
	int count = 0;
	for (p = Tile_list.GetHeadPosition(); p != NULL;) // ��� ������ ���� ��.
	{
		pos = Tile_list.GetNext(p);
		if (m_UDstate == DOWN) // �������ٰ� ���� �ٵ���.
		{
			if (pos.x > pos.x - M_SIZE && pos.x < pos.x + B_SIZE && pos.y > pos.y - M_SIZE && pos.y < pos.y - M_SIZE + B_SIZE / 2)
			{
				m_UDstate = STOP;
				pos.y = pos.y - M_SIZE;
			}
		}
		else if (m_UDstate == STOP) // �ؿ� ������ �ִ��� ������ �˻�.
			if (!(pos.x > pos.x - M_SIZE && pos.x < pos.x + B_SIZE && pos.y > pos.y - M_SIZE && pos.y < pos.y - M_SIZE + B_SIZE / 2))
				count++;//�ؿ� ��� ������ ������ �˻�.
	}
	if (count == Tile_list.GetCount())
		m_UDstate = DOWN; // Ÿ�ϼ��� = �˻��� ���� -> ������.
	if (jumpcount == 6) // ������ 6�� ������ ��ŭ ���� ������.
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
