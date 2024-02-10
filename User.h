#ifndef USER_H
#define USER_H

#include "Person.h"
#include "VideoDatabase.h"
#include "Channel.h"
#include <queue>
#include <list>
#include <deque>
#include <map>

class User : public Person {
public:
    User(const std::string& name, int regNo, VideoDatabase& videoDB);

    using MapType = std::map<int, User>;  // Define MapType alias
     static MapType& getUsers();

    // Getter for regNo
    int getRegNo() const;
     void setRegNo(int newRegNo); 
       
    


    void getVideo();
    void getVideoRecommendations();
    void trendingChannels();
    void exitProgram();

private:
    int regNo;
    static MapType userMap;
    std::queue<Video> videoQueue;
    std::list<Video> videoRecommendations;
    std::deque<Channel> trendingChannelsDeque;
};

#endif // USER_H
