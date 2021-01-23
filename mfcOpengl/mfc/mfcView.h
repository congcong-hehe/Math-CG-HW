// mfcView.h : CmfcView 类的接口
//


#pragma once


class CmfcView : public CView
{
protected: // 仅从序列化创建
	CmfcView();
	DECLARE_DYNCREATE(CmfcView)

// 属性
public:
	CmfcDoc* GetDocument() const;

// 操作
public:
	HGLRC m_hRC;    //Rendering Context着色描述表
	CDC* m_pDC;        //Device Context设备描述表
	BOOL InitializeOpenGL();    //Initialize OpenGL
	BOOL SetupPixelFormat();    //Set up the Pixel Format
	void RenderScene();            //Render the Scene

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
	virtual ~CmfcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // mfcView.cpp 中的调试版本
inline CmfcDoc* CmfcView::GetDocument() const
   { return reinterpret_cast<CmfcDoc*>(m_pDocument); }
#endif

