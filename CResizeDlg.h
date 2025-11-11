#pragma once
#include <afxdialogex.h>

typedef struct _DLG_ELEMENT
{
	HWND hWnd;
	bool bMove;
	bool bCenter;
} DLG_ELEMENT, * PDLG_ELEMENT;

class CResizeDlg :
    public CDialogEx
{
public:
    CResizeDlg(UINT nIDTemplate, CWnd* pParent = nullptr)
        : CDialogEx(nIDTemplate, pParent)
    {
        // Hier ggf. weitere Initialisierung
		m_ptMinMax.x = 300; // Minimale Breite
		m_ptMinMax.y = 200; // Minimale Höhe

		m_oldCx = 0;
		m_oldCy = 0;

		m_pHorElements = nullptr;
		m_pVerElements = nullptr;
		m_dwHorElements = 0;
		m_dwVerElements = 0;
    }

    // Destruktor hinzugefügt
    virtual ~CResizeDlg()
    {
        if(m_pHorElements != nullptr)
			HeapFree(m_hHeap, 0, m_pHorElements);
		if (m_pVerElements != nullptr)
			HeapFree(m_hHeap, 0, m_pVerElements);
    }

    DECLARE_MESSAGE_MAP()
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
private:
    POINT m_ptMinMax;
public:
    void SetMinMaxInfo(CPoint pt);
    void SetMinMaxInfo(POINT pt);
    void SetMinMaxInfo(LONG x, LONG y);
    afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	const HANDLE m_hHeap = GetProcessHeap();
    DLG_ELEMENT* m_pHorElements;
	DLG_ELEMENT* m_pVerElements;
	DWORD m_dwHorElements;
	DWORD m_dwVerElements;
public:
    void AddHorElement(CWnd* pWnd, bool bMove = true, bool bCenter = false);
	void AddVerElement(CWnd* pWnd, bool bMove = true, bool bCenter = false);
	void AddHorElement(UINT nID, bool bMove = true, bool bCenter = false);
	void AddVerElement(UINT nID, bool bMove = true, bool bCenter = false);
private:
	int m_oldCx;
	int m_oldCy;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

