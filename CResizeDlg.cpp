#include "pch.h"
#include "CResizeDlg.h"
#include <atltypes.h>
#include <afxdialogex.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CResizeDlg 1.0 written © by Ralf Rosenberger Dienstag, 11. November 2025
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CResizeDlg, CDialogEx)
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CResizeDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = m_ptMinMax.x; // Minimale Breite
	lpMMI->ptMinTrackSize.y = m_ptMinMax.y; // Minimale Höhe

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void CResizeDlg::SetMinMaxInfo(CPoint pt)
{
	m_ptMinMax = pt;
}

void CResizeDlg::SetMinMaxInfo(POINT pt)
{
	m_ptMinMax = pt;
}

void CResizeDlg::SetMinMaxInfo(LONG x, LONG y)
{
	m_ptMinMax.x = x;
	m_ptMinMax.y = y;
}

void CResizeDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	HDWP hDwp;
	CRect rc,rcFrame;

	if(m_oldCx && cx && m_oldCx != cx)
	{
		hDwp = BeginDeferWindowPos(m_dwHorElements);
		if(!hDwp)
			return;

		// Breite hat sich geändert
		for(DWORD i = 0; i < m_dwHorElements; i++)
		{
			if(m_pHorElements[i].bMove)
			{ 
			::GetWindowRect(m_pHorElements[i].hWnd, &rc);
			ScreenToClient(&rc);

				if (m_pHorElements[i].bCenter)
				{
					GetClientRect(&rcFrame);
					rc.left = (rcFrame.right - (rc.right - rc.left)) / 2;
				}
				else
					rc.left += cx - m_oldCx;

				hDwp = DeferWindowPos(hDwp, m_pHorElements[i].hWnd, NULL, rc.left, rc.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
				}
			else
			{
				::GetWindowRect(m_pHorElements[i].hWnd, &rc);
				ScreenToClient(&rc);

				rc.right += cx - m_oldCx;
				rc.right -= rc.left;
				rc.bottom -= rc.top;

				hDwp = DeferWindowPos(hDwp, m_pHorElements[i].hWnd, NULL, 0, 0, rc.right, rc.bottom, SWP_NOZORDER | SWP_NOMOVE);
			}
		}
		EndDeferWindowPos(hDwp);
	}
	m_oldCx = cx;

	if (m_oldCy && cy && m_oldCy != cy)
	{
		hDwp = BeginDeferWindowPos(m_dwVerElements);
		if (!hDwp)
			return;

		for (DWORD i = 0; i < m_dwVerElements; i++)
		{
			::GetWindowRect(m_pVerElements[i].hWnd, &rc);
			ScreenToClient(&rc);

			if (m_pVerElements[i].bMove)
			{
				if (m_pVerElements[i].bCenter)
				{
					GetClientRect(&rcFrame);
					rc.top = (rcFrame.bottom - (rc.bottom - rc.top)) / 2;
				}
				else
					rc.top += (cy - m_oldCy);

				hDwp = DeferWindowPos(hDwp, m_pVerElements[i].hWnd, NULL, rc.left, rc.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			}
			else
			{
				rc.bottom += (cy - m_oldCy);
				rc.right -= rc.left;
				rc.bottom -= rc.top;
				hDwp = DeferWindowPos(hDwp, m_pVerElements[i].hWnd, NULL, 0, 0, rc.right, rc.bottom, SWP_NOZORDER | SWP_NOMOVE);
			}
		}
		EndDeferWindowPos(hDwp);
	}
	m_oldCy = cy;
}

void CResizeDlg::AddHorElement(CWnd* pWnd, bool bMove, bool bCenter)
{
	if (!m_dwHorElements)
		m_pHorElements = (DLG_ELEMENT*)HeapAlloc(m_hHeap, HEAP_ZERO_MEMORY, sizeof(DLG_ELEMENT));
	else
		m_pHorElements = (DLG_ELEMENT*)HeapReAlloc(m_hHeap, HEAP_ZERO_MEMORY, m_pHorElements, sizeof(DLG_ELEMENT) * (m_dwHorElements + 1));
	if (!m_pHorElements)
		AfxThrowMemoryException();

	m_pHorElements[m_dwHorElements].hWnd = pWnd->GetSafeHwnd();
	m_pHorElements[m_dwHorElements].bMove = bMove;
	m_pHorElements[m_dwHorElements].bCenter = bCenter;

	m_dwHorElements++;
}

void CResizeDlg::AddVerElement(CWnd* pWnd, bool bMove, bool bCenter)
{
	if (!m_dwVerElements)
		m_pVerElements = (DLG_ELEMENT*)HeapAlloc(m_hHeap, HEAP_ZERO_MEMORY, sizeof(DLG_ELEMENT));
	else
		m_pVerElements = (DLG_ELEMENT*)HeapReAlloc(m_hHeap, HEAP_ZERO_MEMORY, m_pVerElements, sizeof(DLG_ELEMENT) * (m_dwVerElements + 1));
	if(!m_pVerElements)
		AfxThrowMemoryException();

	m_pVerElements[m_dwVerElements].hWnd = pWnd->GetSafeHwnd();
	m_pVerElements[m_dwVerElements].bMove = bMove;
	m_pVerElements[m_dwVerElements].bCenter = bCenter;

	m_dwVerElements++;
}

void CResizeDlg::AddHorElement(UINT nID, bool bMove, bool bCenter)
{
	if (!m_dwHorElements)
		m_pHorElements = (DLG_ELEMENT*)HeapAlloc(m_hHeap, HEAP_ZERO_MEMORY, sizeof(DLG_ELEMENT));
	else
		m_pHorElements = (DLG_ELEMENT*)HeapReAlloc(m_hHeap, HEAP_ZERO_MEMORY, m_pHorElements, sizeof(DLG_ELEMENT) * (m_dwHorElements + 1));
	if (!m_pHorElements)
		AfxThrowMemoryException();

	m_pHorElements[m_dwHorElements].hWnd = GetDlgItem(nID)->GetSafeHwnd();
	m_pHorElements[m_dwHorElements].bMove = bMove;
	m_pHorElements[m_dwHorElements].bCenter = bCenter;

	m_dwHorElements++;
}

void CResizeDlg::AddVerElement(UINT nID, bool bMove, bool bCenter)
{
	if (!m_dwVerElements)
		m_pVerElements = (DLG_ELEMENT*)HeapAlloc(m_hHeap, HEAP_ZERO_MEMORY, sizeof(DLG_ELEMENT));
	else
		m_pVerElements = (DLG_ELEMENT*)HeapReAlloc(m_hHeap, HEAP_ZERO_MEMORY, m_pVerElements, sizeof(DLG_ELEMENT) * (m_dwVerElements + 1));
	if (!m_pVerElements)
		AfxThrowMemoryException();

	m_pVerElements[m_dwVerElements].hWnd = GetDlgItem(nID)->GetSafeHwnd();
	m_pVerElements[m_dwVerElements].bMove = bMove;
	m_pVerElements[m_dwVerElements].bCenter = bCenter;

	m_dwVerElements++;
}
BOOL CResizeDlg::OnEraseBkgnd(CDC* pDC)
{
	if (CDialogEx::OnEraseBkgnd(pDC) && !(GetStyle() & WS_MAXIMIZE))
	{
		//draw size grip
		CRect rc;
		static CRect rcOld;

		GetClientRect(&rc);

		if (rc != rcOld)
		{
			InvalidateRect(&rcOld, TRUE);
			rcOld = rc;
		}

		int size = GetSystemMetrics(SM_CXVSCROLL);
		rc.left = rc.right - size;
		rc.top = rc.bottom - size;
		pDC->DrawFrameControl(&rc, DFC_SCROLL, DFCS_SCROLLSIZEGRIP);

		return TRUE;
	}
	else
	{
		return FALSE;
	}

	return CDialogEx::OnEraseBkgnd(pDC);
}
