
// 07_01_替换鼠标指针View.h : CMy07_01_替换鼠标指针View 类的接口
//

#pragma once


class CMy07_01_替换鼠标指针View : public CView
{
protected: // 仅从序列化创建
	CMy07_01_替换鼠标指针View();
	DECLARE_DYNCREATE(CMy07_01_替换鼠标指针View)

// 特性
public:
	CMy07_01_替换鼠标指针Doc* GetDocument() const;

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
	virtual ~CMy07_01_替换鼠标指针View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	bool m_bLbDown;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

#ifndef _DEBUG  // 07_01_替换鼠标指针View.cpp 中的调试版本
inline CMy07_01_替换鼠标指针Doc* CMy07_01_替换鼠标指针View::GetDocument() const
   { return reinterpret_cast<CMy07_01_替换鼠标指针Doc*>(m_pDocument); }
#endif

