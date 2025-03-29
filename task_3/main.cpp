#include "api.h"
#include <iostream>

int main() {
    ApiClient api;

    std::cout << "Fetching users on page 2...\n";
    auto futureUsers = api.getUsers(2);
    auto users = futureUsers.get();
    for (const auto& user : users) {
        std::cout << user.dump(4) << std::endl;
    }

    std::cout << "\nFetching user with ID 2...\n";
    auto futureUser = api.getUser(2);
    auto user = futureUser.get();
    std::cout << user.dump(4) << std::endl;

    return 0;
}
