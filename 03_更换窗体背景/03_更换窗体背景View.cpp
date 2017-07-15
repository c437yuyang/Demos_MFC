
// 03_更换窗体背景View.cpp : CMy03_更换窗体背景View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "03_更换窗体背景.h"
#endif

#include "03_更换窗体背景Doc.h"
#include "03_更换窗体背景View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy03_更换窗体背景View

IMPLEMENT_DYNCREATE(CMy03_更换窗体背景View, CView)

BEGIN_MESSAGE_MAP(CMy03_更换窗体背景View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CMy03_更换窗体背景View 构造/析构

CMy03_更换窗体背景View::CMy03_更换窗体背景View()
{
	// TODO: 在此处添加构造代码

}

CMy03_更换窗体背景View::~CMy03_更换窗体背景View()
{
}

BOOL CMy03_更换窗体背景View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy03_更换窗体背景View 绘制

void CMy03_更换窗体背景View::OnDraw(CDC* /*pDC*/)
{
	CMy03_更换窗体背景Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMy03_更换窗体背景View 打印

BOOL CMy03_更换窗体背景View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy03_更换窗体背景View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy03_更换窗体背景View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy03_更换窗体背景View 诊断

#ifdef _DEBUG
void CMy03_更换窗体背景View::AssertValid() const
{
	CView::AssertValid();
}

void CMy03_更换窗体背景View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy03_更换窗体背景Doc* CMy03_更换窗体背景View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy03_更换窗体背景Doc)));
	return (CMy03_更换窗体背景Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy03_更换窗体背景View 消息处理程序


void CMy03_更换窗体背景View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CView::OnPaint()

	//都是针对View类窗体，Dialog的太简单
#pragma region 更换窗体背景
	//1.资源里面导入相应位图
	//2.以下代码
	CRect rect;
	GetClientRect(&rect); //得到窗体的大小
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP1);//加载背景图片
	BITMAP bitMap;
	bmpBackground.GetBitmap(&bitMap);
	CBitmap* pbmpOld = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitMap.bmWidth, bitMap.bmHeight, SRCCOPY);

#pragma endregion

#pragma region 更改图标

	//1.导入图标
	//2. resource.h里面直接改IDR_MAINFRAME对应的文件路径

#pragma endregion

#pragma region 更改窗体标题

	//1.MainFrame里的precreatewindow里加入如下代码:
	//cs.style &= ~(LONG)FWS_ADDTOTITLE; //设置样式，不然有无标题-....
	//m_strTitle = _T("3DRRESTRUCT By 四川大学图像信息研究所");

#pragma endregion


}
