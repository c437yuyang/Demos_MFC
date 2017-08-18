
// 10_CFile_CFileStatusView.h : CMy10_CFile_CFileStatusView 类的接口
//

#pragma once


class CMy10_CFile_CFileStatusView : public CView
{
protected: // 仅从序列化创建
	CMy10_CFile_CFileStatusView();
	DECLARE_DYNCREATE(CMy10_CFile_CFileStatusView)

// 特性
public:
	CMy10_CFile_CFileStatusDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy10_CFile_CFileStatusView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAFilestatus();
};

#ifndef _DEBUG  // 10_CFile_CFileStatusView.cpp 中的调试版本
inline CMy10_CFile_CFileStatusDoc* CMy10_CFile_CFileStatusView::GetDocument() const
   { return reinterpret_cast<CMy10_CFile_CFileStatusDoc*>(m_pDocument); }
#endif

