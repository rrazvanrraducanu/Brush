
// BrushView.cpp : implementation of the CBrushView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Brush.h"
#endif

#include "BrushDoc.h"
#include "BrushView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBrushView

IMPLEMENT_DYNCREATE(CBrushView, CView)

BEGIN_MESSAGE_MAP(CBrushView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBrushView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CBrushView construction/destruction

CBrushView::CBrushView() noexcept
{
	// TODO: add construction code here

}

CBrushView::~CBrushView()
{
}

BOOL CBrushView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBrushView drawing

void CBrushView::OnDraw(CDC* /*pDC*/)
{
	CBrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CBrushView printing


void CBrushView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBrushView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBrushView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBrushView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CBrushView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBrushView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBrushView diagnostics

#ifdef _DEBUG
void CBrushView::AssertValid() const
{
	CView::AssertValid();
}

void CBrushView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBrushDoc* CBrushView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBrushDoc)));
	return (CBrushDoc*)m_pDocument;
}
#endif //_DEBUG


// CBrushView message handlers


void CBrushView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
	dc.SelectObject(&pen);
	CBrush brush(HS_DIAGCROSS, RGB(0, 0, 255));
	dc.SelectObject(&brush);
	rect.InflateRect(-40, -40);
	dc.Rectangle(rect);
	CView::OnLButtonDown(nFlags, point);
}
