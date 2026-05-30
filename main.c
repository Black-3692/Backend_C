#include "./server/server.h"

int main() {
    if(server_init(3000, 5) != 0) {
        return 1;
    }

    server_start();
    return 0;
}
