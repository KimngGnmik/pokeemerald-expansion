.set LOCALID_MOM, 1

SnowpointCity_PlayersHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SnowpointCity_PlayersHouse_1F_OnFrame
	.byte 0

SnowpointCity_PlayersHouse_1F_OnFrame:
	map_script_2 VAR_SNOWPOINT_INTRO_STATE, 1, SnowpointCity_PlayersHouse_1F_EventScript_MomMorning
	.2byte 0

@ The player arrives on the stairs; Mom leaves the kitchen and comes over to meet them.
SnowpointCity_PlayersHouse_1F_EventScript_MomMorning::
	lockall
	playse SE_PIN
	applymovement LOCALID_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MOM, SnowpointCity_PlayersHouse_1F_Movement_MomToStairs
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	msgbox SnowpointCity_PlayersHouse_1F_Text_FinallyUp, MSGBOX_DEFAULT
	msgbox SnowpointCity_PlayersHouse_1F_Text_BigDay, MSGBOX_DEFAULT
	msgbox SnowpointCity_PlayersHouse_1F_Text_TakeTheseShoes, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message SnowpointCity_PlayersHouse_1F_Text_ReceivedRunningShoes
	waitfanfare
	setflag FLAG_RECEIVED_RUNNING_SHOES
	setflag FLAG_SYS_B_DASH
	msgbox SnowpointCity_PlayersHouse_1F_Text_ExplainRunningShoes, MSGBOX_DEFAULT
	msgbox SnowpointCity_PlayersHouse_1F_Text_DontBeLate, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOM, SnowpointCity_PlayersHouse_1F_Movement_MomToKitchen
	waitmovement 0
	setvar VAR_SNOWPOINT_INTRO_STATE, 2
	releaseall
	end

SnowpointCity_PlayersHouse_1F_Movement_MomToStairs:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	face_up
	step_end

@ Back the way she came, so the stairs are clear again.
SnowpointCity_PlayersHouse_1F_Movement_MomToKitchen:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	face_up
	step_end

SnowpointCity_PlayersHouse_1F_EventScript_Mom::
	lock
	faceplayer
	goto_if_ge VAR_SNOWPOINT_INTRO_STATE, 10, SnowpointCity_PlayersHouse_1F_EventScript_MomAfterCeremony
	msgbox SnowpointCity_PlayersHouse_1F_Text_MomReminder, MSGBOX_DEFAULT
	release
	end

@ After the ceremony Mom heals the party every time; the first time she asks how it went.
SnowpointCity_PlayersHouse_1F_EventScript_MomAfterCeremony::
	goto_if_set FLAG_MOM_AFTER_CEREMONY, SnowpointCity_PlayersHouse_1F_EventScript_MomRest
	bufferpartymonnick STR_VAR_1, 0
	msgbox SnowpointCity_PlayersHouse_1F_Text_HowDidItGo, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message SnowpointCity_PlayersHouse_1F_Text_ReceivedTrainerCard
	waitfanfare
	setflag FLAG_SYS_TRAINER_CARD_GET
	msgbox SnowpointCity_PlayersHouse_1F_Text_TakeCareOfYouBoth, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox SnowpointCity_PlayersHouse_1F_Text_TownIsProud, MSGBOX_DEFAULT
	setflag FLAG_MOM_AFTER_CEREMONY
	release
	end

SnowpointCity_PlayersHouse_1F_EventScript_MomRest::
	msgbox SnowpointCity_PlayersHouse_1F_Text_RestAMinute, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox SnowpointCity_PlayersHouse_1F_Text_TakeCareOfEachOther, MSGBOX_DEFAULT
	release
	end

SnowpointCity_PlayersHouse_1F_EventScript_Sink::
	msgbox SnowpointCity_PlayersHouse_1F_Text_Sink, MSGBOX_SIGN
	end

SnowpointCity_PlayersHouse_1F_EventScript_Fridge::
	msgbox SnowpointCity_PlayersHouse_1F_Text_Fridge, MSGBOX_SIGN
	end

SnowpointCity_PlayersHouse_1F_EventScript_TV::
	msgbox SnowpointCity_PlayersHouse_1F_Text_TV, MSGBOX_SIGN
	end

SnowpointCity_PlayersHouse_1F_EventScript_Wastebasket::
	msgbox SnowpointCity_PlayersHouse_1F_Text_Wastebasket, MSGBOX_SIGN
	end

SnowpointCity_PlayersHouse_1F_EventScript_Bookshelf::
	msgbox SnowpointCity_PlayersHouse_1F_Text_Bookshelf, MSGBOX_SIGN
	end

SnowpointCity_PlayersHouse_1F_EventScript_Table::
	msgbox SnowpointCity_PlayersHouse_1F_Text_Table, MSGBOX_SIGN
	end

SnowpointCity_PlayersHouse_1F_Text_FinallyUp:
	.string "Mom: Good morning, {PLAYER}.\n"
	.string "You're finally up.\p"
	.string "Barry has been by twice already.\p"
	.string "The second time he threw a snowball\n"
	.string "at your window.\p"
	.string "I don't know where that boy gets\n"
	.string "his energy.$"

SnowpointCity_PlayersHouse_1F_Text_BigDay:
	.string "Well, today's a big day!\p"
	.string "Every child in town takes part the\n"
	.string "year they turn ten.$"

SnowpointCity_PlayersHouse_1F_Text_TakeTheseShoes:
	.string "Oh, and before you leave, I want you\n"
	.string "to have these.$"

SnowpointCity_PlayersHouse_1F_Text_ReceivedRunningShoes:
	.string "{PLAYER} received the\n"
	.string "Running Shoes!$"

SnowpointCity_PlayersHouse_1F_Text_ExplainRunningShoes:
	.string "Mom: Hold the B Button to run.\n"
	.string "Just be careful on the ice.$"

SnowpointCity_PlayersHouse_1F_Text_DontBeLate:
	.string "The Elder is waiting, and the whole\n"
	.string "town will be there. Don't be late.$"

SnowpointCity_PlayersHouse_1F_Text_MomReminder:
	.string "Mom: The Elder is waiting, and the\n"
	.string "whole town will be there.\p"
	.string "Don't be late, {PLAYER}!$"

SnowpointCity_PlayersHouse_1F_Text_Sink:
	.string "The breakfast dishes are drying\n"
	.string "by the sink.$"

SnowpointCity_PlayersHouse_1F_Text_Fridge:
	.string "It's full of food.\p"
	.string "There's a note on the door:\n"
	.string "“For after the ceremony.”$"

SnowpointCity_PlayersHouse_1F_Text_TV:
	.string "It's a show about Pokémon that live\n"
	.string "in the snow.\p"
	.string "A Snover is waddling through\n"
	.string "a blizzard…$"

SnowpointCity_PlayersHouse_1F_Text_Wastebasket:
	.string "Eggshells and an empty bag of flour.\n"
	.string "Something was baked this morning.$"

SnowpointCity_PlayersHouse_1F_Text_Bookshelf:
	.string "Cookbooks, a field guide to northern\n"
	.string "Pokémon, and a photo album.$"

SnowpointCity_PlayersHouse_1F_Text_Table:
	.string "There's a plate of warm muffins.\n"
	.string "Mom must have been up early.$"

SnowpointCity_PlayersHouse_1F_Text_HowDidItGo:
	.string "Mom: {PLAYER}! How did it go?\p"
	.string "So {STR_VAR_1} is your partner?\n"
	.string "{STR_VAR_1} is so adorable!\p"
	.string "I am so proud of you, honey!\p"
	.string "Take this. It's your very own\n"
	.string "Trainer Card.$"

SnowpointCity_PlayersHouse_1F_Text_ReceivedTrainerCard:
	.string "{PLAYER} received a Trainer Card!$"

SnowpointCity_PlayersHouse_1F_Text_TakeCareOfYouBoth:
	.string "Mom: Come here, let me take care of\n"
	.string "you both before you go.$"

SnowpointCity_PlayersHouse_1F_Text_TownIsProud:
	.string "Mom: There. Now go on with your\n"
	.string "journey. I love you!$"

SnowpointCity_PlayersHouse_1F_Text_RestAMinute:
	.string "Mom: You look tired, {PLAYER}.\n"
	.string "Rest a minute.$"

SnowpointCity_PlayersHouse_1F_Text_TakeCareOfEachOther:
	.string "Mom: Take care of each other\n"
	.string "out there.$"
