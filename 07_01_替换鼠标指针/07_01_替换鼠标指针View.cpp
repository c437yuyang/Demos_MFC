
// 07_01_替换鼠标指针View.cpp : CMy07_01_替换鼠标指针View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "07_01_替换鼠标指针.h"
#endif

#include "07_01_替换鼠标指针Doc.h"
#include "07_01_替换鼠标指针View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy07_01_替换鼠标指针View

IMPLEMENT_DYNCREATE(CMy07_01_替换鼠标指针View, CView)

BEGIN_MESSAGE_MAP(CMy07_01_替换鼠标指针View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

// CMy07_01_替换鼠标指针View 构造/析构

CMy07_01_替换鼠标指针View::CMy07_01_替换鼠标指针View()
{
	// TODO: 在此处添加构造代码
	m_bLbDown = false;
}

CMy07_01_替换鼠标指针View::~CMy07_01_替换鼠标指针View()
{
}

BOOL CMy07_01_替换鼠标指针View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy07_01_替换鼠标指针View 绘制

void CMy07_01_替换鼠标指针View::OnDraw(CDC* /*pDC*/)
{
	CMy07_01_替换鼠标指针Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMy07_01_替换鼠标指针View 打印

BOOL CMy07_01_替换鼠标指针View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy07_01_替换鼠标指针View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy07_01_替换鼠标指针View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy07_01_替换鼠标指针View 诊断

#ifdef _DEBUG
void CMy07_01_替换鼠标指针View::AssertValid() const
{
	CView::AssertValid();
}

void CMy07_01_替换鼠标指针View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy07_01_替换鼠标指针Doc* CMy07_01_替换鼠标指针View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy07_01_替换鼠标指针Doc)));
	return (CMy07_01_替换鼠标指针Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy07_01_替换鼠标指针View 消息处理程序

#include <iostream>
using namespace std;
void CMy07_01_替换鼠标指针View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bLbDown) 
	{
#pragma region 在这里处理的话，每次鼠标移动又会重新设置样式
		//参见MSDN:
		//Your application can change the design of the cursor by using the SetCursor function
		//and specifying a different cursor handle.However, when the cursor moves,
		//the system redraws the class cursor at the new location.
		//To prevent the class cursor from being redrawn, you must process the WM_SETCURSOR message.
		//Each time the cursor moves and mouse input is not captured, 
		//the system sends this message to the window in which the cursor is moving.
		
		
		//auto cursor = LoadCursorA(AfxGetApp()->m_hInstance, MAKEINTRESOURCEA(IDC_CURSOR3));
		//::SetCursor(cursor);
#pragma endregion

		//m_bLbDown = true;
	}
	else
	{

	}

	CView::OnMouseMove(nFlags, point);
}


void CMy07_01_替换鼠标指针View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bLbDown = true;
	CView::OnLButtonDown(nFlags, point);
}


void CMy07_01_替换鼠标指针View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bLbDown = false;
	CView::OnLButtonUp(nFlags, point);
}


//OnSetCursor由消息 WM_SETCURSOR 触发
//The WM_SETCURSOR message is sent to a window if the mouse causes the cursor to move within a window and mouse input is not captured.
//
//看清楚了，只要鼠标移动OnMouseMOve就会自动发送 WM_SETCURSOR从而触发OnSetCursor，因此在设计改变鼠标指针的程序时，一般不要在OnMouseMOve事件中调用SetCursor，容易引起指针闪烁。设置鼠标指针形状合理的方法是：
//在OnMouseMove中使用一个变量记住各矩形crect中的鼠标形状，然后在OnSetCursor调用SetCursor设置鼠标

BOOL CMy07_01_替换鼠标指针View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	auto cursor = LoadCursorA(AfxGetApp()->m_hInstance, MAKEINTRESOURCEA(IDC_CURSOR3));
	::SetCursor(cursor);
	return TRUE;
	//return CView::OnSetCursor(pWnd, nHitTest, message); //必须屏蔽掉系统的setCursor
}
