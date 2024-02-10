#include "Creator.h"
#include "Video.h"
#include "Channel.h"
#include <iostream>
#include <algorithm>
#include <map>


// Constructor implementation
Creator::Creator(const std::string& channel_name, int regNo, VideoDatabase& videoDB) : Person(channel_name), regNo(regNo) {
}
 Creator::MapType Creator::creatorMap;

// Define the static function to get the creator map
Creator::MapType& Creator::getUsers() {
    return creatorMap;
}

// Getter for registration number
int Creator::getRegNo() const {
    return regNo;
}

void Creator::showChannelScore() {
    VideoDatabase videoDB("fake_youtube_data_updated.txt");  // Assuming the filename is "fake_youtube_data_updated.txt"
    videoDB.readDatabase();  // Read the video data from the file

    float total_likes = 0.0f;
    float total_dislikes = 0.0f;

    for (const auto& video : videoDB.getVideos()) {
        total_likes += video.no_likes;
        total_dislikes += video.no_dislikes;
    }

    like_dislike_ratio_total = total_likes / (total_likes + total_dislikes);

    std::cout << "Channel Score: " << like_dislike_ratio_total << std::endl;
}

void Creator::createVideo() {
    VideoDatabase videoDB("fake_youtube_data_updated.txt");  // Assuming the filename is "fake_youtube_data_updated.txt"
    videoDB.readDatabase();  // Read the video data from the file

    Video newVideo;
    Channel channel;

    std::cout << "Enter the name of the video: ";
    std::cin.ignore();  // Ignore newline character from previous input
    std::getline(std::cin, newVideo.video_name);

    std::cout << "Enter the duration of the video (in seconds): ";
    std::cin >> newVideo.video_duration;

    newVideo.no_likes = 0;
    newVideo.no_dislikes = 0;

    newVideo.channel_name = channel.getChannelName();

    newVideo.video_id = videoDB.getVideos().size() + 1;

    videoDB.addVideo(newVideo);

    videoDB.writeDatabase();

    std::cout << "Video created successfully." << std::endl;
}

void Creator::manageVideo() {
    VideoDatabase videoDB("fake_youtube_data_updated.txt");  // Assuming the filename is "fake_youtube_data_updated.txt"
    videoDB.readDatabase();  // Read the video data from the file

    std::map<int, Video> videoMap;

    for (const auto& video : videoDB.getVideos()) {
        videoMap[video.video_id] = video;
    }

    std::cout << "List of Videos:" << std::endl;
    for (const auto& pair : videoMap) {
        const auto& video = pair.second;
        std::cout << "Video ID: " << video.video_id << ", Name: " << video.video_name
                  << ", Likes: " << video.no_likes << ", Dislikes: " << video.no_dislikes << std::endl;
    }

    int choice;
    std::cout << "Enter the Video ID you want to manage: ";
    std::cin >> choice;

    auto it = videoMap.find(choice);

    if (it != videoMap.end()) {
        Video& selectedVideo = it->second;

        std::cout << "1. Rename Video\n2. Reset Likes/Dislikes\n3. Delete Video\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the new name for the video: ";
                std::cin.ignore();  // Ignore newline character from previous input
                std::getline(std::cin, selectedVideo.video_name);
                break;

            case 2:
                selectedVideo.no_likes = 0;
                selectedVideo.no_dislikes = 0;
                std::cout << "Likes and dislikes reset for the video." << std::endl;
                break;

            case 3:
                videoDB.removeVideo(selectedVideo.video_id);
                std::cout << "Video deleted successfully." << std::endl;
                break;

            default:
                std::cout << "Invalid choice." << std::endl;
        }

        videoDB.writeDatabase();
    } else {
        std::cout << "Invalid Video ID." << std::endl;
    }
}

void Creator::exit() {
    std::cout << "Exiting creator mode..." << std::endl;
    // You may include any necessary cleanup or finalization steps here
    std::exit(0); // Exit the program with status 0

}