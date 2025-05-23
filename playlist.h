#include <string>

struct Song{
    std::string name;
    std::string artist;
    int duration[2];
    std::string genres[3];

    Song();
    Song(std::string n, std::string a, int d[], std::string g[]);
};

struct Playlist{
    Song songs[100];
    int added[100];
    int n;
    int sortedBy;

    Playlist();
    Playlist(Song s[], int m);
    int addSong(Song s);
    int* playlistDuration();
    void sortBy(int how);
    Song* getSongsByArtist(std::string a, int*m);
    int remove(Song s);
    Playlist similarPlaylist(Playlist P);
};