// Monster.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "Monster.h"
#include "ChildView.h"
#include "GameObject.h"


// Monster

IMPLEMENT_DYNAMIC(Monster, CWnd)

Monster::Monster() // ���� ����. �Ű������� ���ϴ� ��ġ�� ����.
{
	jumpcount = 6;
	m_visible = TRUE;
	m_UDstate = DOWN;
	m_LRstate = STOP;
	Lcount = 0;
	Rcount = 0;
	random1 = 0;
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

	if (Lcount == 0 || Rcount == 0)
	{
		random1 = rand() % 3;
	}
	if(Lcount<10 || Rcount<10)
		if (random1 == 0) // ���Ͱ� �������� ���ƴٴ�. �ٵ� ���� Ƚ���� �� ����.
		{
			m_LRstate = LEFT;
			Lcount++;
		}
		else if (random1  == 1)
		{
			m_LRstate = RIGHT;
			Rcount++;
		}
		else  if (random1 == 2)// �������� ����
		{
			for (; jumpcount < 6; jumpcount++)
				m_UDstate = UP;
		}	
	if (Lcount == 10 || Rcount == 10)
	{
		Lcount = 0;
		Rcount = 0;
	}

	
	
	//if( 1�� �浹������ �Ѿư�. (1�� �浹���� : ���Ͱ� ĳ���͸� �ν��ϴ� ����))

	switch (m_UDstate) {
	case STOP:
		m_pos.y += 0;
		break;
	case UP:
		m_pos.y -= 16;
		break;
	case DOWN:
		m_pos.y += 16;
		break;
	}
	switch (m_LRstate) {
	case STOP:
		m_pos.x += 0;
		break;
	case LEFT:
		m_pos.x -= 8;
		break;
	case RIGHT:
		m_pos.x += 8;
		break;
	}
	
}


void Monster::StopState()//���Ӵ����³� ĳ���Ϳ��� ���ݴ��ؼ� �����ִ� ����
{
	m_LRstate = STOP;
	m_UDstate = STOP;
	m_pos.x += 0;
	m_pos.y += 0;

	/*
	if(������ �����ִ� ���� && ĳ���Ͷ� �ε����ٸ�)
	���� �Ҹ�

	*/
}


void Monster::check(CList<CPoint, CPoint&>* Tile_list)
{
	POSITION p;
	CPoint pos;
	int count = 0;
	for (p = Tile_list->GetHeadPosition(); p != NULL;) // ��� ������ ���� ��.
	{
		pos = Tile_list->GetNext(p);
		if (m_UDstate == DOWN) // �������ٰ� ���� �ٵ���.
		{
			if (m_pos.x > pos.x - M_SIZE && m_pos.x < pos.x + B_SIZE && m_pos.y > pos.y - M_SIZE && m_pos.y < pos.y - M_SIZE + B_SIZE / 2)
			{
				m_UDstate = STOP;
				m_pos.y = pos.y - M_SIZE;
			}
		}
		else if (m_UDstate == STOP) // �ؿ� ������ �ִ��� ������ �˻�.
			if (!(m_pos.x > pos.x - M_SIZE && m_pos.x < pos.x + B_SIZE && m_pos.y > pos.y - M_SIZE && m_pos.y < pos.y - M_SIZE + B_SIZE / 2))
				count++;//�ؿ� ��� ������ ������ �˻�.
	}
	if (count == Tile_list->GetCount())
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
	m_pos.x = x;
	m_pos.y = y;
}
