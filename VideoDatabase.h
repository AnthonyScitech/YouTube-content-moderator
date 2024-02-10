#ifndef VIDEODATABASE_H
#define VIDEODATABASE_H

#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "Video.h"

class VideoDatabase {
public:
    VideoDatabase(const std::string& filename);
    void readDatabase();
    void writeDatabase();
    const std::vector<Video>& getVideos() const;

    // Add video to the database
    void addVideo(const Video& video);

    // Remove video from the database by video ID
    void removeVideo(int videoId);

private:
    std::string filename;
    std::vector<Video> videos;
};

#endif // VIDEODATABASE_H
