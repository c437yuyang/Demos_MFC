
// 12_skin_magic_demoView.h : CMy12_skin_magic_demoView 类的接口
//

#pragma once


class CMy12_skin_magic_demoView : public CView
{
protected: // 仅从序列化创建
	CMy12_skin_magic_demoView();
	DECLARE_DYNCREATE(CMy12_skin_magic_demoView)

// 特性
public:
	CMy12_skin_magic_demoDoc* GetDocument() const;

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
	virtual ~CMy12_skin_magic_demoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 12_skin_magic_demoView.cpp 中的调试版本
inline CMy12_skin_magic_demoDoc* CMy12_skin_magic_demoView::GetDocument() const
   { return reinterpret_cast<CMy12_skin_magic_demoDoc*>(m_pDocument); }
#endif

