#include<iostream>
#include<string>
#include<fstream>
using namespace std;
    
    string language;
    string type;
    string getMoodFile(string mood);
    void suggestSongs(string mood);
    void saveMood(string mood);
    void showMoodHistory();
    void showPlaylistHistory();
    void saveFeedback();
int main(){
    while(true)
    {
    int choice=0;
    
string mood;
    
    //Main Menu
    
    
       cout<<"------------------------------"<<endl;
       cout<<"Music Recommender"<<endl;
       cout<<"1- Enter Mood"<<endl;
       cout<<"2- View Mood History"<<endl;
       cout<<"3- View Playlist History"<<endl;
       cout<<"4-Exit"<<endl; 
        cout<<"Enter your choice: ";
        cin>>choice;
       cout<<"------------------------------"<<endl;
       if (choice <=4 && choice>=1)
   {
    

    if (choice==1)                  //Mood Selection
    {
        if(choice==1){
    cout << "=====================================\n";
    cout << "      WELCOME TO MUSIC WORLD\n";
    cout << "=====================================\n";
    suggestSongs(mood);
    cout << "\n\nEnjoy Your Music!\n";

}

        else
        {
            cout<<"Invalid mood entered. Please try again."<<endl;
        }
    }   
    
    else if (choice==2)             //View Mood History
    {
       
        showMoodHistory();
    }
    else if (choice==3)             //View Playlist History
    {
        showPlaylistHistory();
    }
    else if (choice==4)             //Exit
    {
        cout<<"Exiting program. Goodbye!"<<endl;
        return 0;
    }
    cout<<"\nDo you want to give feedback? (y/n)";
    char feedbackChoice;
    cin>>feedbackChoice;
    if (feedbackChoice=='y' || feedbackChoice=='Y')
    {
        saveFeedback();
    }
    else
    {
        cout<<"Thank you for using the Music Recommender!"<<endl;
    }
} 
else
    {
        cout<<"Invalid choice! Please try again."<<endl;
    }
    
}}
void suggestSongs(string mood){
    
    string  language, type, line;
cout << "\n=====================================\n";
    cout << "       SONG RECOMMENDATION SYSTEM\n";
    cout << "=====================================\n";
    cout << "\nEnter Your Mood: ";
    cin >> mood;
    ofstream fout("mood_history.txt", ios::app); //Writing the moods on te file
    fout << mood << endl;
    fout.close();
    // lowercase conversion
    for(int i = 0; i < mood.length(); i++)
    {
        mood[i] = tolower(mood[i]);
    }

    // moods.txt se actual file name lena
    mood = getMoodFile(mood);

    string filename = mood + ".txt";

    ifstream file(filename);

    if(!file)
    {
        cout << "\nMood file not found!\n";
        return;
    }

    cout << "\nChoose Language:\n";
    cout << "hindi\nenglish\nrandom\n";

    cout << "\nEnter Language: ";
    cin >> language;

    cout << "\nChoose Type:\n";
    cout << "90s\nrecent\n";

    cout << "\nEnter Type: ";
    cin >> type;

    // lowercase conversion language
    for(int i = 0; i < language.length(); i++)
    {
        language[i] = tolower(language[i]);
    }

    // lowercase conversion type
    for(int i = 0; i < type.length(); i++)
    {
        type[i] = tolower(type[i]);
    }

    string search = language + " " + type;

    bool found = false;

    while(getline(file, line))
    {
        if(line == search)
        {
            found = true;

            // quote line
            getline(file, line);

            cout << "\n====================================\n";
            cout << line << endl;
            cout << "====================================\n";

            cout << "\nRecommended Songs:\n\n";

            // 3 songs show
            ofstream playlistFile("playlist.txt", ios::app); // add this

for(int i = 0; i < 3; i++)
{
    if(getline(file, line))
    {
        cout << i + 1 << ". " << line << endl;
        playlistFile << line << endl; // save song
    }
}

playlistFile.close(); // close file
            break;
        }
    }

    if(!found)
    {
        cout << "\nNo songs found for this category.\n";
    }

    file.close();

}
string getMoodFile(string mood)
{
    ifstream file("moods.txt");
if(!file)
{
    cout << "moods.txt NOT OPENED!" << endl;
    return mood;
}

    string line;

    while(getline(file, line))
    {
        string key = "";
        string value = "";
        bool foundEqual = false;

        for(int i = 0; i < line.length(); i++)
        {
            if(line[i] == '=')
            {
                foundEqual = true;
                continue;
            }

            // space ignore کرو
            if(line[i] == ' ')
            {
                continue;
            }

            if(foundEqual == false)
            {
                key += line[i];
            }
            else
            {
                value += line[i];
            }
        }

        if(key == mood)
        {
            file.close();
            return value;
        }
    }

    file.close();
    return mood;

}
void showMoodHistory() {

    cout << "\nMood History:\n";
    
    ifstream fin("mood_history.txt");
    string mood;
    while (getline(fin, mood)) {
        cout << "- " << mood << endl;
    }
    fin.close();
}

void showPlaylistHistory() {
    ifstream file("playlist.txt");
    string line;

    if(!file)
    {
        cout << "No playlist history found!\n";
        return;
    }

    cout << "\nPlaylist History:\n";
    
    while (getline(file, line)) {
        cout << "- " << line << endl;
    }

    file.close();
}

void saveFeedback() {
    ofstream file("suggestions.txt");
    string feedback;

    cin.ignore();
    cout << "Enter feedback: ";
    getline(cin, feedback);

    file << feedback << endl;
    file.close();

    cout << "Feedback saved!\n";
}