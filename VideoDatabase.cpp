// VideoDatabase.cpp
#include "VideoDatabase.h"
#include "Video.h"
#include <fstream>
#include <stdexcept>
#include "../../../../MinGW/lib/gcc/mingw32/6.3.0/include/c++/bits/algorithmfwd.h"

VideoDatabase::VideoDatabase(const std::string& filename) : filename(filename) {
    // Constructor
}

void VideoDatabase::readDatabase() {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Error opening video database file.");
    }

    // Assuming the file format is: video_id,video_name,video_duration,no_likes,no_dislikes,channel_name
    while (file.peek() != EOF) {
        Video video;
        int videoId, duration, likes, dislikes;
        file >> videoId;
        file.ignore(); // Ignore comma
        std::getline(file, video.video_name, ',');
        file >> duration >> likes >> dislikes;
        file.ignore(); // Ignore comma
        std::getline(file, video.channel_name);

        video.setVideoId(videoId);
        video.setVideoDuration(duration);
        video.setLikes(likes);
        video.setDislikes(dislikes);

        videos.push_back(video);
    }

    file.close();
    // Optionally, you can store 'videos' in a suitable data structure for further use.
    // You may also perform additional processing based on your requirements.
}

void VideoDatabase::writeDatabase() {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Error opening video database file for writing.");
    }

    for (const auto& video : videos) {
        file << video.getVideoId() << ',' << video.getVideoName() << ',' << video.getVideoDuration()
             << ',' << video.getLikes() << ',' << video.getDislikes() << ',' << video.getChannelName() << '\n';
    }

    file.close();
}
const std::vector<Video>& VideoDatabase::getVideos() const {
    return videos;
}

void VideoDatabase::addVideo(const Video& video) {
    videos.push_back(video);
}

void VideoDatabase::removeVideo(int videoId) {
    auto it = std::remove_if(videos.begin(), videos.end(), [videoId](const Video& video) {
        return video.getVideoId() == videoId;
    });

    if (it != videos.end()) {
        videos.erase(it, videos.end());
    }
}