#include "./server/server.h"
#include "./routes/routes.h"
#include "./request/request.h"
#include "./response/response.h"

void home(Request *req, Response *res) {
    res_send(res, "Hello World ...");
}

void user(Request *req, Response *res) {
    res_send(res, "<h1>Users Page</h1>");
}

int main() {
    if(server_init(3000, 5) != 0) {
        return 1;
    }
    
    get("/", home);
    get("/user", user);

    server_start();
    return 0;
}
