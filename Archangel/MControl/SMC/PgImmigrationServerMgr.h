#pragma once

typedef struct tagChangeStatusPack
{
	tagChangeStatusPack()
	{
		bChangeHandle = bTargetServer = false;
		bChangeServer = bTargetHandle = false;
		bChangeException = bTargetException = false;
	}

	void SetServer(bool const bTaretServer)
	{
		this->bChangeServer = true;
		this->bTargetServer = bTaretServer;
	}
	void SetHandle(bool const bTaretHandle)
	{
		this->bChangeHandle = true;
		this->bTargetHandle = bTaretHandle;
	}
	void SetException(bool const bTargetException)
	{
		this->bChangeException = true;
		this->bTargetException = bTargetException;
	}
	void SetAll(bool const bTaretServer, bool const bTaretHandle, bool const bTargetException)
	{
		SetServer(bTaretServer);
		SetHandle(bTaretHandle);
		SetException(bTargetException);
	}

	bool Empty() const
	{
		return (!bChangeServer && !bChangeHandle && !bChangeException);
	}

	bool Check(SSingleServerStatus& rkServer) const
	{
		bool bChanged = false;
		if( bChangeServer )
		{
			bChanged = (rkServer.bReadyToService != bTargetServer) || bChanged;
			rkServer.bReadyToService = bTargetServer;
		}
		if( bChangeHandle )
		{
//			bChanged = (rkServer.bProcessHandle != bTargetHandle) || bChanged;
//			rkServer.bProcessHandle = bTargetHandle;
		}
		if( bChangeException )
		{
			bChanged = (rkServer.bIsException != bTargetException) || bChanged;
			rkServer.bIsException = bTargetException;
		}

		if( rkServer.bReadyToService && !rkServer.bIsException )
		{
			rkServer.dwLastUpdateTime = timeGetTime();
		}
		return bChanged;
	}

	bool operator == (const SSingleServerStatus& rkServer) const
	{
		bool bCompareResult = true;
		if( bChangeServer )
		{
			bCompareResult &= rkServer.bReadyToService == bTargetServer;
		}
		if( bChangeHandle )
		{
//			bCompareResult &= rkServer.bProcessHandle == bTargetHandle;
		}
		if( bChangeException )
		{
			bCompareResult &= rkServer.bIsException == bTargetException;
		}
		return bCompareResult;
	}

private:
	bool bChangeServer;//이걸 변환 할거냐?
	bool bChangeHandle;
	bool bChangeException;

	bool bTargetServer;//변환할 목표값
	bool bTargetHandle;
	bool bTargetException;
} SChangeStatusPack;

typedef struct tagServerSortInfo
{
	int iServerType;
	int iSortScore;

	tagServerSortInfo(const int iType, const int iScore)
		: iServerType(iType), iSortScore(iScore)
	{}
} SServerSortInfo;









typedef enum eControlCommandType
{
	CCT_None	= 0,
	CCT_On		= 1,
	CCT_Off		= 2,
} EControlCommandType;

typedef struct tagServerControlCommand
{
	EControlCommandType eType;
	ContServerID::value_type kServerID;

	tagServerControlCommand()
	{
		Clear();
	}

	void Clear()
	{
		eType = CCT_None;
		kServerID.Clear();
	}
} SServerControlCommand;
typedef std::vector< SServerControlCommand > ContServerControlCommand;

class PgCommandStack
{
	typedef std::list< SERVER_IDENTITY > ContServerIDList;

public:
	PgCommandStack();
	~PgCommandStack();

	bool AddCommandOn(const ContServerID& rkCommandVec);
	bool AddCommandOff(const ContServerID& rkCommandVec);
	bool NextCommand(SServerControlCommand& rkNext);
	void StackWriteToPacket(CEL::CPacket& rkPacket) const;
	void DelOnCommand(SERVER_IDENTITY const &rkServerID);
	void ClearCommand();

protected:
	void FailPrevCommand(const ContServerID& rkFailVec);

	//
	//CLASS_DECLARATION_S_NO_SET(SServerControlCommand, PrevCommand);
	CLASS_DECLARATION_S_NO_SET(SServerControlCommand, CurCommand);
protected:
	ContServerIDList m_kServerOnStack;
	ContServerIDList m_kServerOffStack;

	Loki::Mutex m_kStackMutex;
};
