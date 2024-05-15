#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>




int main()
{

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(hStdout, &cursor);
    cursor.bVisible = FALSE;

    SetConsoleCursorInfo(hStdout, &cursor);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdout, &csbi);

    const int WindowHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1, WindowWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;


    HWND hWindow = GetConsoleWindow();
    HDC hDeviceContext = GetDC(hWindow);

    
    const COLORREF COLOR_FILL= RGB(122, 122, 89);
    const COLORREF COLOR_EDGE= RGB(200,200,200);

    const POINT initPoints[] = { { 450, 250}, {950, 500} };
    const POINT point1[] = { {950,250},{1100,100},{1100,350,},{950,500} };
    const POINT point2[] = { {450,250},{950,250},{1100,100,},{600,100} };
   
    const int size = sizeof(point1) / sizeof(point1[0]);

    HBRUSH hBrush = CreateSolidBrush(COLOR_FILL);

   

    SelectObject(hDeviceContext, hBrush);

    Rectangle(hDeviceContext, initPoints[0].x, initPoints[0].y, initPoints[1].x, initPoints[1].y);

    Polygon(hDeviceContext, point1,size);
    Polygon(hDeviceContext, point2,size);
    DeleteObject(hBrush);



    HPEN hPen = CreatePen(PS_DASH, 0.9, COLOR_EDGE);


    SelectObject(hDeviceContext, hPen);


    const POINT hiddenEdges[] = { { 600, 100}, {1100 ,350},{450 ,500} };
    const POINT centreEdges = { 600 ,350 };

    for (int  i = 0; i < sizeof(hiddenEdges)/sizeof(hiddenEdges[0]); i++)
    {
        MoveToEx(hDeviceContext, centreEdges.x, centreEdges.y, NULL);
        LineTo(hDeviceContext, hiddenEdges[i].x, hiddenEdges[i].y);
    }


    DeleteObject(hPen);


    ReleaseDC(hWindow, hDeviceContext);


    std::cin.get();
}
