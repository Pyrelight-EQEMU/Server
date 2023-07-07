#include "../client.h"
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

//userid:charactername

//Usage: #discord [list|claim <18-digit Discord ID>]
// arg[0] is 'discord', arg[1] is list\claim 
void command_discord(Client *c, const Seperator *sep)
{   
    bool err = false;

    if (sep->argnum) {
        auto filePath = "users.txt";
        auto charName = c->GetCleanName();
        auto command  = sep->arg[1];

        std::unordered_map<std::string, std::string> users;
        std::ifstream userFile(filePath);
        if (userFile.is_open()) {
            LogDebug("Trying to load users.txt...");
            std::string line;
            while (getline(userFile, line)) { 
                LogDebug("Trying to load a line...");               
                std::size_t sepPos = line.find(':');
                if (sepPos != std::string::npos && sepPos != line.size()-1 && line.substr(0, sepPos).size() == 18) {
                    
                    auto discordID = line.substr(0, sepPos);
                    auto charName = line.substr(sepPos+1);

                    users[charName] = discordID;
                    LogDebug("Loading from file - charName: [{}] discordID [{}]", charName, discordID);
                } else {
                    LogDebug("Corrupted Data in users.txt");
                }
            }
            userFile.close();
        } else { err = true; }

        if (!strcasecmp(sep->arg[1], "list")) {                
            if (c->GetGM()) {
                for (auto& user : users) {
                    c->Message(Chat::White, (user.second + ": " + user.first).c_str());
                }
            } else {
                if (users.find(charName) != users.end()) {
                    c->Message(Chat::White, "Your Discord UserID is: %s", users[charName].c_str());
                } else { c->Message(Chat::White, "You have not set your Discord UserID."); }
            }
        } else if (!strcasecmp(sep->arg[1], "claim")) {
            if (sep->argnum > 1) {
                std::string userID(sep->arg[2]);
                if (userID.size() == 18 && std::all_of(userID.begin(), userID.end(), ::isdigit)) {
                    users[charName] = userID;
                    if (!DiscordWriteFile(users, filePath)) {
                        err = true;
                        c->Message(Chat::Red, "Unable to set Discord UserID.");
                    } else { c->Message(Chat::White, "Your Discord UserID is: %s", users[charName].c_str()); }                  
                } else { 
                    c->Message(Chat::White, "Invalid Discord UserID format. It should be exactly 18 numerical digits.");
                    err = true; 
                }
            } else { err = true; }
        } else if (!strcasecmp(sep->arg[1], "set") && c->GetGM()) {
            if (sep->argnum > 2) {
                std::string userID(sep->arg[3]);
                std::string charName(sep->arg[2]);
                if (userID.size() == 18 && std::all_of(userID.begin(), userID.end(), ::isdigit)) {
                    users[charName] = userID;
                    if (!DiscordWriteFile(users, filePath)) {
                        err = true;
                        c->Message(Chat::Red, "Unable to set Discord UserID.");
                    } else { c->Message(Chat::White, "CharName: %s UserID: %s", charName.c_str(), users[charName].c_str()); }                    
                } else { 
                    c->Message(Chat::White, "Invalid Input. You should know how to use this.");
                    err = true; 
                }
            }      
        } else { err = true; }    
    } else { err = true; }
    
    if (err) {
        c->Message(Chat::White,"Usage: #discord [list|claim <18-digit Discord ID>]");
    }
}

bool DiscordWriteFile(const std::unordered_map<std::string, std::string>& users, const std::string& filePath) {
    std::ofstream outfile(filePath, std::ofstream::out);

    if(outfile.is_open()){
        for(const auto& user : users){
            outfile << user.second.c_str() << ':' << user.first.c_str() << "\n";
        }
        outfile.close();
        return true;
    }else{
        // Error handling
        LogDebug("Cannot open file to write");
        return false;
    }
}
