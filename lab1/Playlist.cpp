#include "Playlist.h"
#include <iostream>
#include <string>

//PlaylistNode default constructor
PlaylistNode::PlaylistNode() {
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = nullptr;
}

//Initializes a node with provided values for ID, name, artist, and length.
PlaylistNode::PlaylistNode(const std::string& id, const std::string& name, const std::string& artist, int length) {
    uniqueID = id;
    songName = name;
    artistName = artist;
    songLength = length;
    nextNodePtr = nullptr;
}

//PlaylistNode destructor
// Does not perform any specific cleanup since no dynamic memory allocation occurs in this class.
PlaylistNode::~PlaylistNode() {
}

//InsertAfter function
// Updates the nextNodePtr of the current node to point to the new node
void PlaylistNode::InsertAfter(PlaylistNode* node) {
    node->nextNodePtr = this->nextNodePtr;
    this->nextNodePtr = node;
}

//SetNext function
// Updates next node pointer
void PlaylistNode::SetNext(PlaylistNode* nextNode) {
    nextNodePtr = nextNode;
}

//Get ID function returns uniqueID
std::string PlaylistNode::GetID() const {
    return uniqueID;
}

//GetSongName function returns songName
std::string PlaylistNode::GetSongName() const {
    return songName;
}

//GetArtistName function returns artistName
std::string PlaylistNode::GetArtistName() const {
    return artistName;
}

//GetSongLength function returns songLength
int PlaylistNode::GetSongLength() const {
    return songLength;
}

//GetNext function returns nextNodePtr
PlaylistNode* PlaylistNode::GetNext() const {
    return nextNodePtr;
}

//PrintPlaylistNode function outputs the contents in playlist to the user.
void PlaylistNode::PrintPlaylistNode() const {
    std::cout << "Unique ID: " << uniqueID << std::endl;
    std::cout << "Song Name: " << songName << std::endl;
    std::cout << "Artist Name: " << artistName << std::endl;
    std::cout << "Song Length (in seconds): " << songLength << std::endl;
}

//Playlist class constructor
// Initializes an empty playlist with a given title
Playlist::Playlist(const std::string& title) {
    playlistTitle = title;
    head = nullptr;
    tail = nullptr;
}

//Playlist destructor
// Deletes all nodes in the playlist to free memory
// Prevent memory leak
Playlist::~Playlist() {
    PlaylistNode* curr = head;
    while (curr != nullptr) {
        PlaylistNode* temp = curr;
        curr = curr->GetNext();
        delete temp;
    }
// Set both head and tail to nullptr
    head = nullptr;
    tail = nullptr;
}

//Playlist addsong function
// Adds a song to the end of the playlist
void Playlist::AddSong() {
    std::string id;
    std::string name;
    std::string artist;
    int length;

// Allow the user to enter the song
    std::cout << "ADD SONG" << std::endl;
    std::cout << "Enter song's unique ID:" << std::endl;
    std::cin >> id;
    std::cout << "Enter song's name:" << std::endl;
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter artist's name:" << std::endl;
    std::getline(std::cin, artist);
    std::cout << "Enter song's length (in seconds):" << std::endl;
    std::cin >> length;
    std::cout << std::endl;

    PlaylistNode* newSong = new PlaylistNode(id, name, artist, length);
    newSong->SetNext(nullptr);

// Set head and tail to newSong when there is no song
    if (head == nullptr) {
        head = newSong;
        tail = newSong;
    } else {
// Add newSong infront of the tail and set the tail to newSong
        tail->SetNext(newSong);
        tail = newSong;
    }
}

//Playlist removesong function
// Removes a song from the playlist by unique ID
void Playlist::RemoveSong() {
    if (head == nullptr) {
// No songs in playlist
        std::cout << "Playlist is empty" << std::endl << std::endl;
        return;
    }

    std::string id;
    std::cout << "REMOVE SONG" << std::endl;
    std::cout << "Enter song's unique ID:" << std::endl;
    std::cin >> id;

    PlaylistNode* prev = nullptr;
    PlaylistNode* curr = head;

// Move through the playlists to find the song with the matching ID
    while (curr && curr->GetID() != id) {
        prev = curr;
        curr = curr->GetNext();
    }

// If the song is not found
    if (curr == nullptr) {
        std::cout << "Song not found" << std::endl << std::endl;
        return;
    }

    std::string songName = curr->GetSongName();

// If the song to remove is the head
    if (curr == head) {
        head = head->GetNext();
        if (head == nullptr) {
            tail = nullptr;
        }
    } else {
// If the song is in the middle or end
        prev->SetNext(curr->GetNext());
        if (curr == tail) {
            tail = prev;
        }
    }

// Free the memory
    delete curr;
    std::cout << "\"" << songName << "\" removed." << std::endl << std::endl;
}

//Playlist changeposition function
void Playlist::ChangePosition() {

// Don't do anything if there is no song to change position
    if (head == nullptr || head == tail) {
        return;
    }

// Asking the user to change position of the song
// User has to provide song's current position and new position
    int currPos, newPos;
    std::cout << "CHANGE POSITION OF SONG" << std::endl;
    std::cout << "Enter song's current position:" << std::endl;
    std::cin >> currPos;
    std::cout << "Enter new position for song:";
    std::cin >> newPos;
    std::cout << std::endl;

// If current position is less than 1 then set it to 1
    if (currPos < 1) {
        currPos = 1;
    }

// Count total number of nodes in the playlist
    int totalNodes = 0;
    PlaylistNode* tempCount = head;
    while (tempCount != nullptr) {
        totalNodes++;
        tempCount = tempCount->GetNext();
    }
// Ensure current and new positions stay within the bounds of the playlist
    if (currPos > totalNodes) {
        currPos = totalNodes;
    }
    if (newPos < 1) {
        newPos = 1;
    }
    if (newPos > totalNodes) {
        newPos = totalNodes;
    }

// If the positions are the same, there's nothing to change
    if (currPos == newPos) {
        return;
    }

// Find the node to move and its previous node
    PlaylistNode* prev = nullptr;
    PlaylistNode* curr = head;
    for (int i = 1; i < currPos; ++i) {
        prev = curr;
        curr = curr->GetNext();
    }

    if (prev == nullptr) {
        head = curr->GetNext();
    } else {
        prev->SetNext(curr->GetNext());
    }
// If the node was the tail, update the tail pointer
    if (curr == tail) {
        tail = prev;
    }

// Insert the node at the new position
    if (newPos == 1) {
// Insert at the beginning
        curr->SetNext(head);
        head = curr;
    } else {
        PlaylistNode* insertPrev = head;
        for (int i = 1; i < newPos - 1; ++i) {
            insertPrev = insertPrev->GetNext();
        }
// Insert the node after insertPrev
    insertPrev->InsertAfter(curr);
// Update tail if inserted at the end
        if (curr->GetNext() == nullptr) {
            tail = curr;
        }
    }

    std::cout << "\"" << curr->GetSongName() << "\" moved to position " << newPos << std::endl << std::endl;
}

//Playlist outputbyartist function
// Outputs all songs by a specific artist through linkedlist
void Playlist::OutputByArtist() const {
    std::cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << std::endl;
    std::cout << "Enter artist's name:" << std::endl;

    std::string artist;
    std::getline(std::cin, artist);
    std::cout << std::endl;

// Start from the head of the playlist
    PlaylistNode* curr = head;
    int position = 1;

    while (curr != nullptr) {
// Find if the current song's artist name matches the input (artist name) from the user
        if (curr->GetArtistName() == artist) {
            std::cout << position << "." << std::endl;
            curr->PrintPlaylistNode();
            std::cout << std::endl;
        }
        curr = curr->GetNext();
        position++;
    }
}

//Playlist totaltime function
// Outputs the total time of all playlists
void Playlist::TotalTime() const {
    int total = 0;
    PlaylistNode* curr = head;

//Add all the time for each song and output the total time in seconds
    while (curr != nullptr) {
        total += curr->GetSongLength();
        curr = curr->GetNext();
    }

    std::cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << std::endl;
    std::cout << "Total time: " << total << " seconds" << std::endl << std::endl;
}

//Playlist outputfullplaylist function
void Playlist::OutputFullPlaylist() const {
    std::cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << std::endl;

    if (head == nullptr) {
        std::cout << "Playlist is empty" << std::endl << std::endl;
    } else {
        PlaylistNode* curr = head;
        int songNumber = 1;

// Show the lists of the playlist until the current goes to nullptr
// Use GetNext() to get the nextsong and print it to the list
        while (curr != nullptr) {
            std::cout << songNumber << "." << std::endl;
            curr->PrintPlaylistNode();
            std::cout << std::endl;
            curr = curr->GetNext();
            songNumber++;
        }
    }
}
