//#pragma once
//
//
//// CDlgSelLvl dialog
//
//class CDlgSelLvl : public CDialog
//{
//	DECLARE_DYNAMIC(CDlgSelLvl)
//
//public:
//	CDlgSelLvl(CWnd* pParent = NULL);   // standard constructor
//	virtual ~CDlgSelLvl();
//
//// Dialog Data
//	enum { IDD = IDD_SELLEVEL };
//
//protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//
//	DECLARE_MESSAGE_MAP()
//};


#if !defined(AFX_DLGSELLVL_H__EA728AA1_9F92_4237_8D8B_F1BDC900803A__INCLUDED_)
#define AFX_DLGSELLVL_H__EA728AA1_9F92_4237_8D8B_F1BDC900803A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelLvl.h : header file
//

#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSelLvl dialog

class CDlgSelLvl : public CDialog
{
	// Construction
public:
	CDlgSelLvl(long lNums, int nLevel, CWnd* pParent = NULL);   // standard constructor

	long m_lNums;
	// Dialog Data
	//{{AFX_DATA(CDlgSelLvl)
	enum { IDD = IDD_SELLEVEL };
	CComboBox	m_cbLevel;
	int		m_nLevel;
	//}}AFX_DATA
	CString		m_strCaption;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelLvl)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSelLvl)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELLVL_H__EA728AA1_9F92_4237_8D8B_F1BDC900803A__INCLUDED_)
