#pragma once
//ĳ����, ���, ���͵� ������Ʈ�� ��κ��� ������ GameObject���Ͽ��� ������ ��ȹ

#define B_SIZE 48      //����� ���� ���� ����
#define C_SIZE 48      //ĳ������ ���� ���� ����
#define STOP 0
#define LEFT 1
#define RIGHT 2
#define UP 1
#define DOWN 2
class GameObject  //��� ������Ʈ�� ������ Ŭ����
{
public:
	CPoint c_pos;
	int c_UDstate;
	int c_LRstate;
	int jumpcount;
	BOOL c_bottom; //ĳ���͹��� ���� ����ִ���
	BOOL c_left;  //ĳ���� ���ʿ� ���� �ִ���
	BOOL c_right; //ĳ���� �����ʿ� ���� �ִ���
	BOOL c_visible;//ĳ���Ͱ� �����Ǿ� �ִ���

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