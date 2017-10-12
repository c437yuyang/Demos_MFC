
// 11_skinh_demoView.h : CMy11_skinh_demoView 类的接口
//

#pragma once


class CMy11_skinh_demoView : public CView
{
protected: // 仅从序列化创建
	CMy11_skinh_demoView();
	DECLARE_DYNCREATE(CMy11_skinh_demoView)

// 特性
public:
	CMy11_skinh_demoDoc* GetDocument() const;

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
	virtual ~CMy11_skinh_demoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // 11_skinh_demoView.cpp 中的调试版本
inline CMy11_skinh_demoDoc* CMy11_skinh_demoView::GetDocument() const
   { return reinterpret_cast<CMy11_skinh_demoDoc*>(m_pDocument); }
#endif

