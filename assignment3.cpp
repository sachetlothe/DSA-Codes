#include <iostream>
using namespace std;

// Class representing a Song
class song {
private:
    string title, artist; // Song title and artist name
    float duration; // Song duration in minutes

public:
    song *next; // Pointer to the next song in the linked list

    // Constructor to initialize the 'next' pointer to NULL
    song() {
        next = NULL;
    }

    // Function to read song details from input
    void read(string name, string artist_name, float time) {
        title = name;
        artist = artist_name;
        duration = time;
    }

    // Function to display song details
    void display() {
        cout << "Song name: " << title << endl;
        cout << "Artist name: " << artist << endl;
        cout << "Duration: " << duration << " mins" << endl;
    }

    // Getter for the 'next' pointer
    song *getNext(){
        return next;
    }

    // Setter for the 'next' pointer
    void setNext(song *temp){
        next = temp;
    }

    // Getter for the song title
    string getName(){
        return title;
    }
};

// Class representing the Playlist, which is a linked list of songs
class myPlaylist {
public:
    song *head; // Pointer to the first song in the playlist

    // Constructor to initialize the 'head' pointer to NULL
    myPlaylist() {
        head = NULL;
    }

    // Function to add a song to the playlist
    void addsong(string name, string artist_name, float time) {
        song *nn = new song; // Create a new song node
        nn->read(name, artist_name, time); // Set song details

        // If the playlist is empty, the new song becomes the head
        if (head == NULL) {
            head = nn;
        } else {
            // Traverse to the end of the list and add the new song
            song *cn;
            for (cn = head; cn->next != NULL; cn = cn->next) {
                // Traverse to the end of the list
            }
            cn->next = nn; // Set the new song as the last node
        }   
    }

    // Function to display all songs in the playlist
    void displayPlaylist() {
        if (head == NULL) { // Check if the playlist is empty
            cout << "Playlist is empty.\n";
            return;
        }
        // Traverse through the playlist and display each song
        song *cn;
        for (cn = head; cn != NULL; cn = cn->next) {
            cn->display(); // Display song details
            cout << endl;
        }
    }

    // Function to delete a song from the playlist by title
    void deleteSong(string value) {
        if (head == NULL) { // Check if the playlist is empty
            cout << "Playlist is empty.\n";
            return;
        }

        song *temp = head; // Temporary pointer to traverse the list
        song *prev = NULL; // To keep track of the previous node

        // Check if the song to be deleted is the head
        if (head->getName() == value) {
            head = head->getNext(); // Move head to the next node
            delete temp; // Delete the old head
            cout << "Song deleted.\n";
            return;
        }

        // Traverse the list to find the song
        while (temp != NULL && temp->getName() != value) {
            prev = temp;
            temp = temp->getNext();
        }

        // If song is not found
        if (temp == NULL) {
            cout << "Song not found.\n";
            return;
        }

        // Remove the song from the list
        prev->setNext(temp->getNext());
        delete temp; // Free the memory of the deleted node
        cout << "Song deleted.\n";
    }

    // Function to play a specific song by title
    void playSong(string songName) {
        song *temp = head; // Start from the head
        while (temp) {
            // Check if the current song matches the requested song
            if (temp->getName() == songName) {
                cout << "\nNow playing:\n";
                temp->display(); // Display song details
                return;
            }
            temp = temp->getNext(); // Move to the next song
        }
        cout << "\nSong not found.\n"; // If song is not in the list
    }
};

// Main function to handle the user interface
int main() {
    myPlaylist playlist; // Create a playlist object
    int choice;
    string title, artist_name;
    float duration;

    // Loop for the menu options
    do {
        cout << "\nMenu:\n";
        cout << "1. Add Song\n";
        cout << "2. Display Playlist\n";
        cout << "3. Remove Song\n";
        cout << "4. Play Song\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // Add song option
                cout << "Enter song title: ";
                cin.ignore(); // To handle newline after choice input
                getline(cin, title);
                cout << "Enter artist name: ";
                getline(cin, artist_name);
                cout << "Enter song duration (in minutes): ";
                cin >> duration;
                playlist.addsong(title, artist_name, duration); // Add song to playlist
                break;

            case 2: // Display playlist option
                playlist.displayPlaylist();
                break;

            case 3: // Remove song option
                cout << "Enter song title to delete: ";
                cin.ignore();
                getline(cin, title);
                playlist.deleteSong(title); // Delete the specified song
                break;

            case 4: // Play song option
                cout << "Enter song title to play: ";
                cin.ignore();
                getline(cin, title);
                playlist.playSong(title); // Play the specified song
                break;

            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 4); // Exit the loop after playing a song

    return 0;
}
