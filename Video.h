#ifndef VIDEO_H
#define VIDEO_H

#include <string>

class Video {
public:
    // Constructor
    Video(int id, const std::string& name, int duration, int likes, int dislikes, const std::string& channel);
    Video();

    // Getters for video attributes
    int getVideoId() const;
    const std::string& getVideoName() const;
    int getVideoDuration() const;
    int getLikes() const;
    int getDislikes() const;
    const std::string& getChannelName() const;

    // Setters for video attributes
    void setVideoId(int id);
    void setVideoName(const std::string& name);
    void setVideoDuration(int duration);
    void setLikes(int likes);
    void setDislikes(int dislikes);
    void setChannelName(const std::string& channel);

public:
    int video_id;
    std::string video_name;
    int video_duration;
    int no_likes;
    int no_dislikes;
    std::string channel_name;
};

#endif // VIDEO_H
