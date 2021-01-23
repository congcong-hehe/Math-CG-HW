// mfcView.h : CmfcView ��Ľӿ�
//


#pragma once


class CmfcView : public CView
{
protected: // �������л�����
	CmfcView();
	DECLARE_DYNCREATE(CmfcView)

// ����
public:
	CmfcDoc* GetDocument() const;

// ����
public:
	HGLRC m_hRC;    //Rendering Context��ɫ������
	CDC* m_pDC;        //Device Context�豸������
	BOOL InitializeOpenGL();    //Initialize OpenGL
	BOOL SetupPixelFormat();    //Set up the Pixel Format
	void RenderScene();            //Render the Scene

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CmfcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // mfcView.cpp �еĵ��԰汾
inline CmfcDoc* CmfcView::GetDocument() const
   { return reinterpret_cast<CmfcDoc*>(m_pDocument); }
#endif

