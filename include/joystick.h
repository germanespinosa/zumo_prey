//
// Created by german on 11/21/19.
//

#ifndef PREY_PREY_H
#define PREY_PREY_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <string>
#include <thread>
#include <mutex>


struct Joystick{
    Joystick(std::string);

    struct js_event event;
    int js;
    std::thread _update_thread;

    static void _update_(Joystick &);
};


#endif //PREY_PREY_H
