#include "../client.h"
#include <map>
#include <functional>

void command_filterheroic(Client *c, const Seperator *sep)
{
	const auto arguments = sep->argnum;
    if (!arguments) {
        c->Message(Chat::White, "Command Syntax: #[filterheroic] - [str|sta|dex|agi|int|wis|cha] [on|off (optional)] - Set or toggle the visibility of additional info about heroic stat effects.");
        return;
    } else {
		LogDebug("[{}] [{}] [{}]", sep->argplus[0], sep->argplus[1], sep->argplus[2]);

        std::map<std::string, std::function<void()>> statMap = {
            {"str", [&](){ 
				if (Strings::ToLower(sep->argplus[2]) == "on") {
					c->SetAccountFlag("filter_hSTR", "true");
				} 
				if (Strings::ToLower(sep->argplus[2]) == "off") {
					c->SetAccountFlag("filter_hSTR", "false");
				}
            }},
            {"sta", [](){ /* handle case STA */ }},
            {"dex", [](){ /* handle case DEX */ }},
            {"agi", [](){ /* handle case AGI */ }},
            {"int", [](){ /* handle case INT */ }},
            {"wis", [](){ /* handle case WIS */ }},
            {"cha", [](){ /* handle case CHA */ }}
        };

        auto statFunction = statMap.find(Strings::ToLower(sep->arg[1]));

        if (statFunction != statMap.end()) {
            statFunction->second();
        } else {
            c->Message(Chat::White, "Command Syntax: #[filterheroic] - [str|sta|dex|agi|int|wis|cha] [on|off (optional)] - Set or toggle the visibility of additional info about heroic stat effects.");
        }
    }
}