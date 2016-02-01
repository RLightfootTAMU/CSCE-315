#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

//structs
struct Achievement{
    int gameID;
    int achievementID;
    string achievementName;
    int achievementPoints;
    int timesAchieved;
    vector<int> PlayersWithAchievement;
};
struct Game{
    int gameID;
    string gameName;
    string IGN;
    int currentScore;
    vector<Achievement> achievementVector;
    vector<int> peopleThatPlay;
};
struct Player{
    int playerID;
    string playerName;
    int gamerPoints;
    vector<Achievement> achievements;
    vector<Game> inGameNames;
    vector<Game> gameScores;
    vector<int> friendList;
    vector<int> gameList;
};

//function prototypes
int getCommand();
void AddPlayer(int, string);
void AddGame(int, string);
void AddAchievement(int, int, string, int);
void Plays(int, int, string);
void AddFriends(int, int);
void Achieve(int, int, int);
void FriendsWhoPlay(int, int);
void ComparePlayers(int, int, int);
void SummarizePlayer(int);
void SummarizeGame(int);
void SummarizeAchievement(int, int);
void AchievementRanking();
//extra functions to help my program
vector<Player>::iterator findPlayer(int);
vector<Game>::iterator findGame(int);
vector<Achievement>::iterator findAchievement(int, int);

//global data structures
vector<Game> gameDB;        //global game database
vector<Player> playerDB;    //global player database

int main(){
    int temp = 1;
    cout << "enter 'q' at any time to quit the program\n";
    while(temp != 0){
        temp = getCommand();
    }
}

int getCommand(){
    string tempCommand;
    int tempInt1;
    int tempInt2;
    int tempInt3;
    string tempS1;
    string tempS2;
    string tempS3;
    string tempS4;
    
    cin >> tempCommand;
    if(tempCommand == "q"){
        return 0;
    }
    else if(tempCommand == "AddPlayer"){
        cin >> tempInt1;
        getline(cin, tempS1, '"');
        getline(cin, tempS2, '"');
        AddPlayer(tempInt1, tempS2);
        return 1;
    }
    else if(tempCommand == "AddGame"){
        cin >> tempInt1;
        getline(cin, tempS1, '"');
        getline(cin, tempS2, '"');
        AddGame(tempInt1, tempS2);
        return 1;
    }
    else if(tempCommand == "AddAchievement"){
        cin >> tempInt1;
        cin >> tempInt2;
        getline(cin, tempS1, '"');
        getline(cin, tempS2, '"');
        cin >> tempInt3;
        AddAchievement(tempInt1, tempInt2, tempS2, tempInt3);
        return 1;
    }
    else if(tempCommand == "Plays"){
        cin >> tempInt1;
        cin >> tempInt2;
        getline(cin, tempS1);
        Plays(tempInt1, tempInt2, tempS1);
        return 1;
    }
    else if(tempCommand == "AddFriends"){
        cin >> tempInt1;
        cin >> tempInt2;
        AddFriends(tempInt1, tempInt2);
        return 1;
    }
    else if(tempCommand == "Achieve"){
        cin >> tempInt1;
        cin >> tempInt2;
        cin >> tempInt3;
        Achieve(tempInt1, tempInt2, tempInt3);
        return 1;
    }
    else if(tempCommand == "FriendsWhoPlay"){
        cin >> tempInt1;
        cin >> tempInt2;
        FriendsWhoPlay(tempInt1, tempInt2);
        return 1;
    }
    else if(tempCommand == "ComparePlayers"){
        cin >> tempInt1;
        cin >> tempInt2;
        cin >> tempInt3;
        ComparePlayers(tempInt1, tempInt2, tempInt3);
        return 1;
    }
    else if(tempCommand == "SummarizePlayer"){
        cin >> tempInt1;
        SummarizePlayer(tempInt1);
        return 1;
    }
    else if(tempCommand == "SummarizeGame"){
        cin >> tempInt1;
        SummarizeGame(tempInt1);
        return 1;
    }
    else if(tempCommand == "SummarizeAchievement"){
        cin >> tempInt1;
        cin >> tempInt2;
        SummarizeAchievement(tempInt1, tempInt2);
        return 1;
    }
    else if(tempCommand == "AchievementRanking"){
        AchievementRanking();
        return 1;
    }
    else {
        cout << "sorry, that's not a valid command\n";
        return 1;
    }
}

void AddPlayer(int pID, string pName){
    Player p1;
    p1.playerID = pID;
    p1.playerName = pName;
    p1.gamerPoints = 0;
    playerDB.push_back(p1);
}

void AddGame(int gID, string gName){
    Game g1;
    g1.gameID = gID;
    g1.gameName = gName;
    gameDB.push_back(g1);
}

void AddAchievement(int gID, int aID, string aName, int aPoints){
    //create achievement object from given vals and push into the respective game's achievement vector 
    Achievement a1;
    a1.gameID = gID;
    a1.achievementID = aID;
    a1.achievementName = aName;
    a1.achievementPoints = aPoints;
    a1.timesAchieved = 0;
    vector<Game>::iterator git;
    git = findGame(gID);
    git->achievementVector.push_back(a1);
}

void Plays(int pID, int gID, string iGN){
    //search player db for pID & gID, pushback players record vectors
    vector<Player>::iterator pit;
    vector<Game>::iterator git;
    pit = findPlayer(pID);
    git = findGame(gID);
    Game g1;
    g1.IGN = iGN;
    g1.gameID = gID;
    Game g2;
    g2.gameID = gID;
    g2.currentScore = 0;
    pit->gameList.push_back(gID);
    pit->inGameNames.push_back(g1);
    pit->gameScores.push_back(g2);
    vector<int>::iterator it = git->peopleThatPlay.begin();
    while(it != git->peopleThatPlay.end()){
        if(pID == *it){
            cout << "Holllllleee up, mannnnnnnnnnnnn\n";
            break;
        }
        it++;
    }
    git->peopleThatPlay.push_back(pID);
}

void AddFriends(int pID1, int pID2){
    //search player db for pIDs, pushback players respective friend vectors with the other players pID
    vector<Player>::iterator it1, it2;
    it1 = findPlayer(pID1);
    it2 = findPlayer(pID2);
    it1->friendList.push_back(pID2);
    it2->friendList.push_back(pID1);
}

void Achieve(int pID, int gID, int aID){
    //search player db for pID, create achievement object and update the players record by pushing the achievement vector and updating points
    vector<Player>::iterator playerit;
    vector<Achievement>::iterator ait;
    ait = findAchievement(aID, gID);
    Achievement a1 = *ait;
    playerit = findPlayer(pID);
    playerit->achievements.push_back(a1);
    playerit->gamerPoints = (playerit->gamerPoints) + (ait->achievementPoints);
    ait->PlayersWithAchievement.push_back(pID);
    ait->timesAchieved = (ait->timesAchieved)+1;
    vector<Game>::iterator git = playerit->gameScores.begin();
    while(git != playerit->gameScores.end()){
        if(git->gameID == gID)
           git->currentScore = (git->currentScore)+(ait->achievementPoints); 
        git++;
    }
}

void FriendsWhoPlay(int pID, int gID){
    //search player db for pIDs, cross-reference for the other pID and print when found
    vector<Player>::iterator p1;
    p1 = findPlayer(pID);
    vector<int>::iterator it1;
    vector<int>::iterator it2;
    vector<Player>::iterator p2;
    vector<Game>::iterator git = findGame(gID);
    cout << "\nGame Name: " << git->gameName << "\n";
    it1 = p1->friendList.begin();
    while(it1 != p1->friendList.end()){
        int temporary = *it1;
        p2 = findPlayer(temporary);
        it2 = p2->gameList.begin();
        while(it2 != p2->gameList.end()){
            if(*it2 == gID)
                cout << "Player ID: " << p2->playerID << "\tPlayer name: " << p2->playerName << " plays the game\n";
            it2++;
        }
        it1++;
    }
    cout << "\n";
}

void ComparePlayers(int pID1, int pID2, int gID){
    //find player1 and iterate through their records in order to print the necessary info, then do it again for player 2
    vector<Player>::iterator p1 = findPlayer(pID1);
    vector<Player>::iterator p2 = findPlayer(pID2);
    vector<Game>::iterator g1 = findGame(gID);
    cout << "\nGame name: " << g1->gameName << "\n";
    cout << "------------------\nPlayer 1 Record:\n";
    cout << "Gamerscore: ";
    g1 = p1->gameScores.begin();
    while(g1 != p1->gameScores.end()){
        if(g1->gameID == gID)
            cout << g1->currentScore;
        g1++;
    }
    cout << "\n------------------\nAchievements: \n";
    vector<Achievement>::iterator a1 = p1->achievements.begin();
    while(a1 != p1->achievements.end()){
        if(a1->gameID == gID)
            cout << a1->achievementName << "\n";
        a1++;
    }
    cout << "\nPlayer 2 Record:\n";
    cout << "Gamerscore: ";
    g1 = p2->gameScores.begin();
    while(g1 != p2->gameScores.end()){
        if(g1->gameID == gID)
            cout << g1->currentScore;
        g1++;
    }
    cout << "\n------------------\nAchievements: \n";
    a1 = p2->achievements.begin();
    while(a1 != p2->achievements.end()){
        if(a1->gameID == gID)
            cout << a1->achievementName << "\n";
        a1++;
    }
    cout << "\n";
}

void SummarizePlayer(int pID){
    //Find the player, then use iterators to print the neccessary information from their record
    vector<Player>::iterator pit;
    vector<Player>::iterator ptemp;
    vector<Game>::iterator temp;
    vector<Game>::iterator igns;
    pit = findPlayer(pID);
    cout << "Player: " << pit->playerName << "\n------------------\n";
    cout << "Total Gamerscore: " << pit->gamerPoints << "\n";
    vector<Game>::iterator git = pit->gameScores.begin();
    while(git != pit->gameScores.end()){
        temp = findGame(git->gameID);
        cout << "Game: " << temp->gameName << "\tpoints: " << git->currentScore << "\tin-game name: ";
        igns = pit->inGameNames.begin();
        while(igns != pit->inGameNames.end()){
            if(igns->gameID == temp->gameID)
                cout << igns->IGN;
            igns++;
        }
        cout << "\n";
        git++;
    }
    cout << "------------------\nFriends: \n";
    vector<int>::iterator friendit = pit->friendList.begin();
    while(friendit != pit->friendList.end()){
        ptemp = findPlayer(*friendit);
        cout << "Name: " << ptemp->playerName << "\tGamerscore: " << ptemp->gamerPoints << "\n";
        friendit++;
    }
    cout << "\n";
}

void SummarizeGame(int gID){
    //use the game database to locate the game. Use the achievement vector and the people who play vectors to print the players and achievements for the specified game
    vector<Game>::iterator git = findGame(gID);
    vector<Player>::iterator pit;
    vector<Achievement>::iterator ait;
    vector<int>::iterator it = git->peopleThatPlay.begin();
    cout << "\nGame Name: " << git->gameName << "\n------------------\n";
    cout << "Players: \n";
    while(it != git->peopleThatPlay.end()){
        pit = findPlayer(*it);
        cout << pit->playerName << " played the game\n";
        it++;
    }
    cout <<  "------------------\n";
    ait = git->achievementVector.begin();
    while(ait != git->achievementVector.end()){
        cout << "Achievement: " << ait->achievementName << " completed " << ait->timesAchieved << " times\n";
        ait++;
    }
    cout << "\n";
}

void SummarizeAchievement(int gID, int aID){
    //use the gameDB vector along with counter variales to count the players both playing the game and who have achieved the specified achievement as they are printed
    int counter1 = 0;
    int counter2 = 0;
    double percentage;
    vector<Achievement>::iterator it;
    vector<Player>::iterator pit;
    vector<Game>::iterator git = findGame(gID);
    it = findAchievement(aID, gID);
    cout << "\nAchievement Name: " << it->achievementName << "\n------------------\n" << "Players who have the Achievement: \n";
    vector<int>::iterator it2 = it->PlayersWithAchievement.begin();
    while (it2 != it->PlayersWithAchievement.end()){
        counter1++;
        cout << counter1 << " ";
        pit = findPlayer(*it2);
        cout << pit->playerName << "\n";
        it2++;
    }
    cout << "------------------\npercentage of players who played with achievement: ";
    vector<int>::iterator it3 = git->peopleThatPlay.begin();
    while (it3 != git->peopleThatPlay.end()){
        counter2++;
        it3++;
    }
    percentage = (counter1*100)/counter2;
    cout << percentage << " percent\n\n";
}

void AchievementRanking(){
    //Copy the playerDB vector and delete the highest entry as it is printed until the copied vector is empty
    cout << "\n";
    vector<Player>::iterator current;
    vector<Player>::iterator high;
    int temp, temphigh, index;
    index = 0;
    vector<Player> playerDBcopy = playerDB; 
    while(playerDBcopy.begin() != playerDBcopy.end()){
        index++;
        current = playerDBcopy.begin();
        high = playerDBcopy.begin();
        current++;
        while(current != playerDBcopy.end()){
            if(current->gamerPoints > high->gamerPoints)
                high = current;
            current++;
        }
        cout << index << " Name: " << high->playerName << "\tGamerpoints: " << high->gamerPoints << "\n";
        playerDBcopy.erase(playerDBcopy.begin());
    }
    cout << "\n";
}

vector<Player>::iterator findPlayer(int pID){
    //extra function to locate a player in the playerDB given pID
    vector<Player>::iterator it;
    it = playerDB.begin();
    while(it != playerDB.end()){
        if(it->playerID == pID){
            return it;
        }
        it++;
    }
    cout << "player not found \n";
}

vector<Game>::iterator findGame(int gID){
    //extra function to locate a game in the gameDB given gID
    vector<Game>::iterator it;
    it = gameDB.begin();
    while(it != gameDB.end()){
        if(it->gameID == gID){
            return it;
        }
        ++it;
    }
    cout << "game not found \n";
}

vector<Achievement>::iterator findAchievement(int aID, int gID){
    //extra function to locate an achievement in the gameDB given both the aID and gID
    vector<Achievement>::iterator it;
    vector<Game>::iterator git = findGame(gID);
    it = git->achievementVector.begin();
    while(it != git->achievementVector.end()){
        if(it->achievementID == aID){
            return it;
        }
        ++it;
    }
    cout << "achievement not found \n";
}
