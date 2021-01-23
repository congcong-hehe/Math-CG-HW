// mfcDoc.cpp : CmfcDoc 类的实现
//

#include "stdafx.h"
#include "mfc.h"

#include "mfcDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmfcDoc

IMPLEMENT_DYNCREATE(CmfcDoc, CDocument)

BEGIN_MESSAGE_MAP(CmfcDoc, CDocument)
END_MESSAGE_MAP()


// CmfcDoc 构造/析构

CmfcDoc::CmfcDoc()
{
	// TODO: 在此添加一次性构造代码

}

CmfcDoc::~CmfcDoc()
{
}

BOOL CmfcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CmfcDoc 序列化

void CmfcDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CmfcDoc 诊断

#ifdef _DEBUG
void CmfcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CmfcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CmfcDoc 命令
