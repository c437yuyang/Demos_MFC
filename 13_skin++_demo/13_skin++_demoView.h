
// 13_skin++_demoView.h : CMy13_skin_demoView 类的接口
//

#pragma once


class CMy13_skin_demoView : public CView
{
protected: // 仅从序列化创建
	CMy13_skin_demoView();
	DECLARE_DYNCREATE(CMy13_skin_demoView)

// 特性
public:
	CMy13_skin_demoDoc* GetDocument() const;

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
	virtual ~CMy13_skin_demoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 13_skin++_demoView.cpp 中的调试版本
inline CMy13_skin_demoDoc* CMy13_skin_demoView::GetDocument() const
   { return reinterpret_cast<CMy13_skin_demoDoc*>(m_pDocument); }
#endif

