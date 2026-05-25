#include "./server/server.h"
#include "./handlers/handler.h"
#include "./routes/routes.h"

int main() {
    // create_server(8080, 5);
    init_routes(10, 10, 10, 10);
    get("/", home_page);

    create_server(8080, 5);
    return 0;
}
