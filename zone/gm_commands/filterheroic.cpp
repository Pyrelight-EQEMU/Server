#include "../client.h"
#include <map>
#include <functional>

void command_filterheroic(Client *c, const Seperator *sep)
{
	const auto arguments = sep->argnum;
    if (!arguments) {
        c->Message(Chat::White, "Command Syntax: #[filterheroic] - [str|sta|dex|agi|int|wis|cha] - Toggle the visibility of additional info about heroic stat effects.");
        return;
    } else {
        auto arg = Strings::ToLower(sep->argplus[1]);

        std::map<std::string, std::function<void()>> statMap = {
            {"str", [](){ /* handle case STR */ }},
            {"sta", [](){ /* handle case STA */ }},
            {"dex", [](){ /* handle case DEX */ }},
            {"agi", [](){ /* handle case AGI */ }},
            {"int", [](){ /* handle case INT */ }},
            {"wis", [](){ /* handle case WIS */ }},
            {"cha", [](){ /* handle case CHA */ }}
        };

        auto statFunction = statMap.find(arg);

        if (statFunction != statMap.end()) {
            statFunction->second();
        } else {
            c->Message(Chat::White, "Command Syntax: #[filterheroic] - [str|sta|dex|agi|int|wis|cha] - Toggle the visibility of additional info about heroic stat effects.");
        }
    }
}