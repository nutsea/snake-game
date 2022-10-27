#pragma once
#include <unistd.h>
#include <termios.h>

//this file was created for macOS, instead of library conio.h

#define STDIN_FILENO 0
#define NB_DISABLE 0
#define NB_ENABLE 1

int kbhit(){
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

void nonblock_enable(){
    struct termios ttystate;
    // Get the terminal state.
    tcgetattr(STDIN_FILENO, &ttystate);
    // Turn off canonical mode.
    ttystate.c_lflag &= ~ICANON;
    // Minimum of number input read.
    ttystate.c_cc[VMIN] = 1;
    // Set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

void nonblock_disable(){
    struct termios ttystate;
    // Get the terminal state.
    tcgetattr(STDIN_FILENO, &ttystate);
    // Turn on canonical mode.
    ttystate.c_lflag |= ICANON;
    // Set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

int getch(){
    // return fgetc(stdin); 
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}