#ifndef __EXCEPTION_HANDLER_H_
#define __EXCEPTION_HANDLER_H_

//#define EH_USE_NO_EXCEPTION
#define EH_USE_SET_EXCEPTION
#define EH_WORK_AROUND_SYMGETLINEFROMADDR_BUG

#include <EH.h>

#pragma warning(disable:4311)
#pragma warning(disable:4312)
#pragma comment(lib, "Rpcrt4.lib")
//#pragma warning(disable:4786)

#ifdef DM_USE_DEBUG_MEMORY
#include "DebugMemory.h"
#endif

class CSystemException
#ifdef USE_MFC
	: public CException
	#ifdef DM_USE_DEBUG_MEMORY
		, public CMemory::CNoTrackObject
	#endif
#elif defined(DM_USE_DEBUG_MEMORY)
	: public CMemory::CNoTrackObject
#endif
{
#ifdef USE_MFC
	DECLARE_DYNAMIC(CSystemException)
#endif

// Constructors
public:
	CSystemException(PEXCEPTION_POINTERS info):mExceptInfo(info) {}

// Attributes
//protected:
	PEXCEPTION_POINTERS mExceptInfo;

// Operations

// Implementation
public:
#ifdef USE_MFC
	virtual			~CSystemException() {}
	virtual BOOL GetErrorMessage(LPTSTR, UINT, PUINT pnHelpContext=NULL);
	virtual void WriteAdditionalInfo();
#else
	BOOL GetErrorMessage(LPTSTR, UINT, PUINT pnHelpContext=NULL);
	void WriteAdditionalInfo();
#endif
};

/*
#ifdef EH_USE_NO_EXCEPTION
	#define BEFORE			{
	#define _BEFORE			{
	#define AFTER			} if (0) {
	#define _AFTER			} if (0) {
	#define FIN				}
	#define _FIN			}
	#define AFTER_FIN		}	
	#define _AFTER_FIN		}
	#define CHECK_LOG
	#define ELOG			(1) ? 0 : _ELOG
	#define EASSERT(expr)
	#define ETHROW
	inline void _ELOG(LPCTSTR, ...) {}
#else // EH_USE_NO_EXCEPTION
	#define BEFORE			try {

#ifdef USE_MFC
	#define AFTER			} catch (CException* e) {																			\
								TCHAR szCause[255];																				\
								e->GetErrorMessage(szCause, sizeof(szCause));													\
								e->Delete();																					\
								ELOG(_T("%s,,,%s,%d,"), szCause, _T(__FILE__) _T("[") _T(__TIMESTAMP__) _T("]"), __LINE__);

#else // USE_MFC
	#define AFTER			} catch (CSystemException* e) {																		\
								TCHAR szCause[255];																				\
								e->GetErrorMessage(szCause, sizeof(szCause));													\
								delete e;																						\
								ELOG(_T("%s,,,%s,%d,"), szCause, _T(__FILE__) _T("[") _T(__TIMESTAMP__) _T("]"), __LINE__);

#endif // USE_MFC

	#define FIN				ETHROW; }
	#define AFTER_FIN		AFTER FIN
	#define CHECK_LOG		ELOG(_T("0,Check,%s,%d,"), _T(__FILE__) _T("[") _T(__TIMESTAMP__) _T("]"), __LINE__);
	#define _BEFORE			_se_translator_function tr_func_org = _set_se_translator(trans_func);								\
							try {

#ifdef USE_MFC
	#define _AFTER			} catch (CException* e) {																			\
								TCHAR szCause[255];																				\
								e->GetErrorMessage(szCause, sizeof(szCause));													\
								e->Delete();																					\
								ELOG(_T("%s,,,%s,%d,"), szCause, _T(__FILE__) _T("[") _T(__TIMESTAMP__) _T("]"), __LINE__);
#else // USE_MFC
	#define _AFTER			} catch (CSystemException* e) {																		\
								TCHAR szCause[255];																				\
								e->GetErrorMessage(szCause, sizeof(szCause));													\
								delete e;																						\
								ELOG(_T("%s,,,%s,%d,"), szCause, _T(__FILE__) _T("[") _T(__TIMESTAMP__) _T("]"), __LINE__);

#endif // USE_MFC

	#define _FIN 			} catch (...) {																						\
								ELOG(_T("0,Unhandled Exception,,,%s,%d,"), _T(__FILE__) _T("[") _T(__TIMESTAMP__) _T("]"), __LINE__); \
							}																									\
							_set_se_translator(tr_func_org);
	#define _AFTER_FIN		_AFTER _FIN

	#define EASSERT(expr)	if (!(expr)) ELOG(_T("0,Assertion Failed,,,%s,%d,"), _T(__FILE__) _T("[") _T(__TIMESTAMP__) _T("]"), __LINE__)
	#define ETHROW			throw new CSystemException(0)

	void 		ELOG(LPCTSTR, ...);
	void 		trans_func(unsigned int, PEXCEPTION_POINTERS);
#endif // EH_USE_NO_EXCEPTION
*/
#endif // __EXCEPTION_HANDLER_H_