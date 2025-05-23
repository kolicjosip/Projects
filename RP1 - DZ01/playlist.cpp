#include <iostream>
#include <string>
#include "playlist.h"

using namespace std;

Song::Song() {
    name = "";
    artist = "";
    duration[1] = duration[0] = 0;
    genres[2] = genres[1] = genres[0] = "";
}

Song::Song(std::string n, std::string a, int d[], std::string g[]) {
    name = n;
    artist = a;
    duration[0] = d[0];
    duration[1] = d[1];
    genres[0] = g[0];
    genres[1] = g[1];
    genres[2] = g[2];
}

Playlist::Playlist() {
    sortedBy = 1;
    n = 0;
}

Playlist::Playlist(Song s[], int m) {
    sortedBy = 1;
    n = m;
    for (int i = 0; i < n; i++) {
        added[i] = i + 1;
        songs[i] = s[i];
    }
}

int Playlist::addSong(Song s) {
    if (n >= 100) return 0;

    for (int i = 0; i < n; i++) {
        if (songs[i].artist == s.artist && songs[i].name == s.name)
            return 0;
    }

    songs[n] = s;
    added[n] = n + 1;
    n++;
    sortBy(sortedBy);
    return 1;
}

int* Playlist::playlistDuration() {
    int* time_duration = new int[3];
    int sve = 0;
    for (int i = 0; i < n; i++) {
        sve += songs[i].duration[0] * 60 + songs[i].duration[1];
    }

    time_duration[0] = sve / 3600;
    sve %= 3600;
    time_duration[1] = sve / 60;
    time_duration[2] = sve % 60;

    return time_duration;
}

void Playlist::sortBy(int how) {
    if (how != 2 && how != 1) return;
    sortedBy = how;

    if (how == 2) {
        for (int i = 0; i < n - 1; i++) {
            int min = i;
            for (int j = i + 1; j < n; j++) {
                if (songs[j].artist < songs[min].artist)
                    min = j;
                else if (songs[j].artist == songs[min].artist && songs[j].name < songs[min].name)
                    min = j;
            }
            if (i != min) {
                swap(songs[i], songs[min]);
                swap(added[i], added[min]);
            }
        }
    }
    else if (how == 1) {
        for (int i = 0; i < n - 1; i++) {
            int m = i;
            for (int j = i + 1; j < n; j++) {
                if (added[m] > added[j])
                    m = j;
            }
            if (m != i) {
                swap(songs[i], songs[m]);
                swap(added[i], added[m]);
            }
        }
    }
}

Song* Playlist::getSongsByArtist(std::string a, int* m) {
    if( n == 0 )
        return nullptr;

    Song* popis = new Song[n];
    *m = 0;
    for (int i = 0; i < n; i++) {
        if (songs[i].artist == a) {
            popis[*m] = songs[i];
            (*m)++;
        }
    }

    if( *m == 0)
        return nullptr;

    Song* result = new Song[*m];
    for (int i = 0; i < *m; i++) {
        result[i] = popis[i];
    }
    delete[] popis;
    return result;
}


int Playlist::remove(Song s) {
    for (int i = 0; i < n; i++) {
        if (s.artist == songs[i].artist && s.name == songs[i].name) {
            int dodan = added[i];
            for (int k = 0; k < n; k++) {
                if (added[i] < added[k])
                    added[k]--;
            }
            for (int j = i; j < n - 1; j++) {
                songs[j] = songs[j + 1];
                added[j] = added[j + 1];
            }
            n--;
            return 1;
        }
    }
    return 0;
}

Playlist Playlist::similarPlaylist(Playlist P) {
    Playlist R;
    R.sortedBy = 1;
    for (int i = 0; i < n; i++) {
        R.addSong(songs[i]);
    }

    for (int p = 0; p < P.n; p++) {
        for (int r = 0; r < n; r++) {
            bool found = false;
            for (int i = 0; i < 3 && P.songs[p].genres[i] != ""; i++) {
                for (int j = 0; j < 3 && R.songs[r].genres[j] != ""; j++) {
                    if (P.songs[p].genres[i] == R.songs[r].genres[j])
                        found = true;
                }
            }
            if (found)
                R.addSong(P.songs[p]);
        }
    }
    return R;
}
