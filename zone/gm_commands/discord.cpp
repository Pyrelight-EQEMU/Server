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

        std::unordered_map<std::string, std::string> users; // Hold charname:userid pairs

        if (!strcasecmp(sep->arg[1], "claim") || !strcasecmp(sep->arg[1], "list")) {
            LogDebug("Got valid command");

            // Read the file and load everything into the data structure
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

                if (!strcasecmp(sep->arg[1], "list")) {
                    // Print all users
                    for (auto& user : users) {
                        c->Message(Chat::White, user.first + ": " + user.second);
                    }
                }
            } else {
                c->Message(Chat::White, "Unable to open file");
            }
        } else { err = true; }    
    } else { err = true; }
    
    if (err) {
        c->Message(Chat::White,"Usage: #discord [list|claim <18-digit Discord ID>]");
    }
}
