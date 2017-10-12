
// 13_skin++_demoView.cpp : CMy13_skin_demoView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "13_skin++_demo.h"
#endif

#include "13_skin++_demoDoc.h"
#include "13_skin++_demoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy13_skin_demoView

IMPLEMENT_DYNCREATE(CMy13_skin_demoView, CView)

BEGIN_MESSAGE_MAP(CMy13_skin_demoView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy13_skin_demoView 构造/析构

CMy13_skin_demoView::CMy13_skin_demoView()
{
	// TODO: 在此处添加构造代码

}

CMy13_skin_demoView::~CMy13_skin_demoView()
{
}

BOOL CMy13_skin_demoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy13_skin_demoView 绘制

void CMy13_skin_demoView::OnDraw(CDC* /*pDC*/)
{
	CMy13_skin_demoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMy13_skin_demoView 打印

BOOL CMy13_skin_demoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy13_skin_demoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy13_skin_demoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy13_skin_demoView 诊断

#ifdef _DEBUG
void CMy13_skin_demoView::AssertValid() const
{
	CView::AssertValid();
}

void CMy13_skin_demoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy13_skin_demoDoc* CMy13_skin_demoView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy13_skin_demoDoc)));
	return (CMy13_skin_demoDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy13_skin_demoView 消息处理程序
