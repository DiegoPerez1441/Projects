/*
Created by Diego Perez
June 7, 2019


Updates:
June 8, 2019
	-Now hides console on startup


*/

// Required for use of newer Windows APIs
#define _WIN32_WINNT 0x0500

#include <iostream>
#include <windows.h>


class InvertedCursor {
private:
	int m_screenW = GetSystemMetrics(SM_CXSCREEN);
	int m_screenH = GetSystemMetrics(SM_CYSCREEN);
public:
	int oldx, oldy;
	int newx, newy;
	int dx, dy;

	// x, y passed by reference
	void getCoords(int& x, int& y) {
		POINT cursorPos;
		GetCursorPos(&cursorPos);
		x = cursorPos.x;
		y = cursorPos.y;
	}

	// set cursor coordinates by finding difference
	void setCoords() { SetCursorPos(oldx - dx, oldy - dy); }

	void run() {
		getCoords(oldx, oldy);
		// determines how smoothly the program will run
		Sleep(5);
		getCoords(newx, newy);
		dx = newx - oldx;
		dy = newy - oldy;

		/* Failsafes so that the cursor doesn't get stuck on the screen's edges */
		if (newx == 0) { dx = -1; }
		if (newy == 0) { dy = -1; }

		if (newx >= m_screenW - 1) { dx = 1; }
		if (newy >= m_screenH - 1) { dy = 1; }

		setCoords();
	}

	void logValues() {
		std::cout << newx << ", " << newy <<
			" | " << dx << ", " << dy << std::endl;
	}
};


int main() {

	// Gets a window handle for the console
	HWND console_handle = GetConsoleWindow();
	// If the handle doesn't initialize properly, exit with return 1;
	if (!console_handle) { return 1; }
	// Hide Console on Startup
	ShowWindow(console_handle, SW_HIDE);

	InvertedCursor IC;

	
	while (true) {
		IC.run();
		// IC.logValues();
	}

	return 0;
}