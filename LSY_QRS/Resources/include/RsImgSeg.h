// RsImgSeg.h : main header file for the RsImgSeg DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRsImgSegApp
// See RsImgSeg.cpp for the implementation of this class
//

class CRsImgSegApp : public CWinApp
{
public:
	CRsImgSegApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

	
};
