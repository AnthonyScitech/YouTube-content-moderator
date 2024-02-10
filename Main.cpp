#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <map>
#include "User.h"
#include "Creator.h"
#include "Person.h"
#include "VideoDatabase.h"

template <typename T>
T login(VideoDatabase& videoDB, const std::string& name) {
    int regNo;
    std::cout << "Enter your registration number: ";
    std::cin >> regNo;

    // Retrieve the users/creators map
    typename T::MapType& users = T::getUsers();

    // Check if the user with the given registration number already exists
    auto it = users.find(regNo);
    if (it != users.end()) {
        std::cout << "Welcome back, " << it->second.getName() << "!" << std::endl;
        return it->second;
    }

    // If not, create a new user/creator and add it to the map
    T newUser(name, regNo, videoDB);
    users[regNo] = newUser;

    std::cout << "Welcome, " << newUser.getName() << "!" << std::endl;
    return newUser;
}

void userOptions(User& user) {
    int choice;
    while (true) {
        std::cout << "\nUser Options:\n";
        std::cout << "1) Get video\n";
        std::cout << "2) Get video recommendations\n";
        std::cout << "3) Trending channels\n";
        std::cout << "4) Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                user.getVideo();
                // Additional logic for likes/dislikes storage
                break;
            case 2:
                user.getVideoRecommendations();
                // Additional logic for likes/dislikes storage
                break;
            case 3:
                user.trendingChannels();
                break;
            case 4:
                user.exitProgram();
                std::exit(0);
            default:
                std::cout << "Invalid choice, try again.\n";
        }
    }
}

void creatorOptions(Creator& creator) {
    int choice;
    while (true) {
        std::cout << "\nCreator Options:\n";
        std::cout << "1) Show channel score\n";
        std::cout << "2) Create a video\n";
        std::cout << "3) Manage a video\n";
        std::cout << "4) Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                creator.showChannelScore();
                break;
            case 2:
                creator.createVideo();
                break;
            case 3:
                creator.manageVideo();
                break;
            case 4:
                creator.exit();
                std::exit(0);
            default:
                std::cout << "Invalid choice, try again.\n";
        }
    }
}

int main() {
    std::string fileName = "users.txt";  // Replace with your actual file name
    VideoDatabase videoDB("fake_youtube_data_updated.txt");
    videoDB.readDatabase();

    while (true) {
        std::cout << "Enter 1 to login as user or 2 to login as creator: ";
        int userType;
        std::cin >> userType;

        if (userType == 1) {
            User user = login<User>(videoDB, fileName);
            userOptions(user);
        } else if (userType == 2) {
            Creator creator = login<Creator>(videoDB, fileName);
            creatorOptions(creator);
        } else {
            std::cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}
