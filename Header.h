#pragma once
enum ConsoleColor;
void SetColor(ConsoleColor text, ConsoleColor background);
void moveCursor(int x, int y);
char** createField(int width, int height);
void showArray(char** array);
void showLogo();
void showMenu();
void render(char** field);
void windowSettings(int width, int height);
int keyboardListener();