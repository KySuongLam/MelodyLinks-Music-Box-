#include "DoublyLinkedList.h"
#include "MusicBox.h"
#include "Song.h"

#include <iostream>
#include <string>

/*
    Author: Ky Lam
    Date: November 2, 2023
    Description: MelodyLinks is a command-line music player application that offers a 
    user-friendly interface for managing a playlist of songs. Utilizing the MusicBox class, 
    this program allows users to interact with their music library efficiently. 
    The menu-driven system provides various options, including adding songs to the playlist, 
    removing songs, playing the next or previous song, viewing the currently playing song, 
    displaying the entire playlist with durations, searching for specific songs, sort the playlist 
    by song titles in alphabetical order, and exiting the application.
*/

int main() {
    
    MusicBox musicBox; 

    std::cout << "Welcome to MelodyLinks!" << std::endl;
    std::cout<<std::endl;

    std::cout << "Menu:" << std::endl;
    std::cout << "1. Add song to the playlist" << std::endl;
    std::cout << "2. Remove song from the playlist" << std::endl;
    std::cout << "3. Play the next song" << std::endl;
    std::cout << "4. Play the previous song" << std::endl;
    std::cout << "5. Display current song" << std::endl;
    std::cout << "6. Display the entire playlist with durations" << std::endl;
    std::cout << "7. Search for a song" << std::endl;
    std::cout << "8. Sort the playlist" << std::endl;
    std::cout << "9. Shuffle the playlist" << std::endl;
    std::cout << "10. Exit" << std::endl;

    while (true) 
    {
        int choice;
        std::cout << std::endl;
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) 
        {
            // Adding song
            case 1: 
            {
                std::string title;
                int duration;
                std::cout << "Enter song title: ";
                std::cin.ignore(); 
                std::getline(std::cin, title);

                std::cout << "Enter song duration (in seconds): ";
                std::cin >> duration;
                std::cout<<std::endl;
                musicBox.addSong(title, duration);
                break;
            }
            // Removing song
            case 2: 
            {
                std::string title;
                std::cout << "Enter song title to remove: ";
                std::cin.ignore(); 
                std::getline(std::cin, title);
                musicBox.removeSong(title,false);
                break;
            }
            // Next song
            case 3:
            {
                musicBox.playNext();
                break;
            }
            // Previous song
            case 4:
            {
                musicBox.playPrevious();
                break;
            }
            // Display current song
            case 5:
            {
                musicBox.currentSong();
                break;
            }
            // Display the playlist
            case 6:
            {
                musicBox.displayPlaylist();
                break;
            }
            // Search song
            case 7: 
            {
                std::string title;
                std::cout << "Enter song title to search for: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                musicBox.searchSong(title);
                break;
            }
            // Sorting the playlist
            case 8:
            {
                musicBox.sort();
                break;
            }

            // Shuffle playlist
            case 9:
            {
                musicBox.shufflePlaylist();
                break;
            }

            // Exit
            case 10:
            {
                std::cout << std::endl;
                std::cout << "Thank you for using MelodyLinks!" << std::endl;
                return false; // Exit the program
            }

            // If the user inputs an invalid option (not 1 to 10), ask the user to try again.       
            default:
                std::cout << std::endl;
                std::cout << "Invalid option. Please choose a valid option." << std::endl;
                break;
        }
    }

    return 0;
}