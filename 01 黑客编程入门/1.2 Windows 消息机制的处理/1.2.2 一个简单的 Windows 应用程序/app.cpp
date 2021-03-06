#include <cwchar>
#include <Windows.h>

wchar_t const* ClassName{ L"Test Application" };

ATOM registerClass(HINSTANCE instance);
bool initInstance(HINSTANCE instance, int cmdShow);
LRESULT CALLBACK windowProcess(HWND window, unsigned message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR cmdLine, int cmdShow) {
  registerClass(instance);

  if (!initInstance(instance, SW_SHOWNORMAL)) {
    return false;
  }

  int ret;
  MSG message;
  while ((ret = GetMessageW(&message, nullptr, 0, 0)) != 0
    && ret != -1) {
    TranslateMessage(&message);
    DispatchMessageW(&message);
  }
  return static_cast<int>(message.wParam);
}

ATOM registerClass(HINSTANCE instance) {
  WNDCLASSEXW wc{};

  wc.cbSize = sizeof(wc);
  wc.lpfnWndProc = windowProcess;
  wc.hInstance = instance;
  wc.lpszClassName = ClassName;
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOWFRAME + 1);
  wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
  wc.hIcon = LoadIconW(nullptr, IDI_QUESTION);

  return RegisterClassExW(&wc);
}

bool initInstance(HINSTANCE instance, int cmdShow) {
  HWND window{ CreateWindowExW(WS_EX_CLIENTEDGE, ClassName,
    L"MyFirstWindow", WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    nullptr, nullptr, instance, nullptr) };
  
  if (window == nullptr) return false;

  ShowWindow(window, cmdShow);

  return true;
}

LRESULT CALLBACK windowProcess(HWND window, unsigned message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
  case WM_PAINT:
  {
    PAINTSTRUCT ps;
    HDC dc{ BeginPaint(window, &ps) };
    RECT rect;
    GetClientRect(window, &rect);
    wchar_t const* drawText{ L"Hello Windows Program." };
    DrawTextW(dc,
      drawText, static_cast<int>(std::wcslen(drawText)), &rect,
      DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    EndPaint(window, &ps);
    break;
  }
  case WM_CLOSE:
  {
    if (MessageBoxW(window, L"是否退出程序", L"MyFirstWin", MB_YESNO) == IDYES) {
      DestroyWindow(window);
      PostQuitMessage(0);
    }
    break;
  }
  }
  return DefWindowProcW(window, message, wParam, lParam);
}
