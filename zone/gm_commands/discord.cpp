#include "../client.h"
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>

//userid:charactername

//Usage: #discord [list|claim <18-digit Discord ID>]
// arg[0] is 'discord', arg[1] is list\claim 
void command_discord(Client *c, const Seperator *sep)
{   
    bool err = false;

    if (sep->argnum) {
        auto filePath = "users.txt";
        auto charName = c->GetCleanName();
        auto command  - sep->arg[1];
        
        if (strcasecmp(sep->arg[1], "claim") || strcasecmp(sep->arg[1], "list")) {
            LogDebug("Got valid command");

        } else { err = true; }

    
    } else { err = true ;}
    
    if (err) {
        c->Message(Chat::White,"Usage: #discord [list|claim <18-digit Discord ID>]");
    }
}
