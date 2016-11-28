#pragma once
#define B_SIZE 48      //블록의 가로 세로 길이
#define M_SIZE 48      //캐릭터의 가로 세로 길이
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
	BOOL m_bottom; //몬스터발이 땅에 닿아있는지
	BOOL m_left;  //몬스터 왼쪽에 벽이 있는지
	BOOL m_right; //몬스터 오른쪽에 벽이 있는지
	BOOL m_visible;//몬스터가 생성되어 있는지

protected:
	DECLARE_MESSAGE_MAP()
public:
	void MoveState();
	void StopState();
};


