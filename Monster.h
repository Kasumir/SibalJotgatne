#pragma once
#define B_SIZE 48      //����� ���� ���� ����
#define M_SIZE 48      //ĳ������ ���� ���� ����
#define STOP 0
#define LEFT 1
#define RIGHT 2
#define UP 1
#define DOWN 2
class GameObject;
// Monster

class Monster : public CWnd
{
	DECLARE_DYNAMIC(Monster)

public:
	CPoint pos;
	Monster(int, int);
	virtual ~Monster();
	BOOL m_bottom; //���͹��� ���� ����ִ���
	BOOL m_left;  //���� ���ʿ� ���� �ִ���
	BOOL m_right; //���� �����ʿ� ���� �ִ���
	BOOL m_visible;//���Ͱ� �����Ǿ� �ִ���

protected:
	DECLARE_MESSAGE_MAP()
public:
	void MoveState();
	void StopState();
};


