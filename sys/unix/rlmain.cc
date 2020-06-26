
#include <cstring>
#include <iostream>
#include <termios.h>

extern "C" {
#include "hack.h"
}

extern "C" {
#include "dlb.h"
}

extern "C" {
#include "nle.h"
}

void
play(nle_ctx_t *nle)
{
    char i;
    while (!nle->done) {
        read(STDIN_FILENO, &i, 1);
        nle = nle_step(nle, i);
    }
}

int
main(int argc, char **argv)
{
    struct termios old, tty;
    tcgetattr((int) STDIN_FILENO, &old);
    tty = old;
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);

    nle_ctx_t *nle = nle_start();
    play(nle);
    nle_reset(nle);
    play(nle);
    nle_end(nle);

    tcsetattr(STDIN_FILENO, TCSANOW, &old);
}
