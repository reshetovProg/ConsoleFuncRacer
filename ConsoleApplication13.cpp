#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"


using namespace std;
#define random(a,b) a+rand()%(b+1-a)
#define DEBUG

enum ConsoleColor
{
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};
void SetColor(ConsoleColor text, ConsoleColor background)
{
    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleHandle, text | background);
}
void moveCursor(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
char** createField(int width, int height) {
    char** field = new char* [height];
    for (int i = 0; i < height; i++) {
        field[i] = new char[width];
        for(int j=0; j<width; j++)
            field[i][j]= char(176);
    }
    return field;
}
void showArray(char** array) {
    int size = _msize(array) / sizeof(array[0]);
    int size2 = _msize(array[0]) / sizeof(array[0][0]);
    for (int i = 0; i < size; i++) {
        moveCursor(10, 5+i);
        for (int j = 0; j < size2; j++) {
            cout << array[i][j]<<array[i][j];
        }
        cout << endl;
    }
}
void showLogo() {
    moveCursor(10, 2);
    cout << "$$  $$ $$$$$$  $$$$" << endl;
    moveCursor(10, 3);
    cout << "$$$ $$ $$     $$" << endl;
    moveCursor(10, 4);
    cout << "$$ $$$ $$$$    $$$$" << endl;
    moveCursor(10, 5);
    cout << "$$  $$ $$         $$" << endl;
    moveCursor(10, 6);
    cout << "$$  $$ $$      $$$$" << endl;
}
void showMenu() {
    int counter = 0;
    int keyCode = 0;
    while (true) {
        moveCursor(15, 10);
        if (counter == 0 ) SetColor(ConsoleColor::Yellow, ConsoleColor::Black);
        else SetColor(ConsoleColor::Green, ConsoleColor::Black);
        cout << "NEW GAME";

        moveCursor(17, 12);
        if (counter == 1 ) SetColor(ConsoleColor::Yellow, ConsoleColor::Black);
        else SetColor(ConsoleColor::Green, ConsoleColor::Black);       
        cout << "EXIT";

        keyCode = keyboardListener();
        switch (keyCode) {
        case 72:
        case 119:
            if (counter > 0) counter--;
            break;
        case 80:
        case 115:
            if (counter < 1) counter++;
            break;
        case 13:
            if (counter == 1) 
                exit(0);
            if (counter == 0)
                startGame();
            
        }
   
    }
   
}

void startGame() {
    system("cls");
    int keyCode = 0;
    char** field = createField(9, 12);
    while (true) {
        keyCode = keyboardListener();
        showArray(field);

        switch (keyCode) {
        case 27:
            render();
        }
    }
    
    
   
    
}

void render() {
    system("cls");
    showLogo();
    showMenu();
    //showArray(field);
}
void windowSettings(int width, int height) {
    system("color 02");
    
    HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD crd = { width, height };
    SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
    SetConsoleWindowInfo(out_handle, true, &src);
    SetConsoleScreenBufferSize(out_handle, crd);

    HWND hWnd;
    HMENU hm;
    if ((hWnd = GetConsoleWindow()) == NULL)
    {
        printf("No console window!?\n");
        return;
    }
    hm = GetSystemMenu(hWnd, FALSE);
    RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
    RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
    DrawMenuBar(hWnd);

    //позиционирование
    HWND window_header = GetConsoleWindow();
    MoveWindow(window_header, 700, 250, width*15, height*30, false);

}
int keyboardListener() {

#ifdef DEBUG
    moveCursor(14, 19);
    cout << "key code:";
#endif   
    if (_kbhit()) {
#ifdef DEBUG
        moveCursor(17, 20);
        cout << "      ";
        moveCursor(17, 20);
#endif
        int n = _getch();
#ifdef DEBUG
        cout << n;
#endif
        return n;
    }
}


int main()
{  
    srand(time(NULL));
    windowSettings(30,20);   
    render();
}