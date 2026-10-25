TillbrookTown_House4_MapScripts::
	.byte 0

TillbrookTown_House4_EventScript_Farmer::
	lock
	faceplayer
	goto_if_set FLAG_TILLBROOK_RECEIVED_MIRACLE_SEED, TillbrookTown_House4_EventScript_SeedAdvice
	msgbox TillbrookTown_House4_Text_TakeSeed, MSGBOX_DEFAULT
	giveitem ITEM_MIRACLE_SEED
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_TILLBROOK_RECEIVED_MIRACLE_SEED
TillbrookTown_House4_EventScript_SeedAdvice:
	msgbox TillbrookTown_House4_Text_SeedAdvice, MSGBOX_DEFAULT
	release
	end

TillbrookTown_House4_Text_TakeSeed:
	.string "My fields grow better with Grass\n"
	.string "Pokémon around. Take this.$"

TillbrookTown_House4_Text_SeedAdvice:
	.string "A held Miracle Seed boosts the power\n"
	.string "of Grass-type moves.\p"
	.string "Help your Pokémon put down roots!$"
