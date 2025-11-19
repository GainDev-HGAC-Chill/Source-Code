
// Error Code
#define GM_ERR_SUCCESS			0x00000000	// success
#define GM_ERR_NOT_MEMBER		0x10000001	// Not member
#define GM_ERR_NOT_ONLINE		0x10000002	// not online state
#define GM_ERR_TOO_LONG_STRING	0x10000003	// String is too long
#define GM_ERR_NOT_IMPLEMENTED	0x10000004	// Not implemented
#define GM_ERR_SYSTEM_ERR		0x10000005


typedef enum
{
	EACCOUNT_STATE_NONE		= 0,
	EACCOUNT_STATE_NORMAL	= 1,
	EACCOUNT_STATE_BLOCK		= 901,
} EAccountState;

typedef enum
{
	EPASSWORD_SET_NONE		= 0,
	EPASSWORD_SET_CHANGE	= 1,
	EPASSWORD_SET_INIT		= 2,
} EPasswordSetType;

typedef enum
{
	EGMC_NONE = 0,
	EGMC_KICKUSER = 1,
} EGMCommandType;