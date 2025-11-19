// Page_Control.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GMTool.h"
#include "GMServer.h"
#include "Page_Control.h"

// 임시 맵
int g_iMapTotal = 19;
wchar_t *g_szMapName[19][2] =
{
	{L"브리즈", L"9018100"},
	{L"용사의 해안", L"9010100"},
	{L"용사의 계곡", L"9010200"},
	{L"바람평원", L"9010300"},
	{L"배신자의 고개", L"9010400"},
	{L"오델리아", L"9018200"},
	{L"침묵의 섬 나루터", L"9010501"},
	{L"침묵의 섬 버려진요새", L"9010502"},
	{L"침묵의 섬 비밀의 방(파렐)", L"9010503"},
	{L"사파이어 드래곤", L"9010600"},
	{L"악마의 숨결", L"9020100"},
	{L"이글거리는 늪지대", L"9020300"},
	{L"큰나무지대", L"9020400"},
	{L"신들의 안식처", L"9020500"},
	{L"버섯마을", L"9028100"},
	{L"배신자의고개 바리에이션1", L"9010401"},
	{L"배신자의고개 바리에이션2", L"9010402"},
	{L"배신자의고개 바리에이션3", L"9010405"},
	{L"배신자의고개 바리에이션4", L"9010406"},
};


// CPage_Control 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPage_Control, CPropertyPage)

CPage_Control::CPage_Control()
	: CPropertyPage(CPage_Control::IDD)
{

}

CPage_Control::~CPage_Control()
{
}

void CPage_Control::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_CONTROL_CHARLIST, m_kGridCharList);
	//DDX_Control(pDX, IDC_CONTROL_SELECTLIST, m_kGridSelectList);
	DDX_Control(pDX, IDC_PAGE_CONTROL_MAPMOVE_MAPNO, m_cbMapNo);
	//DDX_Control(pDX, IDC_CONTROL_LIST_CHAR1, m_listChar1);
}


BEGIN_MESSAGE_MAP(CPage_Control, CPropertyPage)
	ON_BN_CLICKED(IDC_PAGE_CONTROL_MAPMOVE_MOVE, &CPage_Control::OnBnClickedPageControlMapmoveMove)
	ON_CBN_SELCHANGE(IDC_PAGE_CONTROL_MAPMOVE_MAPNO, &CPage_Control::OnCbnSelchangePageControlMapmoveMapno)
END_MESSAGE_MAP()


#include <string>
// CPage_Control 메시지 처리기입니다.
BOOL CPage_Control::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	/*
	// Create Grid
	CGrid* pGrid = 0;
	CMFCGrid* pkGrid[2];
	pkGrid[0] = &m_kGridCharList;
	pkGrid[1] = &m_kGridSelectList;

	for (int iGrid=0 ; iGrid<2 ; iGrid++)
	{	
		pGrid = GetGrid(pkGrid[iGrid]->m_hWnd);
		if(pGrid) {
			pGrid->SetCols(3);
			pGrid->SetRows(10);
			pGrid->SetColumnType(1, MYVT_BOOL);
			pGrid->SetColumnType(2, MYVT_PTCHAR);
			pGrid->SetColWidth(0, 20);
			pGrid->SetColWidth(1, 20);

			// set const
			POINT pt;
			for(int i=2;i<pGrid->GetCols();i++) {
				for(int j=1;j<pGrid->GetRows();j++) {
					pt.x=i;
					pt.y=j;
					pGrid->SetCellConst(pt, true);
				}
			}
		}
	}
	*/

	// 임시 맵
	for (int i=0 ; i<g_iMapTotal ; i++)
	{
		m_cbMapNo.InsertString(i, g_szMapName[i][0]);
	}
	m_cbMapNo.SetCurSel(0);
	SetDlgItemText(IDC_PAGE_CONTROL_MAPMOVE_MAPID, g_szMapName[0][1]);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}
void CPage_Control::OnBnClickedPageControlMapmoveMove()
{
	wchar_t wString[32];
	GetDlgItemText(IDC_PAGE_CONTROL_MAPMOVE_MAPID, wString, 32);

#ifdef USE_OLD_GMSERVER
	g_pkGMServer->Send_NetReqMapMove(_wtol(wString), 0, 0, 0);
#endif
}

void CPage_Control::OnCbnSelchangePageControlMapmoveMapno()
{
	int iCur = m_cbMapNo.GetCurSel();
	if (iCur != -1)
	{
		SetDlgItemText(IDC_PAGE_CONTROL_MAPMOVE_MAPID, g_szMapName[iCur][1]);
	}
}
