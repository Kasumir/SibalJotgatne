// Monster.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "Monster.h"


// Monster

IMPLEMENT_DYNAMIC(Monster, CWnd)

Monster::Monster(int x, int y) // ���� ����. �Ű������� ���ϴ� ��ġ�� ����.
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



// Monster �޽��� ó�����Դϴ�.




void Monster::MoveState()//���ƴٴϴٰ� ������ �ν��ϸ� �Ѿư�
{
	int random1, random2;
	random1 = rand() % 2;
	random2 = rand() % 20 + 1;

	/* 
	��Ͽ� �ȿ����� �¿�� ���ƴٴϴ� ���
	if(random == 0)
		for(int i=0;i<random2;i++)
			pos.x += 8;
	else
		for(int i=0;i<random2;i++)
			pos.x -= 8;
	
	��Ͽ��� �������� ����� ģ����.
	pos.y += 16;
	pos.y -= 16;
	
	if( ĳ���Ͱ�ü ��� ��������? ĳ���Ͱ�ü.��ǥ +- 15 < = ���Ͱ�ü ��ǥ. 10 ) if�� 4���� �Ѿư��°� ����
	
	*/
	
}


void Monster::StopState()//���Ӵ����³� ĳ���Ϳ��� ���ݴ��ؼ� �����ִ� ����
{
	pos.x = pos.x;
	pos.y = pos.y;

	/*
	if(������ �����ִ� ���� && ĳ���Ͷ� �ε����ٸ�)
	���� �Ҹ�

	*/
}
