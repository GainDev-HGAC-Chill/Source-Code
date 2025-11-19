#include "stdafx.h"
#include "NoticeDlg.h"

#define MAX_SYSTEM_TEXT		9
#define STRING_TABLE_NOTIC	60000


int g_iNoticCount;		//출력할 공지의 전체 수
//int g_iNoticDelyTime;		//공지와 다음 공지간 딜레이
int g_iTextDely;		//문단 딜레이
int g_iTextCount;		//보내진 문단수.

IMPLEMENT_DYNAMIC(CNoticeDlg, CDialog)

CNoticeDlg::CNoticeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNoticeDlg::IDD, pParent)
{

}

CNoticeDlg::~CNoticeDlg()
{
	KillTimer(99);
}

void CNoticeDlg::StartNoticeDlg()
{
	
	CWnd *pkWnd;
	CString kString;
	STRING_TABLE::iterator Itr;

	for(int i = 1; i <= MAX_SYSTEM_TEXT; i++)
	{
		Itr =  g_kXmlMgr.m_kStrTable.find(STRING_TABLE_NOTIC + i);
		kString = UNI(Itr->second.c_str());
		pkWnd = GetDlgItem(IDD_NOTIC_FRM + i);
		pkWnd->SetWindowText(kString);
	}

	m_bCheck = false;
	//공지 반복 카운터
	m_kCountEdit.SetLimitText(3);
	m_kCountEdit.SetWindowTextW(L"1"); 
	g_iNoticCount = 1;
	
	//공지간 딜레이
	m_kNoticDelyTimeEdit.SetLimitText(3);
	m_kNoticDelyTimeEdit.SetWindowTextW(L"1");


	//문단 시간차
	m_kTextDelyEdit.SetLimitText(3);
	m_kTextDelyEdit.SetWindowTextW(L"10");
	CString kDely;
	m_kTextDelyEdit.GetWindowTextW(kDely);
	int iTextDely= _wtoi(kDely);
	g_iTextDely = iTextDely;		//문단 딜레이(일단 값이 있어야 한번 출력된다

	g_iTextCount = 0;		//문단 수 카운터

	SetServerInfo();

	SetTimer(99, 1000, 0);

	theApp.m_pkLoginDlg->ShowWindow(SW_HIDE);
	theApp.m_pMainWnd = theApp.m_pkNoticDlg;
	theApp.m_pkNoticDlg->ShowWindow(SW_SHOW);
	theApp.m_pkNoticDlg->SetFocus();
}

void CNoticeDlg::SetServerInfo()
{
	//Realm Setting
	CONT_REALM kContRealm;
	g_kRealmMgr.GetRealmCont(kContRealm);

	m_kCombo_Server.Clear();
	m_kCombo_Server.InsertString(0, L"All Realm");

	CONT_REALM::iterator Itr = kContRealm.begin();
	while(Itr != kContRealm.end())
	{
		CONT_REALM::mapped_type kElement = Itr->second;
		CONT_REALM::key_type kKey = Itr->first;

		if(kKey > 0)
			m_kCombo_Server.InsertString(kKey, kElement.Name().c_str());
				
		++Itr;
	}

	m_kCombo_Server.SetCurSel(0);

	//Channel Setting
	m_kCombo_Channel.Clear();
	m_kCombo_Channel.InsertString(0, L"All Channel");
	m_kCombo_Channel.SetCurSel(0);
	m_kCombo_Channel.EnableWindow(false);
}

void CNoticeDlg::SetChannelInfo(unsigned short usRealmNo)
{
	PgRealm kRealm;
	CONT_CHANNEL kContChannel;

	g_kRealmMgr.GetRealm(usRealmNo, kRealm);
	if(usRealmNo ==  0)
	{
		m_kCombo_Channel.SetCurSel(0);
		g_kProcessInfoMgr.m_kMyInfo.ChannelNo(0);
		return ;
	}
	kRealm.GetChannelCont(kContChannel);
	CONT_CHANNEL::iterator Itr = kContChannel.begin();
	while(Itr != kContChannel.end())
	{
		CONT_CHANNEL::key_type kKey = Itr->first;
		CONT_CHANNEL::mapped_type kElement = Itr->second;
		m_kCombo_Channel.InsertString(kKey, kElement.ChannelName().c_str());
		++Itr;
	}
}

void CNoticeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPIT_COUNT_EDIT, m_kCountEdit);
	DDX_Control(pDX, IDC_REPIT_TIME_EDIT, m_kNoticDelyTimeEdit);
	DDX_Control(pDX, IDC_NOTIC_EDIT, m_kNoticEdit);
	DDX_Control(pDX, ID_SET_BTN, m_kSetBtn);
	DDX_Control(pDX, IDC_NOWTIME_LABEL, m_kNowTimeLabel);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_kStartTime);
	DDX_Control(pDX, IDC_TEXT_TIME_EDIT, m_kTextDelyEdit);
	DDX_Control(pDX, IDC_COMBO_NOTICE_SERVERNUM, m_kCombo_Server);
	DDX_Control(pDX, IDC_COMBO_NOTICE_CHANNELNUM, m_kCombo_Channel);
}


BEGIN_MESSAGE_MAP(CNoticeDlg, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_SET_BTN, &CNoticeDlg::OnBnClickedSetBtn)
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_NOTIC_CLOSE, &CNoticeDlg::OnBnClickedNoticClose)
	ON_CBN_SELCHANGE(IDC_COMBO_NOTICE_SERVERNUM, &CNoticeDlg::OnCbnSelchangeComboNoticeServernum)
	ON_CBN_SELCHANGE(IDC_COMBO_NOTICE_CHANNELNUM, &CNoticeDlg::OnCbnSelchangeComboNoticeChannelnum)
END_MESSAGE_MAP()


BOOL CNoticeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE; 
}

void CNoticeDlg::PostNcDestroy()
{
	delete this;
	CDialog::PostNcDestroy();
}

void CNoticeDlg::OnClose()
{
	theApp.m_pkLoginDlg->OnClose();
}

void CNoticeDlg::OnBnClickedSetBtn()
{
	CString kString;
	STRING_TABLE::iterator Itr;
	std::vector<std :: wstring> kNotic;

	if(m_bCheck)
	{
		Itr =  g_kXmlMgr.m_kStrTable.find(60006);
		kString = UNI(Itr->second.c_str());
		m_kSetBtn.SetWindowText(kString);
		m_bCheck = false;
		KillTimer(0);
		SetTimer(1, 0, 0);
	} else
	{
		Itr =  g_kXmlMgr.m_kStrTable.find(60008);
		kString = UNI(Itr->second.c_str());
		m_kSetBtn.SetWindowText(kString);
		m_bCheck = true;
		//데이터를 만들고 타이머를 돌려 패킷을 보낸다.
		if(MakeSendString())
		{
			SetTimer(0, 1000, 0);
		}
		else
		{
			//데이터 만드는데 실패했으면 경고 메시지를 띄어주고 버튼은 이전 상태로 돌린다.
			ShowMessageBox(m_hWnd, 10010, 10001);
			Itr =  g_kXmlMgr.m_kStrTable.find(60006);
			kString = UNI(Itr->second.c_str());
			m_kSetBtn.SetWindowText(kString);
			m_bCheck = false;
		}
	}	
}

bool CNoticeDlg::MakeSendString()
{
	CString kString;
	m_kNoticEdit.GetWindowTextW(kString);
	int iCount = m_kNoticEdit.GetWindowTextLengthW();
	if( (wcscmp(kString, L"") == 0) || (wcscmp(kString, L" ") == 0) )
	{
		return false;
	}
	std::wstring kText = kString;
	int iStart = 0, iEnd = 0;
	std::basic_string<wchar_t> kTemp;
	for(int i = 0; i < iCount; i++)
	{
		kTemp = kText.substr(i, 2);
		iEnd = i;
		if(wcscmp(kTemp.c_str(), L"\r\n") == 0)
		{
			kTemp = kText.substr(iStart, iEnd - iStart);
			m_kNoticText.push_back(kTemp);
			iStart = i+2;
			++i;
		}
	}
	//나머지 끝부분 추가
	kTemp = kText.substr(iStart, iEnd+1 - iStart);
	m_kNoticText.push_back(kTemp);

	m_kNoticEdit.Clear();
	kString = L"";
	m_kNoticEdit.SetWindowTextW(kString);

	return true;
}

void CNoticeDlg::StartSendNotic()
{
	std::wstring kSendText;
	//먼저 시작 시간 설정을 확인한다.
	CTime kTime;
	m_kStartTime.GetTime(kTime);
	
	DBTIMESTAMP kTempTime;
	kTime.GetAsDBTIMESTAMP(kTempTime);
	
	BM::DBTIMESTAMP_EX kStartTime, kNowTime;
	kStartTime = kTempTime;
	g_kProcessInfoMgr.GetServerTime(kNowTime);
	
	if( kStartTime <= kNowTime)
	{
		//반복 횟수 비교;
		CString kCount;
		m_kCountEdit.GetWindowTextW(kCount);
		int iNoticCount = _wtoi(kCount);

		if(g_iNoticCount > iNoticCount)
		{
			KillTimer(0);
			SetTimer(1, 1000, 0);
			return;
		}
		
		if(g_iTextCount == m_kNoticText.size())
		{
			g_iTextCount = 0;
			++g_iNoticCount;
		} 
		else
		{
			CString kDely;
			m_kTextDelyEdit.GetWindowTextW(kDely);
			int iTextDely= _wtoi(kDely);
			//문장 딜레이 타임 비교
			if(g_iTextDely == iTextDely)
			{

				//패킷 보내기.
				CEL::CPacket kPacket(PT_O_G_REQ_GMCOMMAND, EGMC_NOTICE);
				std::wstring wstrContents = m_kNoticText[g_iTextCount];
				kPacket.Push((short)m_kCombo_Server.GetCurSel());
				kPacket.Push((short)m_kCombo_Channel.GetCurSel());
				kPacket.Push(wstrContents);
				if(!g_kNetwork.SendToLoginServer(kPacket))
				{
					KillTimer(0);
					SetTimer(1, 1000, 0);
					return ;
				}
				//보냈으니 메모장에 보낸 문장을 시간과 함께 출력해준다.
				CString kTime, kMemoString;
				m_kNoticEdit.GetWindowTextW(kMemoString);	
				g_kProcessInfoMgr.GetServerTime(kNowTime);
				CString wstrTime;
				wstrTime.Format(L"%d-%02d-%02d %02d:%02d:%02d", kNowTime.year, kNowTime.month, kNowTime.day, 
						kNowTime.hour, kNowTime.minute,kNowTime.second);

				std::wstring kMemo = kMemoString;
				kMemo += kTime;
				kMemo += m_kNoticText[g_iTextCount];
				kMemo += L"\r\n";
				m_kNoticEdit.SetWindowTextW(kMemo.c_str());

				g_iTextDely = 0;		//문장 딜레이 초기화
				++g_iTextCount;
			}
			else
			{
				++g_iTextDely;	
			}
		}
	}
}

void CNoticeDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0)
	{
		StartSendNotic();
	}
	else if (nIDEvent == 1)
	{
		KillTimer(1);

		std::vector<std::wstring>::iterator Itr = m_kNoticText.begin();
		std::wstring kText;
		while(Itr != m_kNoticText.end())
		{
			kText += Itr->c_str();
			kText += L"\r\n";
			Itr++;			
		}
		CString kString = L"";
		m_kNoticEdit.SetWindowTextW(kText.c_str());

		g_iTextCount = 0;		//문단 수 카운터
		g_iNoticCount = 1;

		m_kTextDelyEdit.GetWindowTextW(kString);
		int iTextDely= _wtoi(kString);
		g_iTextDely = iTextDely;
		
		m_kNoticText.clear();

		//버튼 원상복귀
		STRING_TABLE::iterator Itr_str;
		Itr_str =  g_kXmlMgr.m_kStrTable.find(60006);
		kString = UNI(Itr_str->second.c_str());
		m_kSetBtn.SetWindowText(kString);
		m_bCheck = false;		
	}
	else if(nIDEvent == 99)
	{
		SetDateTime();
	}
}


void CNoticeDlg::SetDateTime()
{
	BM::DBTIMESTAMP_EX kNowTime;
	g_kProcessInfoMgr.GetServerTime(kNowTime);

	CString wstrTime;
	wstrTime.Format(L"%d-%02d-%02d %02d:%02d:%02d", kNowTime.year, kNowTime.month, kNowTime.day, 
		kNowTime.hour, kNowTime.minute,kNowTime.second);

	m_kNowTimeLabel.SetWindowTextW(wstrTime);
}


void CNoticeDlg::OnCbnSelchangeComboNoticeServernum()
{
	int iRealmNo = m_kCombo_Server.GetCurSel();

	if( iRealmNo > 0)
	{
		m_kCombo_Channel.EnableWindow(true);
	} else
	{
		m_kCombo_Channel.EnableWindow(false);
	}
	SetChannelInfo(iRealmNo);
}

void CNoticeDlg::OnBnClickedNoticClose()
{
	OnClose();
}


void CNoticeDlg::OnCbnSelchangeComboNoticeChannelnum()
{
}
