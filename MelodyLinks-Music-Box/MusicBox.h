#ifndef MUSIC_BOX_H
#define MUSIC_BOX_H
#include "DoublyLinkedList.h"
#include "Song.h"

/*
    Author: Ky Lam
    Date: October 30, 2023
    Description: The MusicBox class is a music player application that manages a playlist of songs. 
    It offers various features for efficient music playback and playlist management. 
    Users can add new songs to the playlist, remove specific songs, play the next or previous song, 
    view the currently playing song, display the entire playlist with song titles and durations, 
    search for songs within the playlist, shuffle and sort the playlist by song titles in alphabetical order.
*/

class MusicBox
{
private:
    DoublyLinkedList<Song> playlist;    // A doubly-linked list that stores the songs in the playlist.
    Node<Song>* currentSongNode;        // A pointer to the currently played song in the playlist.

public:
    // Constructor: initialize an empty MusicBox.
    MusicBox();

    // Copy constructor: create a new MusicBox as a copy of another MusicBox.
    MusicBox(const MusicBox& other);

    // Assignment operator: assign the contents of another MusicBox to this one.
    MusicBox& operator=(const MusicBox& other);

    // Adds a new song to the playlist.
    void addSong(const std::string& title, int duration);

    // Removes a song from the playlist. 
    bool removeSong(const std::string& title, bool isDestructorCall);

    // Check if a song in the playlist.
    bool searchSong(const std::string& title);

    // Plays the next song in the playlist.
    void playNext();

    // Plays the previous song in the playlist.
    void playPrevious();

    // Displays the currently playing song.
    void currentSong();

    // Displays the entire playlist with song titles and durations.
    void displayPlaylist();

    // Sorts the playlist by song titles in alphabetical order using Quick Sort algorithm.
    void sort();

    // Shuffle feature: randomly reorder songs in the playlist
    void shufflePlaylist();

    // Destructor: clean up the MusicBox by removing all songs from the playlist.
    ~MusicBox();
};

// Constructor
MusicBox::MusicBox(): currentSongNode(nullptr) 
{
}

// Copy constructor
// Parameters:
//     - other: the other MusicBox is copied.
MusicBox::MusicBox(const MusicBox& other)
{
    Node<Song>* otherCurrent = other.playlist.getHead();
    while (otherCurrent != nullptr)
    {
        Song otherSong = otherCurrent->data;
        addSong(otherSong.getTitle(), otherSong.getDuration());

        otherCurrent = otherCurrent->next;
    }
}

// Assignment Operator
// Parameters:
//     - other: the other MusicBox is copied.
// Returns: the new MusicBox after copy from the other.
MusicBox& MusicBox::operator=(const MusicBox& other)
{
    if (this == &other)
    {
        return *this; 
    }

    // Clear the current playlist
    while (playlist.getSize() > 0)
    {
        Node<Song>* firstNode = playlist.getHead();

        Song firstSong = firstNode->data;
        std::string songTitle = firstSong.getTitle();

        removeSong(songTitle, true);
    }

    // Copy Songs from other playlist to this playlist
    Node<Song>* otherCurrent = other.playlist.getHead();
    while (otherCurrent != nullptr)
    {
        Song otherSong = otherCurrent->data;
        addSong(otherSong.getTitle(), otherSong.getDuration());

        otherCurrent = otherCurrent->next;
    }

    return *this;
}

// Adds a new song to the playlist.
// Parameters:
//   - title: The title of the new Song.
//   - duration: The duration of the new Song in seconds.
// Output the message when the Song is added successfully.
void MusicBox::addSong(const std::string& title, int duration)
{
    if (currentSongNode == nullptr)
    {
        Song newSong(title, duration);
        playlist.push_back(newSong);

        currentSongNode = playlist.getHead();
    }
    else
    {
        Song newSong(title, duration);
        playlist.push_back(newSong);
    }

    std::cout<<"\""<< title <<"\""<< " added to the playlist."<< std::endl;
}

// Removes a song from the playlist. 
// Parameters:
//   - removeTitle: The title of the removed Song need to be removed.
//   - isDestructorCall: boolean variable to check if this is removed by users or by the Destructor.
// Returns: True if the removal is successful, false otherwise.
// Output the message when the Song is removed successfully or not.
// If isDestructorCall is set to true, it suppresses output messages for destructor calls.
bool MusicBox::removeSong(const std::string& removeTitle, bool isDestructorCall)
{
    Node<Song>* current = playlist.getHead();

    while (current != nullptr) 
    {
        Song currSong = current->data;

        if(removeTitle == currSong.getTitle())
        {
            if (currSong == currentSongNode->data)
            {
                //If NO more song in the playlist after remove
                if (playlist.getHead()->next == nullptr)
                {
                    currentSongNode = nullptr;
                }
                else
                {
                    currentSongNode = currentSongNode->next ? currentSongNode->next : playlist.getHead();
                }
            }
            
            if (!isDestructorCall) 
            {
                std::cout << std::endl;
                std::cout<<"\""<<currSong.getTitle()<<"\""<< " removed from the playlist."<< std::endl;
            }
            return playlist.remove(currSong);
        }
        current = current->next;
    }

    if (!isDestructorCall)
    {
        std::cout << std::endl;
        std::cout<<"\""<<removeTitle<<"\""<< " is not in the playlist. Fail to remove."<< std::endl;
    }
    return false;
}

// Check if the Song is on the playlist.
// Parameters:
//   - title: The Song's title needs to be checked.
// Returns: True if the Song is on the playlist, false otherwise.
// Output the message if the Song is found or not.
bool MusicBox::searchSong(const std::string& title)
{
    Node<Song>* current = playlist.getHead();
    std::cout << std::endl;
    while (current != nullptr) 
    {
        if (current->data.getTitle() == title) 
        {
            std::cout<<"Song \""<<title<<"\""<< " found in the playlist!"<< std::endl;
            return true;  
        }
        current = current->next;
    }

    std::cout<<"Song \""<<title<<"\""<< " NOT found in the playlist!"<< std::endl;
    return false;  
}

// Plays the next song in the playlist.
// Displays the title and the duration of the new current playing Song.
void MusicBox::playNext()
{
    if (currentSongNode == nullptr) 
    {
        currentSongNode = playlist.getHead();
    } 
    else 
    {
        currentSongNode = currentSongNode->next ? currentSongNode->next : playlist.getHead();
    }
    std::cout << std::endl;
    std::cout<<"Now playing: \""<<currentSongNode->data.getTitle()<<"\" Duration: "<<currentSongNode->data.getDuration()<<" seconds."<< std::endl;

}

// Plays the previous song in the playlist.
// Displays the title and the duration of the new current playing Song.
void MusicBox::playPrevious()
{
    if (currentSongNode == nullptr) 
    {
        currentSongNode = playlist.getTail();
    } 
    else 
    {
        currentSongNode = currentSongNode->previous ? currentSongNode->previous : playlist.getTail();
    }
    std::cout << std::endl;
    std::cout<<"Now playing: \""<<currentSongNode->data.getTitle()<<"\" Duration: "<<currentSongNode->data.getDuration()<<" seconds."<< std::endl;
}

// Displays the title and duration of currently playing Song.
void MusicBox::currentSong()
{
    if (currentSongNode == nullptr) 
    {
        std::cout << std::endl;
        std::cout << "Playlist is empty, NOT playing any song now." <<std::endl;
    } 
    else 
    {
        Song currSong = currentSongNode->data;
        std::cout << std::endl;
        std::cout << "Now playing: \"" << currSong.getTitle()<<"\" Duration: "<< currSong.getDuration()<<" seconds."<<std::endl;
    }
}

// Displays the entire playlist with song titles and durations.
void MusicBox::displayPlaylist()
{
    Node<Song>* current = playlist.getHead();
    std::cout << std::endl;
    std::cout << "Playlist:" <<endl;

    while (current != nullptr) 
    {
        Song currSong = current->data;
        std::cout << currSong.getTitle() << " - " << currSong.getDuration() << " seconds" << std::endl;
        current = current->next;
    }
}

// Helper function (Quick Sort) for the sort method.
// Parameters:
//   - playlist: The playlist need to be sorted.
//   - low: The pointer to the first Song of the playlist.
//   - high: The pointer to the last Song of the playlist.
void quickSort(DoublyLinkedList<Song>& playlist, Node<Song>* low, Node<Song>* high)
{
    if (low != nullptr && high != nullptr && low != high && low->previous != high)
    {
        Node<Song>* pivot = low;
        Node<Song>* left = low;
        Node<Song>* right = high;
        int pivotIsLeftPrevious = 0;

        while(left != right)
        {
            // Move left while the title is less than or equal to the pivot's title
            while (left != nullptr && left->data.getTitle() <= pivot->data.getTitle() && left != right)
                left = left->next;

            // Move right while the title is greater than the pivot's title
            while (right != nullptr && right->data.getTitle() > pivot->data.getTitle() && left != right)
                right = right->previous;

            //Swap pivot
            if(left == right) 
            {
                if (pivot->data < left->data)
                {
                    std::swap(pivot->data, left->previous->data);
                    pivotIsLeftPrevious = 1;
                }
                else
                {
                    std::swap(pivot->data, left->data);
                    pivotIsLeftPrevious = 0;
                }
            }
            // Swap nodes  
            else if (left != nullptr && right != nullptr && left != right)
            {
                // Swap left and right elements
                std::swap(left->data, right->data);
            }
        }

        // Recursively sort the two sublists
        if(left->previous != nullptr && pivotIsLeftPrevious == 0)
        {
            quickSort(playlist, low, left->previous);
        }
        else 
        if(left->previous->previous != nullptr && pivotIsLeftPrevious == 1)
        {
            quickSort(playlist, low, left->previous->previous);
        }
        
        quickSort(playlist, right, high);
    }
}

// Sorts the playlist by song titles in alphabetical order by using the Quick Sort algorithm.
void MusicBox::sort()
{
    if (playlist.getSize() <= 1)
    {
        return;
    }

    Node<Song>* low = playlist.getHead();
    Node<Song>* high = playlist.getTail();

    quickSort(playlist, low, high);

    std::cout << std::endl;
    std::cout << "Playlist sorted by song titles." << std::endl;
}

// Randomly reorder songs in the playlist.
void MusicBox::shufflePlaylist() 
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int listSize = playlist.getSize();

    for (int i = listSize - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);

        // Swap songs at index i and j.
        if (i != j) {
            Node<Song>* node1 = playlist.getHead();
            Node<Song>* node2 = playlist.getHead();

            for (int k = 0; k < i; ++k) {
                node1 = node1->next;
            }
            for (int k = 0; k < j; ++k) {
                node2 = node2->next;
            }

            std::swap(node1->data, node2->data);
        }
    }
    std::cout << std::endl;
    std::cout << "Playlist shuffled randomly." << std::endl;
}

// Destructor:
MusicBox::~MusicBox()
{
    while (playlist.getSize() > 0)
    {
        Node<Song>* firstNode = playlist.getHead();

        Song firstSong = firstNode->data;
        std::string songTitle = firstSong.getTitle();

        removeSong(songTitle, true);
    }
}

#endif