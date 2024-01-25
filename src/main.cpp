#include <Windows.h>
#include <cstdio>
#include <thread>
#include <iostream>

void sendBacktick(const wchar_t* backtickChar, const int Interval) {

	HGLOBAL hClipboardData = nullptr;
    if (OpenClipboard(NULL)) {

		size_t size = wcslen(backtickChar) * sizeof(wchar_t);
		hClipboardData = GlobalAlloc(GMEM_DDESHARE, size + sizeof(wchar_t));

		if (hClipboardData != NULL) {
			wchar_t* pClipboardData = static_cast<wchar_t*>(GlobalLock(hClipboardData));
			if (pClipboardData != NULL) {
				memcpy(pClipboardData, backtickChar, size);
				pClipboardData[size / sizeof(wchar_t)] = L'\0'; 
				std::cout << pClipboardData << "\n";
				GlobalUnlock(hClipboardData);

				// Set clipboard data
				SetClipboardData(CF_UNICODETEXT, hClipboardData);
			}

			CloseClipboard();
			
			keybd_event(VK_INSERT, 0, 0, 0);

			std::this_thread::sleep_for(std::chrono::milliseconds(Interval));


		}

		std::cout << "breakpoint\n";
        

    }

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// Hide the console window
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	while (true) {
		// Check if Shift and Escape keys are pressed
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000 && GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			const wchar_t* backtickChar = L"`";
			const int interval = 50;
			std::cout << "Sending backtick to clipboard and simulating paste...\n";
			sendBacktick(backtickChar, interval);
		}

		// Add any other background processing or conditions as needed

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return 0;
}