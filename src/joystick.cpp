#include "joystick.h"

using namespace std;

Joystick::Joystick(string device_path) {
    js = open(device_path.c_str(), O_RDONLY);
    _update_thread = std::thread(_update_, std::ref(*this));
}

void Joystick::_update_(Joystick &j) {

}