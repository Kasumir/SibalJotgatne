
// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	object.CreateCharacter(0, 0);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()
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

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);
	BITMAP bmpinfo;
	bitmap.GetBitmap(&bmpinfo);
	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc);
	dcmem.SelectObject(&bitmap);

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
	for (p = object.Tile_list.GetHeadPosition(); p != NULL;)    //블록출력
	{
		CPoint pos(object.Tile_list.GetNext(p));
		dc.BitBlt(pos.x, pos.y, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
	}
	if (object.c_visible)   //캐릭출력
	{
		object.move();
		object.check();
		dc.BitBlt(object.c_pos.x, object.c_pos.y, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
	}

	Sleep(1000 / 8);     //프레임
	object.jumpcount++;
	Invalidate();
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPoint pos;
	pos.x = (point.x / B_SIZE) * B_SIZE;
	pos.y = (point.y / B_SIZE) * B_SIZE;
	POSITION p;
	for (p = object.Tile_list.GetHeadPosition(); p != NULL;) {
		if (pos == object.Tile_list.GetAt(p)) {
			return;
		}
		object.Tile_list.GetNext(p);
	}
	object.Tile_list.AddTail(pos);
}



void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CPoint pos;
	pos.x = (point.x / B_SIZE) * B_SIZE;
	pos.y = (point.y / B_SIZE) * B_SIZE;
	POSITION p;
	for (p = object.Tile_list.GetHeadPosition(); p != NULL;) {
		if (pos == object.Tile_list.GetAt(p)) {
			object.Tile_list.RemoveAt(p);
			break;
		}
		object.Tile_list.GetNext(p);
	}
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
	case VK_LEFT:
		object.c_LRstate = LEFT;
		break;
	case VK_RIGHT:
		object.c_LRstate = RIGHT;
		break;
	case VK_UP:
		if (object.c_UDstate == STOP) {
			object.c_UDstate = UP;
			object.jumpcount = 0;
		}
		break;
	}
}


void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
	case VK_LEFT:
		object.c_LRstate = STOP;
		break;
	case VK_RIGHT:
		object.c_LRstate = STOP;
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
	for (p = object.Tile_list.GetHeadPosition(); p != NULL;) {
		int buf[2];
		buf[0] = object.Tile_list.GetAt(p).x;
		buf[1] = object.Tile_list.GetNext(p).y;
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
	object.Tile_list.RemoveAll();
	for (int i = 0; i < file.GetLength() / 8; i++)
	{
		int buf[2];
		file.Read(buf, 2 * sizeof(int));
		CPoint pos = { buf[0], buf[1] };
		object.Tile_list.AddTail(pos);
	}
}
