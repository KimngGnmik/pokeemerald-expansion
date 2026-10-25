TillbrookTown_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, TillbrookTown_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, TillbrookTown_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, TillbrookTown_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TillbrookTown_OnFrame
	.byte 0

.set LOCALID_TILLBROOK_BARRY, 43
.set LOCALID_TILLBROOK_PAUL, 44
.set LOCALID_TILLBROOK_STARTER, 45
.set LOCALID_TILLBROOK_STARLY, 46

TillbrookTown_OnLoad:
	call TillbrookTown_InitStory
	goto_if_set FLAG_TILLBROOK_BERRIES_INITIALIZED, TillbrookTown_BerriesInitialized
	setberrytree BERRY_TREE_TILLBROOK_01, BERRY_ID_ORAN, BERRY_STAGE_BERRIES
	setberrytree BERRY_TREE_TILLBROOK_03, BERRY_ID_PECHA, BERRY_STAGE_BERRIES
	setberrytree BERRY_TREE_TILLBROOK_05, BERRY_ID_CHERI, BERRY_STAGE_BERRIES
	setberrytree BERRY_TREE_TILLBROOK_07, BERRY_ID_CHESTO, BERRY_STAGE_BERRIES
	setberrytree BERRY_TREE_TILLBROOK_09, BERRY_ID_ORAN, BERRY_STAGE_BERRIES
	setberrytree BERRY_TREE_TILLBROOK_11, BERRY_ID_PECHA, BERRY_STAGE_BERRIES
	setberrytree BERRY_TREE_TILLBROOK_13, BERRY_ID_CHERI, BERRY_STAGE_BERRIES
	setberrytree BERRY_TREE_TILLBROOK_15, BERRY_ID_CHESTO, BERRY_STAGE_BERRIES
	setberrytree BERRY_TREE_TILLBROOK_17, BERRY_ID_ORAN, BERRY_STAGE_BERRIES
	setberrytree BERRY_TREE_TILLBROOK_19, BERRY_ID_PECHA, BERRY_STAGE_BERRIES
	setberrytree BERRY_TREE_TILLBROOK_21, BERRY_ID_CHERI, BERRY_STAGE_BERRIES
	setberrytree BERRY_TREE_TILLBROOK_23, BERRY_ID_CHESTO, BERRY_STAGE_BERRIES
	setflag FLAG_TILLBROOK_BERRIES_INITIALIZED
TillbrookTown_BerriesInitialized:
	end

TillbrookTown_InitStory:
	setflag FLAG_TILLBROOK_HIDE_BARRY
	setflag FLAG_TILLBROOK_HIDE_PAUL
	setflag FLAG_TILLBROOK_HIDE_STARTER
	setflag FLAG_TILLBROOK_HIDE_STARLY
	goto_if_eq VAR_TILLBROOK_STORY, 0, TillbrookTown_InitStarter
	goto_if_eq VAR_TILLBROOK_STORY, 2, TillbrookTown_InitBarryFields
	goto_if_ne VAR_TILLBROOK_STORY, 1, TillbrookTown_InitStarter
	setobjectxyperm LOCALID_TILLBROOK_BARRY, 35, 15
	clearflag FLAG_TILLBROOK_HIDE_BARRY
	goto TillbrookTown_InitStarter
TillbrookTown_InitBarryFields:
	setobjectxyperm LOCALID_TILLBROOK_BARRY, 30, 23
	clearflag FLAG_TILLBROOK_HIDE_BARRY
TillbrookTown_InitStarter:
	switch VAR_STARTER_MON
	case 0, TillbrookTown_StarterTangela
	case 1, TillbrookTown_StarterSnorunt
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES_SHINY(CRANIDOS)
	return
TillbrookTown_StarterTangela:
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES_SHINY(TANGELA)
	return
TillbrookTown_StarterSnorunt:
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES_SHINY(SNORUNT)
	return

TillbrookTown_OnTransition:
	clearflag FLAG_SYS_USE_STRENGTH
	setvar VAR_TEMP_4, 0
	goto_if_unset FLAG_BADGE01_GET, TillbrookTown_TransitionEnd
	goto_if_set FLAG_TILLBROOK_PAUL_COMPLETE, TillbrookTown_TransitionEnd
	setobjectxyperm LOCALID_TILLBROOK_PAUL, 37, 15
	clearflag FLAG_TILLBROOK_HIDE_PAUL
	setvar VAR_TEMP_4, 1
TillbrookTown_TransitionEnd:
	end

TillbrookTown_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, TillbrookTown_InitialFacings
	.2byte 0
TillbrookTown_InitialFacings:
	turnobject 1, DIR_NORTH
	turnobject 2, DIR_SOUTH
	turnobject 3, DIR_EAST
	turnobject 4, DIR_WEST
	end

TillbrookTown_OnFrame:
	map_script_2 VAR_TEMP_4, 1, TillbrookTown_CheckPaulArrival
	.2byte 0
TillbrookTown_CheckPaulArrival:
	setvar VAR_TEMP_4, 0
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 36, TillbrookTown_TransitionEnd
	goto_if_eq VAR_0x8005, 14, TillbrookTown_EventScript_Paul
	goto_if_eq VAR_0x8005, 15, TillbrookTown_EventScript_Paul
	end

TillbrookTown_EventScript_Arrival::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TillbrookTown_Movement_EnterTown
	waitmovement 0
	getplayerxy VAR_0x8004, VAR_0x8005
	clearflag FLAG_TILLBROOK_HIDE_BARRY
	goto_if_eq VAR_0x8004, 23, TillbrookTown_ArrivalRight
	setobjectxyperm LOCALID_TILLBROOK_BARRY, 22, 4
	goto TillbrookTown_ArrivalBattle
TillbrookTown_ArrivalRight:
	setobjectxyperm LOCALID_TILLBROOK_BARRY, 23, 4
TillbrookTown_ArrivalBattle:
	addobject LOCALID_TILLBROOK_BARRY
	turnobject LOCALID_TILLBROOK_BARRY, DIR_SOUTH
	playse SE_DOOR
	msgbox TillbrookTown_Text_BarryWait, MSGBOX_DEFAULT
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	applymovement LOCALID_TILLBROOK_BARRY, TillbrookTown_Movement_BarryCatchUp
	waitmovement 0
	msgbox TillbrookTown_Text_BarryChallenge, MSGBOX_DEFAULT
	closemessage
	switch VAR_STARTER_MON
	case 0, TillbrookTown_BarrySnorunt
	case 1, TillbrookTown_BarryCranidos
	trainerbattle_earlyrival TRAINER_BARRY_TILLBROOK_TANGELA, 0, TillbrookTown_Text_BarryDefeat, TillbrookTown_Text_BarryWin
	goto TillbrookTown_AfterBarry
TillbrookTown_BarrySnorunt:
	trainerbattle_earlyrival TRAINER_BARRY_TILLBROOK_SNORUNT, 0, TillbrookTown_Text_BarryDefeat, TillbrookTown_Text_BarryWin
	goto TillbrookTown_AfterBarry
TillbrookTown_BarryCranidos:
	trainerbattle_earlyrival TRAINER_BARRY_TILLBROOK_CRANIDOS, 0, TillbrookTown_Text_BarryDefeat, TillbrookTown_Text_BarryWin
TillbrookTown_AfterBarry:
	setvar VAR_TILLBROOK_STORY, 1
	msgbox TillbrookTown_Text_BarryAfter, MSGBOX_DEFAULT
	closemessage
	setobjectxyperm LOCALID_TILLBROOK_PAUL, 32, 8
	clearflag FLAG_TILLBROOK_HIDE_PAUL
	addobject LOCALID_TILLBROOK_PAUL
	applymovement LOCALID_TILLBROOK_PAUL, TillbrookTown_Movement_PaulApproaches
	waitmovement 0
	turnobject LOCALID_TILLBROOK_PAUL, DIR_WEST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox TillbrookTown_Text_PaulInsult, MSGBOX_DEFAULT
	msgbox TillbrookTown_Text_BarryWho, MSGBOX_DEFAULT
	msgbox TillbrookTown_Text_PaulNobody, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_TEMP_5, VAR_0x8005
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft
	waitmovement 0
	call_if_eq VAR_TEMP_5, 23, TillbrookTown_PlayerStepsAsideRight
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	applymovement LOCALID_TILLBROOK_PAUL, TillbrookTown_Movement_PaulToGym
	waitmovement 0
	removeobject LOCALID_TILLBROOK_PAUL
	setflag FLAG_TILLBROOK_HIDE_PAUL
	msgbox TillbrookTown_Text_BarryGymNext, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_TEMP_5, 22, TillbrookTown_BarryLeftToGym
	call_if_eq VAR_TEMP_5, 23, TillbrookTown_BarryRightToGym
	removeobject LOCALID_TILLBROOK_BARRY
	setobjectxyperm LOCALID_TILLBROOK_BARRY, 35, 15
	addobject LOCALID_TILLBROOK_BARRY
	releaseall
	end
TillbrookTown_PlayerStepsAsideRight:
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft
	waitmovement 0
	return
TillbrookTown_BarryLeftToGym:
	applymovement LOCALID_TILLBROOK_BARRY, TillbrookTown_Movement_BarryLeftToGym
	waitmovement 0
	return
TillbrookTown_BarryRightToGym:
	applymovement LOCALID_TILLBROOK_BARRY, TillbrookTown_Movement_BarryRightToGym
	waitmovement 0
	return

TillbrookTown_EventScript_BarryOutside::
	lockall
	goto_if_ne VAR_TILLBROOK_STORY, 1, TillbrookTown_BarryFields
	msgbox TillbrookTown_Text_BarryBadge, MSGBOX_DEFAULT
	setflag FLAG_TILLBROOK_BARRY_GYM_TALK
	setvar VAR_TILLBROOK_STORY, 2
	closemessage
	applymovement LOCALID_TILLBROOK_BARRY, TillbrookTown_Movement_BarryToFields
	waitmovement 0
	copyobjectxytoperm LOCALID_TILLBROOK_BARRY
	releaseall
	end
TillbrookTown_BarryFields:
	msgbox TillbrookTown_Text_BarryTraining, MSGBOX_DEFAULT
	releaseall
	end

TillbrookTown_EventScript_Paul::
	lockall
	goto_if_set FLAG_TILLBROOK_PAUL_COMPLETE, TillbrookTown_PaulEnd
	goto_if_unset FLAG_BADGE01_GET, TillbrookTown_PaulEnd
	removeobject LOCALID_TILLBROOK_BARRY
	setflag FLAG_TILLBROOK_HIDE_BARRY
	turnobject LOCALID_TILLBROOK_PAUL, DIR_WEST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox TillbrookTown_Text_PaulChallenge, MSGBOX_DEFAULT
	closemessage
	special Tillbrook_SaveFaintedParty
	switch VAR_STARTER_MON
	case 0, TillbrookTown_PaulSnorunt
	case 1, TillbrookTown_PaulCranidos
	trainerbattle_earlyrival TRAINER_PAUL_TILLBROOK_TANGELA, RIVAL_BATTLE_NO_WHITEOUT, TillbrookTown_Text_PaulDefeat, TillbrookTown_Text_PaulWin
	goto TillbrookTown_AfterPaul
TillbrookTown_PaulSnorunt:
	trainerbattle_earlyrival TRAINER_PAUL_TILLBROOK_SNORUNT, RIVAL_BATTLE_NO_WHITEOUT, TillbrookTown_Text_PaulDefeat, TillbrookTown_Text_PaulWin
	goto TillbrookTown_AfterPaul
TillbrookTown_PaulCranidos:
	trainerbattle_earlyrival TRAINER_PAUL_TILLBROOK_CRANIDOS, RIVAL_BATTLE_NO_WHITEOUT, TillbrookTown_Text_PaulDefeat, TillbrookTown_Text_PaulWin
TillbrookTown_AfterPaul:
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, TillbrookTown_PaulWon
	special Tillbrook_RevivePaulCasualties
	msgbox TillbrookTown_Text_PaulAfterLoss, MSGBOX_DEFAULT
	goto TillbrookTown_PaulRelease
TillbrookTown_PaulWon:
	msgbox TillbrookTown_Text_PaulAfterWin, MSGBOX_DEFAULT
TillbrookTown_PaulRelease:
	setvar VAR_TILLBROOK_PRE_PAUL_FAINTED, 0
	closemessage
	playse SE_BALL_OPEN
	clearflag FLAG_TILLBROOK_HIDE_STARTER
	clearflag FLAG_TILLBROOK_HIDE_STARLY
	addobject LOCALID_TILLBROOK_STARTER
	addobject LOCALID_TILLBROOK_STARLY
	delay 30
	setflag FLAG_PAUL_STARTER_ROUTE216
	applymovement LOCALID_TILLBROOK_STARTER, TillbrookTown_Movement_StarterEscapes
	waitmovement 0
	removeobject LOCALID_TILLBROOK_STARTER
	setflag FLAG_TILLBROOK_HIDE_STARTER
	clearflag FLAG_TILLBROOK_HIDE_BARRY
	setobjectxyperm LOCALID_TILLBROOK_BARRY, 34, 16
	addobject LOCALID_TILLBROOK_BARRY
	turnobject LOCALID_TILLBROOK_BARRY, DIR_EAST
	msgbox TillbrookTown_Text_BarryStarly, MSGBOX_DEFAULT
	closemessage
	playse SE_BALL_THROW
	delay 30
	playse SE_RG_BALL_CLICK
	removeobject LOCALID_TILLBROOK_STARLY
	setflag FLAG_TILLBROOK_HIDE_STARLY
	setflag FLAG_BARRY_CAUGHT_STARLY
	setflag FLAG_TILLBROOK_PAUL_COMPLETE
	setvar VAR_TILLBROOK_STORY, 3
	applymovement LOCALID_TILLBROOK_PAUL, TillbrookTown_Movement_PaulLeaves
	waitmovement 0
	removeobject LOCALID_TILLBROOK_PAUL
	setflag FLAG_TILLBROOK_HIDE_PAUL
	msgbox TillbrookTown_Text_BarryAfterRelease, MSGBOX_DEFAULT
	setflag FLAG_TILLBROOK_HIDE_BARRY
	removeobject LOCALID_TILLBROOK_BARRY
TillbrookTown_PaulEnd:
	releaseall
	end

TillbrookTown_EventScript_Magikarp::
	lock
	faceplayer
	playmoncry SPECIES_MAGIKARP, CRY_MODE_NORMAL
	msgbox TillbrookTown_Text_Magikarp, MSGBOX_DEFAULT
	waitmoncry
	release
	end

TillbrookTown_EventScript_BerryFarmer::
	lock
	faceplayer
	goto_if_set FLAG_TILLBROOK_RECEIVED_PAIL, TillbrookTown_BerryOran
	checkitem ITEM_WAILMER_PAIL
	goto_if_ne VAR_RESULT, 0, TillbrookTown_HasPail
	msgbox TillbrookTown_Text_BerryGift, MSGBOX_DEFAULT
	giveitem ITEM_WAILMER_PAIL
	goto_if_eq VAR_RESULT, 0, TillbrookTown_GiftEnd
TillbrookTown_HasPail:
	setflag FLAG_TILLBROOK_RECEIVED_PAIL
TillbrookTown_BerryOran:
	goto_if_set FLAG_TILLBROOK_RECEIVED_ORAN, TillbrookTown_BerryPecha
	giveitem ITEM_ORAN_BERRY, 2
	goto_if_eq VAR_RESULT, 0, TillbrookTown_GiftEnd
	setflag FLAG_TILLBROOK_RECEIVED_ORAN
TillbrookTown_BerryPecha:
	goto_if_set FLAG_TILLBROOK_RECEIVED_PECHA, TillbrookTown_BerryAdvice
	giveitem ITEM_PECHA_BERRY, 2
	goto_if_eq VAR_RESULT, 0, TillbrookTown_GiftEnd
	setflag FLAG_TILLBROOK_RECEIVED_PECHA
TillbrookTown_BerryAdvice:
	msgbox TillbrookTown_Text_BerryAdvice, MSGBOX_DEFAULT
TillbrookTown_GiftEnd:
	release
	end

TillbrookTown_EventScript_Milk::
	lock
	faceplayer
	message TillbrookTown_Text_Milk
	waitmessage
	pokemart TillbrookTown_MilkStock
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end
	.align 2
TillbrookTown_MilkStock:
	.2byte ITEM_MOOMOO_MILK
	pokemartlistend

TillbrookTown_EventScript_RanchKid::
	msgbox TillbrookTown_Text_RanchKid, MSGBOX_NPC
	end
TillbrookTown_EventScript_GymSign::
	msgbox TillbrookTown_Text_GymSign, MSGBOX_SIGN
	end
TillbrookTown_EventScript_Farmhand::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE01_GET, TillbrookTown_FarmhandWait
	goto_if_set FLAG_TILLBROOK_RECEIVED_CUT, TillbrookTown_FarmhandDone
	msgbox TillbrookTown_Text_CutGift, MSGBOX_DEFAULT
	giveitem ITEM_HM_CUT
	goto_if_eq VAR_RESULT, 0, TillbrookTown_GiftEnd
	setflag FLAG_TILLBROOK_RECEIVED_CUT
TillbrookTown_FarmhandDone:
	msgbox TillbrookTown_Text_CutRoad, MSGBOX_DEFAULT
	release
	end
TillbrookTown_FarmhandWait:
	msgbox TillbrookTown_Text_FarmhandWait, MSGBOX_DEFAULT
	release
	end

TillbrookTown_Movement_PaulApproaches:
	.rept 8
	walk_left
	.endr
	step_end
TillbrookTown_Movement_PaulToGym:
	walk_left
	.rept 8
	walk_down
	.endr
	.rept 13
	walk_right
	.endr
	walk_up
	walk_up
	step_end
TillbrookTown_Movement_BarryCatchUp:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end
TillbrookTown_Movement_EnterTown:
	walk_down
	walk_down
	step_end
TillbrookTown_Movement_BarryToFields:
	walk_down
	.rept 5
	walk_left
	.endr
	.rept 7
	walk_down
	.endr
	step_end
TillbrookTown_Movement_BarryLeftToGym:
	walk_right
	.rept 9
	walk_down
	.endr
	.rept 13
	walk_right
	.endr
	walk_up
	walk_up
	step_end
TillbrookTown_Movement_BarryRightToGym:
	walk_left
	.rept 9
	walk_down
	.endr
	.rept 14
	walk_right
	.endr
	walk_up
	walk_up
	step_end
TillbrookTown_Movement_StarterEscapes:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end
TillbrookTown_Movement_PaulLeaves:
	walk_down
	.rept 4
	walk_right
	.endr
	.rept 10
	walk_down
	.endr
	step_end

TillbrookTown_Text_BarryWait:
	.string "Barry: {PLAYER}! Wait up!$"
TillbrookTown_Text_BarryChallenge:
	.string "We've both been training, right?\n"
	.string "Let's see who's stronger now!$"
TillbrookTown_Text_BarryDefeat:
	.string "Aw, man! Okay, okay.\nNext time for sure.$"
TillbrookTown_Text_BarryWin:
	.string "Yes! I'm getting stronger!$"
TillbrookTown_Text_BarryAfter:
	.string "Barry: Aw, man! Okay, okay.\nNext time for sure.$"
TillbrookTown_Text_PaulInsult:
	.string "Paul: Pathetic. Both of you.$"
TillbrookTown_Text_BarryWho:
	.string "Barry: Hey! Who are you?!$"
TillbrookTown_Text_PaulNobody:
	.string "Paul: Nobody you need to remember.$"
TillbrookTown_Text_BarryGymNext:
	.string "Barry: Is he going to the Gym?\n"
	.string "I'm not letting him get ahead!$"
TillbrookTown_Text_BarryBadge:
	.string "Barry: I won! I got the Furrow Badge!\p"
	.string "But that Paul guy got his first.\n"
	.string "That doesn't count, right?\l"
	.string "It shouldn't count!\p"
	.string "I'm going to go train in the fields.\n"
	.string "Next time, I'm beating him!$"
TillbrookTown_Text_BarryTraining:
	.string "Barry: Next time, I'm beating him!$"
TillbrookTown_Text_PaulChallenge:
	.string "Paul: So you beat Hale too.\n"
	.string "Let's see if it meant anything.$"
TillbrookTown_Text_PaulDefeat:
	.string "Hm.$"
TillbrookTown_Text_PaulWin:
	.string "Exactly what I expected.$"
TillbrookTown_Text_PaulAfterLoss:
	.string "Paul: Exactly what I expected.\p"
	.string "Go heal. Not that it'll make\n"
	.string "a difference.$"
TillbrookTown_Text_PaulAfterWin:
	.string "Paul: Hm. Hale must have been\n"
	.string "easier than I thought.$"
TillbrookTown_Text_BarryStarly:
	.string "Barry: He just let them go?!\p"
	.string "Starly! Wait! I'll look after you!$"
TillbrookTown_Text_BarryAfterRelease:
	.string "Barry: I caught Starly!\p"
	.string "That other Pokémon ran toward the\n"
	.string "fields. I hope it finds someone kind.$"
TillbrookTown_Text_Magikarp:
	.string "Magikarp swims past with a splash!$"
TillbrookTown_Text_BerryGift:
	.string "Soil like this wants something\n"
	.string "growing in it.\p"
	.string "Here. Plant these, and keep them\n"
	.string "watered with this.$"
TillbrookTown_Text_BerryAdvice:
	.string "Come back in a day or so.\n"
	.string "Berries grow faster when you\l"
	.string "look after them.$"
TillbrookTown_Text_Milk:
	.string "Fresh Moomoo Milk from Hale's ranch!\n"
	.string "Would you like some?$"
TillbrookTown_Text_RanchKid:
	.string "Our Miltank keep getting loose in\n"
	.string "the barn. Hale made it a Gym puzzle!\p"
	.string "Nudge each one into its empty stall\n"
	.string "and the next gate will open.$"
TillbrookTown_Text_GymSign:
	.string "Tillbrook Town Pokémon Gym\n"
	.string "Leader: Hale\p"
	.string "The steady hand of the ranch$"
TillbrookTown_Text_CutGift:
	.string "The Furrow Badge! Hale trusts you.\n"
	.string "Take this HM for Cut.$"
TillbrookTown_Text_CutRoad:
	.string "Cut that little tree to head west\n"
	.string "toward Aria's cliffside town.$"
TillbrookTown_Text_FarmhandWait:
	.string "That tree blocks the road west.\n"
	.string "Earn Hale's badge and I'll help you.$"

TillbrookTown_EventScript_TownSign::
	msgbox TillbrookTown_Text_TownSign, MSGBOX_SIGN
	end

TillbrookTown_EventScript_Miltank::
	lock
	faceplayer
	playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	msgbox TillbrookTown_Text_Miltank, MSGBOX_DEFAULT
	waitmoncry
	release
	end

TillbrookTown_EventScript_Mareep::
	lock
	faceplayer
	playmoncry SPECIES_MAREEP, CRY_MODE_NORMAL
	msgbox TillbrookTown_Text_Mareep, MSGBOX_DEFAULT
	waitmoncry
	release
	end

TillbrookTown_EventScript_Tauros::
	lock
	faceplayer
	playmoncry SPECIES_TAUROS, CRY_MODE_NORMAL
	msgbox TillbrookTown_Text_Tauros, MSGBOX_DEFAULT
	waitmoncry
	release
	end

TillbrookTown_Text_TownSign:
	.string "Tillbrook Town\n"
	.string "Fields that feed the north$"

TillbrookTown_Text_Miltank:
	.string "Miltank: Mooo!$"

TillbrookTown_Text_Mareep:
	.string "Mareep: Baa-aah!$"

TillbrookTown_Text_Tauros:
	.string "The Tauros are grazing by the river.\n"
	.string "One has settled right in the way!$"
