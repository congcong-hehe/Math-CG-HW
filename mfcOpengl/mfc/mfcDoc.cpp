// mfcDoc.cpp : CmfcDoc ���ʵ��
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


// CmfcDoc ����/����

CmfcDoc::CmfcDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CmfcDoc::~CmfcDoc()
{
}

BOOL CmfcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CmfcDoc ���л�

void CmfcDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CmfcDoc ���

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


// CmfcDoc ����
