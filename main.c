#include <stdlib.h>

#include <libdill.h>

static coroutine void attacker();

int main(void) {
    go(attacker());
    return EXIT_SUCCESS;
}

static coroutine void attacker() {

}