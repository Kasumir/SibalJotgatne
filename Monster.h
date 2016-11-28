#pragma once

#define M_SIZE 48		//몬스터의 가로 세로 길이.
#define B_SIZE 48      //블록의 가로 세로 길이
#define C_SIZE 48      //캐릭터의 가로 세로 길이
#define STOP 0
#define LEFT 1
#define RIGHT 2
#define UP 1
#define DOWN 2

// Monster

class Monster : public CWnd
{
	DECLARE_DYNAMIC(Monster)

public:
	CPoint pos;
	Monster();
	virtual ~Monster();
	BOOL m_bottom; //몬스터발이 땅에 닿아있는지
	BOOL m_left;  //몬스터 왼쪽에 벽이 있는지
	BOOL m_right; //몬스터 오른쪽에 벽이 있는지
	BOOL m_visible;//몬스터가 생성되어 있는지
	int m_UDstate;
	int m_LRstate;
	int jumpcount;
	int LRcount;
	

protected:
	DECLARE_MESSAGE_MAP()
public:
	void MoveState();
	void StopState();
	void check();
	void MonsterDie();
	CList<CPoint, CPoint&> Tile_list; // 벽돌을 내가 정의하는게 아닌거같은데-- GameObject에 정의되어있는 벽돌 변수를 어떻게 쓰지 ;ㅅ; 8ㅅ8 -> 게임오브젝트에서 전역.

	void MonsterCreate(int x, int y);
};


