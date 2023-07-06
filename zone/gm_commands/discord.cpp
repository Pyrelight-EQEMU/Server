#include "../client.h"
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>

//userid:charactername
void command_discord(Client *c, const Seperator *sep)
{
    std::string filePath = "../users.txt";
    std::vector<std::string> lines;

    // Obtain character name
    std::string characterName = c->GetCleanName();

    // Check if the second argument exists
    if (sep->argnum >= 2) {
        // Obtain user ID from the second argument
        std::string userId = sep->arg[1];

        // Check if the user ID is an 18-digit number
        if (userId.size() == 18 && std::all_of(userId.begin(), userId.end(), ::isdigit)) {
            std::ifstream infile(filePath);

            if (infile.is_open()) {
                std::string line;

                // Read all lines
                while (getline(infile, line)) {
                    // Only add lines that do not contain the characterName
                    if (line.find(characterName) == std::string::npos) {
                        lines.push_back(line);
                    }
                }

                infile.close();
            } else {
                c->Message(Chat::White, "Unable to open file for reading");
                return;
            }

            // Add the new line
            lines.push_back(userId + ":" + characterName);

            std::ofstream outfile(filePath);

            if (outfile.is_open()) {
                // Write all lines
                for (const auto& line : lines) {
                    outfile << line << "\n";
                }

                outfile.close();
            } else {
                c->Message(Chat::White, "Unable to open file for writing");
                return;
            }
        } else {
            c->Message(Chat::White,"Invalid user ID. It should be an 18-digit number");
            return;
        }
    } else {
        c->Message(Chat::White,"Invalid command format. Expected <command> <userId>");
        return;
    }

    c->Message(Chat::White,"Hello, world!");
}
