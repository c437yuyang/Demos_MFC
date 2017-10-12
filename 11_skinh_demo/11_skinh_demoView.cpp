
// 11_skinh_demoView.cpp : CMy11_skinh_demoView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "11_skinh_demo.h"
#endif

#include "11_skinh_demoDoc.h"
#include "11_skinh_demoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy11_skinh_demoView

IMPLEMENT_DYNCREATE(CMy11_skinh_demoView, CView)

BEGIN_MESSAGE_MAP(CMy11_skinh_demoView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMy11_skinh_demoView 构造/析构

CMy11_skinh_demoView::CMy11_skinh_demoView()
{
	// TODO: 在此处添加构造代码

}

CMy11_skinh_demoView::~CMy11_skinh_demoView()
{
}

BOOL CMy11_skinh_demoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy11_skinh_demoView 绘制

void CMy11_skinh_demoView::OnDraw(CDC* /*pDC*/)
{
	CMy11_skinh_demoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMy11_skinh_demoView 打印

BOOL CMy11_skinh_demoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy11_skinh_demoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy11_skinh_demoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy11_skinh_demoView 诊断

#ifdef _DEBUG
void CMy11_skinh_demoView::AssertValid() const
{
	CView::AssertValid();
}

void CMy11_skinh_demoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy11_skinh_demoDoc* CMy11_skinh_demoView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy11_skinh_demoDoc)));
	return (CMy11_skinh_demoDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy11_skinh_demoView 消息处理程序


void CMy11_skinh_demoView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	switch (nType)
	{
	//case SIZE_RESTORED:
	//	AfxMessageBox(L"捕获到窗口还原消息");
	//	break;
	case SIZE_MINIMIZED:
		AfxMessageBox(L"捕获到窗口最小化消息");
		break;
	case SIZE_MAXIMIZED:
		AfxMessageBox(L"捕获到窗口最大化消息");
		break;
	}
}
