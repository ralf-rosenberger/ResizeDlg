
// ResizeDlg.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CResizeDlgApp:
// Siehe ResizeDlg.cpp für die Implementierung dieser Klasse
//

class CResizeDlgApp : public CWinApp
{
public:
	CResizeDlgApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CResizeDlgApp theApp;
