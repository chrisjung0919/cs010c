#pragma unique

#include <string>
#include <iostream>

// PlaylistNode class definition
class PlaylistNode {
 private:
   
   //private member variables for playlist
   std::string uniqueID;
   std::string songName;
   std::string artistName;
   int songLength;
   PlaylistNode* nextNodePtr;

 public:
   // Default constructor
   PlaylistNode();

   // Constructor with parameters
   PlaylistNode(const std::string& id, const std::string& name, const std::string& artist, int length);

   //Destructor
   ~PlaylistNode();

   //InsertAfter function
   void InsertAfter(PlaylistNode* node);

   //SetNext function
   void SetNext(PlaylistNode* nextNode);

   //Accessors
   std::string GetID() const;
   std::string GetSongName() const;
   std::string GetArtistName() const;
   int GetSongLength() const;
   PlaylistNode* GetNext() const;

   //Print playlist function
   void PrintPlaylistNode() const;
};

// Playlist class definition
class Playlist {
 private:
   
   //First node and last node
   std::string playlistTitle;
   PlaylistNode* head;
   PlaylistNode* tail;

 public:
   //Constructor
   Playlist(const std::string& title);

   //Destructor
   ~Playlist();

   //Copy constructor and assignment operator both set to delete
   Playlist(const Playlist& other) = delete;
   Playlist& operator=(const Playlist& other) = delete;

   // Functions that depends on the user input
   // These are function declarations
   void AddSong();
   void RemoveSong();
   void ChangePosition();
   void OutputByArtist() const;
   void TotalTime() const;
   void OutputFullPlaylist() const;
};
