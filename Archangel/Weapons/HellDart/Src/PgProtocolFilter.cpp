#include "stdafx.h"
#include "PgProtocolFilter.h"

PgProtocolFilter::PgProtocolFilter()
{
}

PgProtocolFilter::~PgProtocolFilter()
{
}

HRESULT PgProtocolFilter::FilterProtocol(BM::Stream &kInPacket)const
{
	kInPacket.RdPos(0);//패킷 타입 안뺀척.

	HRESULT hFunctionRet = E_FAIL;
	WORD dwPacketType = 0;
	kInPacket.Pop(dwPacketType);
	if(Execute(dwPacketType, kInPacket, hFunctionRet))
	{
		return hFunctionRet;
	}
	else
	{//함수 등록이 안되었다. 끊을 수는 없다.
	}
	return S_OK;
}