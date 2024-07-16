#include "ConnectFour.hpp"
#include <memory>

int main() {
    std::unique_ptr<ConnectFour> cFour(new ConnectFour);
    cFour->run();
    cFour.reset();
    return 0;
}