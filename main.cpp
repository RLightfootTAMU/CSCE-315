#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

//structs
struct Achievement{
    string gameID;
    int achievementID;
    string achievementName;
    int achievementPoints;
};
struct Game{
    int gameID;
    string gameName;
    vector<Achievement> achievementVector;
};
struct GamePlayed{
    int gameID;
    vector<Achievement> achievementVector;
    string gameName;
    string IGN;
    int achievementCount;
    int maxpoints;
    int currentpoints;
};
struct Player{
    int playerID;
    string playerName;
    int gamerPoints;
    vector<Achievement> achievements;
    vector<int> friendList;
    vector<GamePlayed> gameList;
};

//function prototypes
int getCommand();
void AddPlayer(int playerId, string playerName);
void AddGame(int gameId, string gameName);
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
void printGameDB();
void printPlayerDB();



//Player* findPlayer(int);
vector<Player>::iterator findPlayer(int);
vector<Game>::iterator findGame(int);
vector<Achievement>::iterator findAchievement(int);
Player* globalPtr;

//global data structures
vector<Game> gameDB;        //global game database
vector<Player> playerDB;    //global player database
vector<Achievement> achievementDB;

int main(){
    int temp = 1;
    cout << "enter 'q' at any time to quit the program\n";
    while(temp != 0){
        temp = getCommand();
    }
    //cout << "Please enter a command\n";
    //cin >> tempCommand;
    
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
        //cin >> tempS1;
        AddPlayer(tempInt1, tempS2);
        return 1;
    }
    else if(tempCommand == "AddGame"){
        cin >> tempInt1;
        //cin >> tempS1;
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
        //cin >> tempS3;
        cin >> tempInt3;
        AddAchievement(tempInt1, tempInt2, tempS2, tempInt3);
        return 1;
    }
    else if(tempCommand == "Plays"){
        cin >> tempInt1;
        cin >> tempInt2;
        //getline(cin, tempS1, '"');
        getline(cin, tempS1);
        //cin >> tempS2;
        Plays(tempInt1, tempInt2, tempS1);
        return 1;
    }
    else if(tempCommand == "AddFriends"){
        cin >> tempInt1;
        cin >> tempInt2;
        //AddFriends(tempInt1, tempInt2);
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
    else if(tempCommand == "PrintGames"){
        printGameDB();
        return 1;
    }
    else if(tempCommand == "PrintPlayers"){
        printPlayerDB();
        return 1;
    }
    else if(tempCommand == "Find"){
        cin >> tempInt1;
        //Player* pptr = findPlayer(tempInt1);
        findPlayer(tempInt1);
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
    //cout << "The Player name is " << p1.playerName << "\n";
    playerDB.push_back(p1);
}

void AddGame(int gID, string gName){
    Game g1;
    g1.gameID = gID;
    g1.gameName = gName;
    gameDB.push_back(g1);
}

void AddAchievement(int gID, int aID, string aName, int aPoints){
    Achievement a1;
    a1.gameID = gID;
    a1.achievementID = aID;
    a1.achievementName = aName;
    a1.achievementPoints = aPoints;
    cout << "Game id: " << gID << "\n";
    vector<Game>::iterator it;
    it = findGame(gID);
    it->achievementVector.push_back(a1);
    achievementDB.push_back(a1);
    //cout << "A name is: " << aName << "\n";
    //cout << "A points is: " << aPoints << "\n";
}

void Plays(int pID, int gID, string iGN){
    vector<Player>::iterator it;
    it = findPlayer(pID);
    GamePlayed gp1;
    gp1.IGN = iGN;
    gp1.achievementCount = 0;
    gp1.gameID = gID;
    it->gameList.push_back(gp1);
    //search player db for pID, pushback players game vector
}

void AddFriends(int pID1, int pID2){
    vector<Player>::iterator it1, it2;
    it1 = findPlayer(pID1);
    it2 = findPlayer(pID2);
    it1->friendList.push_back(pID2);
    it2->friendList.push_back(pID1);
    //search player  db for pIDs, add other pid to friend list
}

void Achieve(int pID, int gID, int aID){
    vector<Player>::iterator playerit;
    vector<Achievement>::iterator ait;
    ait = findAchievement(aID);
    Achievement a1 = *ait;
    playerit->achievements.push_back(a1);
    playerit->gamerPoints = (playerit->gamerPoints) + (ait->achievementPoints);
    //search playerdb for player, add achievement to the achievement vector
}

void FriendsWhoPlay(int pID, int gID){
   // Player* ptr = findPlayer(pID);
   /* vector<Player>::iterator p1;
    p1 = findPlayer(pID);
    vector<int>::iterator it1;
    vector<int>::iterator it2;
    vector<Player>::iterator p2;
    it1 = p1->friendList.begin();
    while(it1 != p1->friendList.end()){
        int temporary = *it1;
        p2 = findPlayer(temporary);
        it2 = p2->gameList.begin();
        while(it2 != p2->gameList.end()){
            if(*it2 == gID)
                cout << "Player ID: " << p2->playerID << " plays the game\n";
            it2++;
        }
        it1++;
    }*/
   
    //get players friendlist & cross-references for the specified gameID
}

void ComparePlayers(int pID1, int pID2, int gID){
    //compare players records and scores for the given game
}

void SummarizePlayer(int pID){
    //report the players friends, games they play, and point totals
    vector<Player>::iterator it;
    it = findPlayer(pID);
    cout << "Player: " << it->playerName << "\n";
    cout << "Total Gamerscore: " << it->gamerPoints << "\n";
    cout << "Game \t Achievements \t Gamerscore \t IGN\n";
    vector<GamePlayed>::iterator git;
    git = it->gameList.begin();
    while(git != gameList.end()){
        cout << git->gameName << "\t";
        
        git++;
    }
}

void SummarizeGame(int gID){
    //report nummber of players playing the specified game and the achievement totals
}

void SummarizeAchievement(int gID, int aID){
    
}

//Player* findPlayer(int pID){
vector<Player>::iterator findPlayer(int pID){
    vector<Player>::iterator it;
    it = playerDB.begin();
    while(it != playerDB.end()){
        if(it->playerID == pID){
            Player* found;
            //found = *it;
            //*found = *it;
            //*globalPtr = *it;
            cout << "Player was found\n";
            return it;
            //return globalPtr;
        }
        it++;
    }
    cout << "player not found \n";
    //return NULL;
}

vector<Game>::iterator findGame(int gID){
    vector<Game>::iterator it;
    it = gameDB.begin();
    while(it != gameDB.end()){
        if(it->gameID == gID){
            //Game *found;
            //*found = *it;
            return it;
        }
        ++it;
    }
    cout << "game not found \n";
    //return NULL;
}

vector<Achievement>::iterator findAchievement(int aID){
    vector<Achievement>::iterator it;
    it = achievementDB.begin();
    while(it != achievementDB.end()){
        if(it->achievementID == aID){
            //Achievement *found;
            //*found = *it;
            return it;
        }
        ++it;
    }
    cout << "achievement not found \n";
}

void printGameDB(){
    vector<Game>::iterator it;
    it = gameDB.begin();
    while(it != gameDB.end()){
        cout << "Name: " << it->gameName << "--------" << " Game id: " << it->gameID << "\n";
        ++it;
    }
    //cout << "Name: " << it->gameName << "--------" << " Game id: " << it->gameID << "\n";
    return;
}

void printPlayerDB(){
    vector<Player>::iterator it;
    it = playerDB.begin();
    while(it != playerDB.end()){
        cout << "Name: " << it->playerName << "--------" << " Player id: " << it->playerID << "\n";
        ++it;
    }
    //cout << "Name: " << it->gameName << "--------" << " Game id: " << it->gameID << "\n";
    return;
}
