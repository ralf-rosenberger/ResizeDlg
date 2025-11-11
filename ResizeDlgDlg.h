
// SizeDlgAppDlg.h: Headerdatei
//
#include "CResizeDlg.h"

#pragma once


// CResizeDlgDlg-Dialogfeld
class CResizeDlgDlg : public /*CDialogEx*/ CResizeDlg
{
// Konstruktion
public:
	CResizeDlgDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIZEDLGAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_staticBitmapCenter;
};
