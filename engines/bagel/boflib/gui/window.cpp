/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "bagel/boflib/gui/window.h"
#include "bagel/boflib/debug.h"
#include "bagel/boflib/app.h"
#include "bagel/boflib/sound.h"

namespace Bagel {

// Local function prototypes
//
#if BOF_WINDOWS
LRESULT CALLBACK BofWindowProcedure(HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam);
#endif

ULONG TranslateChar(UINT nChar, ULONG nRepCount, ULONG nFlags);
ULONG TranslateKey(UINT nChar, ULONG nRepCount, ULONG nFlags);

// Static members defined here
//
CBofWindow *CBofWindow::m_pWindowList = nullptr;
CBofWindow *CBofWindow::m_pActiveWindow = nullptr;
CBofTimerPacket *CBofWindow::m_pTimerList = nullptr;

#if PALETTESHIFTFIX
#include <iostream>
CBofList<PaletteShiftItem> *CBofWindow::m_pPaletteShiftList = nullptr;

#if __POWERPC__
typedef UniversalProcPtr SetEntriesUPP;

enum {
	uppSetEntriesProcInfo = kPascalStackBased | STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(short))) | STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(short))) | STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(ColorSpec *)))
};
#else
typedef pascal void (*SetEntriesProcPtr)(short, short, CSpecArray);
typedef SetEntriesProcPtr SetEntriesUPP;
#endif

#define NewSetEntriesProc(userRoutine) \
    (SetEntriesUPP) NewRoutineDescriptor((ProcPtr)(userRoutine), uppSetEntriesProcInfo, GetCurrentArchitecture())

SetEntriesUPP gOldSetEntries;
SetEntriesUPP gNewSetEntries;

BOOL gPalettePatchesInstalled = false;
BOOL gBlankBeforePaletteShift = false;
BOOL gAllowPaletteShifts = true;

pascal void MySetEntries(short start, short count, CSpecArray aTable);

void InstallPalettePatch();
void PaintScreenBlack();
BOOL PalettesAreCompatible(PaletteHandle inPalette1, PaletteHandle inPalette2);

#endif

#if BOF_MAC
CBofWindow *CBofWindow::m_pCapturedWindow = nullptr;
#endif

#if BOF_WINDOWS
HBRUSH CBofWindow::m_hBrush = nullptr;
#endif

// This flag is set if playing any of the word games
//
BOOL g_bWordGamePackHack;

void CBofWindow::initStatics() {
	m_pWindowList = nullptr;
	m_pActiveWindow = nullptr;
	m_pTimerList = nullptr;
	g_bWordGamePackHack = FALSE;
}


CBofWindow::CBofWindow() {
#if BOF_WINDOWS
	m_hWnd = nullptr;
	m_hLastCapture = nullptr;

#elif BOF_MAC
	m_pWindow = nullptr;
	m_bEnabled = FALSE;
	m_bVisible = FALSE;
	m_pLastCapture = nullptr;
	m_bCustomMacWindow = FALSE;
	m_pPrevActiveWindow = nullptr;
	InstallPalettePatch();
#endif

	if (m_pActiveWindow == nullptr)
		m_pActiveWindow = this;

	if (m_pWindowList == nullptr) {
		m_pWindowList = this;
	} else {
		m_pWindowList->Insert(this);
	}
}

CBofWindow::CBofWindow(const CHAR *pszName, INT x, INT y, INT nWidth, INT nHeight, CBofWindow *pParent) {
	m_pBackdrop = nullptr;
	m_pParentWnd = nullptr;
	m_bCaptured = FALSE;
	m_nID = 0;
	// jwl 07.16.96 don't initialize a static in a constructor
	// m_pTimerList = nullptr;
	m_cBkColor = RGB(255, 255, 255);
	m_cFgColor = RGB(0, 0, 0);

#if BOF_WINDOWS
	m_hWnd = nullptr;
	m_hLastCapture = nullptr;

#elif BOF_MAC
	m_pWindow = nullptr;
	m_bEnabled = FALSE;
	m_bVisible = FALSE;
	m_pLastCapture = nullptr;
	m_bCustomMacWindow = FALSE;
	m_pPrevActiveWindow = nullptr;
	InstallPalettePatch();
#endif

	if (m_pWindowList == nullptr) {
		m_pWindowList = this;
	} else {
		m_pWindowList->Insert(this);
	}

	Create(pszName, x, y, nWidth, nHeight, pParent);
}

CBofWindow::~CBofWindow() {
	Assert(IsValidObject(this));

#if BOF_MAC
	if (IsInActiveList()) {
		RemoveFromActiveList();
	}
#endif

	KillMyTimers();

	// Remove this window from the list
	if (m_pWindowList == this) {
		m_pWindowList = (CBofWindow *)GetNext();
	}

	KillBackdrop();

	Destroy();
}

ERROR_CODE CBofWindow::Initialize() {
	return ERR_NONE;
}

ERROR_CODE CBofWindow::ShutDown() {
	return ERR_NONE;
}

VOID CBofWindow::Destroy() {
	ReleaseCapture();

#if BOF_MAC || BOF_WINMAC
	// If we're at the last window, then set paint to white
	// as to make sure that we don't trash other application windows lying
	// beneath ours.
	if (m_pWindowList == nil) {
		LMSetPaintWhite(true);
	} else {
		LMSetPaintWhite(false);
	}
#endif

#if BOF_WINDOWS
	if (m_hWnd != nullptr) {
		::DestroyWindow(m_hWnd);
		m_hWnd = nullptr;
	}

#elif BOF_MAC

	if (m_pWindow != nullptr) {
#if PALETTESHIFTFIX
		// jwl 09.04.96 palette shift fix... take all the calls that cause palette shifts
		// and move them as close to the onscreen rendering code as possible, this will
		// minimize the shift... but not eliminate it.

		LONG nItemOfInterest = (LONG)m_pWindow;
		LONG nAssociatedItem = (m_pParentWnd && m_pParentWnd->m_pWindow) ? (LONG)m_pParentWnd->m_pWindow : 0;

		AddToPaletteShiftList(DISPOSEWINDOW, nItemOfInterest, nAssociatedItem);

		m_pWindow = nullptr;

		if (m_pParentWnd == nullptr || m_pParentWnd->m_pWindow == nullptr) {
			return;
		}

		// jwl 07.10.96 Make sure that the underlying window becomes
		// our current grafport.
		::SetPort(m_pParentWnd->m_pWindow);

		ValidateAnscestors();
#else
		gAllowPaletteShifts = false;
		::DisposeWindow(m_pWindow);
		gAllowPaletteShifts = true;
		m_pWindow = nullptr;
#endif
	}
#endif
}

VOID CBofWindow::ValidateAnscestors(CBofRect *pRect) {
	Assert(IsValidObject(this));

	CBofWindow *pParent;

	// Validate all anscestors
	//
	pParent = m_pParentWnd;
	while (pParent != nullptr) {
#if BOF_MAC || BOF_WINMAC
		//  jwl 07.02.96 On the mac, we have to make sure that
		//  the grafport is our current grafport (i.e. the window
		//  that we are validating).

		if (pParent->m_pWindow) {
#endif
			pParent->ValidateRect(pRect);

#if BOF_MAC || BOF_WINMAC
		}
#endif
		pParent = pParent->GetParent();
	}
}

ERROR_CODE CBofWindow::Create(const CHAR *pszName, INT x, INT y, INT nWidth, INT nHeight, CBofWindow *pParent, UINT nControlID) {
	Assert(IsValidObject(this));
	Assert(pszName != nullptr);
	Assert(pParent != this);

	// remember who our parent is
	m_pParentWnd = pParent;

	m_nID = nControlID;

	// remember the name of this window
	strncpy(m_szTitle, pszName, MAX_TITLE);

	// retain screen coordinates for this window
	m_cWindowRect.SetRect(x, y, x + nWidth - 1, y + nHeight - 1);

#if BOF_WINDOWS

	STATIC BOOL bInit = FALSE;
	CHAR szBuf[20];
	DWORD dwStyle;
	HWND hParent;

	// Register one of each type of BofWindow
	//
	if (!bInit) {
		ATOM iAtom;
		WNDCLASS wc;

		// Register a parent window
		//
		memset(&wc, 0, sizeof(WNDCLASS));
		wc.lpszClassName = "BofWindowParent";
		wc.lpfnWndProc = BofWindowProcedure;
		wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
		wc.hInstance = CBofApp::GetInstanceHandle();

		// Always use 0 for resource ID
		// Load this app's icon
		wc.hIcon = ::LoadIcon(wc.hInstance, "BOFFO_APP_ICON");

		if ((wc.hCursor = CBofApp::GetApp()->GetDefaultCursor().GetWinCursor()) == nullptr) {
			wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		}
		wc.hbrBackground = nullptr; //(HBRUSH)(COLOR_WINDOW + 1);
		iAtom = RegisterClass(&wc);

		// Register a child window
		//
		wc.lpszClassName = "BofWindowChild";
		wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
		wc.hIcon = nullptr;
		iAtom = RegisterClass(&wc);

		bInit = TRUE;
	}

	// Parent or child window?
	//
	hParent = nullptr;
	dwStyle = WS_POPUP;
	strcpy(szBuf, "BofWindowParent");

	if (pParent != nullptr) {
		strcpy(szBuf, "BofWindowChild");
		hParent = pParent->m_hWnd;
		dwStyle = WS_CHILD;
	}

	// There must not already be a window (would cause bad resource leak)
	Assert(m_hWnd == nullptr);

	// Build the actual window
	//
	if ((m_hWnd = ::CreateWindow(szBuf, pszName, dwStyle, x, y, nWidth, nHeight, hParent, nullptr, CBofApp::GetInstanceHandle(), nullptr)) != nullptr) {

		RECT rect;
		::GetWindowRect(m_hWnd, &rect);

		// reset screen coordinates (in case we are using the defaults set up
		// by CreateWindow).
		//
		m_cWindowRect = rect;

	} else {

		ReportError(ERR_UNKNOWN, "Unable to CreateWindow(%s)", pszName);
	}

#elif BOF_MAC
	UCHAR szBuf[256];
	Rect stRect = {y, x, y + nHeight, x + nWidth};

	// If this is a child window then convert it's area to global coordinates
	//
	if (pParent != nullptr) {

		stRect.left += pParent->GetWindowRect().left;
		stRect.right += pParent->GetWindowRect().left;
		stRect.top += pParent->GetWindowRect().top;
		stRect.bottom += pParent->GetWindowRect().top;
	}

	strcpy((CHAR *)szBuf, m_szTitle);
	StrCToPascal((CHAR *)szBuf);

	INT winType = plainDBox;
	if (IsCustomWindow() == true) {
		winType = (16 * 1000) + 0;
	}

	if ((m_pWindow = NewCWindow(nullptr, &stRect, szBuf, FALSE, winType, WindowPtr(-1), FALSE, 0)) != nullptr) {

		// SetWRefCon(m_pWindow, this);

		SetPort(m_pWindow);

		// ForeColor(blackColor);
		// BackColor(whiteColor);
		// PenNormal();

		// set this window's global coordinates
		m_cWindowRect = stRect;

	} else {
		ReportError(ERR_UNKNOWN, "Unable to NewCWindow(%s)", pszName);
	}

#endif

	if (!ErrorOccurred()) {

		CBofPalette *pPalette;
		if ((pPalette = CBofApp::GetApp()->GetPalette()) != nullptr) {
			SelectPalette(pPalette);
		}

		// retain local coordinates (based on own window)
		m_cRect.SetRect(0, 0, m_cWindowRect.Width() - 1, m_cWindowRect.Height() - 1);
	}

	return m_errCode;
}

ERROR_CODE CBofWindow::Create(const CHAR *pszName, CBofRect *pRect, CBofWindow *pParent, UINT nControlID) {
	Assert(IsValidObject(this));
	Assert(pszName != nullptr);

	INT x, y, nWidth, nHeight;

	x = y = 0;
	nWidth = nHeight = USE_DEFAULT;
	if (pRect != nullptr) {
		x = pRect->left;
		y = pRect->top;
		nWidth = pRect->Width();
		nHeight = pRect->Height();
	}

	return Create(pszName, x, y, nWidth, nHeight, pParent, nControlID);
}

VOID CBofWindow::ReleaseCapture() {
#if BOF_WINDOWS

	if (m_hLastCapture != nullptr) {
		CBofWindow *pWnd;

		pWnd = CBofWindow::FromHandle(m_hLastCapture);
		if (pWnd != nullptr) {
			pWnd->SetCapture();
		}
	} else {
		::ReleaseCapture();
	}

	m_bCaptured = FALSE;

#elif BOF_MAC
	m_pCapturedWindow = m_pLastCapture;
	m_bCaptured = FALSE;

	if (m_pLastCapture != nullptr) {
		m_pLastCapture->SetCapture();
	}

#endif
}

VOID CBofWindow::SetCapture() {
#if BOF_WINDOWS
	if (!m_bCaptured) {
		m_hLastCapture = ::SetCapture(m_hWnd);
		m_bCaptured = TRUE;
	}

#elif BOF_MAC
	if (!m_bCaptured) {
		m_pLastCapture = m_pCapturedWindow;

		if (m_pLastCapture != nullptr) {
			m_pLastCapture->m_bCaptured = FALSE;
		}

		m_pCapturedWindow = this;

		m_bCaptured = TRUE;
	}
#endif
}

VOID CBofWindow::Center() {
	Assert(IsValidObject(this));

	CBofWindow *pParent;
	INT x, y;

	if ((pParent = m_pParentWnd) != nullptr) {
		CBofRect cWindowRect;

		cWindowRect = pParent->GetWindowRect();

		x = cWindowRect.left + (pParent->Width() - Width()) / 2;
		y = cWindowRect.top + (pParent->Height() - Height()) / 2;
	} else {
		x = (CBofApp::GetApp()->ScreenWidth() - Width()) / 2;
		y = (CBofApp::GetApp()->ScreenHeight() - Height()) / 2;
	}
	Move(x, y);
}

VOID CBofWindow::Move(const INT x, const INT y, BOOL bRepaint) {
	Assert(IsValidObject(this));
	Assert(IsCreated());

#if BOF_WINDOWS

	::MoveWindow(m_hWnd, x, y, m_cRect.Width(), m_cRect.Height(), bRepaint);

#elif BOF_MAC
#if PALETTESHIFTFIX // scg 01.26.97

	AddToPaletteShiftList(MOVEWINDOW, (LONG)m_pWindow, (LONG)((x << 16) | y));

#else

	gAllowPaletteShifts = false;
	::MoveWindow(m_pWindow, x, y, FALSE);
	gAllowPaletteShifts = true;

#endif

#endif

	// we now have a new position (in screen coordinates)
	m_cWindowRect.SetRect(x, y, x + m_cRect.Width() - 1, y + m_cRect.Height() - 1);
}

VOID CBofWindow::ReSize(CBofRect *pRect, BOOL bRepaint) {
	Assert(IsValidObject(this));
	Assert(IsCreated());
	Assert(pRect != nullptr);

#if BOF_WINDOWS

	::MoveWindow(m_hWnd, pRect->left, pRect->top, pRect->Width(), pRect->Height(), bRepaint);

#elif BOF_MAC
	if ((pRect->left != m_cWindowRect.left) || (pRect->top != m_cWindowRect.top)) {
		Move(pRect->left, pRect->top, FALSE);
	}

#if PALETTESHIFTFIX // scg 01.26.97

	AddToPaletteShiftList(SIZEWINDOW, (LONG)m_pWindow, (LONG)((pRect->Width() << 16) | pRect->Height()));

#else

	gAllowPaletteShifts = false;
	::SizeWindow(m_pWindow, pRect->Width(), pRect->Height(), bRepaint);
	gAllowPaletteShifts = true;

#endif
	if (bRepaint == true)
		::ShowWindow(m_pWindow); // jwl 07.03.96
#endif

	// we now have a new position (in screen coordinates)
	m_cWindowRect = *pRect;
	m_cRect.SetRect(0, 0, m_cWindowRect.Width() - 1, m_cWindowRect.Height() - 1);
}

VOID CBofWindow::Select() {
#if BOF_MAC
	::SelectWindow(m_pWindow);
	::SetPort(m_pWindow);
#else
#endif
}

VOID CBofWindow::Show() {
	Assert(IsValidObject(this));

	if (!ErrorOccurred()) {

		Assert(IsCreated());

		if (IsCreated()) {

#if BOF_MAC || BOF_WINMAC
			LMSetPaintWhite(FALSE);
#endif

#if BOF_WINDOWS

			::ShowWindow(m_hWnd, SW_SHOWNORMAL);

			// Fix for Dialog repaint problem
			//
			if (g_bWordGamePackHack) {
				ValidateAnscestors();
			}

#elif BOF_MAC

			// jwl 08.20.96 warning to future mac hackers... go directly to the
			// invalidate call below when using the debug-ger, or you'll crash your
			// machine.

#if PALETTESHIFTFIX

			AddToPaletteShiftList(SHOWWINDOW, (LONG)m_pWindow);

#else

			{
				STBofScreen scrObj(&m_pWindow->portRect);

				::ShowWindow(m_pWindow);
				::SelectWindow(m_pWindow);
			}
#endif
			::SetPort(m_pWindow);

			//  generate an update event.
			InvalidateRect(&m_cRect);

			m_bVisible = TRUE;
#endif
		}
	}
}

VOID CBofWindow::Hide() {
	Assert(IsValidObject(this));

	if (!ErrorOccurred()) {

		Assert(IsCreated());

#if BOF_WINDOWS

		::ShowWindow(m_hWnd, SW_HIDE);

#elif BOF_MAC

#if PALETTESHIFTFIX

		AddToPaletteShiftList(HIDEWINDOW, (LONG)m_pWindow);

#else
		gAllowPaletteShifts = false;
		LMSetPaintWhite(FALSE);
		::HideWindow(m_pWindow);
		gAllowPaletteShifts = true;
#endif
		m_bVisible = FALSE;
#endif
	}
}

VOID CBofWindow::PostMessage(ULONG nMessage, ULONG lParam1, ULONG lParam2) {
	Assert(IsValidObject(this));
	Assert(IsCreated());

#if BOF_WINDOWS
	::PostMessage(m_hWnd, nMessage, (WPARAM)lParam1, lParam2);

#elif BOF_MAC

	CBofMessage *pMessage;

	// Create a user defined message.
	// NOTE: This message will be deleted by HandleMacEvent()
	//
	if ((pMessage = new CBofMessage) != nullptr) {

		pMessage->m_pWindow = this;
		pMessage->m_nMessage = nMessage;
		pMessage->m_lParam1 = lParam1;
		pMessage->m_lParam2 = lParam2;

		PostEvent(app3Evt, (LONG)pMessage);
	}
#endif
}

#if BOF_MAC
#define GETTIME() (ULONG)(16.66 * TickCount())
#endif

VOID CBofWindow::SetTimer(UINT nID, UINT nInterval, BOFCALLBACK pCallBack) {
	Assert(IsValidObject(this));
	Assert(IsCreated());

	CBofTimerPacket *pPacket;

#if BOF_WINDOWS
	if (pCallBack != nullptr) {
#endif

#if BOF_DEBUG
		CheckTimerID(nID);
#endif

		// jwl 08.15.96 don't add it if there's already a timer there
		// with the same id.

		pPacket = m_pTimerList;
		while (pPacket != nullptr) {

			if (pPacket->m_nID == nID) {
				return;
			}
			pPacket = (CBofTimerPacket *)pPacket->GetNext();
		}

		if ((pPacket = new CBofTimerPacket) != nullptr) {

			pPacket->m_nID = nID;
			pPacket->m_nInterval = nInterval;
			pPacket->m_pCallBack = pCallBack;
			pPacket->m_pOwnerWindow = this;

			// Add this timer to the list of current timers
			//

			if (m_pTimerList != nullptr) {
				m_pTimerList->AddToHead(pPacket);
			}
			m_pTimerList = pPacket;
		}

#if BOF_WINDOWS
	}
#endif

#if BOF_WINDOWS
	::SetTimer(m_hWnd, nID, nInterval, nullptr);

#elif BOF_MAC

	pPacket->m_lLastTime = GETTIME();

#endif
}

#if BOF_DEBUG
VOID CBofWindow::CheckTimerID(UINT nID) {
	CBofTimerPacket *pPacket;

	pPacket = m_pTimerList;
	while (pPacket != nullptr) {

		if (pPacket->m_nID == nID) {
			LogWarning(BuildString("CBofWindow::SetTimer() - there is already a timer with ID %d", nID));
			break;
		}
		pPacket = (CBofTimerPacket *)pPacket->GetNext();
	}
}
#endif

VOID CBofWindow::KillTimer(UINT nID) {
	Assert(IsValidObject(this));

#if BOF_WINDOWS
	::KillTimer(m_hWnd, nID);

#elif BOF_MAC

#endif

	// Find and remove the timer packet for this timer
	CBofTimerPacket *pPacket;

	pPacket = m_pTimerList;
	while (pPacket != nullptr) {
		if (pPacket->m_nID == nID) {

			if (pPacket == m_pTimerList) {
				m_pTimerList = (CBofTimerPacket *)m_pTimerList->GetNext();
			}

			delete pPacket;
			break;
		}
		pPacket = (CBofTimerPacket *)pPacket->GetNext();
	}
}

VOID CBofWindow::KillMyTimers() {
	Assert(IsValidObject(this));

	CBofTimerPacket *pTimer, *pNextTimer;

	pTimer = m_pTimerList;
	while (pTimer != nullptr) {

		pNextTimer = (CBofTimerPacket *)pTimer->GetNext();

		if (pTimer->m_pOwnerWindow == this) {
			KillTimer(pTimer->m_nID);
		}

		pTimer = pNextTimer;
	}
}

VOID CBofWindow::ScreenToClient(CBofPoint *pPoint) {
	Assert(IsValidObject(this));

	Assert(pPoint != nullptr);

#if BOF_MAC
	// jwl 07.24.96 make sure that our frontmost window is our current
	// grafport.

	Point stPoint;
	GrafPtr savePort;

	//::GetPort (&savePort);
	//::SetPort (m_pWindow);

	stPoint.v = pPoint->y;
	stPoint.h = pPoint->x;

	GlobalToLocal(&stPoint);

	//::SetPort (savePort);

	pPoint->y = stPoint.v;
	pPoint->x = stPoint.h;

#elif BOF_WINDOWS
	POINT stPoint;

	stPoint.x = pPoint->x;
	stPoint.y = pPoint->y;

	::ScreenToClient(m_hWnd, &stPoint);

	pPoint->x = stPoint.x;
	pPoint->y = stPoint.y;
#endif
}

VOID CBofWindow::ClientToScreen(CBofPoint *pPoint) {
	Assert(IsValidObject(this));

	Assert(pPoint != nullptr);

#if BOF_MAC
#if DEVELOPMENT
	Assert(false);
#endif
#elif BOF_WINDOWS
	POINT stPoint;

	stPoint.x = pPoint->x;
	stPoint.y = pPoint->y;

	::ClientToScreen(m_hWnd, &stPoint);

	pPoint->x = stPoint.x;
	pPoint->y = stPoint.y;
#endif
}

CBofRect CBofWindow::GetClientRect() {
	Assert(IsValidObject(this));

	CBofRect cRect(0, 0, m_cRect.Width() - 1, m_cRect.Height() - 1);

#if BOF_WINDOWS
	RECT stRect;

	::GetClientRect(m_hWnd, &stRect);

	cRect = stRect;
#endif

	return cRect;
}

VOID CBofWindow::PostUserMessage(ULONG lMessage, ULONG lExtraInfo) {
#if 0
	PostMessage(BM_USER, lMessage, lExtraInfo);
#endif
}

/*****************************************************************************
 *
 *  GetAnscestor     - Retrieves oldest anscestor of this window
 *
 *  DESCRIPTION:
 *
 *
 *
 *  SAMPLE USAGE:
 *  pOldestParent = pWnd->GetAnscestor();
 *
 *  RETURNS:  CBofWindow * = pointer to oldest anscestor
 *
 *****************************************************************************/
CBofWindow *CBofWindow::GetAnscestor() {
	Assert(IsValidObject(this));

	CBofWindow *pCurWnd, *pLastWnd;

	pLastWnd = this;
	pCurWnd = m_pParentWnd;

	while (pCurWnd != nullptr) {
		pLastWnd = pCurWnd;

		pCurWnd = pCurWnd->m_pParentWnd;
	}

	return pLastWnd;
}

/*****************************************************************************
 *
 *  FlushAllMessages - Flushes every pending Windows message for current window
 *
 *  DESCRIPTION:
 *
 *
 *  SAMPLE USAGE:
 *  pWindow->FlushAllMessages();
 *
 *  RETURNS:  nothing
 *
 *****************************************************************************/
VOID CBofWindow::FlushAllMessages() {
	// make sure this is a valid window
	Assert(IsValidObject(this));
	Assert(IsCreated());

#if BOF_WINDOWS

	MSG msg;

	/*
	 * find and remove all events
	 */
	while (PeekMessage(&msg, m_hWnd, 0, 0, PM_REMOVE)) {

		/*
		 * hack to handle special case Paint message, otherwise it will
		 * keep generating new paint messages
		 */
		if (msg.message == WM_PAINT) {
			ValidateRect(nullptr);
		}
	}
#elif BOF_MAC
	FlushEvents(0xFFFF, 0);
#endif
}

VOID CBofWindow::ValidateRect(CBofRect *pRect) {
#if BOF_WINDOWS
	RECT stRect;

	// if (m_hWnd != nullptr) {

	if (pRect == nullptr) {
		::ValidateRect(m_hWnd, nullptr);

	} else {
		stRect = *pRect;

		/*stRect.left = pRect->left;
		stRect.top = pRect->top;
		stRect.right = pRect->right;
		stRect.bottom = pRect->bottom;*/

		::ValidateRect(m_hWnd, &stRect);
	}
	//}
#elif BOF_MAC
	{
		// jwl 08.21.96 set current port... don't require caller to do this.
		STBofPort stSavePort(GetMacWindow());
		if (pRect == nullptr)
			pRect = &m_cRect;

		Rect stRect = {pRect->left, pRect->top, pRect->right + 1, pRect->bottom + 1};

		::ValidRect(&stRect);
	}
#endif
}

VOID CBofWindow::InvalidateRect(CBofRect *pRect) {
#if BOF_WINDOWS
	RECT stRect;

	if (pRect == nullptr) {
		::InvalidateRect(m_hWnd, nullptr, FALSE);

	} else {
		stRect = *pRect;

		/*stRect.left = pRect->left;
		stRect.top = pRect->top;
		stRect.right = pRect->right;
		stRect.bottom = pRect->bottom;*/

		::InvalidateRect(m_hWnd, &stRect, FALSE);
	}
#elif BOF_MAC
	STBofPort stSavePort(GetMacWindow());

	if (pRect == nullptr)
		pRect = &m_cRect;

	Rect stRect = {pRect->left, pRect->top, pRect->right + 1, pRect->bottom + 1};

	::InvalRect(&stRect);
#endif
}

ERROR_CODE CBofWindow::SetBackdrop(CBofBitmap *pNewBitmap, BOOL bRefresh) {
	Assert(IsValidObject(this));

	// use KillBackdrop() if you don't want the current backdrop anymore
	Assert(pNewBitmap != nullptr);

	// destroy old backdrop (if any)
	KillBackdrop();

	// we take ownership of this bitmap!
	m_pBackdrop = pNewBitmap;

	if (bRefresh) {
		m_pBackdrop->Paint(this, 0, 0);
	}

	return m_errCode;
}

ERROR_CODE CBofWindow::SetBackdrop(const CHAR *pszFileName, BOOL bRefresh) {
	Assert(IsValidObject(this));

	// use KillBackdrop() if you don't want the current backdrop anymore
	Assert(pszFileName != nullptr);

	CBofBitmap *pBmp;
	CBofPalette *pPalette;

	// use Application's palette if none supplied
	pPalette = CBofApp::GetApp()->GetPalette();

	if ((pBmp = new CBofBitmap(pszFileName, pPalette)) != nullptr) {

		return SetBackdrop(pBmp, bRefresh);
	} else {
		ReportError(ERR_MEMORY, "Could not allocate a new CBofBitmap");
	}

	return m_errCode;
}

VOID CBofWindow::KillBackdrop() {
	Assert(IsValidObject(this));

	if (m_pBackdrop != nullptr) {
		delete m_pBackdrop;
		m_pBackdrop = nullptr;
	}
}

ERROR_CODE CBofWindow::PaintBackdrop(CBofRect *pRect, INT nTransparentColor) {
	Assert(IsValidObject(this));

	if (m_pBackdrop != nullptr) {

		if (pRect == nullptr) {

			m_errCode = m_pBackdrop->Paint(this, &m_cRect, nullptr, nTransparentColor);

		} else {
			m_errCode = m_pBackdrop->Paint(this, pRect, pRect, nTransparentColor);
		}
	}

	return m_errCode;
}

VOID CBofWindow::SelectPalette(CBofPalette *pPal) {
	Assert(IsValidObject(this));
	Assert(IsCreated());

	if (pPal != nullptr) {
		Assert(IsValidObject(pPal));

#if BOF_WINDOWS
		// BCW - 01-20-97 - Fixed part 3 of resource leak by commenting
		// out this code.  This could introduce palette shifts,
		// but maybe only on 8 bit displays.
		//
		/*HDC hDC;

		if ((hDC = GetDC()) != nullptr) {
		    ::SelectPalette(hDC, pPal->GetPalette(), FALSE);

		#if BOF_WINMAC
		    if (g_bRealizePalette)
		#endif
		    ::RealizePalette(hDC);

		    ReleaseDC(hDC);
		}*/

#if BOF_WINMAC
		SetMacPalette(pPal);
#endif

#elif BOF_MAC
		Assert(pPal != nullptr);
		Assert(m_pWindow != nullptr);
		PaletteHandle newPH = pPal->GetPalette();

		// jwl 08.08.96 have seen newPH nullptr, if it is, the default 256 colors
		// of the game are used (see 'pltt' resource)
		if (newPH != nullptr) {
			Assert((*newPH)->pmEntries == 256);
			Assert(GetHandleSize((Handle)newPH) != 0);

			// jwl 09.04.96 palette shift fix... take all the calls that cause palette shifts
			// and move them as close to the onscreen rendering code as possible, this will
			// minimize the shift... but not eliminate it.

#if PALETTESHIFTFIX
			// scg 01.28.97 simplified using AddToPaletteShiftList

			AddToPaletteShiftList(SETPALETTE, (LONG)newPH, (LONG)m_pWindow);
#else
			::SetPalette(m_pWindow, newPH, false);
#endif
		}
#endif
	}
}

#if BOF_WINMAC
BOOL CBofWindow::SetMacPalette(CBofPalette *pPalette) {
	Assert(IsValidObject(this));
	Assert(pPalette != nullptr);
	Assert(pPalette->GetPalette() != nullptr);

	WindowPtr myWindow;
	CGrafPtr pThisPort;
	GrafPtr pSavePort;
	PALETTEENTRY PalEntries[256];
	INT i;
	OSErr err;
	static PaletteHandle hMainMacPal = nullptr;
	PaletteHandle hOldMainMacPal;
	HWND hMainWnd;
	HPALETTE hMainPal;
	CTabHandle hMainCLUT;

	hMainWnd = m_hWnd;
	hMainPal = (HPALETTE)pPalette->GetPalette();

	myWindow = GetWrapperWindow(hMainWnd);
	pThisPort = (CGrafPtr)myWindow;

	GetPort(&pSavePort);
	SetPort((GrafPort *)pThisPort);

	LockPixels(pThisPort->portPixMap);
	hMainCLUT = (**(*pThisPort).portPixMap).pmTable;
	UnlockPixels(pThisPort->portPixMap);
	err = HandToHand((CHAR ***)&hMainCLUT);
	if (err != noErr) {
		SetPort(pSavePort);
		return FALSE;
	}

	::GetPaletteEntries(hMainPal, 0, 256, PalEntries);
	for (i = 0; i < (*hMainCLUT)->ctSize; i++) {
		(*hMainCLUT)->ctTable[i].rgb.red = (USHORT)((PalEntries[i].peRed * 0xFFFF) / 0xFF);
		(*hMainCLUT)->ctTable[i].rgb.green = (USHORT)((PalEntries[i].peGreen * 0xFFFF) / 0xFF);
		(*hMainCLUT)->ctTable[i].rgb.blue = (USHORT)((PalEntries[i].peBlue * 0xFFFF) / 0xFF);
		(*hMainCLUT)->ctTable[i].value = (SHORT)i;

		PalEntries[i].peFlags = (UBYTE)(PC_EXPLICIT | i);
	}
	::SetPaletteEntries(hMainPal, 0, 256, PalEntries);

	(*hMainCLUT)->ctFlags = 0x4000;
	(*hMainCLUT)->ctSeed = GetCTSeed();

	hOldMainMacPal = hMainMacPal;
	hMainMacPal = NewPalette(256, hMainCLUT, pmExplicit | pmTolerant, 0x0000);
	if (hMainMacPal == nullptr) {
		DisposCTable(hMainCLUT);
		SetPort(pSavePort);
		return FALSE;

	} else {

		if (hOldMainMacPal && (hOldMainMacPal = ::GetPalette(myWindow)) != nullptr)
			DisposePalette(hOldMainMacPal);
	}

	SetPalette((WindowPtr) - 1, hMainMacPal, true);

	SetPalette(myWindow, hMainMacPal, true);
	ActivatePalette(myWindow);

	SetPort(pSavePort);

	g_bRealizePalette = FALSE;

	return TRUE;
}
#endif

Graphics::ManagedSurface *CBofWindow::getSurface() {
	error("TODO: Implement CBofWindow::getSurface");
}


// Default version of these virtual functions don't do anything
//
VOID CBofWindow::OnMouseMove(UINT, CBofPoint *) {}

VOID CBofWindow::OnLButtonDown(UINT, CBofPoint *, void *) {}
VOID CBofWindow::OnLButtonUp(UINT, CBofPoint *, void *) {}
VOID CBofWindow::OnLButtonDblClk(UINT, CBofPoint *) {}

VOID CBofWindow::OnRButtonDown(UINT, CBofPoint *) {}
VOID CBofWindow::OnRButtonUp(UINT, CBofPoint *) {}
VOID CBofWindow::OnRButtonDblClk(UINT, CBofPoint *) {}

VOID CBofWindow::OnKeyHit(ULONG, ULONG) {}

VOID CBofWindow::OnReSize(CBofSize *) {}
VOID CBofWindow::OnPaint(CBofRect *) {}
VOID CBofWindow::OnTimer(UINT) {}

VOID CBofWindow::OnClose() {}

VOID CBofWindow::OnCommand(ULONG, ULONG) {}

VOID CBofWindow::OnBofButton(CBofObject *, INT) {}
VOID CBofWindow::OnBofScrollBar(CBofObject *, INT) {}
VOID CBofWindow::OnBofListBox(CBofObject *, INT) {}
VOID CBofWindow::OnUserMessage(ULONG, ULONG) {}
VOID CBofWindow::OnMainLoop() {}

VOID CBofWindow::OnSoundNotify(CBofObject *, ULONG) {}
VOID CBofWindow::OnMovieNotify(ULONG, ULONG) {}

VOID CBofWindow::OnActivate() {}
VOID CBofWindow::OnDeActivate() {}

VOID CBofWindow::OnMCINotify(ULONG wParam, ULONG lParam) {
	Assert(IsValidObject(this));

#if 0
	if (wParam == MCI_NOTIFY_SUCCESSFUL) {
		CBofSound *pSound;

		pSound = CBofSound::OnMCIStopped(wParam, lParam);
		if (pSound != nullptr) {
			OnSoundNotify(pSound, 0);
		}
	}
#endif
}

#if BOF_WINDOWS

CBofWindow *CBofWindow::FromHandle(HWND hWnd) {
	CBofWindow *pWnd;

	pWnd = m_pWindowList;
	while (pWnd != nullptr) {

		if (pWnd->m_hWnd == hWnd)
			break;

		pWnd = (CBofWindow *)pWnd->GetNext();
	}

	return pWnd;
}

LRESULT CALLBACK BofWindowProcedure(HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam) {
	CBofWindow *pWnd;

	Assert(hWnd != nullptr);

	if ((pWnd = CBofWindow::FromHandle(hWnd)) != nullptr) {

		return pWnd->WindowProcedure(nMessage, wParam, lParam);

	} else {
		return ::DefWindowProc(hWnd, nMessage, wParam, lParam);
	}
}

LONG CBofWindow::OnDefWinProc(UINT nMessage, WPARAM wParam, LPARAM lParam) {
	Assert(IsValidObject(this));

	return ::DefWindowProc(m_hWnd, nMessage, wParam, lParam);
}

BOOL CBofWindow::IsChildOf(CBofWindow *pWin) {
	Assert(IsValidObject(this));
	Assert(pWin != nullptr);

	CBofWindow *pParent;

	pParent = nullptr;
	if (pWin != nullptr) {

		pParent = pWin->m_pParentWnd;
		while (pParent != nullptr) {

			if (pParent == this)
				break;

			pParent = pParent->m_pParentWnd;
		}
	}

	return pParent != nullptr;
}

BOOL CBofWindow ::IsParentOf(CBofWindow *pWin) {
	Assert(IsValidObject(this));
	Assert(pWin != nullptr);

	BOOL bIsParent;

	bIsParent = FALSE;
	if (pWin != nullptr) {
		bIsParent = pWin->IsChildOf(this);
	}
	return bIsParent;
}

LONG CBofWindow::WindowProcedure(UINT nMessage, WPARAM wParam, LPARAM lParam) {
	Assert(IsValidObject(this));

	switch (nMessage) {

	case WM_ACTIVATE: {
		USHORT nFlags;

		nFlags = LOWORD(wParam);

		if (nFlags == WA_ACTIVE || nFlags == WA_CLICKACTIVE) {
			OnActivate();
		} else {
			OnDeActivate();
		}
		break;
	}

	case MM_MCINOTIFY:
		OnMCINotify(wParam, lParam);
		break;

#if BOF_WINNT

	case WM_CTLCOLOREDIT: {
		CBofWindow *pWnd;
		LOGBRUSH stBrush;

		if ((pWnd = FromHandle((HWND)lParam)) != nullptr) {

			stBrush.lbStyle = BS_SOLID;
			stBrush.lbColor = pWnd->GetBkColor();
			stBrush.lbHatch = 0; // This member will be ignored

			if (m_hBrush != nullptr) {
				if (::DeleteObject(m_hBrush) == FALSE) {
					LogError("DeleteObject() failed");
				}
			}
			m_hBrush = ::CreateBrushIndirect(&stBrush);

			::SetTextColor((HDC)wParam, pWnd->GetFgColor());
			::SetBkColor((HDC)wParam, pWnd->GetBkColor());
		}

		return (LONG)m_hBrush;
	}

#elif BOF_WIN16

	case WM_CTLCOLOR: {

		if (HIWORD(lParam) == CTLCOLOR_EDIT) {
			CBofWindow *pWnd;
			LOGBRUSH stBrush;

			if ((pWnd = FromHandle((HWND)LOWORD(lParam))) != nullptr) {

				stBrush.lbStyle = BS_SOLID;
				stBrush.lbColor = pWnd->GetBkColor();
				stBrush.lbHatch = 0; // This member will be ignored

				if (m_hBrush != nullptr) {
					if (::DeleteObject(m_hBrush) == FALSE) {
						LogError("DeleteObject() failed");
					}
				}
				m_hBrush = ::CreateBrushIndirect(&stBrush);

				::SetTextColor((HDC)wParam, pWnd->GetFgColor());
				::SetBkColor((HDC)wParam, pWnd->GetBkColor());
			}

			return (LONG)m_hBrush;

		} else {
			return nullptr;
		}
	}

#endif

	case WM_ERASEBKGND: {
		// just return non-zero to pretend that we erased the background
		return 1;
	}

	case WM_MOUSEMOVE: {
		CBofPoint cPoint((SHORT)LOWORD(lParam), (SHORT)HIWORD(lParam));
		::SetCursor(CBofCursor::GetCurrent());

		OnMouseMove(wParam, &cPoint);
		break;
	}
	case WM_LBUTTONDOWN: {
		CBofPoint cPoint((SHORT)LOWORD(lParam), (SHORT)HIWORD(lParam));

		OnLButtonDown(wParam, &cPoint);
		break;
	}

	case WM_LBUTTONUP: {
		CBofPoint cPoint((SHORT)LOWORD(lParam), (SHORT)HIWORD(lParam));

		OnLButtonUp(wParam, &cPoint);
		break;
	}

	case WM_LBUTTONDBLCLK: {
		CBofPoint cPoint((SHORT)LOWORD(lParam), (SHORT)HIWORD(lParam));

		OnLButtonDblClk(wParam, &cPoint);
		break;
	}

	case WM_RBUTTONDOWN: {
		CBofPoint cPoint((SHORT)LOWORD(lParam), (SHORT)HIWORD(lParam));

		OnRButtonDown(wParam, &cPoint);
		break;
	}

	case WM_RBUTTONUP: {
		CBofPoint cPoint((SHORT)LOWORD(lParam), (SHORT)HIWORD(lParam));

		OnRButtonUp(wParam, &cPoint);
		break;
	}

	case WM_RBUTTONDBLCLK: {
		CBofPoint cPoint((SHORT)LOWORD(lParam), (SHORT)HIWORD(lParam));

		OnRButtonDblClk(wParam, &cPoint);
		break;
	}

	case WM_SYSCHAR:
	case WM_CHAR: {
		ULONG lNewKey;

		if ((lNewKey = TranslateChar(wParam, lParam & 0x0000FFFF, lParam >> 16)) != BKEY_UNKNOWN) {
			OnKeyHit(lNewKey, lParam & 0x0000FFFF);
		}
		break;
	}

	case WM_SYSKEYDOWN:
	case WM_KEYDOWN: {
		ULONG lNewKey;

		if ((lNewKey = TranslateKey(wParam, lParam & 0x0000FFFF, lParam >> 16)) != BKEY_UNKNOWN) {
			OnKeyHit(lNewKey, lParam & 0x0000FFFF);
		}
		break;
	}

	case WM_SYSKEYUP:
	case WM_KEYUP:
		break;

	case WM_SETCURSOR:
		return TRUE;
		break;

	case WM_SIZE: {
		CBofSize cSize(LOWORD(lParam), HIWORD(lParam));

		OnReSize(&cSize);
		break;
	}

	case WM_PAINT: {
		PAINTSTRUCT ps;

		Assert(m_hWnd != nullptr);

		BeginPaint(m_hWnd, &ps);

		// Hack to work around incompatibility with Microsoft RECT
		//
		CBofRect cRect(&ps.rcPaint);

		if ((cRect.Width() != 0) && (cRect.Height() != 0)) {
			OnPaint(&cRect);
		}

		// Make sure the Window still exists
		//
		if (m_hWnd != nullptr) {
			EndPaint(m_hWnd, &ps);
		}
		break;
	}

	case WM_TIMER: {
		BOFCALLBACK pCallBack;

		if ((pCallBack = (BOFCALLBACK)lParam) != nullptr) {
			(*pCallBack)(wParam, this);

		} else {
			OnTimer(wParam);
		}
		break;
	}

	case WM_COMMAND: {
		OnCommand(wParam, lParam);
		break;
	}

	case WM_CLOSE: {
		OnClose();
		break;
	}
	case WM_USER: {
		OnUserMessage(wParam, lParam);
		break;
	}

	default:
		return OnDefWinProc(nMessage, wParam, lParam);
	}
	return 0;
}

#elif BOF_MAC
BOOL CBofWindow::HandleMacEvent(EventRecord *pEvent) {
	// Assert(pEvent != nullptr);
	BOOL bQuit;
	// assume not quitting
	bQuit = FALSE;

	switch (pEvent->what) {

	case keyUp:
		break;

	case autoKey:
	case keyDown:
		HandleKeyDown(pEvent);
		break;

	case updateEvt:
		HandleUpdateEvt(pEvent);
		break;

	case mouseDown:
		HandleMouseDown(pEvent);
		break;

	case mouseUp:
		HandleMouseUp(pEvent);
		break;

	case app3Evt:
		bQuit = HandleApp3Evt(pEvent);
		break;

	case activateEvt:
		HandleActivateEvt(pEvent);
		break;

	case osEvt:
		HandleOSEvt(pEvent);
		break;

	default:
		// LogInfo(BuildString("Unknown event: what=%d, message=%d, when=%d, where=(%d,%d), modifiers=%d", pEvent->what, pEvent->message, pEvent->when, pEvent->where.h, pEvent->where.v, pEvent->modifiers));
		break;
	}

	return bQuit;
}

#if BOF_MAC
VOID CBofWindow::HandleKeyDown(EventRecord *pEvent) {
	ULONG lNewKey;

	// jwl 08.14.96 handle translating keys in translate key...
	char key = pEvent->message & charCodeMask;

	if ((lNewKey = TranslateKey(pEvent->message, 1, pEvent->modifiers)) != BKEY_UNKNOWN) {
		CBofWindow *pobj = m_pActiveWindow;
		if (m_pActiveWindow != nullptr) {
			STBofPort stSavePort(m_pActiveWindow->GetMacWindow());
			m_pActiveWindow->OnKeyHit(lNewKey, 1);
		}
	}
}
#endif

VOID CBofWindow::HandleUpdateEvt(EventRecord *pEvent) {
	CBofWindow *pWindow;
	WindowPtr pMacWindow;

	if ((pMacWindow = (WindowPtr)pEvent->message) != nullptr) {

		if ((pWindow = CBofWindow::FromMacWindow(pMacWindow)) != nullptr) {
			STBofPort stSavePort(pMacWindow);
			pWindow->HandleUpdate();
		}
	}
}

VOID CBofWindow::HandleMouseDown(EventRecord *pEvent) {
	CBofWindow *pWnd;
	WindowPtr pMacWin;

	// determine which window the mouse button was pressed in
	//
	FindWindow(pEvent->where, &pMacWin);

	if (pMacWin != nullptr) {

		// let that window know about it
		//
		if ((pWnd = CBofWindow::FromMacWindow(pMacWin)) != nullptr) {
			STBofPort stSavePort(pMacWin);

			// Have to adjust the mouse coordinates from
			// global to local coordinates
			//
			// GlobalToLocal(&pEvent->where);

			// If any window has captured the mouse, then use
			// that window instead.
			//
			if (m_pCapturedWindow != nullptr) {
				pWnd = m_pCapturedWindow;
			}

			CBofPoint cPoint(pEvent->where.h, pEvent->where.v);

			cPoint -= pWnd->m_cWindowRect.TopLeft();
			pWnd->m_cPrevMouseDown = cPoint; // jwl 08.29.96 need to save local mouse coords

			pWnd->OnLButtonDown(0, &cPoint);
		}
		//
		// Otherwise we might have to activate the non-Boffo window
		//
		/*
		else {
		    ::SelectWindow(pMacWin);
		}
		*/
	}
}

VOID CBofWindow::HandleMouseUp(EventRecord *pEvent) {
	CBofWindow *pWnd;
	WindowPtr pMacWin;

	// determine which window the mouse button was released in
	FindWindow(pEvent->where, &pMacWin);

	if (pMacWin != nullptr) {

		// let that window know about it
		//
		if ((pWnd = CBofWindow::FromMacWindow(pMacWin)) != nullptr) {
			STBofPort stSavePort(pMacWin);

			// Have to adjust the mouse coordinates from
			// global to local coordinates
			//
			// GlobalToLocal(&pEvent->where);

			// If any window has captured the mouse, then use
			// that window instead.
			//
			if (m_pCapturedWindow != nullptr) {
				pWnd = m_pCapturedWindow;
			}

			CBofPoint cPoint(pEvent->where.h, pEvent->where.v);

			cPoint -= pWnd->m_cWindowRect.TopLeft();

			pWnd->OnLButtonUp(0, &cPoint);
		}
	}
}

VOID CBofWindow::HandleActivateEvt(EventRecord *pEvent) {

	CBofWindow *pWindow;
	WindowPtr pMacWindow;

	if ((pMacWindow = (WindowPtr)pEvent->message) != nullptr) {

		if ((pWindow = CBofWindow::FromMacWindow(pMacWindow)) != nullptr) {
			STBofPort stSavePort(pMacWindow);
			if (pEvent->modifiers & 1) {
				pWindow->OnActivate();
			} else {
				pWindow->OnDeActivate();
			}
		}
	}

	return;
}

VOID CBofWindow::HandleOSEvt(EventRecord *pEvent) {

	switch ((pEvent->message >> 24) & 0x0ff) {

	case mouseMovedMessage: {

		// if mouse moved
		//
		if ((g_nMouseX != pEvent->where.h) || (g_nMouseY != pEvent->where.v)) {

			// keep track of new mouse cursor position
			//
			g_nMouseX = pEvent->where.h;
			g_nMouseY = pEvent->where.v;

			WindowPtr pMacWindow;
			CBofWindow *pWindow;

			// determine which window it was over at the time
			//
			FindWindow(pEvent->where, &pMacWindow);

			if (pMacWindow != nullptr) {
				if ((pWindow = CBofWindow::FromMacWindow(pMacWindow)) != nullptr) {
					STBofPort stSavePort(pMacWindow);

					// If any window has captured the mouse, then use
					// that window instead.
					//
					if (m_pCapturedWindow != nullptr) {
						pWindow = m_pCapturedWindow;
					}

					// Have to adjust the mouse coordinates from
					// global to local coordinates
					//
					// GlobalToLocal(&pEvent->where); // jwl 07.03.96

					CBofPoint cPoint(pEvent->where.h, pEvent->where.v);

					cPoint -= pWindow->m_cWindowRect.TopLeft(); // jwl 07.03.96

					pWindow->OnMouseMove(0, &cPoint);
				}
			}
		}
	}
	}
}

BOOL CBofWindow::HandleApp3Evt(EventRecord *pEvent) {
	BOOL bQuit = false;
	CBofMessage *pMessage;

	// just a mask for our bof message
	//
	if ((pMessage = (CBofMessage *)(pEvent->message)) != nullptr) {

		// make sure it's a valid message
		Assert(IsValidObject(pMessage));

		switch (pMessage->m_nMessage) {

		// handle user defined events
		//
		case BM_USER:
			Assert(pMessage->m_pWindow != nullptr);
			pMessage->m_pWindow->OnUserMessage(pMessage->m_lParam1, pMessage->m_lParam2);
			break;

		case BM_CLOSE:
			Assert(pMessage->m_pWindow != nullptr);
			pMessage->m_pWindow->OnClose();
			break;

		case BM_QUIT:
			bQuit = TRUE;
			break;

		default:
			LogWarning(BuildString("Unknown Boffo Message: %d", pMessage->m_nMessage));
			break;
		}

		delete pMessage;

	} else {
		LogWarning(BuildString("Unknown app3Evt event: message=%d, where=(%d,%d)", pEvent->message, pEvent->where.h, pEvent->where.v));
	}

	return bQuit;
}

VOID CBofWindow::HandleMacTimers() {
	CBofTimerPacket *pTimer, *pNextTimer;
	ULONG lCurrentTime;

	pTimer = m_pTimerList;
	while (pTimer != nullptr) {

		// jwl 07.15.96 Get the next timer packet first as our execution
		// code below can trash m_pTimerList.
		pNextTimer = (CBofTimerPacket *)pTimer->GetNext();
		lCurrentTime = GETTIME();

		if ((UINT)(lCurrentTime - pTimer->m_lLastTime) >= pTimer->m_nInterval) {

			// Remember for next time
			pTimer->m_lLastTime = lCurrentTime;

			if (pTimer->m_pCallBack != nullptr) {

				// Execute call back
#if __POWERPC__
#if DEVELOPMENT
				DebugStr("\pCallback being executed in CBofWindow::HandleMacTimers!!!!! yikes");
#else
				MacMessageBox("Callback being executed in CBofWindow::HandleMacTimers!!!!! yikes", nullptr);
#endif
#endif
				(*pTimer->m_pCallBack)(pTimer->m_nID, pTimer->m_pOwnerWindow);

				// otherwise, just call the virtual OnTimer()
				//
			} else {

				pTimer->m_pOwnerWindow->OnTimer(pTimer->m_nID);
			}
		}

		pTimer = pNextTimer;
	}
}

CBofWindow *CBofWindow::FromMacWindow(WindowPtr pWindow) {
	Assert(pWindow != nullptr);

	CBofWindow *pWnd;

	pWnd = m_pWindowList;
	while (pWnd != nullptr) {

		if (pWnd->m_pWindow == pWindow)
			break;

		pWnd = (CBofWindow *)pWnd->GetNext();
	}

	return pWnd;
}

VOID CBofWindow::HandleUpdate() {
	Assert(IsValidObject(this));
	Assert(IsCreated());

	::SetPort(m_pWindow); // scg 01.23.97 Spotlight complained
	::BeginUpdate(m_pWindow);

	// Get the bounding rectangle around the invalid region
	// of this window.
	//
	Rect stRect, holdRect;
	holdRect = stRect = (*m_pWindow->visRgn)->rgnBBox;
	CBofRect cRect(stRect.left, stRect.top, stRect.right - 1, stRect.bottom - 1);

	// tell window to repaint that area (unless there's nothing to repaint)
	//
	if ((cRect.Width() != 0) && (cRect.Height() != 0)) {
		OnPaint(&cRect);
	}

	// jwl 08.19.94 With the full permission of my peers for this hack... it is
	// possible for GotoNewWindow to be called by the onpaint method above which
	// subsequently trashes the existing game window.  So... check for a nullptr
	// window before continuing.

	if (m_pWindow)
		::EndUpdate(m_pWindow);
}

#endif // !BOF_WINDOWS

ULONG TranslateChar(UINT nChar, ULONG /*nRepCount*/, ULONG nFlags) {
	ULONG nCode;

	nCode = nChar;

#if BOF_WINDOWS

	if (nFlags & KF_ALTDOWN) {
		nCode |= BKF_ALT;
	}
#endif

	// LogInfo(BuildString("TranslateChar(%04x, %d, %04x) = %d", nChar, nRepCount, nFlags, nCode));

	return nCode;
}

ULONG TranslateKey(UINT nChar, ULONG /*nRepCount*/, ULONG nFlags) {
	ULONG nCode = 0;

#if BOF_WINDOWS

	nCode = nChar;

	switch (nChar) {

	case VK_F1:
		nCode = BKEY_F1;
		break;

	case VK_F2:
		nCode = BKEY_F2;
		break;

	case VK_F3:
		nCode = BKEY_F3;
		break;

	case VK_F4:
		nCode = BKEY_F4;
		break;

	case VK_F5:
		nCode = BKEY_F5;
		break;

	case VK_F6:
		nCode = BKEY_F6;
		break;

	case VK_F7:
		nCode = BKEY_F7;
		break;

	case VK_F8:
		nCode = BKEY_F8;
		break;

	case VK_F9:
		nCode = BKEY_F9;
		break;

	case VK_F10:
		nCode = BKEY_F10;
		break;

	case VK_F11:
		nCode = BKEY_F11;
		break;

	case VK_F12:
		nCode = BKEY_F12;
		break;

	case VK_END:
		nCode = BKEY_END;
		break;

	case VK_HOME:
		nCode = BKEY_HOME;
		break;

	case VK_LEFT:
		nCode = BKEY_LEFT;
		break;

	case VK_RIGHT:
		nCode = BKEY_RIGHT;
		break;

	case VK_UP:
		nCode = BKEY_UP;
		break;

	case VK_DOWN:
		nCode = BKEY_DOWN;
		break;

	case VK_INSERT:
		nCode = BKEY_INS;
		break;

	case VK_DELETE:
		nCode = BKEY_DEL;
		break;

	case VK_SCROLL:
		nCode = BKEY_SCRL_LOCK;
		break;

	case VK_PRIOR:
		nCode = BKEY_PAGEUP;
		break;

	case VK_NEXT:
		nCode = BKEY_PAGEDOWN;
		break;

	// no translation for this key
	//
	default:
		nCode = BKEY_UNKNOWN;
		break;
	}

	if (nCode != BKEY_UNKNOWN) {

		if (nFlags & KF_ALTDOWN) {
			nCode |= BKF_ALT;
		}
	}

#elif BOF_MAC
	// jwl 10.23.96 only want the bottom two nibbles
	nCode = nChar & 0xff;
	switch (nChar & charCodeMask) {

	case 0x1C:
		nCode = BKEY_LEFT;
		break;

	case 0x1D:
		nCode = BKEY_RIGHT;
		break;

	case 0x1E:
		nCode = BKEY_UP;
		break;

	case 0x1F:
		nCode = BKEY_DOWN;
		break;

	case 0x0B:
		nCode = BKEY_PAGEUP;
		break;

	case 0x0C:
		nCode = BKEY_PAGEDOWN;
		break;

	case 0x01:
		nCode = BKEY_HOME;
		break;

	case 0x04:
		nCode = BKEY_END;
		break;

	case 0x1B:
		nCode = BKEY_ESC;
		break;

	case 0x03:
	case 0x0D:
		nCode = BKEY_ENTER;
		break;

	case 0x7F:
		nCode = BKEY_DEL;
		break;

	case 0x08:
		nCode = BKEY_BACK;
		break;

	case 0x10:
		nCode = BKEY_F1;
		break;

	// command z will give us pzzazzl vision.
	case BKEY_z:
	case BKEY_Z:
		if (nFlags & cmdKey) {
			nCode = BKEY_SCRL_LOCK;
			return nCode;
		}
		break;

	// command-s will save a game for us...
	case BKEY_o:
	case BKEY_O:
		if (nFlags & cmdKey) {
			nCode = BKEY_F4;
			return nCode;
		}
		break;

	// command-s will save a game for us...
	case BKEY_s:
	case BKEY_S:
		if (nFlags & cmdKey) {
			nCode = BKEY_F2;
			return nCode;
		}
		break;

	// command-r will restore a game for us...
	case BKEY_r:
	case BKEY_R:
		if (nFlags & cmdKey) {
			nCode = BKEY_F3;
			return nCode;
		}
		break;

	// no translation for this key
	//
	default:
		nCode = nChar & charCodeMask;
		break;
	}

	// Check for Command key down STDKEYS.H
	//
	if (nFlags & cmdKey) {
		nCode |= BKF_CMD;
	}

#endif

	// LogInfo(BuildString("TranslateKey(%04x, %d, %04x) = %08lx", nChar, nRepCount, nFlags, nCode));

	return nCode;
}

// jwl 12.18.96 provide a method to paint a full window that does not
// necessarily have a backdrop.
// scg 01.26.97 changed to call FillRect

VOID CBofWindow::FillWindow(UBYTE iColor) {
	FillRect(nullptr, iColor);
}

// scg 01.22.97 Fill part of a window.

VOID CBofWindow::FillRect(CBofRect *pRect, UBYTE iColor) {
	// Can we just fill the backdrop?
	//
	// if (GetBackdrop()) {
	//  GetBackdrop()->FillRect(pRect, iColor);

	// Otherwise, things get tough.
	//
	//} else {

#if BOF_MAC || BOF_WINMAC
	// On the mac, we'll just draw directly into the graphics port that
	// is being used by the window.
	WindowPtr pWindow = GetMacWindow();
	STBofPort stSavePort(pWindow);
	Pattern cPat;

	// jwl 1.23.97 make sure we don't get a white flash
	LMSetPaintWhite(FALSE);

	for (INT i = 0; i < 8; i++) {
		((CHAR *)&cPat)[i] = iColor;
	}

	Rect theRect;

	if (pRect == nullptr)
		theRect = pWindow->portRect;
	else
		theRect = pRect->GetMacRect();

	RgnHandle theRgn = ::NewRgn();
	WindowPtr pFWindow = ::FrontWindow();
	::ShowWindow(pWindow);

	::GetClip(theRgn);
	::ClipRect(&theRect);

	::FillRect(&theRect, &cPat);

	::SetClip(theRgn);
	::DisposeRgn(theRgn);

	if (pFWindow != nullptr)
		::ShowWindow(pFWindow);
#else
	// BCW - 12/19/96 08:04 pm
	// Slow, but should work fine
	//
	CBofBitmap cBmp(Width(), Height(), CBofApp::GetApp()->GetPalette());
	cBmp.FillRect(pRect, iColor);
	cBmp.Paint(this, 0, 0);
#endif
	//}
}

#if BOF_WINMAC
WindowPtr CBofWindow::GetMacWindow() {
	Assert(IsValidObject(this));

	WindowPtr pWindow;

	if ((pWindow = GetWrapperWindow(m_hWnd)) == nullptr) {
		pWindow = GetWrapperContainerWindow(m_hWnd);
	}
	return pWindow;
}
#endif

//	jwl 07.15.96 OS8 imcompatible.  Please don't shoot me for this hack...
//  until I find out the proper way to do this, this code will have to do.
//  The window manager call "ShowWindow" below will do a very valiant job
//  of showing the window, however, in our games, some of the windows are
//  bitmaps with not so rigid borders.  Unfortunatley, the window manager
//  starts the show window call by framing the window and this leaves a very
//  unsightly rectangle around the bitmap.  What I did below was to fool the
//  window manager into believing the screen is 1 pixel smaller than the
//  window thus preventing the frame from being drawn... sigh...

#if BOF_MAC

STBofScreen::STBofScreen(Rect *parentWindRect) {
	GDHandle screenGD;
	GWorldPtr curWorld;

	GetGWorld(&curWorld, &screenGD);
	Rect winRect = *parentWindRect;

	m_screenRect = (*(*screenGD)->gdPMap)->bounds;

	(*(*screenGD)->gdPMap)->bounds = winRect;
	(*screenGD)->gdRect = winRect;
}

STBofScreen::~STBofScreen() {
	GDHandle screenGD;
	GWorldPtr curWorld;

	GetGWorld(&curWorld, &screenGD);

	(*(*screenGD)->gdPMap)->bounds = m_screenRect;
	(*screenGD)->gdRect = m_screenRect;
}

// jwl 08.07.96 used to switch to the port that we really need to update
// and restore when we're done.
STBofPort::STBofPort(WindowPtr pMacWindow) {
	m_bNewPort = false;
	::GetPort(&m_pSavePort);

	BOOL bValid = TRUE;

	if (m_pSavePort != pMacWindow && pMacWindow != nullptr && bValid) {
		m_nCheckCookie = m_pSavePort->device;
		m_bNewPort = true;
		::SetPort(pMacWindow);
	}
}

STBofPort::~STBofPort() {
	BOOL bValid = TRUE;
	if (m_bNewPort) {

#if TRUE
		CBofWindow *pWnd = CBofWindow::FromMacWindow(m_pSavePort);
		if (pWnd == nullptr || pWnd->GetMacWindow() == nullptr) {
			bValid = FALSE;
		}
#else

		// jwl 12.13.96 check to make sure this is a valid window.
		if (m_pSavePort->portBits.rowBytes & 0x8000) {
			if (GetHandleSize((Handle)((CGrafPtr)m_pSavePort)->portPixMap) == 0) {
				bValid = FALSE;
			}
		} else {
			if (GetPtrSize((Ptr)m_pSavePort->portBits.baseAddr) == 0) {
				bValid = FALSE;
			}
		}
#endif

		// Don't bother with these debug messages as they are a fairly common
		// occurrence (it will get triggered whenever a mouse down/up causes
		// a window to go away, such as with popup menus).
#if DEVELOPMENT
#if DISPLAYINVGRAFPORT
		if (bValid == FALSE) {
			DebugStr("\pSTBofPort::~STBofPort is restoring an invalid grafport...");
		}
#endif
#endif

		if (m_nCheckCookie != m_pSavePort->device) {
#if DEVELOPMENT
			DebugStr("\pSTBofPort::~STBofPort ran into a weird situation...");
#endif
		} else {
			if (bValid == TRUE) {
				::SetPort(m_pSavePort);
			}
		}
	}
}

// jwl 08.23.96 need to have routines to have more than a single
// active object.

BOOL CBofWindow::IsInActiveList() {
	CBofWindow *pactive = m_pActiveWindow;

	while (pactive) {
		if (pactive == this) {
			return true;
		}
		pactive = pactive->m_pPrevActiveWindow;
	}

	return false;
}

VOID CBofWindow::SetActive() {

	if (m_pActiveWindow != this) {
		if (m_pActiveWindow == nullptr) {
			m_pActiveWindow = this;
		} else {
			if (!IsInActiveList()) {
				CBofWindow *pactive = m_pActiveWindow;
				m_pActiveWindow = this;
				m_pActiveWindow->m_pPrevActiveWindow = pactive;
			} else {
				// it's in the active list, but it's not at the front...
				// find it and bring it to the front.
				CBofWindow *prevActive = m_pActiveWindow;
				CBofWindow *pActive = m_pActiveWindow->m_pPrevActiveWindow;

				while (pActive) {
					if (pActive == this) {
						prevActive->m_pPrevActiveWindow = pActive->m_pPrevActiveWindow;
						pActive->m_pPrevActiveWindow = m_pActiveWindow;
						m_pActiveWindow = pActive;
						return;
					}
					prevActive = pActive;
					pActive = pActive->m_pPrevActiveWindow;
				}
			}
		}
	}
}

VOID CBofWindow::RemoveFromActiveList() {

	// Should ALWAYS be the first object in the list.

	CBofWindow *prevActive = m_pActiveWindow;
	CBofWindow *pActive = (m_pActiveWindow == nullptr ? nullptr : m_pActiveWindow->m_pPrevActiveWindow);

	if (m_pActiveWindow == this) {
		m_pActiveWindow = m_pActiveWindow->m_pPrevActiveWindow;
	} else {
		while (pActive) {
			if (pActive == this) {
				prevActive->m_pPrevActiveWindow = pActive->m_pPrevActiveWindow;
				break;
			} else {
				prevActive = pActive;
				pActive = pActive->m_pPrevActiveWindow;
			}
		}
	}
}

#endif

// Used to reset a font and set it back to it's starting value
// once the routine that instantiates it is done executing.
STBofFont::STBofFont(INT nFont) {
#if BOF_MAC
	GrafPtr curPort;

	::GetPort(&curPort);
	m_nSaveFont = curPort->txFont;

	::TextFont(nFont);
#else
#endif
}

STBofFont::~STBofFont() {
#if BOF_MAC
	::TextFont(m_nSaveFont);
#else
#endif
}

static const CBofRect viewPortRect(80, 10, 559, 369);

#if PALETTESHIFTFIX

VOID CBofWindow::AddToPaletteShiftList(ITEMTYPE inItemID, LONG inItemOfInterest, LONG inAssociatedItem) {
	PaletteShiftItem psi;

	psi.m_eItemID = inItemID;
	psi.m_nItemOfInterest = inItemOfInterest;
	psi.m_nAssociatedItem = inAssociatedItem;

	if (m_pPaletteShiftList == nullptr)
		m_pPaletteShiftList = new CBofList<PaletteShiftItem>;

	volatile WindowPtr wp = (WindowPtr)psi.m_nItemOfInterest;

	switch (psi.m_eItemID) {

#if 0
	case DISPOSEWINDOW:

		gAllowPaletteShifts = false;
		LMSetPaintWhite(FALSE);
		::DisposeWindow(wp);
		if (psi.m_nAssociatedItem != 0)
			::SetPort((WindowPtr) psi.m_nAssociatedItem);
		gAllowPaletteShifts = true;
		break;

	case DISPOSEPALETTE:

		gAllowPaletteShifts = false;
		::DisposePalette((PaletteHandle) psi.m_nItemOfInterest);
		gAllowPaletteShifts = true;
		break;
#endif

	default:
		m_pPaletteShiftList->AddToTail(psi);
		break;
	}
}

VOID CBofWindow::CheckPaletteShiftList() {
	// jwl 09.04.96 palette shift fix... take all the calls that cause palette shifts
	// and move them as close to the onscreen rendering code as possible, this will
	// minimize the shift... but not eliminate it.

	if (m_pPaletteShiftList != nullptr) {

		volatile INT numItems = m_pPaletteShiftList->GetCount();

		if (numItems > 0) {

			gBlankBeforePaletteShift = true;

			for (volatile INT i = 0; i < numItems; i++) {

				PaletteShiftItem psi = m_pPaletteShiftList->GetNodeItem(i);
				volatile WindowPtr wp = (WindowPtr)psi.m_nItemOfInterest;

				switch (psi.m_eItemID) {

				case SETPALETTE:

					::SetPalette((WindowPtr)psi.m_nAssociatedItem,
					             (PaletteHandle)psi.m_nItemOfInterest,
					             false);
					break;

				case SHOWWINDOW:

					LMSetPaintWhite(FALSE);
					::ShowWindow(wp);

					// jwl 09.24.96 bring to front instead of select window, this makes sure we
					// suffer no premature palette shifts.
					//::SelectWindow (wp);
					::BringToFront(wp);
					::SetPort(wp);
					break;

				case DISPOSEWINDOW:

					gAllowPaletteShifts = false;
					LMSetPaintWhite(FALSE);
					::DisposeWindow(wp);
					if (psi.m_nAssociatedItem != 0)
						::SetPort((WindowPtr)psi.m_nAssociatedItem);
					gAllowPaletteShifts = true;
					break;

				case DISPOSEPALETTE:

					gAllowPaletteShifts = false;
					::DisposePalette((PaletteHandle)psi.m_nItemOfInterest);
					gAllowPaletteShifts = true;
					break;

				case HIDEWINDOW:

					LMSetPaintWhite(FALSE);
					::HideWindow(wp);
					break;

				case MOVEWINDOW:

					short x = HiWord(psi.m_nAssociatedItem);
					short y = LoWord(psi.m_nAssociatedItem);

					::MoveWindow(wp, x, y, FALSE);
					break;

				case SIZEWINDOW:

					short sizeX = HiWord(psi.m_nAssociatedItem);
					short sizeY = LoWord(psi.m_nAssociatedItem);

					::SizeWindow(wp, sizeX, sizeY, FALSE);
					break;

				default:

					Debugger();
				}
			}

			// jwl 09.30.96 stop memory leaks!
			m_pPaletteShiftList->RemoveAll();

			gBlankBeforePaletteShift = false;
		}
	}
}

void PaintScreenBlack() {
	static GrafPtr screenPort = nullptr;
	static GrafPort portRec;

	if (screenPort == nullptr) {
		::OpenPort(&portRec);
		screenPort = &portRec;
	}

	Rect theRect = {0, 0, 480, 640};
	GrafPtr savePort;

	GetPort(&savePort);
	SetPort(screenPort);
	FillRect(&theRect, &qd.black);
	SetPort(savePort);
}

pascal void MySetEntries(short start, short count, CSpecArray aTable) {
	// color components within "tol" of each other are considered equal
	// when deciding whether or not the screen should be blanked before
	// a palette change.
	const long tol = 1000;

	// C++ guarantees that statics are filled with zeros which we want here
	static ColorSpec prevTable[256];

	for (short i = start; i <= start + count; ++i) {
		if (gBlankBeforePaletteShift) {
			long dr = aTable[i].rgb.red - prevTable[i].rgb.red;
			long dg = aTable[i].rgb.green - prevTable[i].rgb.green;
			long db = aTable[i].rgb.blue - prevTable[i].rgb.blue;

			if (dr < -tol || dr > tol || dg < -tol || dg > tol || db < -tol || db > tol) {
				PaintScreenBlack();
				gBlankBeforePaletteShift = false;
			}
		}
		prevTable[i].rgb.red = aTable[i].rgb.red;
		prevTable[i].rgb.green = aTable[i].rgb.green;
		prevTable[i].rgb.blue = aTable[i].rgb.blue;
	}

#if __POWERPC__
	CallUniversalProc(gOldSetEntries, uppSetEntriesProcInfo, start, count, aTable);
#else
	(*gOldSetEntries)(start, count, aTable);
#endif
}

void InstallPalettePatch() {
	if (!gPalettePatchesInstalled) {

		//      gOldActivatePalette = GetToolboxTrapAddress(_ActivatePalette);
		//      gNewActivatePalette = NewActivatePaletteProc(MyActivatePalette);
		//      SetToolboxTrapAddress(gNewActivatePalette, _ActivatePalette);

		gOldSetEntries = (SetEntriesUPP)GetToolboxTrapAddress(_SetEntries);
		gNewSetEntries = NewSetEntriesProc(MySetEntries);
#if __POWERPC__
		SetToolboxTrapAddress(gNewSetEntries, _SetEntries);
#else
		SetToolboxTrapAddress((ProcPtr)gNewSetEntries, _SetEntries);
#endif

		//      gActivePalette = GetPalette((WindowPtr) -1);
		//      gActivePaletteWindow = nullptr;
		gPalettePatchesInstalled = true;
	}
}

#endif

} // namespace Bagel
