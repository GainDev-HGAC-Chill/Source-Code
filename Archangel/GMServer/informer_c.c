

/* this ALWAYS GENERATED file contains the RPC client stubs */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for informer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#include <string.h>

#include "informer_h.h"

#define TYPE_FORMAT_STRING_SIZE   11                                
#define PROC_FORMAT_STRING_SIZE   433                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _informer_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } informer_MIDL_TYPE_FORMAT_STRING;

typedef struct _informer_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } informer_MIDL_PROC_FORMAT_STRING;

typedef struct _informer_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } informer_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const informer_MIDL_TYPE_FORMAT_STRING informer__MIDL_TypeFormatString;
extern const informer_MIDL_PROC_FORMAT_STRING informer__MIDL_ProcFormatString;
extern const informer_MIDL_EXPR_FORMAT_STRING informer__MIDL_ExprFormatString;

#define GENERIC_BINDING_TABLE_SIZE   0            


/* Standard interface: informer, ver. 1.0,
   GUID={0xC11502DD,0x6086,0x4217,{0xB1,0xBA,0x02,0x25,0x36,0x27,0xD6,0x74}} */


static const RPC_PROTSEQ_ENDPOINT __RpcProtseqEndpoint[] = 
    {
    {(unsigned char *) "ncacn_ip_tcp", (unsigned char *) "12345"}
    };


static const RPC_CLIENT_INTERFACE informer___RpcClientInterface =
    {
    sizeof(RPC_CLIENT_INTERFACE),
    {{0xC11502DD,0x6086,0x4217,{0xB1,0xBA,0x02,0x25,0x36,0x27,0xD6,0x74}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    1,
    (RPC_PROTSEQ_ENDPOINT *)__RpcProtseqEndpoint,
    0,
    0,
    0x00000000
    };
RPC_IF_HANDLE informer_v1_0_c_ifspec = (RPC_IF_HANDLE)& informer___RpcClientInterface;

extern const MIDL_STUB_DESC informer_StubDesc;

static RPC_BINDING_HANDLE informer__MIDL_AutoBindHandle;


int KickPlayer( 
    /* [in] */ handle_t hBinding,
    /* [string][in] */ const wchar_t *szAccountID)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&informer_StubDesc,
                  (PFORMAT_STRING) &informer__MIDL_ProcFormatString.Format[0],
                  ( unsigned char * )&hBinding);
    return ( int  )_RetVal.Simple;
    
}


int ChangePassword( 
    /* [in] */ handle_t hBinding,
    /* [string][in] */ const wchar_t *szAccountID,
    /* [string][in] */ const wchar_t *szPassword)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&informer_StubDesc,
                  (PFORMAT_STRING) &informer__MIDL_ProcFormatString.Format[40],
                  ( unsigned char * )&hBinding);
    return ( int  )_RetVal.Simple;
    
}


int CreateAccount( 
    /* [in] */ handle_t hBinding,
    /* [string][in] */ const wchar_t *szAccountID,
    /* [string][in] */ const wchar_t *szPassword,
    /* [string][in] */ const wchar_t *szBirthday)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&informer_StubDesc,
                  (PFORMAT_STRING) &informer__MIDL_ProcFormatString.Format[86],
                  ( unsigned char * )&hBinding);
    return ( int  )_RetVal.Simple;
    
}


int FreezeAccount( 
    /* [in] */ handle_t hBinding,
    /* [string][in] */ const wchar_t *szAccountID,
    /* [in] */ int iNewState)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&informer_StubDesc,
                  (PFORMAT_STRING) &informer__MIDL_ProcFormatString.Format[138],
                  ( unsigned char * )&hBinding);
    return ( int  )_RetVal.Simple;
    
}


int AuxiliaryPassword( 
    /* [in] */ handle_t hBinding,
    /* [string][in] */ const wchar_t *szAccountID,
    /* [string][in] */ const wchar_t *szAuxiliaryPassword,
    /* [in] */ int iSetType)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&informer_StubDesc,
                  (PFORMAT_STRING) &informer__MIDL_ProcFormatString.Format[184],
                  ( unsigned char * )&hBinding);
    return ( int  )_RetVal.Simple;
    
}


int AddPoint( 
    /* [in] */ handle_t hBinding,
    /* [string][in] */ const wchar_t *szPayId,
    /* [string][in] */ const wchar_t *szAccountID,
    /* [in] */ const int iPoints)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&informer_StubDesc,
                  (PFORMAT_STRING) &informer__MIDL_ProcFormatString.Format[236],
                  ( unsigned char * )&hBinding);
    return ( int  )_RetVal.Simple;
    
}


int GiveItem( 
    /* [in] */ handle_t hBinding,
    /* [string][in] */ const wchar_t *szCharName,
    /* [in] */ int iItemID,
    /* [in] */ const int iCount)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&informer_StubDesc,
                  (PFORMAT_STRING) &informer__MIDL_ProcFormatString.Format[288],
                  ( unsigned char * )&hBinding);
    return ( int  )_RetVal.Simple;
    
}


int GetPoint( 
    /* [in] */ handle_t hBinding,
    /* [string][in] */ const wchar_t *szAccountID,
    /* [out] */ int *piReturnCode)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&informer_StubDesc,
                  (PFORMAT_STRING) &informer__MIDL_ProcFormatString.Format[340],
                  ( unsigned char * )&hBinding);
    return ( int  )_RetVal.Simple;
    
}


int ChangeBirthday( 
    /* [in] */ handle_t hBinding,
    /* [string][in] */ const wchar_t *szAccountID,
    /* [string][in] */ const wchar_t *szBirthday)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&informer_StubDesc,
                  (PFORMAT_STRING) &informer__MIDL_ProcFormatString.Format[386],
                  ( unsigned char * )&hBinding);
    return ( int  )_RetVal.Simple;
    
}


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const informer_MIDL_PROC_FORMAT_STRING informer__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure KickPlayer */

			0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 12 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 14 */	NdrFcShort( 0x0 ),	/* 0 */
/* 16 */	NdrFcShort( 0x8 ),	/* 8 */
/* 18 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 20 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */
/* 26 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter szAccountID */

/* 28 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 30 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 32 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Return value */

/* 34 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 36 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 38 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ChangePassword */

/* 40 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 42 */	NdrFcLong( 0x0 ),	/* 0 */
/* 46 */	NdrFcShort( 0x1 ),	/* 1 */
/* 48 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 50 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 52 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x8 ),	/* 8 */
/* 58 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 60 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */
/* 64 */	NdrFcShort( 0x0 ),	/* 0 */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter szAccountID */

/* 68 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 70 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 72 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Parameter szPassword */

/* 74 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 76 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 78 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Return value */

/* 80 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 82 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 84 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateAccount */

/* 86 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 88 */	NdrFcLong( 0x0 ),	/* 0 */
/* 92 */	NdrFcShort( 0x2 ),	/* 2 */
/* 94 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 96 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 98 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */
/* 102 */	NdrFcShort( 0x8 ),	/* 8 */
/* 104 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 106 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 108 */	NdrFcShort( 0x0 ),	/* 0 */
/* 110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 112 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter szAccountID */

/* 114 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 116 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 118 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Parameter szPassword */

/* 120 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 122 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 124 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Parameter szBirthday */

/* 126 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 128 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 130 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Return value */

/* 132 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 134 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 136 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FreezeAccount */

/* 138 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 140 */	NdrFcLong( 0x0 ),	/* 0 */
/* 144 */	NdrFcShort( 0x3 ),	/* 3 */
/* 146 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 148 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 150 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 152 */	NdrFcShort( 0x8 ),	/* 8 */
/* 154 */	NdrFcShort( 0x8 ),	/* 8 */
/* 156 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 158 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 160 */	NdrFcShort( 0x0 ),	/* 0 */
/* 162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter szAccountID */

/* 166 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 168 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 170 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Parameter iNewState */

/* 172 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 174 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 176 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 178 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 180 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 182 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AuxiliaryPassword */

/* 184 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 186 */	NdrFcLong( 0x0 ),	/* 0 */
/* 190 */	NdrFcShort( 0x4 ),	/* 4 */
/* 192 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 194 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 196 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 198 */	NdrFcShort( 0x8 ),	/* 8 */
/* 200 */	NdrFcShort( 0x8 ),	/* 8 */
/* 202 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 204 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 206 */	NdrFcShort( 0x0 ),	/* 0 */
/* 208 */	NdrFcShort( 0x0 ),	/* 0 */
/* 210 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter szAccountID */

/* 212 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 214 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 216 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Parameter szAuxiliaryPassword */

/* 218 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 220 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 222 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Parameter iSetType */

/* 224 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 226 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 228 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 230 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 232 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 234 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddPoint */

/* 236 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 238 */	NdrFcLong( 0x0 ),	/* 0 */
/* 242 */	NdrFcShort( 0x5 ),	/* 5 */
/* 244 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 246 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 248 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 250 */	NdrFcShort( 0x8 ),	/* 8 */
/* 252 */	NdrFcShort( 0x8 ),	/* 8 */
/* 254 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 256 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 258 */	NdrFcShort( 0x0 ),	/* 0 */
/* 260 */	NdrFcShort( 0x0 ),	/* 0 */
/* 262 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter szPayId */

/* 264 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 266 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 268 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Parameter szAccountID */

/* 270 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 272 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 274 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Parameter iPoints */

/* 276 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 278 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 280 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 282 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 284 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 286 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GiveItem */

/* 288 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 290 */	NdrFcLong( 0x0 ),	/* 0 */
/* 294 */	NdrFcShort( 0x6 ),	/* 6 */
/* 296 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 298 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 300 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 302 */	NdrFcShort( 0x10 ),	/* 16 */
/* 304 */	NdrFcShort( 0x8 ),	/* 8 */
/* 306 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 308 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 310 */	NdrFcShort( 0x0 ),	/* 0 */
/* 312 */	NdrFcShort( 0x0 ),	/* 0 */
/* 314 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter szCharName */

/* 316 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 318 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 320 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Parameter iItemID */

/* 322 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 324 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 326 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter iCount */

/* 328 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 330 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 332 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 334 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 336 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 338 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetPoint */

/* 340 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 342 */	NdrFcLong( 0x0 ),	/* 0 */
/* 346 */	NdrFcShort( 0x7 ),	/* 7 */
/* 348 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 350 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 352 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 354 */	NdrFcShort( 0x0 ),	/* 0 */
/* 356 */	NdrFcShort( 0x24 ),	/* 36 */
/* 358 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 360 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 366 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter szAccountID */

/* 368 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 370 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 372 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Parameter piReturnCode */

/* 374 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 376 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 378 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 380 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 382 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 384 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ChangeBirthday */

/* 386 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 388 */	NdrFcLong( 0x0 ),	/* 0 */
/* 392 */	NdrFcShort( 0x8 ),	/* 8 */
/* 394 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 396 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 398 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 400 */	NdrFcShort( 0x0 ),	/* 0 */
/* 402 */	NdrFcShort( 0x8 ),	/* 8 */
/* 404 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 406 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 408 */	NdrFcShort( 0x0 ),	/* 0 */
/* 410 */	NdrFcShort( 0x0 ),	/* 0 */
/* 412 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter szAccountID */

/* 414 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 416 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 418 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Parameter szBirthday */

/* 420 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 422 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 424 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Return value */

/* 426 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 428 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 430 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const informer_MIDL_TYPE_FORMAT_STRING informer__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  4 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  8 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const unsigned short informer_FormatStringOffsetTable[] =
    {
    0,
    40,
    86,
    138,
    184,
    236,
    288,
    340,
    386
    };


static const MIDL_STUB_DESC informer_StubDesc = 
    {
    (void *)& informer___RpcClientInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    &informer__MIDL_AutoBindHandle,
    0,
    0,
    0,
    0,
    informer__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x801026e, /* MIDL Version 8.1.622 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_) */

