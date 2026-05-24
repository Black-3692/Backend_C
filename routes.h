#ifndef ROUTES_H
#define ROUTES_H

// Function pointer used for route handlers.
//
// A route handler is the function executed
// when a route matches the incoming request.
//
// Example:
//
// void home() {
//     printf("Home Page");
// }
//
// get("/", home);
//
// Here:
// home -> RouteHandler
typedef void (*RouteHandler)();

// Structure used to store route information.
// //
// // Each route contains:
// //
// // 1. HTTP Method
// //    Example: GET, POST
// //
// // 2. Route Path
// //    Example: /users
// //
// // 3. Handler Function
// //    Function executed when route matches
typedef struct {
    // Stores the Method
    char method[10];

    // Stores the route Path
    char path[100];

    // Store the route handler function
    RouteHandler handler;
} Route;

// Function used to register GET routes.
// //
// // path    -> Route path
// // handler -> Function executed for the route
// //
// // Example:
// //
// // get("/users", users_handler);
void get(char *path, RouteHandler handler);

// Function used to register POST routes.
// //
// // path    -> Route path
// // handler -> Function executed for the route
// //
// // Example:
// //
// // post("/users", create_user);
void post(char *path, RouteHandler handler);

// Function used to match incoming requests
// with registered routes.
//
// method -> HTTP method from request
// path   -> Route path from request
//
// If route matches:
// corresponding handler function is executed.
void handle_route(char *method, char *path);
#endif
