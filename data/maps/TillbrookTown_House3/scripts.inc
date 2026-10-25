TillbrookTown_House3_MapScripts::
	.byte 0

TillbrookTown_House3_EventScript_Fisherman::
	lock
	faceplayer
	goto_if_set FLAG_TILLBROOK_RECEIVED_OLD_ROD, TillbrookTown_House3_EventScript_FishingAdvice
	msgbox TillbrookTown_House3_Text_TakeRod, MSGBOX_DEFAULT
	checkitem ITEM_OLD_ROD
	goto_if_eq VAR_RESULT, TRUE, TillbrookTown_House3_EventScript_AlreadyHasRod
	giveitem ITEM_OLD_ROD
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
TillbrookTown_House3_EventScript_AlreadyHasRod:
	setflag FLAG_TILLBROOK_RECEIVED_OLD_ROD
TillbrookTown_House3_EventScript_FishingAdvice:
	msgbox TillbrookTown_House3_Text_FishingAdvice, MSGBOX_DEFAULT
	release
	end

TillbrookTown_House3_Text_TakeRod:
	.string "A good farmer knows the river, too!\p"
	.string "Take this Old Rod and try fishing\n"
	.string "from the riverbank.$"

TillbrookTown_House3_Text_FishingAdvice:
	.string "Face the water and use your Old Rod.\n"
	.string "When you get a bite, press A!\p"
	.string "Here in Tillbrook, Magikarp and\n"
	.string "Goldeen bite during the day.\p"
	.string "At night, try for Feebas and Corphish.\n"
	.string "The river changes after sundown!$"
