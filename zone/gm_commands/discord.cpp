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
            c->Message(Chat::White, "ok, try this? [{}], [{}]", sep->arg[1], sep->arg[2]);
        }         
        else { err = true; }    
    } else { err = true; }
    
    if (err) {
        c->Message(Chat::White,"Usage: #discord [list|claim <18-digit Discord ID>]");
    }
}