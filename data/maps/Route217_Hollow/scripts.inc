Route217_Hollow_MapScripts::
	.byte 0

Route217_Hollow_EventScript_Bram::
	trainerbattle_single TRAINER_BRAM, Route217_Hollow_Text_BramIntro, Route217_Hollow_Text_BramDefeat
	msgbox Route217_Hollow_Text_BramPostBattle, MSGBOX_AUTOCLOSE
	end

Route217_Hollow_EventScript_ItemPokeBalls::
	finditem ITEM_POKE_BALL, 2
	end

Route217_Hollow_EventScript_ItemHardStone::
	finditem ITEM_HARD_STONE
	end

Route217_Hollow_EventScript_ItemNugget::
	finditem ITEM_NUGGET
	end

Route217_Hollow_EventScript_ItemRareCandy::
	finditem ITEM_RARE_CANDY
	end

Route217_Hollow_EventScript_ItemRevive::
	finditem ITEM_REVIVE
	end

Route217_Hollow_Text_BramIntro:
	.string "The rocks down here are older\n"
	.string "than the town up top!$"

Route217_Hollow_Text_BramDefeat:
	.string "Solid as a rock… almost.$"

Route217_Hollow_Text_BramPostBattle:
	.string "I came up here to see the temple.\n"
	.string "I heard the ceremony is something\l"
	.string "to see.$"
