#pragma once
//캐릭터, 블록, 몬스터등 오브젝트들 대부분의 정보를 GameObject파일에서 관리할 계획

#define B_SIZE 48      //블록의 가로 세로 길이
#define C_SIZE 48      //캐릭터의 가로 세로 길이
#define STOP 0
#define LEFT 1
#define RIGHT 2
#define UP 1
#define DOWN 2
class GameObject  //모든 오브젝트를 관리할 클레스
{
public:
	CPoint c_pos;
	int c_UDstate;
	int c_LRstate;
	int jumpcount;
	BOOL c_bottom; //캐릭터발이 땅에 닿아있는지
	BOOL c_left;  //캐릭터 왼쪽에 벽이 있는지
	BOOL c_right; //캐릭터 오른쪽에 벽이 있는지
	BOOL c_visible;//캐릭터가 생성되어 있는지

public:
	void move();
	void check();
	void CreateCharacter(int, int);
	void DeleteCharacter();
	GameObject();
	~GameObject();

public:
	CList<CPoint, CPoint&> Tile_list;
};