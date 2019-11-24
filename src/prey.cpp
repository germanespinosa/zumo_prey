#include "joystick.h"
#include <iostream>
#include <gcomm.h>
using namespace std;
using namespace gcomm;

struct data {
    int32_t axis[8];
};


int main(int argc, char *argv[]) {
    GUartStream serial(GUartStream::baudrate::b57600);
    GStreamConnector conn(serial);
    GComm<data,data> comm(conn);
    data new_data;
    string device("/dev/input/js0");
    Joystick j(device);
    bool h = true;
    while (h){
        for (int i = 0;i<j.axes.size();i++) {
            cout << j.axes[i] << "\t";
            new_data.axis[i] = j.axes[i];
        }
        cout << endl;
        comm.write_object(new_data);
/*        for (int i = 0;i<j.buttons.size();i++) {
            cout << j.buttons[i].state << "\t";
        }*/

        usleep(1000000);
    }
}