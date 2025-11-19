// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GSMBRIDGE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GSMBRIDGE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef GSMBRIDGE_EXPORTS
#define GSMBRIDGE_API __declspec(dllexport)
#else
#define GSMBRIDGE_API __declspec(dllimport)
#endif

// This class is exported from the GSMBridge.dll

#ifdef __cplusplus
extern "C" {
#endif

struct  GSMBRIDGE_API PortalFlag {
	//PortalFlag() {roleFlag = 0; warnFlag =0; coinBlockFlag =0; gameBlockFlag =0;};
	int roleFlag;
	int warnFlag;
	int coinBlockFlag;
	int gameBlockFlag;
	int	authBlockFlag;
};

struct  GSMBRIDGE_API GameFlag {
	//GameFlag() {roleFlag = 0; warnFlag =0; innerBlockFlag =0; outerBlockFlag =0;};
	int roleFlag;
	int warnFlag;
	int innerBlockFlag;
	int outerBlockFlag;
};


GSMBRIDGE_API bool BridgeDLLStartup(wchar_t *callerDirPath,int callerDirPathLength );
GSMBRIDGE_API void BridgeDLLTerminate(void);
GSMBRIDGE_API int  LoginWithWebSID(unsigned char* webSID,__int64 macAddr ,unsigned char* gusID, wchar_t* account, 
								   int* userID, PortalFlag * pPortalFlag, GameFlag *pGameFlag, int *birthDay);

GSMBRIDGE_API int  LoginWithWebSID2(unsigned char* webSID,unsigned long userIP,unsigned char* gusID, wchar_t* account, 
								   int* userID, PortalFlag * pPortalFlag, GameFlag *pGameFlag, int *birthDay);

GSMBRIDGE_API int  LoginWithIDPWD(wchar_t *account,wchar_t* pwd ,__int64 macAddr, unsigned long userIP,unsigned char* gusID, int* userID,
								   PortalFlag * pPortalFlag, GameFlag *pGameFlag, int *birthDay);
GSMBRIDGE_API int GetUserInfo(unsigned char* gusID, wchar_t* nickName, BYTE *gender, BYTE* city, int *userGrade);
GSMBRIDGE_API int GetUserOneInfo(unsigned char* gusID,BYTE infoType, short bufferSize, BYTE *dataType,char*  oneData,int * dataLength);
GSMBRIDGE_API int LogOut(unsigned char* gusID);
GSMBRIDGE_API int GetRemainCoin(unsigned char* gusID, int *paidCoin,int * freeCoin,int *gameFreeCoin, int *mileage);
GSMBRIDGE_API int OnRecv(unsigned char*  packet, int packetLength, int * castType,void * resultData,int * resultDataSize);
GSMBRIDGE_API int CheckPCCafeIP(unsigned char *gusID, unsigned long userIP, int *pccafeCode , int *pccafeGrade);
GSMBRIDGE_API int GetWebSessionID(unsigned char* gusID, unsigned char* webSessionID,  __int64 *macAddr);

GSMBRIDGE_API bool GetErrorMsg(int errCode, int errMsgSize, wchar_t* errMessage, int &errMsgLength);

GSMBRIDGE_API bool GetPortalBlockMsg(int blockCode, int errMsgSize, wchar_t* errMessage, int &errMsgLength);
GSMBRIDGE_API bool GetGameBlockMsg(int innerblockCode, int outerblockCode, int errMsgSize, wchar_t* errMessage, int &errMsgLength);

#ifdef __cplusplus
}
#endif
