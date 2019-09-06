#include <stdlib.h>
#include <stdio.h>

#include <libdill.h>

#define VICTIM_IPV4 "www.google.com"
#define VICTIM_PORT 443

static coroutine void attacker(const struct ipaddr *remote_addr);

int main(void) {
    struct ipaddr remote_addr;
    if (ipaddr_remote(&remote_addr, VICTIM_IPV4, VICTIM_PORT, 0, now() + 7000) == -1) {
        perror("Failed to recognise the victim's IP");
        return EXIT_FAILURE;
    }

    go(attacker(&remote_addr));
    return EXIT_SUCCESS;
}

static coroutine void attacker(const struct ipaddr *remote_addr) {
    int socket_handle;

    try_connect_tcp:;
    if ((socket_handle = tcp_connect(remote_addr, now() + 7000)) == -1) {
        perror("Failed to connect a TCP stream");
        goto try_connect_tcp;
    }

    if (tls_attach_client(socket_handle, now() + 7000) == -1) {
        perror("Failed to attach a TLS client");
        goto try_connect_tcp;
    }

    

    if (tcp_close(socket_handle, now() + 7000) == -1) {
        perror("Failed to close a TCP stream");
    }
}