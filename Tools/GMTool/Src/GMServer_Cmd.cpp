#include "stdafx.h"
//#include "resource.h"
//#include "GeneralDlg.h"
//#include "GMServer.h"
//
////send
//void CGMServer::Send_NetReqMapMove(DWORD dwMapNo, float fX, float fY, float fZ)
//{
//	SCPacket_NetReqMapMove kInfo;
//	kInfo.dwMapNo = dwMapNo;
//	kInfo.fPosX = fX;
//	kInfo.fPosY = fY;
//	kInfo.fPosZ = fZ;
//	
//	Send(
//		sizeof(SCPacket_NetReqMapMove),
//		((char *)&kInfo)
//		);
//}
//void CGMServer::Send_Chat(wchar_t *pwString)
//{
//	SCPacket_Chat kInfo;
//	wcscpy_s(kInfo.wString, SCPacket_STRING_SIZE, pwString);
//
//	Send(
//		sizeof(kInfo),
//		((char *)&kInfo)
//		);
//}
//void CGMServer::Send_Notice(wchar_t *pwString)
//{
//	SCPacket_Notice kInfo;
//	wcscpy_s(kInfo.wString, SCPacket_STRING_SIZE, pwString);
//
//	Send(
//		sizeof(kInfo),
//		((char *)&kInfo)
//		);
//}
//void CGMServer::Send_NoticeWithColor(wchar_t *pwString, DWORD dwColor)
//{
//	SCPacket_NoticeColor kInfo;
//	wcscpy_s(kInfo.wString, SCPacket_STRING_SIZE, pwString);
//	kInfo.dwColor = dwColor;
//
//	Send(
//		sizeof(kInfo),
//		((char *)&kInfo)
//		);
//}
//void CGMServer::Send_ChangeClass(
//								 SCPacket_ChangeClass::ESCPacket_ChangeClass eClassType,
//								 DWORD dwLevel)
//{
//	SCPacket_ChangeClass kInfo;
//	kInfo.eClassType = eClassType;
//	kInfo.dwLevel = dwLevel;
//
//	Send(
//		sizeof(kInfo),
//		((char *)&kInfo)
//		);
//}
//
////recv
//void CGMServer::PacketProcess(char *pkData)
//{
//	GMTool_CSPacket *pkPacket = (GMTool_CSPacket *)pkData;
//
//	if (pkPacket->ePacketType == GMTool_CSPacket::CS_PT_NONE)
//	{
//	}
//	else if (pkPacket->ePacketType == GMTool_CSPacket::CS_PT_CHANNEL)
//	{
//#ifdef USE_IMPERFECT_EMBODIMENT
//		CSPacket_Channel *pkInfo = (CSPacket_Channel *)pkData;
//		CComboBox* pkCombo = ((CComboBox*)m_pkStateDlg->GetDlgItem(IDC_GENERAL_SELECT_SERVER));
//		if (pkCombo)
//		{
//			pkCombo->ResetContent();
//			pkCombo->InsertString(0, pkInfo->wString);
//			pkCombo->SetCurSel(0);
//		}
//#endif
//	}
//	else if (pkPacket->ePacketType == GMTool_CSPacket::CS_PT_IDPW)
//	{
//#ifdef USE_IMPERFECT_EMBODIMENT
//		CSPacket_IDPW *pkInfo = (CSPacket_IDPW*)pkData;
//		m_pkStateDlg->SetDlgItemText(IDC_GENERAL_ID, pkInfo->wID);
//#endif
//	}
//}
