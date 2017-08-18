
// 10_CFile_CFileStatusView.cpp : CMy10_CFile_CFileStatusView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "10_CFile_CFileStatus.h"
#endif

#include "10_CFile_CFileStatusDoc.h"
#include "10_CFile_CFileStatusView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy10_CFile_CFileStatusView

IMPLEMENT_DYNCREATE(CMy10_CFile_CFileStatusView, CView)

BEGIN_MESSAGE_MAP(CMy10_CFile_CFileStatusView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_A_FILESTATUS, &CMy10_CFile_CFileStatusView::OnAFilestatus)
END_MESSAGE_MAP()

// CMy10_CFile_CFileStatusView 构造/析构

CMy10_CFile_CFileStatusView::CMy10_CFile_CFileStatusView()
{
	// TODO: 在此处添加构造代码

}

CMy10_CFile_CFileStatusView::~CMy10_CFile_CFileStatusView()
{
}

BOOL CMy10_CFile_CFileStatusView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy10_CFile_CFileStatusView 绘制

void CMy10_CFile_CFileStatusView::OnDraw(CDC* /*pDC*/)
{
	CMy10_CFile_CFileStatusDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMy10_CFile_CFileStatusView 打印

BOOL CMy10_CFile_CFileStatusView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy10_CFile_CFileStatusView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy10_CFile_CFileStatusView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy10_CFile_CFileStatusView 诊断

#ifdef _DEBUG
void CMy10_CFile_CFileStatusView::AssertValid() const
{
	CView::AssertValid();
}

void CMy10_CFile_CFileStatusView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy10_CFile_CFileStatusDoc* CMy10_CFile_CFileStatusView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy10_CFile_CFileStatusDoc)));
	return (CMy10_CFile_CFileStatusDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy10_CFile_CFileStatusView 消息处理程序


void CMy10_CFile_CFileStatusView::OnAFilestatus()
{
	// TODO: 在此添加命令处理程序代码
	CString Filename("I:\\My Documents\\My Desktop\\无标题.png");
	CFile file;
	file.Open(Filename, CFile::modeRead);
	CFileStatus status;
	file.GetStatus(status);

}
