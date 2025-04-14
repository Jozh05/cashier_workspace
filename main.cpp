#include "./headers/App.hpp"

App* App_ptr = nullptr;

void signalHandler(int signal) {
    if (signal == SIGINT) {
        if (App_ptr != nullptr) {
            std::cout << "Emergency termination of the program..." << std::endl;
            App_ptr->stop(-1);
        }
    }
}

int main() {
    std::signal(SIGINT, signalHandler);
    App app;
    App_ptr = &app;
    app.start();
    app.stop(0);
}