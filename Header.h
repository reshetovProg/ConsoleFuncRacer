#pragma once
enum ConsoleColor;
void SetColor(ConsoleColor text, ConsoleColor background);
void moveCursor(int x, int y);
char** createField(int width, int height);
void showArray(char** array);
void showLogo();
void showMenu();
void render();
void windowSettings(int width, int height);
int keyboardListener();
void startGame();
void clearField(char** array);
void renderPlayer(char** field, int x);