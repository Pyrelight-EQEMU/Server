#include "../client.h"

void command_mystats(Client *c, const Seperator *sep)
{
	Mob* t = c;
	if (c->GetTarget()) {
		t = c->GetTarget();
	}

	if (
		(t->IsPet() && t == c->GetPet()) ||
		(t->IsBot() && t->CastToBot()->GetOwner() && t->CastToBot()->GetOwner() == c)
	) {
		t->ShowStats(c);


		// Pyrelight Custom Code - Ugly hack to look at pet equipment
		
		for (int i = EQ::invslot::EQUIPMENT_BEGIN; i <= EQ::invslot::EQUIPMENT_END; i++) {
			
			const EQ::ItemInstance *inst_main = nullptr;
			const EQ::ItemInstance *inst_sub  = nullptr;
			const EQ::ItemInstance *inst_aug  = nullptr;
			const EQ::ItemData     *item_data = nullptr;

			EQ::SayLinkEngine linker;
			linker.SetLinkType(EQ::saylink::SayLinkItemInst);

			inst_main = t->GetInvPublic().GetItem(i);
			
			if (inst_main) {
				item_data  = inst_main->GetItem();
				linker.SetItemInst(inst_main);
			} else {
				item_data = nullptr;
				LogDebug("Didn't find an item in slot %i", i);
			}
			

			if (item_data) {
				std::string padded_slot_name = fmt::format("{:<10}", EQ::invslot::GetInvPossessionsSlotName(i));
				std::replace(padded_slot_name.begin(), padded_slot_name.end(), ' ', '_');

				c->Message(
					Chat::White,
					fmt::format(
						"Slot {} | {} ({})",
						padded_slot_name,
						linker.GenerateLink(),
						item_data->ID
					).c_str()
				);
			}
		}

		return;
	}

	c->ShowStats(c);
}