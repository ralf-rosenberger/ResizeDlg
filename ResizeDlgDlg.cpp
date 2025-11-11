
// SizeDlgAppDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "ResizeDlg.h"
#include "ResizeDlgDlg.h"
#include "afxdialogex.h"
#include "CResizeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CResizeDlg
{
public:
	CAboutDlg();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

// Implementierung
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog(void);
};

CAboutDlg::CAboutDlg() : CResizeDlg(IDD_ABOUTBOX)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizeDlg::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CResizeDlg)
	ON_WM_CREATE()
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CResizeDlg::OnInitDialog();

	AddHorElement(IDOK);

	return TRUE;
}

// CResizeDlgDlg-Dialogfeld

CResizeDlgDlg::CResizeDlgDlg(CWnd* pParent /*=nullptr*/)
	: CResizeDlg(IDD_SIZEDLGAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CResizeDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizeDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICCENTER, m_staticBitmapCenter);
}

BEGIN_MESSAGE_MAP(CResizeDlgDlg, CResizeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CResizeDlgDlg-Meldungshandler

BOOL CResizeDlgDlg::OnInitDialog()
{
	CResizeDlg::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	SetMinMaxInfo(600, 500);

	AddHorElement(IDCANCEL);
	AddHorElement(IDC_BUTTONRIGHT);
	AddHorElement(IDC_BUTTONCENTER,true,true);
	AddHorElement(IDC_STATICCENTER,true,true);
	AddHorElement(IDC_EDIT, false);
	AddHorElement(IDC_BUTTONRIGHT);
	AddHorElement(IDC_STATICCENTERTEXT, true, true);
	
	AddVerElement(IDOK);
	AddVerElement(IDCANCEL);
	AddVerElement(IDC_BUTTONCENTER);
	AddVerElement(IDC_STATICCENTER,true,true);
	AddVerElement(IDC_BUTTONLEFT, true, true);
	AddVerElement(IDC_BUTTONRIGHT, true, true);
	AddVerElement(IDC_EDIT, false);

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

void CResizeDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CResizeDlg::OnSysCommand(nID, lParam);
	}
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CResizeDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CResizeDlg::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CResizeDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}