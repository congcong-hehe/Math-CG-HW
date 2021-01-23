// mfcView.cpp : CmfcView 类的实现
//

#include "stdafx.h"
#include "mfc.h"

#include "mfcDoc.h"
#include "mfcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmfcView

IMPLEMENT_DYNCREATE(CmfcView, CView)

BEGIN_MESSAGE_MAP(CmfcView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CmfcView 构造/析构

typedef GLfloat point3[3];
void triangle(point3 a, point3 b, point3 c);
void divide_triangle(point3 a, point3 b, point3 c, int m);

CmfcView::CmfcView()
{
	// TODO: 在此处添加构造代码

}

CmfcView::~CmfcView()
{
}

BOOL CmfcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;//Tramp
	return CView::PreCreateWindow(cs);
}

// CmfcView 绘制

void CmfcView::OnDraw(CDC* /*pDC*/)
{
	CmfcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	RenderScene();//绘图都放在这
	// Tell OpenGL to flush its pipeline
	::glFinish();
	// Now Swap the buffers
	::SwapBuffers( m_pDC->GetSafeHdc() );

}


// CmfcView 打印

BOOL CmfcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CmfcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CmfcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CmfcView 诊断

#ifdef _DEBUG
void CmfcView::AssertValid() const
{
	CView::AssertValid();
}

void CmfcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmfcDoc* CmfcView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmfcDoc)));
	return (CmfcDoc*)m_pDocument;
}
#endif //_DEBUG


// CmfcView 消息处理程序

int CmfcView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
		InitializeOpenGL();//初始化openGL绘图

	return 0;
}

void CmfcView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	//Make the RC non-current
	if(::wglMakeCurrent (0,0) == FALSE)
	{
		MessageBox(_T("Could not make RC non-current"));
	}

	//Delete the rendering context
	if(::wglDeleteContext (m_hRC)==FALSE)
	{
		MessageBox(_T("Could not delete RC"));
	}
	//Delete the DC
	if(m_pDC)
	{
		delete m_pDC;
	}
	//Set it to NULL
	m_pDC = NULL;

}

void CmfcView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	// TODO: 在此处添加消息处理程序代码
	GLdouble aspect_ratio; // width/height ratio

	if ( 0 >= cx || 0 >= cy )
	{
		return;
	}
	// select the full client area
	::glViewport(0, 0, cx, cy);
	// compute the aspect ratio
	// this will keep all dimension scales equal
	aspect_ratio = (GLdouble)cx/(GLdouble)cy;
	// select the projection matrix and clear it
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity(); 
	::gluPerspective(45.0f, aspect_ratio, .01f, 200.0f);//画三维
	//::gluOrtho2D(-10.0f, 10.0f, -10.0f, 10.0f);    //二维


	// switch back to the modelview matrix and clear it
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();

}

BOOL CmfcView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}
BOOL CmfcView::InitializeOpenGL()
{
	//Get a DC for the Client Area
	m_pDC = new CClientDC(this);
	//Failure to Get DC
	if(m_pDC == NULL)
	{
		//::MessageBox("Error Obtaining DC");
		return FALSE;
	}
	//Failure to set the pixel format
	if(!SetupPixelFormat())
	{
		return FALSE;
	}
	//Create Rendering Context
	m_hRC = ::wglCreateContext (m_pDC->GetSafeHdc ());
	//Failure to Create Rendering Context
	if(m_hRC == 0)
	{
		//	MessageBox("Error Creating RC");
		return FALSE;
	}
	//Make the RC Current
	if(::wglMakeCurrent (m_pDC->GetSafeHdc (), m_hRC)==FALSE)
	{
		//	MessageBox("Error making RC Current");
		return FALSE;
	}
	//Specify Black as the clear color
	::glClearColor(0.0f,0.0f,0.0f,0.0f);
	//Specify the back of the buffer as clear depth
	::glClearDepth(1.0f);
	//Enable Depth Testing
	::glEnable(GL_DEPTH_TEST);
	return TRUE;

}
//设置像素格式
BOOL CmfcView::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |            // support OpenGL
		PFD_DOUBLEBUFFER,                // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		16,                             // 16-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if ( m_nPixelFormat == 0 )
	{
		return FALSE;
	}
	if ( ::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}
void CmfcView::RenderScene()
{
	point3 f1_v0 = { 0.0f, 1.0f, 0.0f };
	point3 f1_v1 = { -1.0f,-1.0f, 1.0f };
	point3 f1_v2 = { 1.0f,-1.0f, 1.0f };

	point3 f2_v0 = { 0.0f, 1.0f, 0.0f };
	point3 f2_v1 = { 1.0f,-1.0f, 1.0f };
	point3 f2_v2 = { 1.0f,-1.0f, -1.0f };

	point3 f3_v0 = { 0.0f, 1.0f, 0.0f };
	point3 f3_v1 = { -1.0f,-1.0f,-1.0f };
	point3 f3_v2 = { -1.0f,-1.0f, 1.0f };

	point3 f4_v0 = { 0.0f, 1.0f, 0.0f };
	point3 f4_v1 = { -1.0f,-1.0f,-1.0f };
	point3 f4_v2 = { 1.0f,-1.0f, -1.0f };

	glShadeModel(GL_FLAT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(0.0f,0.0f,-4.0f);						// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(30,0.0f,1.0f,0.0f);						// Rotate The Triangle On The Y axis ( NEW )
	glBegin(GL_TRIANGLES);								// Start Drawing A Triangle

	glColor3f(1.0f, 0.0f, 0.0f);
	divide_triangle(f1_v0, f1_v1, f1_v2, 3);
	glColor3f(0.0f, 1.0f, 0.0f);
	divide_triangle(f2_v0, f2_v1, f2_v2, 3);
	glColor3f(0.0f, 0.0f, 1.0f);
	divide_triangle(f3_v0, f3_v1, f3_v2, 3);
	glColor3f(1.0f, 1.0f, 0.0f);
	divide_triangle(f4_v0, f4_v1, f4_v2, 3);

	glEnd();											// Done Drawing The Pyramid
}

void triangle(point3 a, point3 b, point3 c)
{
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}

void divide_triangle(point3 a, point3 b, point3 c, int m)
{
	point3 v1, v2, v3;
	int j;
	if (m > 0)
	{
		for (j = 0; j < 3; ++j) v1[j] = (a[j] + b[j]) / 2;
		for (j = 0; j < 3; ++j) v2[j] = (a[j] + c[j]) / 2;
		for (j = 0; j < 3; ++j) v3[j] = (b[j] + c[j]) / 2;
		divide_triangle(a, v1, v2, m - 1);
		divide_triangle(c, v2, v3, m - 1);
		divide_triangle(b, v3, v1, m - 1);
	}
	else
	{
		triangle(a, b, c);
	}
}
