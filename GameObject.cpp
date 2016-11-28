#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	c_UDstate = DOWN;
	c_LRstate = STOP;
	c_visible = FALSE;
	jumpcount = 6;
	LRcount = 1;
}
GameObject::~GameObject()
{
	
}
void GameObject::check()
{
	POSITION p;
	CPoint pos;
	int count = 0;
	for (p = Tile_list.GetHeadPosition(); p != NULL;) // 모르겠음 설명해주셈. 타일위에 붙어있게 하는거같은데..
	{
		pos = Tile_list.GetNext(p);
		if (c_UDstate == DOWN)
		{
			if (c_pos.x > pos.x - C_SIZE && c_pos.x < pos.x + B_SIZE && c_pos.y > pos.y - C_SIZE && c_pos.y < pos.y - C_SIZE + B_SIZE / 2)
			{
				c_UDstate = STOP;
				c_pos.y = pos.y - C_SIZE;
			}
		}
		else if (c_UDstate == STOP)
			if (!(c_pos.x > pos.x - C_SIZE && c_pos.x < pos.x + B_SIZE && c_pos.y > pos.y - C_SIZE && c_pos.y < pos.y - C_SIZE + B_SIZE / 2))
				count++;
	}
	if (count == Tile_list.GetCount())
		c_UDstate = DOWN;
	if (jumpcount == 6)
		c_UDstate = DOWN;

}
void GameObject::CreateCharacter(int x, int y)
{
	c_pos.x = x;
	c_pos.y = y;
	c_visible = TRUE;
}
void GameObject::DeleteCharacter()
{
	c_visible = FALSE;
}
void GameObject::move()
{
	switch (c_UDstate) {
	case STOP:
		c_pos.y += 0;
		break;
	case UP:
		c_pos.y -= 16;
		break;
	case DOWN:
		c_pos.y += 16;
		break;
	}
	switch (c_LRstate) {
	case STOP:
		c_pos.x += 0;
		break;
	case LEFT:
		c_pos.x -= 8;
		break;
	case RIGHT:
		c_pos.x += 8;
		break;
	}
}