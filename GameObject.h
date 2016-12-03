#pragma once
//ĳ����, ���, ���͵� ������Ʈ�� ��κ��� ������ GameObject���Ͽ��� ������ ��ȹ
//���ʹ� ���������� �����ϹǷ�... ���⿡ �Լ� ���鼭 �ߴµ� �ȵǼ� Ŭ������ ����.

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
	int LRcount;
	int c_lastLRstate; // ĳ���Ͱ� ���������� �����ִ� ������ Ȯ���մϴ�.
	int wd_LRstate[4];	//�� ������� LR state ������ ��� �ֽ��ϴ�.
	int wdcount[4]; // ����� ī��Ʈ, �ε��� 0�� ���� �ֱ�� ������� ��� ���� OnPain()�� ȣ�� Ƚ���� �����մϴ�.
	BOOL c_bottom; //ĳ���͹��� ���� ����ִ���
	BOOL c_left;  //ĳ���� ���ʿ� ���� �ִ���
	BOOL c_right; //ĳ���� �����ʿ� ���� �ִ���
	BOOL c_visible;//ĳ���Ͱ� �����Ǿ� �ִ���
	BOOL c_space; //space ���� ����, space�� �����ִ��� ���¸� �����մϴ�.
	BOOL wd_visible; // ������� �����Ǿ� �ִ��� Ȯ���մϴ�.

public:
	void move();
	void check(CList<CPoint, CPoint&>*);
	void CreateCharacter(int, int);
	void DeleteCharacter();
	void WaterDrop();
	void WaterDropMove();
	GameObject();
	~GameObject();

public:
	CArray<CPoint, CPoint&> Water_drop; //����� ��ǥ ����
};