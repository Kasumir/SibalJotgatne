
// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ChildView.h"
#include "Monster.h"
#include "GameObject.h"
#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define EDITMODE 1
// CChildView

CChildView::CChildView()
{
	object.CreateCharacter(0, 0);
	monster1.MonsterCreate(500, 100);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
ON_WM_RBUTTONDOWN()
ON_WM_KEYDOWN()
ON_WM_KEYUP()
ON_COMMAND(ID_SAVE, &CChildView::OnSave)
ON_COMMAND(ID_LOAD, &CChildView::OnLoad)
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	CBitmap bitmap, c_bitmap;
	bitmap.LoadBitmap(IDB_BLOCK);
	BITMAP bmpinfo;
	bitmap.GetBitmap(&bmpinfo);
	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc);
	

	CBitmap m1_bitmap, b1_bitmap, wd_bitmap;
	b1_bitmap.LoadBitmap(IDB_BACKGROUND1);
	BITMAP b1_bmpinfo;
	b1_bitmap.GetBitmap(&b1_bmpinfo);
	
	dcmem.SelectObject(&b1_bitmap);
	dc.StretchBlt(0, 0, b1_bmpinfo.bmWidth*4/3, b1_bmpinfo.bmHeight*4/3, &dcmem, 0, 0, b1_bmpinfo.bmWidth, b1_bmpinfo.bmHeight, SRCCOPY);//맵 그림. 맵 후에 다른거그려야함! 순서중요

	dcmem.SelectObject(&bitmap); // 블록비트맵로딩.

	CRect rect;
	GetWindowRect(&rect);
	for (int i = 0; i <= rect.bottom; i += B_SIZE) {   //가로선
		dc.MoveTo(0, i);
		dc.LineTo(rect.right, i);
	}
	for (int i = 0; i <= rect.right; i += B_SIZE) {    //세로선
		dc.MoveTo(i, 0);
		dc.LineTo(i, rect.bottom);
	}

	POSITION p;
	for (p = Tile_list.GetHeadPosition(); p != NULL;)    //블록출력
	{
		CPoint pos(Tile_list.GetNext(p));
		dc.BitBlt(pos.x, pos.y, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
	}

	if (object.c_visible)   //캐릭출력
	{
		object.move();
		object.check(&Tile_list);
		if (object.c_LRstate == STOP)
		{
			if (object.LRcount > 0) {
				object.LRcount = 1;
				c_bitmap.LoadBitmap(IDB_CR1);
			}
			else if (object.LRcount < 0) {
				object.LRcount = -1;
				c_bitmap.LoadBitmap(IDB_CL1);
			}
		}
		else if (object.c_LRstate == RIGHT)
		{
			object.LRcount++;
			c_bitmap.LoadBitmap((object.LRcount % 6) + 335);
		}
		else if (object.c_LRstate == LEFT)
		{
			object.LRcount++;
			c_bitmap.LoadBitmap((object.LRcount % 6) + 342);
		}

		BITMAP c_bmpinfo;
		c_bitmap.GetBitmap(&c_bmpinfo);
		CDC c_dcmem;
		c_dcmem.CreateCompatibleDC(&dc);
		c_dcmem.SelectObject(&c_bitmap);
		//dc.BitBlt(object.c_pos.x, object.c_pos.y, c_bmpinfo.bmWidth, c_bmpinfo.bmHeight, &c_dcmem, 0, 0, SRCCOPY);
		dc.TransparentBlt(object.c_pos.x, object.c_pos.y, c_bmpinfo.bmWidth *2/ 3, c_bmpinfo.bmHeight*2/ 3, &c_dcmem, 0, 0, c_bmpinfo.bmWidth, c_bmpinfo.bmHeight, RGB(0, 255, 0));
	}


	if (monster1.m_visible == TRUE) 
	{
		monster1.MoveState();
		monster1.check(&Tile_list);
		m1_bitmap.LoadBitmap(IDB_MONSTER1);
		
		BITMAP m1_bmpinfo;
		m1_bitmap.GetBitmap(&m1_bmpinfo);
		CDC m1_dcmem;
		m1_dcmem.CreateCompatibleDC(&dc);
		m1_dcmem.SelectObject(&m1_bitmap);
		dc.TransparentBlt(monster1.m_pos.x, monster1.m_pos.y, m1_bmpinfo.bmWidth , m1_bmpinfo.bmHeight , &m1_dcmem, 0, 0, m1_bmpinfo.bmWidth, m1_bmpinfo.bmHeight, RGB(0, 255, 0));
	}
	//스페이스 바가 눌렸을 때, 물방울을 생성합니다.
	if (object.c_space == TRUE) {
		object.WaterDrop();
		object.wdcount[0] += 1;
		if (object.wdcount[0] == 8)
			object.wdcount[0] = 0;

	}
	else if (object.wdcount[1] == 0 && object.wdcount[2] == 0 && object.wdcount[3] == 0)
		object.wdcount[0] = 0;

	//물방울을 출력하는 코드입니다.

	if (object.wd_visible == TRUE) {

		wd_bitmap.LoadBitmap(IDB_WaterDrop);
		BITMAP wd_bmpinfo;
		wd_bitmap.GetBitmap(&wd_bmpinfo);
		CDC wd_dcmem;
		CPoint pos;
		wd_dcmem.CreateCompatibleDC(&dc);
		wd_dcmem.SelectObject(&wd_bitmap);
		for (int i = 1; i <= 3; i++) {
			if (object.wdcount[i] != 0) {
				pos = object.Water_drop.GetAt(i);
				dc.TransparentBlt(pos.x, pos.y, wd_bmpinfo.bmWidth, wd_bmpinfo.bmHeight, &wd_dcmem, 0, 0, wd_bmpinfo.bmWidth, wd_bmpinfo.bmHeight, RGB(0, 255, 0));
			}
		}
		object.WaterDropMove();
	}

	Sleep(1000 / 8);     //프레임
	object.jumpcount++;
	monster1.jumpcount++;
	Invalidate();
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)//블록생성
{
	CPoint pos;
	pos.x = (point.x / B_SIZE) * B_SIZE;
	pos.y = (point.y / B_SIZE) * B_SIZE;
	POSITION p;
	for (p = Tile_list.GetHeadPosition(); p != NULL;) {
		if (pos == Tile_list.GetAt(p)) {
			return;
		}
		Tile_list.GetNext(p);
	}
	Tile_list.AddTail(pos);
}



void CChildView::OnRButtonDown(UINT nFlags, CPoint point)//블록삭제
{
	CPoint pos;
	pos.x = (point.x / B_SIZE) * B_SIZE;
	pos.y = (point.y / B_SIZE) * B_SIZE;
	POSITION p;
	for (p = Tile_list.GetHeadPosition(); p != NULL;) {
		if (pos == Tile_list.GetAt(p)) {
			Tile_list.RemoveAt(p);
			break;
		}
		Tile_list.GetNext(p);
	}
	
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
	case VK_LEFT:
		object.c_LRstate = LEFT;
		object.c_lastLRstate = LEFT;
		break;
	case VK_RIGHT:
		object.c_LRstate = RIGHT;
		object.c_lastLRstate = RIGHT;
		break;
	case VK_UP:
		if (object.c_UDstate == STOP) {
			object.c_UDstate = UP;
			object.jumpcount = 0;
		}
		break;
	case VK_SPACE:
		object.c_space = TRUE;
		object.wdcount[0] = 0;
		break;
	}
}


void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
	case VK_LEFT:
		object.c_LRstate = STOP;
		object.LRcount = -1;
		break;
	case VK_RIGHT:
		object.LRcount = 1;
		object.c_LRstate = STOP;
		break;
	case VK_SPACE:
		object.c_space = FALSE;
		break;
	}
}


void CChildView::OnSave()
{
	CFile file;
	CFileException e;
	if (!file.Open(_T("mytext.txt"), CFile::modeCreate | CFile::modeWrite, &e)) {
		e.ReportError();
		return;
	}
	POSITION p;
	for (p = Tile_list.GetHeadPosition(); p != NULL;) {
		int buf[2];
		buf[0] = Tile_list.GetAt(p).x;
		buf[1] = Tile_list.GetNext(p).y;
		file.Write(buf, 2 * sizeof(int));
	}

}


void CChildView::OnLoad()
{
	CFile file;
	CFileException e;
	if (!file.Open(_T("mytext.txt"), CFile::modeRead, &e)) {
		e.ReportError();
		return;
	}
	Tile_list.RemoveAll();
	for (int i = 0; i < file.GetLength() / 8; i++)
	{
		int buf[2];
		file.Read(buf, 2 * sizeof(int));
		CPoint pos = { buf[0], buf[1] };
		Tile_list.AddTail(pos);
	}
}
