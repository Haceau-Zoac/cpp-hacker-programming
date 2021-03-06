#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>

char* caption{};

void CALLBACK refresh(HWND, UINT, UINT_PTR, DWORD);

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Too few arguments.\n";
    return -1;
  }

  int interval{ std::stoi(argv[2]) };
  if (argv[1] == "" || interval == 0) return -1;

  caption = argv[1];
  SetTimer(nullptr, 1, interval * 1000, refresh);

  _getch();
  KillTimer(nullptr, 1);
}

void CALLBACK refresh(HWND, UINT, UINT_PTR, DWORD) {
    HWND window{ FindWindowA(nullptr, caption) };
    PostMessageA(window, WM_KEYDOWN, VK_F5, 1);
    Sleep(50);
    PostMessageA(window, WM_KEYUP, VK_F5, 1);
}