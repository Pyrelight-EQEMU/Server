#include "../client.h"
#include <fstream>

void command_discord(Client *c, const Seperator *sep)
{
    std::ofstream outfile;
    outfile.open("../users.txt", std::ios_base::app); // append instead of overwrite

    if (!outfile) {
        c->Message(Chat::White,"Unable to open file");
        return; // return if the file failed to open
    }

    outfile << "This is a new line of text to be added\n";
    outfile.close();

    c->Message(Chat::White,"Hello, world!");
}
