#include <iostream>
#include <limits>
#include "Playlist.h"

using namespace std;

// Displays the playlist menu with options to manage songs and view playlist details.
void PrintMenu(const string& title) {
    cout << title << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
    cout << "Choose an option:" << endl;
}

int main() {
    string title;
    string command;

    // Prompt for and read the title for the playlist (may contain spaces).
    cout << "Enter playlist's title:" << endl;
    getline(cin, title);
    cout << endl;

    // Build a playlist object with this title.
    Playlist myPlayList(title);

    while (command != "q") {
        PrintMenu(title);
        cin >> command;
    // ignore characters until we get to a newline or end-of-file
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (command == "a") {
            myPlayList.AddSong();
        } else if (command == "d") {
            myPlayList.RemoveSong();
        } else if (command == "c") {
            myPlayList.ChangePosition();
        } else if (command == "s") {
            myPlayList.OutputByArtist();
        } else if (command == "t") {
            myPlayList.TotalTime();
        } else if (command == "o") {
            myPlayList.OutputFullPlaylist();
        }
    }

    return 0;
}
