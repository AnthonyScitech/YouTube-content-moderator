#pragma once
#include<map>
#include "Person.h"
#include "VideoDatabase.h"  // Include the VideoDatabase header file

class Creator : public Person {
public:
    Creator(const std::string& channel_name, int regNo, VideoDatabase& videoDB);
     using MapType = std::map<int, Creator>;  // Define MapType alias
    // ...
static MapType& getUsers();
    int getRegNo() const;

    // Member functions
    void showChannelScore();
    void createVideo();
    void manageVideo();
    void exit();
    

private:
 static MapType creatorMap;
    int regNo;
    float like_dislike_ratio_total;  // Assuming this is a member variable needed for channel score calculation
};
