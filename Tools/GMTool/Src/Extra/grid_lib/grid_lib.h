#include "grid.h"

bool			InitGrid(HINSTANCE hInstance);
HWND			CreateGrid(DWORD dwStyle, int x, int y, int cx, int cy, HWND hWndParent, HINSTANCE hInstance);
CGrid*			GetGrid(HWND hWnd);