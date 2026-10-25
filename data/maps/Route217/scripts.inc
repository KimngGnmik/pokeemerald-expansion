Route217_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route217_OnTransition
	.byte 0

Route217_OnTransition:
	goto_if_unset FLAG_SYS_POKEDEX_GET, Route217_EventScript_End
	goto_if_set FLAG_SYS_NATIONAL_DEX, Route217_EventScript_End
	special EnableNationalPokedex
Route217_EventScript_End:
	end

@ ---------------------------------------------------------------- Barry past the gate
@ Barry waits at (5, 1). The player steps in at x 1 on rows 1-3; he comes over, steps into the first
@ patch of snow grass at (5, 4) and catches a Bidoof while the player watches, then runs on ahead.
Route217_EventScript_BarryPastGate::
	lockall
	setvar VAR_ROUTE217_STATE, 1
	playse SE_PIN
	applymovement LOCALID_ROUTE217_BARRY, Common_Movement_ExclamationMark
	waitmovement 0
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_eq VAR_0x8005, 1, Route217_EventScript_BarryComesRow1
	call_if_eq VAR_0x8005, 2, Route217_EventScript_BarryComesRow2
	call_if_eq VAR_0x8005, 3, Route217_EventScript_BarryComesRow3
	msgbox Route217_Text_BarryWatchMe, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8005, 1, Route217_EventScript_BarryToGrassFromRow1
	call_if_ne VAR_0x8005, 1, Route217_EventScript_BarryToGrassFromAbove
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	hidefollower
	setflag FLAG_TEMP_HIDE_FOLLOWER
	special SavePlayerParty
	special LoadBarryTutorialMon
	special StartBarryTutorialBattle
	clearflag FLAG_TEMP_HIDE_FOLLOWER
	special RestorePlayerPartyAfterTutorial
	applymovement LOCALID_ROUTE217_BARRY, Common_Movement_FaceLeft
	waitmovement 0
	msgbox Route217_Text_BarrySeeEasy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE217_BARRY, Route217_Movement_BarryRunsAhead
	waitmovement 0
	removeobject LOCALID_ROUTE217_BARRY
	releaseall
	end

@ Player on (1, 1): Barry stops at (2, 1).
Route217_EventScript_BarryComesRow1::
	applymovement LOCALID_ROUTE217_BARRY, Route217_Movement_BarryLeft3
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	return

@ Player on (1, 2): Barry stops above them at (1, 1).
Route217_EventScript_BarryComesRow2::
	applymovement LOCALID_ROUTE217_BARRY, Route217_Movement_BarryLeft4FaceDown
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	return

@ Player on (1, 3): Barry stops above them at (1, 2).
Route217_EventScript_BarryComesRow3::
	applymovement LOCALID_ROUTE217_BARRY, Route217_Movement_BarryLeft4Down1
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	return

@ From (2, 1) into the first patch of grass at (5, 4).
Route217_EventScript_BarryToGrassFromRow1::
	applymovement LOCALID_ROUTE217_BARRY, Route217_Movement_BarryToGrassFromRow1
	waitmovement 0
	return

@ From (1, 1) or (1, 2) into the grass at (5, 4).
Route217_EventScript_BarryToGrassFromAbove::
	call_if_eq VAR_0x8005, 3, Route217_EventScript_BarryStepUp
	applymovement LOCALID_ROUTE217_BARRY, Route217_Movement_BarryToGrassFromCorner
	waitmovement 0
	return

Route217_EventScript_BarryStepUp::
	applymovement LOCALID_ROUTE217_BARRY, Common_Movement_WalkUp
	waitmovement 0
	return

Route217_Movement_BarryLeft3:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route217_Movement_BarryLeft4FaceDown:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	face_down
	step_end

Route217_Movement_BarryLeft4Down1:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	step_end

Route217_Movement_BarryToGrassFromRow1:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	step_end

Route217_Movement_BarryToGrassFromCorner:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	step_end

@ From (5, 4) out of the grass and off down the route.
Route217_Movement_BarryRunsAhead:
	walk_faster_right
	walk_faster_right
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	step_end

Route217_EventScript_TillbrookSign::
	msgbox Route217_Text_TillbrookSign, MSGBOX_SIGN
	end

Route217_EventScript_ItemPotion::
	finditem ITEM_POTION
	end

Route217_EventScript_ItemOranBerry::
	finditem ITEM_ORAN_BERRY
	end

@ ---------------------------------------------------------------- trainers
Route217_EventScript_Tad::
	trainerbattle_single TRAINER_TAD, Route217_Text_TadIntro, Route217_Text_TadDefeat
	msgbox Route217_Text_TadPostBattle, MSGBOX_AUTOCLOSE
	end

Route217_EventScript_Wes::
	trainerbattle_single TRAINER_WES, Route217_Text_WesIntro, Route217_Text_WesDefeat
	msgbox Route217_Text_WesPostBattle, MSGBOX_AUTOCLOSE
	end

Route217_EventScript_Dana::
	trainerbattle_single TRAINER_DANA, Route217_Text_DanaIntro, Route217_Text_DanaDefeat
	msgbox Route217_Text_DanaPostBattle, MSGBOX_AUTOCLOSE
	end

Route217_EventScript_Cora::
	trainerbattle_single TRAINER_CORA, Route217_Text_CoraIntro, Route217_Text_CoraDefeat
	msgbox Route217_Text_CoraPostBattle, MSGBOX_AUTOCLOSE
	end

Route217_Text_TadIntro:
	.string "Hey! You came down from Snowpoint,\n"
	.string "right? Let's see what you've got!$"

Route217_Text_TadDefeat:
	.string "Aw, I was so close!$"

Route217_Text_TadPostBattle:
	.string "Snowpoint kids always get the\n"
	.string "toughest Pokémon. No fair!$"

Route217_Text_WesIntro:
	.string "Bug Pokémon like the snow more\n"
	.string "than you'd think!$"

Route217_Text_WesDefeat:
	.string "My bugs got cold feet…$"

Route217_Text_WesPostBattle:
	.string "Kricketot sings louder when it's\n"
	.string "cold. Listen!$"

Route217_Text_DanaIntro:
	.string "Snover is the reason this slope is so\n"
	.string "good for skiing.\p"
	.string "Snover keeps the snow from melting.$"

Route217_Text_DanaDefeat:
	.string "Wiped out!$"

Route217_Text_DanaPostBattle:
	.string "Back up the slope for another run.\n"
	.string "Watch out for the deep snow!$"

Route217_Text_CoraIntro:
	.string "You're almost at Tillbrook!\n"
	.string "But first, a battle!$"

Route217_Text_CoraDefeat:
	.string "My cute Pokémon…$"

Route217_Text_CoraPostBattle:
	.string "Tillbrook's Gym uses Normal types.\n"
	.string "Don't underestimate them!$"

Route217_Text_BarryWatchMe:
	.string "Barry: {PLAYER}! What took you\n"
	.string "so long?\p"
	.string "I already tried to catch a Starly.\n"
	.string "Starly flew off before I could even\l"
	.string "throw the ball!\p"
	.string "Cynthia said you have to weaken a\n"
	.string "Pokémon first. Nobody told me that!\p"
	.string "Okay, watch me this time.$"

Route217_Text_BarrySeeEasy:
	.string "Barry: Ha! See? Easy!\p"
	.string "I'm heading to the next town.\n"
	.string "The first Gym is there, and I'm\l"
	.string "going to be first!$"

Route217_Text_TillbrookSign:
	.string "South: Tillbrook Town\n"
	.string "Home of the Normal-type Gym$"
