#include <iostream>
#include "playlist.h"

using namespace std;

void printPlaylistDuration(int d[]){
    if(d[0] != 0){
        cout << d[0] << ":";
        if(d[1] < 10) cout << 0;
    }
    
    cout << d[1] << ":";
    if(d[2] < 10) cout << 0;
    cout << d[2];
}

void printSong(Song s){
    cout << s.artist <<" - "<< s.name << ", " << s.duration[0] << ":";
    if(s.duration[1] < 10) cout << 0;
    cout << s.duration[1] << ", " << s.genres[0];
    for(int i = 1; i < 3; ++i){
        if(s.genres[i] != "") cout << ", " << s.genres[i];
        else break;
    }
}

void printPlaylist(Playlist P){
    for(int i = 0; i < P.n; ++i){
        printSong(P.songs[i]);
        cout << endl;
    }
    cout <<"-------------------------------------------------------";
}

int main(){ 
    int d1[2] = {2, 54}; string g1[] = {"pop rock", "", ""};
    Song s1("Dose No. 2", "The Maine", d1, g1);
    int d2[2] = {3, 20}; string g2[] = {"electropop", "dance-pop", ""};
    Song s2("Tok Tok", "Ke$ha", d2, g2);
    int d3[2] = {3, 2}; string g3[] = {"pop rock", "indie rock", "alternative rock"};
    Song s3("Am I Pretty", "The Maine", d3, g3);
    Song s[3]; s[0] = s1; s[1] = s2; s[2] = s3;
    Playlist P(s, 3);
    int d4[2] = {4, 15}; string g4[] = {"pop", "funk", "rock"};
    Song s4("Girls", "The 1975", d4, g4);
    cout << "Playlist P:\n";
    printPlaylist(P);
    cout << endl;
    P.sortBy(2);
    cout << "Playlist P after sorting alphabetically:\n";
    printPlaylist(P);
    cout << endl;
    P.addSong(s4);
    cout << "Playlist P after adding a song:\n";
    printPlaylist(P);
    cout << endl;
    P.sortBy(1);
    cout << "Playlist P after sorting by the order of adding:\n";
    printPlaylist(P);
    cout << endl;
    int *d = P.playlistDuration();
    cout << "Playlist duration is "; printPlaylistDuration(d);
    cout << endl << endl; 
    P.remove(s2);
    cout << "Playlist P after removing a song:\n";
    printPlaylist(P);
    cout << endl;
    int m;
    Song *songsByTheMaine = P.getSongsByArtist("The Maine", &m);
    if(songsByTheMaine == nullptr) cout << "There are no songs by The Maine!\n";
    else{
        cout << "Songs by The Maine:\n";
        for(int i = 0; i < m; ++i){
            printSong(songsByTheMaine[i]);
            cout << endl;
        }
    } 
    cout << endl;
    int d5[2] = {3, 48}; string g5[] = {"pop rock", "indie rock", "power pop"};
    Song s5("So High School", "Taylor Swift", d5, g5);
    Playlist Q; Q.addSong(s5);
    Playlist R = Q.similarPlaylist(P);
    cout << "Playlist R:\n";
    printPlaylist(R);
    cout << endl; 
    return 0;
}