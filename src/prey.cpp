#include "joystick.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    string device("/dev/input/js0");
    Joystick j(device);
    bool h = true;
    while (h){
        for (int i = 0;i<j.axes.size();i++) {
            cout << j.axes[i] << "\t";
        }
        for (int i = 0;i<j.buttons.size();i++) {
            cout << j.buttons[i].state << "\t";
        }
        cout << endl;
    }
}