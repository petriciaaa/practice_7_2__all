#include <iostream>
#include <math.h>
#include <windows.h>
#include <string>
#include <conio.h>

#include <stdlib.h>

void clearConsole() {

    system("cls");
}
void hideCursor(HANDLE hStdout) {

    CONSOLE_CURSOR_INFO cursor;

    GetConsoleCursorInfo(hStdout, &cursor);

    cursor.bVisible = FALSE;

    SetConsoleCursorInfo(hStdout, &cursor);

}

void drawCircle(HDC hDeviceContext,  const COORD CENTER, double radius, COLORREF color) {

    HBRUSH hBrush = CreateSolidBrush(color);
    SelectObject(hDeviceContext, hBrush);
    Ellipse(hDeviceContext, CENTER.X - radius, CENTER.Y - radius, CENTER.X + radius, CENTER.Y + radius);
    DeleteObject(hBrush);

}


int main()
{

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    hideCursor(hStdout);

    HWND hWindow = GetConsoleWindow();
    HDC hDeviceContext = GetDC(hWindow);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdout, &csbi);

    const int windowHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1, windowWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    const COLORREF COLOR_BLACK = RGB(0, 0, 0);
    const COLORREF  COLOR_WHITE = RGB(255, 255, 255);
    const int CIRCLES_COUNTER = 10;
    const COORD CENTER = { 700,300};
    const int RADIUS_SCALE = 25;

    for (int i = CIRCLES_COUNTER; i > 0; i--)
    {
        drawCircle(hDeviceContext, CENTER, RADIUS_SCALE * i, i % 2 == 0 ? COLOR_WHITE : COLOR_BLACK);

    }

    for (int i = CIRCLES_COUNTER; i >= 0; i--)
    {

        std::string text = (CIRCLES_COUNTER - i) % 2 == 0 && CIRCLES_COUNTER != i ? std::to_string(CIRCLES_COUNTER - i) : "";
        SetBkColor(hDeviceContext, COLOR_BLACK);
        SetTextColor(hDeviceContext, COLOR_WHITE);

        const char* ctext = text.c_str();
        if (!i)
        {
            TextOutA(hDeviceContext, CENTER.X -8 + (RADIUS_SCALE * i), CENTER.Y - 8, ctext, strlen(ctext));
            
        }
        else {
            // 8 px - one char width i height ( maybe thats an false, stack thx)
            const int charSize = 8;
            TextOutA(hDeviceContext, CENTER.X + charSize + (RADIUS_SCALE * i), CENTER.Y-8, ctext, strlen(ctext));
            TextOutA(hDeviceContext, CENTER.X - charSize*2 - (RADIUS_SCALE * i), CENTER.Y-8, ctext, strlen(ctext));
        }
        
        
     

    }

    ReleaseDC(hWindow, hDeviceContext);
    _getche();

    return 0;
}

