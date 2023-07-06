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
            std::string line;
            while (getline(userFile, line)) {
                // Each line should exactly be charname:18-digit userid
                std::size_t sepPos = line.find(':');
                if (sepPos != std::string::npos && sepPos != line.size()-1 && line.substr(sepPos+1).size() == 18) {
                    users[line.substr(0, sepPos)] = line.substr(sepPos+1);
                } else {
                    LogDebug("Invalid line format");
                }
            }
            userFile.close();
        } else { err = true; }

        if (!strcasecmp(sep->arg[1], "list")) {                
            if (c->GetGM()) {
                for (auto& user : users) {
                    c->Message(Chat::White, (user.first + ": " + user.second).c_str());
                }
            } else {
                if (users.find(charName) != users.end()) {
                    c->Message(Chat::White, "Your Discord ID is: %s", users[charName].c_str());
                }
            }
        } else if (!strcasecmp(sep->arg[1], "claim")) {           

            if (sep->argnum > 1) { // check that there is a third argument
                
                for (int p = 0; p <= sep->argnum; p++) {
                    LogDebug("Arg %i", p);
                }

                std::string userID(sep->arg[2], strlen(sep->arg[2])); // get the user ID from the third argument
                LogDebug("Got arg: %s (%i digits)", userID.c_str(), userID.size());
                if (userID.size() == 18 && std::all_of(userID.begin(), userID.end(), ::isdigit)) {
                    users[charName] = userID;

                    std::ofstream outfile(filePath, std::ofstream::out);

                    if(outfile.is_open()){
                        for(const auto& user : users){
                            outfile << user.first << ':' << user.second << "\n";
                        }
                        outfile.close();
                    }else{
                        // Error handling
                        LogDebug("Cannot open file to write");
                    }
                } else { err = true; }
            } else { err = true; }
        }         
        else { err = true; }    
    } else { err = true; }
    
    if (err) {
        c->Message(Chat::White,"Usage: #discord [list|claim <18-digit Discord ID>]");
    }
}