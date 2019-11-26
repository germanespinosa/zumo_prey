#include "joystick.h"
#include <iostream>
#include <gcomm.h>
using namespace std;
using namespace gcomm;

struct data {
    int32_t axis[2];
};


int main(int argc, char *argv[]) {
    GUartBuffers serial(GUart::Baudrate::b57600);
    GBufferConnector conn(serial.rx_buffer, serial.tx_buffer);
    GComm<data,data> comm(conn);
    data new_data;
    string device("/dev/input/js0");
    Joystick j(device);
    bool h = true;
    while (h){
        cout << j.axes[1] << "\t" << j.axes[3] << endl;
        new_data.axis[0] = j.axes[1];
        new_data.axis[1] = j.axes[2];
        comm.write_object(new_data);
/*        for (int i = 0;i<j.buttons.size();i++) {
            cout << j.buttons[i].state << "\t";
        }*/

        usleep(50000);
    }
}