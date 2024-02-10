// Video.cpp
#include "Video.h"

// Constructor
Video::Video(int id, const std::string& name, int duration, int likes, int dislikes, const std::string& channel)
    : video_id(id), video_name(name), video_duration(duration), no_likes(likes), no_dislikes(dislikes), channel_name(channel) {}

// Getter for video_id
int Video::getVideoId() const {
    return video_id;
}

// Getter for video_name
const std::string& Video::getVideoName() const {
    return video_name;
}

// Getter for video_duration
int Video::getVideoDuration() const {
    return video_duration;
}

// Getter for no_likes
int Video::getLikes() const {
    return no_likes;
}

// Getter for no_dislikes
int Video::getDislikes() const {
    return no_dislikes;
}

// Getter for channel_name
const std::string& Video::getChannelName() const {
    return channel_name;
}
// Setters for video attributes
void Video::setVideoId(int id) {
    video_id = id;
}

void Video::setVideoName(const std::string& name) {
    video_name = name;
}

void Video::setVideoDuration(int duration) {
    video_duration = duration;
}

void Video::setLikes(int likes) {
    no_likes = likes;
}

void Video::setDislikes(int dislikes) {
    no_dislikes = dislikes;
}

void Video::setChannelName(const std::string& channel) {
    channel_name = channel;
}
