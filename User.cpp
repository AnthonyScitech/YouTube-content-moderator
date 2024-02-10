#include "User.h"
#include "Channel.h"
#include <iostream>
#include <algorithm>
#include <cstdlib> // for std::rand and std::srand
#include <ctime>   // for std::time


User::User(const std::string& name, int regNo, VideoDatabase& videoDB) : Person(name), regNo(regNo) {
    // Seed for random number generation
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}
User::MapType User::userMap;

User::MapType& User::getUsers() {
    return userMap;
}

// Getter for regNo
    int User:: getRegNo() const {
        return regNo;
    }

    // Setter for regNo
    void User:: setRegNo(int newRegNo) {
        regNo = newRegNo;
    }


void User::getVideo() {
    VideoDatabase videoDB("fake_youtube_data_updated.txt"); // Assuming the filename is "fake_youtube_data_updated.txt"
    videoDB.readDatabase(); // Read the video data from the file
    string keyword;
    cout << "Enter a keyword to get video recommendations: ";
    cin >> keyword;


    queue<Video> matchedVideos;

    for (const auto& video : videoDB.getVideos()) {
        if (video.video_name.find(keyword) != string::npos) {
            matchedVideos.push(video);
        }
    }

    if (matchedVideos.empty()) {
        cout << "No videos found with the given keyword." << endl;
        return;
    }

    cout << "Here are the top 20 videos based on your keyword:" << endl;
    for (size_t i = 0; i < 20 && !matchedVideos.empty(); ++i) {
        const auto& video = matchedVideos.front();
        matchedVideos.pop();
        cout << "Video ID: " << video.video_id << ", Name: " << video.video_name << ", Duration: " << video.video_duration
             << ", Likes: " << video.no_likes << ", Dislikes: " << video.no_dislikes << ", Channel: " << video.channel_name << endl;
    }

    string choice;
    cout << "Enter the ID of the video you want to watch or 'menu' to return to the main menu: ";
    cin >> choice;

    if (choice == "menu") {
        return;
    }

    Video selectedVideo;
    bool found = false;
    for (auto& video : videoDB.getVideos()) {
        if (video.video_id == stoi(choice)) {
            selectedVideo = video;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Invalid video ID." << endl;
        return;
    }

    int likes, dislikes;
    cout << "Do you like or dislike this video? (like/dislike): ";
    cin >> choice;

    if (choice == "like") {
        ++selectedVideo.no_likes;
    } else if (choice == "dislike") {
        ++selectedVideo.no_dislikes;
    } else {
        cout << "Invalid choice." << endl;
        return;
    }

    // Write the changes back to the file
    videoDB.writeDatabase();

    cout << "You have chosen " << choice << " this video." << endl;
}


void User::getVideoRecommendations() {
    VideoDatabase videoDB("fake_youtube_data_updated.txt"); // Assuming the filename is "fake_youtube_data_updated.txt"
    videoDB.readDatabase(); // Read the video data from the file

    string keyword;
    cout << "Enter a keyword to get video recommendations: ";
    cin >> keyword;

    vector<Video> videos;
    for (const auto& video : videoDB.getVideos()) {
        if (video.video_name.find(keyword) != string::npos) {
            videos.push_back(video);
        }
    }

    sort(videos.begin(), videos.end(), [](const Video& a, const Video& b) {
        return (double)a.no_likes / (a.no_likes + a.no_dislikes) > (double)b.no_likes / (b.no_likes + b.no_dislikes);
    });

    cout << "Here are the top 10 video recommendations based on your keyword:" << endl;
    for (size_t i = 0; i < 10 && i < videos.size(); ++i) {
        const auto& video = videos[i];
        cout << "Video ID: " << video.video_id << ", Name: " << video.video_name << ", Duration: " << video.video_duration
             << ", Likes: " << video.no_likes << ", Dislikes: " << video.no_dislikes << ", Channel: " << video.channel_name << endl;
    }

    string choice;
    cout << "Enter the ID of the video you want to watch, 'menu' to return to the main menu, or 'exit' to exit: ";
    cin >> choice;

    if (choice == "menu") {
        return;
    } else if (choice == "exit") {
        // Handle exit
        // You may want to include a mechanism to exit the program here
        return;
    }

    Video selectedVideo;
    bool found = false;
    for (auto& video : videos) {
        if (video.video_id == stoi(choice)) {
            selectedVideo = video;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Invalid video ID." << endl;
        return;
    }

    int likes, dislikes;
    cout << "Do you like or dislike this video? (like/dislike): ";
    cin >> choice;

    if (choice == "like") {
        ++selectedVideo.no_likes;
    } else if (choice == "dislike") {
        ++selectedVideo.no_dislikes;
    } else {
        cout << "Invalid choice." << endl;
        return;
    }

    // Write the changes back to the file
    videoDB.writeDatabase();

    cout << "You have chosen " << choice << " for this video." << endl;
}
void User::trendingChannels() {
    VideoDatabase videoDB("fake_youtube_data_updated.txt");
    videoDB.readDatabase();

    std::deque<Channel> channels;

    for (const auto& video : videoDB.getVideos()) {
        auto it = std::find_if(channels.begin(), channels.end(), [&video](const Channel& channel) {
            return channel.getChannelName() == video.getChannelName();
        });

        if (it == channels.end()) {
            Channel newChannel(video.getChannelName(), static_cast<double>(video.getLikes()) / (video.getLikes() + video.getDislikes()));
            channels.push_back(newChannel);
        } else {
            it->setScore(it->getScore() + static_cast<double>(video.getLikes()) / (video.getLikes() + video.getDislikes()));
        }
    }

    std::sort(channels.begin(), channels.end(), [](const Channel& a, const Channel& b) {
        return a.getScore() > b.getScore();
    });

    std::cout << "Here are the top 10 trending channels:" << std::endl;
    for (size_t i = 0; i < 10 && i < channels.size(); ++i) {
        const auto& channel = channels[i];
        std::cout << "Channel Name: " << channel.getChannelName() << ", Score: " << channel.getScore() << std::endl;
    }

    std::string choice;
    std::cout << "Enter the name of the channel you want to explore, 'menu' to return to the main menu, or 'exit' to exit: ";
    std::cin >> choice;

    if (choice == "menu") {
        return;
    } else if (choice == "exit") {
        exitProgram();
    }

    auto selectedChannel = std::find_if(channels.begin(), channels.end(), [&choice](const Channel& channel) {
        return channel.getChannelName() == choice;
    });

    if (selectedChannel == channels.end()) {
        std::cout << "Invalid channel name." << std::endl;
        return;
    }

    std::cout << "Videos of the channel " << selectedChannel->getChannelName() << ":" << std::endl;
    for (const auto& video : videoDB.getVideos()) {
        if (video.getChannelName() == selectedChannel->getChannelName()) {
            std::cout << "Video ID: " << video.getVideoId() << ", Name: " << video.getVideoName() << ", Duration: " << video.getVideoDuration()
                 << ", Likes: " << video.getLikes() << ", Dislikes: " << video.getDislikes() << std::endl;
        }
    }

    std::cout << "Enter the ID of the video you want to watch or 'menu' to return to the main menu: ";
    std::cin >> choice;

    if (choice == "menu") {
        return;
    }

    Video selectedVideo;
    bool found = false;
    for (const auto& video : videoDB.getVideos()) {
        if (video.getVideoId() == std::stoi(choice)) {
            selectedVideo = video;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Invalid video ID." << std::endl;
        return;
    }

    int likes, dislikes;
    std::cout << "Do you like or dislike this video? (like/dislike): ";
    std::cin >> choice;

    if (choice == "like") {
        selectedVideo.setLikes(selectedVideo.getLikes() + 1);
    } else if (choice == "dislike") {
        selectedVideo.setDislikes(selectedVideo.getDislikes() + 1);
    } else {
        std::cout << "Invalid choice." << std::endl;
        return;
    }

    videoDB.writeDatabase();

    std::cout << "You have chosen " << choice << " for this video." << std::endl;
}

void User::exitProgram() {
    std::cout << "Exiting the program. Goodbye!" << std::endl;
    std::exit(0);
}
