
// 12_skin_magic_demoView.cpp : CMy12_skin_magic_demoView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "12_skin_magic_demo.h"
#endif

#include "12_skin_magic_demoDoc.h"
#include "12_skin_magic_demoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy12_skin_magic_demoView

IMPLEMENT_DYNCREATE(CMy12_skin_magic_demoView, CView)

BEGIN_MESSAGE_MAP(CMy12_skin_magic_demoView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy12_skin_magic_demoView 构造/析构

CMy12_skin_magic_demoView::CMy12_skin_magic_demoView()
{
	// TODO: 在此处添加构造代码

}

CMy12_skin_magic_demoView::~CMy12_skin_magic_demoView()
{
}

BOOL CMy12_skin_magic_demoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy12_skin_magic_demoView 绘制

void CMy12_skin_magic_demoView::OnDraw(CDC* /*pDC*/)
{
	CMy12_skin_magic_demoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMy12_skin_magic_demoView 打印

BOOL CMy12_skin_magic_demoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy12_skin_magic_demoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy12_skin_magic_demoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy12_skin_magic_demoView 诊断

#ifdef _DEBUG
void CMy12_skin_magic_demoView::AssertValid() const
{
	CView::AssertValid();
}

void CMy12_skin_magic_demoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy12_skin_magic_demoDoc* CMy12_skin_magic_demoView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy12_skin_magic_demoDoc)));
	return (CMy12_skin_magic_demoDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy12_skin_magic_demoView 消息处理程序
