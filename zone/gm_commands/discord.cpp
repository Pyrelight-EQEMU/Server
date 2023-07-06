#include "../client.h"
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>

//userid:charactername

//Usage: #discord [list|claim <18-digit Discord ID>] 
void command_discord(Client *c, const Seperator *sep)
{
    std::string filePath = "users.txt";
    std::vector<std::string> lines;

    // Check if there's at least one argument
    if (sep->argnum >= 2) {
        std::string command = sep->arg[1];
        LogDebug(command);
        if (command == "list") {
            std::ifstream infile(filePath);

            if (infile.is_open()) {
                std::string line;

                if (c->GetGM()) {
                    // Read and print all lines
                    while (getline(infile, line)) {
                        c->Message(Chat::White, line.c_str());
                    }
                } else {
                    // Obtain character name
                    std::string characterName = c->GetCleanName();
                    // print only our character's ID
                    while (getline(infile, line)) {
                        if (line.find(characterName) != std::string::npos) {
                            c->Message(Chat::White, line.c_str());
                            break;
                        }
                    }
                }

                infile.close();
            } else {
                c->Message(Chat::White, "Unable to open file for reading");
            }
        } else if (command == "claim") {
            // Obtain character name
            std::string characterName = c->GetCleanName();

            if (sep->argnum >= 2) {
                // Obtain user ID from the second argument
                std::string userId = sep->arg[2];

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

                    c->Message(Chat::White,"Character claimed successfully!");
                } else {
                    c->Message(Chat::White,"Invalid user ID. It should be an 18-digit number");
                }
            } else {
                c->Message(Chat::White,"Invalid command format. Expected claim <userId>");
            }
        } else {
            c->Message(Chat::White, "Invalid command format. Expected list or claim <userId>");
        }
    } else {
        c->Message(Chat::White,"Invalid command format. Expected #discord [list|claim <userId>]");
    }
}
