#include <iostream>
#include <cstring>
#include <Windows.h>

void onClose();
void onExecute();
void onEditWindow();
void onGetWindow();

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "No Arguments.\n";
    return -1;
  }

  if (std::strcmp(argv[1], "close") == 0) {
    onClose();
  } else if (std::strcmp(argv[1], "run") == 0) {
    onExecute();
  } else if (std::strcmp(argv[1], "edit") == 0) {
    onEditWindow();
  } else if (std::strcmp(argv[1], "get") == 0) {
    onGetWindow();
  } else {
    std::cerr << "Unknown arguments.\n";
  }
}

void onClose() {
  HWND window{ FindWindowW(L"Notepad", nullptr) };
  if (window == nullptr) {
    std::cout << "Notepad not found.\n";
  } else {
    SendMessageW(window, WM_CLOSE, 0, 0);
  }
}

void onExecute() {
  WinExec("notepad.exe", SW_SHOW);
}

void onEditWindow() {
  HWND window{ FindWindowW(nullptr, L"无标题 - 记事本") };
  if (window == nullptr) {
    std::cout << "Notepad not found.\n";
  } else {
    wchar_t const* caption{ L"消息测试" };
    SendMessageW(window, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(caption));
  }
}

void onGetWindow() {
  HWND window{ FindWindowW(L"Notepad", nullptr) };
  if (window == nullptr) {
    std::cout << "Notepad not found.\n";
  } else {
    wchar_t caption[MAXBYTE]{ 0 };
    SendMessageW(window, WM_GETTEXT, static_cast<WPARAM>(MAXBYTE), reinterpret_cast<LPARAM>(caption));
    std::wcout << "Caption:" << caption;
  }
}