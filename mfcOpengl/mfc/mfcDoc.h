// mfcDoc.h : CmfcDoc ��Ľӿ�
//


#pragma once


class CmfcDoc : public CDocument
{
protected: // �������л�����
	CmfcDoc();
	DECLARE_DYNCREATE(CmfcDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CmfcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


