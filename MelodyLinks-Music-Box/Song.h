#ifndef SONG_H
#define SONG_H
#include <string>

/*
    Author: Ky Lam
    Date: October 29, 2023
    Description: The `Song` class represents a musical composition with attributes 
    such as its title and duration. It provides methods to access and compare song attributes.
*/

class Song 
{
    private:
        std::string title;  // The title or name of the song.
        int duration;       // The duration of the song in seconds.
    
    public:
        // Constructor: to initialize a Song object with a title and duration.
        Song(const std::string&, int); 
        // Returns the title of the song. 
        std::string getTitle() const;
        // Returns the duration of the song in seconds.
        int getDuration() const;

    // Overloaded the operator == for comparing Song objects on their title and duration.
    bool operator==(const Song& other) const
    {
        return (title == other.title) && (duration == other.duration);
    }

    // Overloaded the operator < for comparing Song objects based on their titles.
    bool Song::operator<(const Song& other) const
    {
        return title < other.title;
    }
    

};
// Constructor:
Song::Song(const std::string& title, int duration) : title(title), duration(duration) 
{
}

std::string Song::getTitle() const 
{
    return title;
}

int Song::getDuration() const 
{
    return duration;
}

#endif