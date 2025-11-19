
extern CView* g_pkView;
class CSuperVw;
//#define CC_SHOW_LOG if (AfxGetMainWnd() != NULL) ((CSuperVw*)((CFrameWnd*)AfxGetMainWnd())->GetActiveView())->OutputLog
#define CC_SHOW_LOG if (g_pkView != NULL) ((CSuperVw*)g_pkView)->OutputLog

bool GetMainDirectory(LPTSTR lpszPath, int iPathLen);