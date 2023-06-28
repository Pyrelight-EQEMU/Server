#include "../client.h"
#include <map>
#include <functional>

void command_filterheroic(Client *c, const Seperator *sep)
{
    const auto arguments = sep->argnum;
    if (!arguments) {
        c->Message(Chat::White, "Command Syntax: #[filterheroic] - [str|sta|dex|agi|int|wis|cha|all] [on|off] - Set the visibility of additional info about heroic stat effects.");
        return;
    } 

    std::map<std::string, std::string> statMap = {
        {"str", "filter_hSTR"},
        {"sta", "filter_hSTA"},
        {"dex", "filter_hDEX"},
        {"agi", "filter_hAGI"},
        {"int", "filter_hINT"},
        {"wis", "filter_hWIS"},
        {"cha", "filter_hCHA"},
        {"pet", "filter_hPets"},
    };
	std::string flagSuffix = Strings::ToLower(sep->arg[2]);

    if (Strings::ToLower(sep->arg[1]) == "all") {
		if (flagSuffix != "on" && flagSuffix != "off") {
			c->Message(Chat::White, "Error: You must specify [on|off] for [all] command.");
			return;
		}

        for (auto& stat : statMap) {
            if (stat.second != "filter_hPets") {
                c->SetAccountFlag(stat.second, flagSuffix);
            }
        }
    } else {
        auto statIt = statMap.find(Strings::ToLower(sep->arg[1]));
        if (statIt != statMap.end()) {
            c->SetAccountFlag(statIt->second, flagSuffix);
        } else {
            c->Message(Chat::White, "Command Syntax: #[filterheroic] - [str|sta|dex|agi|int|wis|cha|all] [on|off] - Set the visibility of additional info about heroic stat effects.");
        }
    }
}
