// BusStation_ClientDoc.h : interface of the CBusStation_ClientDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUSSTATION_CLIENTDOC_H__0C449594_DDC0_444C_8F3E_6522529E46BA__INCLUDED_)
#define AFX_BUSSTATION_CLIENTDOC_H__0C449594_DDC0_444C_8F3E_6522529E46BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBusStation_ClientDoc : public CDocument
{
protected: // create from serialization only
	CBusStation_ClientDoc();
	DECLARE_DYNCREATE(CBusStation_ClientDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBusStation_ClientDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBusStation_ClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBusStation_ClientDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUSSTATION_CLIENTDOC_H__0C449594_DDC0_444C_8F3E_6522529E46BA__INCLUDED_)
