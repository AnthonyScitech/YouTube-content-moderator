#include "Channel.h"

// Default constructor
Channel::Channel() : score(0.0) {
    // Initialize with default values
}

// Parameterized constructor
Channel::Channel(const std::string& name, double score) : name(name), score(score) {
    // Initialize with provided values
}

// Getter for channel name
std::string Channel::getChannelName() const {
    return name;
}

// Getter for channel score
double Channel::getScore() const {
    return score;
}

// Setter for channel name
void Channel::setChannelName(const std::string& newName) {
    name = newName;
}

// Setter for channel score
void Channel::setScore(double newScore) {
    score = newScore;
}

// Add any additional member function definitions related to Channel if needed
