SnowpointCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SnowpointCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SnowpointCity_OnFrame
	.byte 0

SnowpointCity_OnTransition:
	call_if_set FLAG_SYS_POKEMON_GET, SnowpointCity_EventScript_ShovelerStepsAside
	call SnowpointCity_EventScript_SetUpCeremony
	end

@ The Poké Balls stay hidden until the Elder lays them out, and Barry waits by the temple from the race until the ceremony ends.
SnowpointCity_EventScript_SetUpCeremony::
	goto_if_ge VAR_SNOWPOINT_INTRO_STATE, 10, SnowpointCity_EventScript_SetUpCeremonyEnd
	call_if_lt VAR_SNOWPOINT_INTRO_STATE, 5, SnowpointCity_EventScript_HideStarterBalls
	goto_if_lt VAR_SNOWPOINT_INTRO_STATE, 3, SnowpointCity_EventScript_SetUpCeremonyEnd
	call SnowpointCity_EventScript_BarryWaitsAtTemple
SnowpointCity_EventScript_SetUpCeremonyEnd::
	return

SnowpointCity_EventScript_HideStarterBalls::
	setflag FLAG_HIDE_SNOWPOINT_CITY_BALL_SNORUNT
	setflag FLAG_HIDE_SNOWPOINT_CITY_BALL_CRANIDOS
	setflag FLAG_HIDE_SNOWPOINT_CITY_BALL_TANGELA
	return

SnowpointCity_EventScript_BarryWaitsAtTemple::
	clearflag FLAG_HIDE_SNOWPOINT_CITY_BARRY
	setobjectxyperm LOCALID_SNOWPOINT_BARRY, 7, 10
	setobjectmovementtype LOCALID_SNOWPOINT_BARRY, MOVEMENT_TYPE_JOG_IN_PLACE_DOWN
	return

@ Once the player has a partner, the shoveler stands off the road beside the east exit.
SnowpointCity_EventScript_ShovelerStepsAside::
	setobjectxyperm LOCALID_SNOWPOINT_SHOVELER, 33, 32
	setobjectmovementtype LOCALID_SNOWPOINT_SHOVELER, MOVEMENT_TYPE_FACE_DOWN
	return

SnowpointCity_OnFrame:
	map_script_2 VAR_SNOWPOINT_INTRO_STATE, 2, SnowpointCity_EventScript_MeetBarry
	.2byte 0

@ The player steps out of the house; Barry, jogging in the yard, circles them and skids to a stop.
SnowpointCity_EventScript_MeetBarry::
	lockall
	applymovement LOCALID_SNOWPOINT_BARRY, SnowpointCity_Movement_BarryCircleIn
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox SnowpointCity_Text_BarryFinally, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SNOWPOINT_BARRY, SnowpointCity_Movement_BarryLap
	applymovement OBJ_EVENT_ID_PLAYER, SnowpointCity_Movement_PlayerWatchLap
	waitmovement 0
	msgbox SnowpointCity_Text_BarryRun, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SNOWPOINT_BARRY, SnowpointCity_Movement_BarrySprintOff
	waitmovement 0
	call SnowpointCity_EventScript_BarryWaitsAtTemple
	setvar VAR_SNOWPOINT_INTRO_STATE, 3
	releaseall
	end

@ Barry starts in the yard below and to the right of the door, and loops round to the player's right side.
SnowpointCity_Movement_BarryCircleIn:
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_in_place_faster_left
	face_left
	step_end

@ A lap underneath the player, ending on their left side.
SnowpointCity_Movement_BarryLap:
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_up
	face_right
	step_end

SnowpointCity_Movement_PlayerWatchLap:
	delay_8
	face_down
	delay_16
	face_left
	step_end

@ Up the west side of town to his spot beside the temple steps (7, 10).
SnowpointCity_Movement_BarrySprintOff:
	walk_faster_left
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_right
	walk_faster_right
	walk_faster_right
	step_end

@ Halfway to the temple (a line across row 16): if the player is walking, Barry runs back down to hurry them along.
SnowpointCity_EventScript_BarryTooSlow::
	lockall
	setvar VAR_SNOWPOINT_INTRO_STATE, 4
	specialvar VAR_RESULT, IsPlayerRunning
	goto_if_eq VAR_RESULT, TRUE, SnowpointCity_EventScript_BarryTooSlowEnd
	getplayerxy VAR_0x8004, VAR_0x8005
	removeobject LOCALID_SNOWPOINT_BARRY
	setobjectxyperm LOCALID_SNOWPOINT_BARRY, VAR_0x8004, 11
	addobject LOCALID_SNOWPOINT_BARRY
	applymovement LOCALID_SNOWPOINT_BARRY, SnowpointCity_Movement_BarryComeBack
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox SnowpointCity_Text_BarryTooSlow, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SNOWPOINT_BARRY, SnowpointCity_Movement_BarryRunBack
	waitmovement 0
	removeobject LOCALID_SNOWPOINT_BARRY
	setobjectxyperm LOCALID_SNOWPOINT_BARRY, 7, 10
	addobject LOCALID_SNOWPOINT_BARRY
SnowpointCity_EventScript_BarryTooSlowEnd::
	releaseall
	end

SnowpointCity_Movement_BarryComeBack:
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_in_place_faster_down
	step_end

SnowpointCity_Movement_BarryRunBack:
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	step_end

@ ---------------------------------------------------------------- the ceremony
@ The plaza in front of the temple is closed off by a line of triggers across row 12.
@ Arriving starts the ceremony; while choosing, stepping back onto the line sends the player back up.
SnowpointCity_EventScript_TempleSteps::
	goto_if_eq VAR_SNOWPOINT_INTRO_STATE, 3, SnowpointCity_EventScript_Ceremony
	goto_if_eq VAR_SNOWPOINT_INTRO_STATE, 4, SnowpointCity_EventScript_Ceremony
	goto_if_eq VAR_SNOWPOINT_INTRO_STATE, 5, SnowpointCity_EventScript_NotChosenYet
	end

@ Elder at (9, 9), CYNTHIA and GARCHOMP to her right, Barry at (7, 10).
@ The player is brought to (9, 11) and the Poké Balls go down at (8, 10), (9, 10) and (10, 10).
SnowpointCity_EventScript_Ceremony::
	lockall
	applymovement LOCALID_SNOWPOINT_BARRY, SnowpointCity_Movement_BarryHop
	waitmovement 0
	msgbox SnowpointCity_Text_BarryYouMadeIt, MSGBOX_DEFAULT
	closemessage
	call SnowpointCity_EventScript_WalkToElder
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	turnobject LOCALID_SNOWPOINT_BARRY, DIR_NORTH
	waitmovement 0
	msgbox SnowpointCity_Text_ElderWelcome, MSGBOX_DEFAULT
	turnobject LOCALID_SNOWPOINT_ELDER, DIR_EAST
	msgbox SnowpointCity_Text_ElderAsksCynthia, MSGBOX_DEFAULT
	turnobject LOCALID_SNOWPOINT_CYNTHIA, DIR_WEST
	msgbox SnowpointCity_Text_CynthiaOfCourse, MSGBOX_DEFAULT
	turnobject LOCALID_SNOWPOINT_CYNTHIA, DIR_SOUTH
	turnobject LOCALID_SNOWPOINT_ELDER, DIR_SOUTH
	msgbox SnowpointCity_Text_CynthiaLegend, MSGBOX_DEFAULT
	msgbox SnowpointCity_Text_ElderCeremony, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SNOWPOINT_ELDER, SnowpointCity_Movement_ElderToFirstBall
	waitmovement 0
	call SnowpointCity_EventScript_LayBall
	addobject LOCALID_SNOWPOINT_BALL_SNORUNT
	applymovement LOCALID_SNOWPOINT_ELDER, SnowpointCity_Movement_ElderToNextBall
	waitmovement 0
	call SnowpointCity_EventScript_LayBall
	addobject LOCALID_SNOWPOINT_BALL_CRANIDOS
	applymovement LOCALID_SNOWPOINT_ELDER, SnowpointCity_Movement_ElderToNextBall
	waitmovement 0
	call SnowpointCity_EventScript_LayBall
	addobject LOCALID_SNOWPOINT_BALL_TANGELA
	applymovement LOCALID_SNOWPOINT_ELDER, SnowpointCity_Movement_ElderBackToCenter
	waitmovement 0
	msgbox SnowpointCity_Text_ElderChoose, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SNOWPOINT_BARRY, SnowpointCity_Movement_BarryMeFirst
	waitmovement 0
	msgbox SnowpointCity_Text_BarryMeFirst, MSGBOX_DEFAULT
	turnobject LOCALID_SNOWPOINT_ELDER, DIR_WEST
	msgbox SnowpointCity_Text_ElderPatience, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_SNOWPOINT_ELDER, DIR_SOUTH
	setvar VAR_SNOWPOINT_INTRO_STATE, 5
	releaseall
	end

SnowpointCity_EventScript_LayBall::
	playse SE_BALL
	delay 16
	return

@ From anywhere on row 12, walk along the row to x = 9 and step up in front of the ELDER.
SnowpointCity_EventScript_WalkToElder::
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_lt VAR_0x8004, 9, SnowpointCity_EventScript_WalkToElderRight
	goto_if_gt VAR_0x8004, 9, SnowpointCity_EventScript_WalkToElderLeft
	applymovement OBJ_EVENT_ID_PLAYER, SnowpointCity_Movement_WalkUp
	waitmovement 0
	return

SnowpointCity_EventScript_WalkToElderRight::
	applymovement OBJ_EVENT_ID_PLAYER, SnowpointCity_Movement_WalkRight
	waitmovement 0
	goto SnowpointCity_EventScript_WalkToElder

SnowpointCity_EventScript_WalkToElderLeft::
	applymovement OBJ_EVENT_ID_PLAYER, SnowpointCity_Movement_WalkLeft
	waitmovement 0
	goto SnowpointCity_EventScript_WalkToElder

SnowpointCity_EventScript_NotChosenYet::
	lockall
	turnobject LOCALID_SNOWPOINT_ELDER, DIR_SOUTH
	msgbox SnowpointCity_Text_ElderPokemonWaiting, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, SnowpointCity_Movement_WalkUp
	waitmovement 0
	releaseall
	end

@ ---------------------------------------------------------------- choosing a starter
SnowpointCity_EventScript_BallSnorunt::
	lockall
	goto_if_ge VAR_SNOWPOINT_INTRO_STATE, 10, SnowpointCity_EventScript_ReservedBall
	showmonpic SPECIES_SNORUNT, 10, 3
	msgbox SnowpointCity_Text_ChooseSnorunt, MSGBOX_YESNO
	hidemonpic
	goto_if_eq VAR_RESULT, NO, SnowpointCity_EventScript_NotThisOne
	setvar VAR_STARTER_MON, 0
	givemon SPECIES_SNORUNT, 5
	removeobject LOCALID_SNOWPOINT_BALL_SNORUNT
	bufferspeciesname STR_VAR_1, SPECIES_SNORUNT
	msgbox SnowpointCity_Text_ElderAboutSnorunt, MSGBOX_DEFAULT
	goto SnowpointCity_EventScript_ReceivedStarter

SnowpointCity_EventScript_BallCranidos::
	lockall
	goto_if_ge VAR_SNOWPOINT_INTRO_STATE, 10, SnowpointCity_EventScript_ReservedBall
	showmonpic SPECIES_CRANIDOS, 10, 3
	msgbox SnowpointCity_Text_ChooseCranidos, MSGBOX_YESNO
	hidemonpic
	goto_if_eq VAR_RESULT, NO, SnowpointCity_EventScript_NotThisOne
	setvar VAR_STARTER_MON, 1
	givemon SPECIES_CRANIDOS, 5
	removeobject LOCALID_SNOWPOINT_BALL_CRANIDOS
	bufferspeciesname STR_VAR_1, SPECIES_CRANIDOS
	msgbox SnowpointCity_Text_ElderAboutCranidos, MSGBOX_DEFAULT
	goto SnowpointCity_EventScript_ReceivedStarter

SnowpointCity_EventScript_BallTangela::
	lockall
	goto_if_ge VAR_SNOWPOINT_INTRO_STATE, 10, SnowpointCity_EventScript_ReservedBall
	showmonpic SPECIES_TANGELA, 10, 3
	msgbox SnowpointCity_Text_ChooseTangela, MSGBOX_YESNO
	hidemonpic
	goto_if_eq VAR_RESULT, NO, SnowpointCity_EventScript_NotThisOne
	setvar VAR_STARTER_MON, 2
	givemon SPECIES_TANGELA, 5
	removeobject LOCALID_SNOWPOINT_BALL_TANGELA
	bufferspeciesname STR_VAR_1, SPECIES_TANGELA
	msgbox SnowpointCity_Text_ElderAboutTangela, MSGBOX_DEFAULT
	goto SnowpointCity_EventScript_ReceivedStarter

SnowpointCity_EventScript_NotThisOne::
	releaseall
	end

@ After the ceremony, the ball left on the altar is kept for the other new trainer.
SnowpointCity_EventScript_ReservedBall::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, SnowpointCity_EventScript_ReservedBallDawn
	msgbox SnowpointCity_Text_ReservedForLucas, MSGBOX_DEFAULT
	releaseall
	end

SnowpointCity_EventScript_ReservedBallDawn::
	msgbox SnowpointCity_Text_ReservedForDawn, MSGBOX_DEFAULT
	releaseall
	end

SnowpointCity_EventScript_ReceivedStarter::
	playfanfare MUS_OBTAIN_ITEM
	message SnowpointCity_Text_ReceivedStarter
	waitmessage
	waitfanfare
	setflag FLAG_SYS_POKEMON_GET
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SnowpointCity_EventScript_NicknameStarter
	closemessage
	hidefollower
	call SnowpointCity_EventScript_BackInFrontOfElder
	switch VAR_STARTER_MON
	case 0, SnowpointCity_EventScript_BarryTakesCranidos
	case 1, SnowpointCity_EventScript_BarryTakesTangela
	case 2, SnowpointCity_EventScript_BarryTakesSnorunt
	end

SnowpointCity_EventScript_NicknameStarter::
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	return

@ The player can take a ball from any free side of it; bring them back to (9, 11) through the tile the ball left behind.
SnowpointCity_EventScript_BackInFrontOfElder::
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8005, 9, SnowpointCity_EventScript_BackFromAbove
	goto_if_eq VAR_0x8005, 10, SnowpointCity_EventScript_BackFromRightSide
	call_if_eq VAR_0x8004, 8, SnowpointCity_EventScript_StepRight
	call_if_eq VAR_0x8004, 10, SnowpointCity_EventScript_StepLeft
	goto SnowpointCity_EventScript_FaceElder

SnowpointCity_EventScript_BackFromAbove::
	applymovement OBJ_EVENT_ID_PLAYER, SnowpointCity_Movement_DownTwice
	waitmovement 0
	call_if_eq VAR_0x8004, 8, SnowpointCity_EventScript_StepRight
	call_if_eq VAR_0x8004, 10, SnowpointCity_EventScript_StepLeft
	goto SnowpointCity_EventScript_FaceElder

SnowpointCity_EventScript_BackFromRightSide::
	applymovement OBJ_EVENT_ID_PLAYER, SnowpointCity_Movement_BackFromRightSide
	waitmovement 0
	goto SnowpointCity_EventScript_FaceElder

SnowpointCity_EventScript_StepRight::
	applymovement OBJ_EVENT_ID_PLAYER, SnowpointCity_Movement_WalkRight
	waitmovement 0
	return

SnowpointCity_EventScript_StepLeft::
	applymovement OBJ_EVENT_ID_PLAYER, SnowpointCity_Movement_WalkLeft
	waitmovement 0
	return

SnowpointCity_EventScript_FaceElder::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	return

@ Barry always goes for the type that beats the player's pick.
SnowpointCity_EventScript_BarryTakesCranidos::
	applymovement LOCALID_SNOWPOINT_BARRY, SnowpointCity_Movement_BarryToMiddleBall
	waitmovement 0
	bufferspeciesname STR_VAR_2, SPECIES_CRANIDOS
	call SnowpointCity_EventScript_BarryPicks
	call SnowpointCity_EventScript_RemainingBall
	applymovement LOCALID_SNOWPOINT_BARRY, SnowpointCity_Movement_BarryFromMiddleBall
	waitmovement 0
	goto SnowpointCity_EventScript_BarryBattle

SnowpointCity_EventScript_BarryTakesTangela::
	applymovement LOCALID_SNOWPOINT_BARRY, SnowpointCity_Movement_BarryToRightBall
	waitmovement 0
	bufferspeciesname STR_VAR_2, SPECIES_TANGELA
	call SnowpointCity_EventScript_BarryPicks
	call SnowpointCity_EventScript_RemainingBall
	applymovement LOCALID_SNOWPOINT_BARRY, SnowpointCity_Movement_BarryFromRightBall
	waitmovement 0
	goto SnowpointCity_EventScript_BarryBattle

SnowpointCity_EventScript_BarryTakesSnorunt::
	applymovement LOCALID_SNOWPOINT_BARRY, Common_Movement_FaceRight
	waitmovement 0
	bufferspeciesname STR_VAR_2, SPECIES_SNORUNT
	call SnowpointCity_EventScript_BarryPicks
	call SnowpointCity_EventScript_RemainingBall
	applymovement LOCALID_SNOWPOINT_BARRY, SnowpointCity_Movement_BarryFromLeftBall
	waitmovement 0
	goto SnowpointCity_EventScript_BarryBattle

SnowpointCity_EventScript_BarryPicks::
	msgbox SnowpointCity_Text_BarryMyTurn, MSGBOX_DEFAULT
	closemessage
	switch VAR_STARTER_MON
	case 0, SnowpointCity_EventScript_RemoveCranidosBall
	case 1, SnowpointCity_EventScript_RemoveTangelaBall
	case 2, SnowpointCity_EventScript_RemoveSnoruntBall
SnowpointCity_EventScript_BarryPicksEnd::
	playse SE_BALL
	waitse
	msgbox SnowpointCity_Text_BarryLookAtThat, MSGBOX_DEFAULT
	closemessage
	return

SnowpointCity_EventScript_RemoveCranidosBall::
	removeobject LOCALID_SNOWPOINT_BALL_CRANIDOS
	goto SnowpointCity_EventScript_BarryPicksEnd

SnowpointCity_EventScript_RemoveTangelaBall::
	removeobject LOCALID_SNOWPOINT_BALL_TANGELA
	goto SnowpointCity_EventScript_BarryPicksEnd

SnowpointCity_EventScript_RemoveSnoruntBall::
	removeobject LOCALID_SNOWPOINT_BALL_SNORUNT
	goto SnowpointCity_EventScript_BarryPicksEnd

SnowpointCity_EventScript_RemainingBall::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, SnowpointCity_EventScript_RemainingBallDawn
	call_if_eq VAR_RESULT, FEMALE, SnowpointCity_EventScript_RemainingBallLucas
	closemessage
	return

SnowpointCity_EventScript_RemainingBallDawn::
	msgbox SnowpointCity_Text_RemainingGoesToDawn, MSGBOX_DEFAULT
	return

SnowpointCity_EventScript_RemainingBallLucas::
	msgbox SnowpointCity_Text_RemainingGoesToLucas, MSGBOX_DEFAULT
	return

@ Barry has stepped round to (9, 12), just below the player.
SnowpointCity_EventScript_BarryBattle::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	playbgm MUS_DP_RIVAL, FALSE
	msgbox SnowpointCity_Text_BarryLetsBattle, MSGBOX_DEFAULT
	turnobject LOCALID_SNOWPOINT_ELDER, DIR_SOUTH
	msgbox SnowpointCity_Text_ElderSnowpointSpirit, MSGBOX_DEFAULT
	closemessage
	switch VAR_STARTER_MON
	case 0, SnowpointCity_EventScript_BattleBarryCranidos
	case 1, SnowpointCity_EventScript_BattleBarryTangela
	case 2, SnowpointCity_EventScript_BattleBarrySnorunt
	end

SnowpointCity_EventScript_BattleBarrySnorunt::
	trainerbattle_earlyrival TRAINER_BARRY_SNOWPOINT_SNORUNT, RIVAL_BATTLE_HEAL_AFTER, SnowpointCity_Text_BarryDefeat, SnowpointCity_Text_BarryVictory
	goto SnowpointCity_EventScript_AfterBarryBattle

SnowpointCity_EventScript_BattleBarryCranidos::
	trainerbattle_earlyrival TRAINER_BARRY_SNOWPOINT_CRANIDOS, RIVAL_BATTLE_HEAL_AFTER, SnowpointCity_Text_BarryDefeat, SnowpointCity_Text_BarryVictory
	goto SnowpointCity_EventScript_AfterBarryBattle

SnowpointCity_EventScript_BattleBarryTangela::
	trainerbattle_earlyrival TRAINER_BARRY_SNOWPOINT_TANGELA, RIVAL_BATTLE_HEAL_AFTER, SnowpointCity_Text_BarryDefeat, SnowpointCity_Text_BarryVictory
	goto SnowpointCity_EventScript_AfterBarryBattle

@ Cynthia steps down to (10, 11), beside the player, then goes back to her place.
SnowpointCity_EventScript_AfterBarryBattle::
	special HealPlayerParty
	applymovement LOCALID_SNOWPOINT_CYNTHIA, SnowpointCity_Movement_CynthiaComesForward
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	msgbox SnowpointCity_Text_CynthiaPokedex, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message SnowpointCity_Text_ReceivedPokedex
	waitmessage
	waitfanfare
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
	msgbox SnowpointCity_Text_BarryReceivedPokedex, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SNOWPOINT_CYNTHIA, SnowpointCity_Movement_CynthiaGoesBack
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	msgbox SnowpointCity_Text_ElderPokeBalls, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
	msgbox SnowpointCity_Text_ElderGym, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	msgbox SnowpointCity_Text_BarryGoingToBeChampion, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SNOWPOINT_BARRY, SnowpointCity_Movement_BarryRunOff
	waitmovement 0
	removeobject LOCALID_SNOWPOINT_BARRY
	setvar VAR_SNOWPOINT_INTRO_STATE, 10
	releaseall
	end

@ ---------------------------------------------------------------- ceremony NPCs
SnowpointCity_EventScript_Elder::
	lock
	faceplayer
	goto_if_ge VAR_SNOWPOINT_INTRO_STATE, 10, SnowpointCity_EventScript_ElderAfterCeremony
	msgbox SnowpointCity_Text_ElderChoose, MSGBOX_DEFAULT
	release
	end

SnowpointCity_EventScript_ElderAfterCeremony::
	msgbox SnowpointCity_Text_ElderAfterCeremony, MSGBOX_DEFAULT
	release
	end

SnowpointCity_EventScript_Cynthia::
	lock
	faceplayer
	goto_if_ge VAR_SNOWPOINT_INTRO_STATE, 10, SnowpointCity_EventScript_CynthiaAfterCeremony
	msgbox SnowpointCity_Text_CynthiaDuringChoice, MSGBOX_DEFAULT
	release
	end

SnowpointCity_EventScript_CynthiaAfterCeremony::
	msgbox SnowpointCity_Text_CynthiaAfterCeremony, MSGBOX_DEFAULT
	release
	end

SnowpointCity_EventScript_Garchomp::
	lock
	faceplayer
	playmoncry SPECIES_GARCHOMP, CRY_MODE_NORMAL
	msgbox SnowpointCity_Text_Garchomp, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SnowpointCity_EventScript_Barry::
	lock
	faceplayer
	msgbox SnowpointCity_Text_BarryHurryUp, MSGBOX_DEFAULT
	release
	end

SnowpointCity_Movement_BarryHop:
	face_down
	jump_in_place_down
	step_end

SnowpointCity_Movement_BarryMeFirst:
	jump_in_place_up
	jump_in_place_up
	step_end

SnowpointCity_Movement_WalkUp:
	walk_up
	step_end

SnowpointCity_Movement_WalkLeft:
	walk_left
	step_end

SnowpointCity_Movement_WalkRight:
	walk_right
	step_end

SnowpointCity_Movement_DownTwice:
	walk_down
	walk_down
	step_end

@ From (11, 10), the right-hand side of the right ball.
SnowpointCity_Movement_BackFromRightSide:
	walk_left
	walk_down
	walk_left
	step_end

SnowpointCity_Movement_ElderToFirstBall:
	walk_left
	face_down
	step_end

SnowpointCity_Movement_ElderToNextBall:
	walk_right
	face_down
	step_end

SnowpointCity_Movement_ElderBackToCenter:
	walk_left
	face_down
	step_end

@ The Snorunt ball is gone, so Barry steps into its place.
SnowpointCity_Movement_BarryToMiddleBall:
	walk_fast_right
	face_right
	step_end

@ The Snorunt ball is still there and the player is at (9, 11), so Barry goes round below them.
SnowpointCity_Movement_BarryToRightBall:
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	face_up
	step_end

@ From beside each ball to (9, 12), facing the player.
SnowpointCity_Movement_BarryFromLeftBall:
	walk_down
	walk_down
	walk_right
	walk_right
	face_up
	step_end

SnowpointCity_Movement_BarryFromMiddleBall:
	walk_down
	walk_down
	walk_right
	face_up
	step_end

SnowpointCity_Movement_BarryFromRightBall:
	walk_down
	walk_left
	face_up
	step_end

SnowpointCity_Movement_CynthiaComesForward:
	walk_down
	walk_down
	walk_left
	face_left
	step_end

SnowpointCity_Movement_CynthiaGoesBack:
	walk_right
	walk_up
	walk_up
	face_down
	step_end

SnowpointCity_Movement_BarryRunOff:
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	step_end

@ ---------------------------------------------------------------- east exit (to Route 217)
@ Triggers on the three road tiles in front of the shoveler; they do nothing once the player has a POKéMON.
SnowpointCity_EventScript_ShovelerBlocks::
	goto_if_set FLAG_SYS_POKEMON_GET, SnowpointCity_EventScript_ShovelerBlocksEnd
	lockall
	applymovement LOCALID_SNOWPOINT_SHOVELER, Common_Movement_FaceLeft
	waitmovement 0
	msgbox SnowpointCity_Text_RoadIsBuried, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, SnowpointCity_Movement_StepBackWest
	waitmovement 0
	releaseall
SnowpointCity_EventScript_ShovelerBlocksEnd::
	end

SnowpointCity_Movement_StepBackWest:
	walk_left
	step_end

SnowpointCity_EventScript_Shoveler::
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKEMON_GET, SnowpointCity_EventScript_ShovelerRoadClear
	msgbox SnowpointCity_Text_RoadIsBuried, MSGBOX_DEFAULT
	release
	end

SnowpointCity_EventScript_ShovelerRoadClear::
	msgbox SnowpointCity_Text_RoadIsClear, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------- townspeople
SnowpointCity_EventScript_SnoruntKid::
	msgbox SnowpointCity_Text_SnoruntKid, MSGBOX_NPC
	end

SnowpointCity_EventScript_Snorunt::
	lock
	faceplayer
	playmoncry SPECIES_SNORUNT, CRY_MODE_NORMAL
	msgbox SnowpointCity_Text_Snorunt, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SnowpointCity_EventScript_YoungTrainer::
	msgbox SnowpointCity_Text_YoungTrainer, MSGBOX_NPC
	end

SnowpointCity_EventScript_TempleWoman::
	msgbox SnowpointCity_Text_TempleWoman, MSGBOX_NPC
	end

SnowpointCity_EventScript_OlderMan::
	msgbox SnowpointCity_Text_OlderMan, MSGBOX_NPC
	end

SnowpointCity_EventScript_Teenager::
	msgbox SnowpointCity_Text_Teenager, MSGBOX_NPC
	end

SnowpointCity_EventScript_GymDoor::
	msgbox SnowpointCity_Text_GymDoor, MSGBOX_SIGN
	end

SnowpointCity_EventScript_ItemPotion::
	finditem ITEM_POTION
	end

SnowpointCity_EventScript_ItemPokeBall::
	finditem ITEM_POKE_BALL
	end

SnowpointCity_EventScript_ItemNeverMeltIce::
	finditem ITEM_NEVER_MELT_ICE
	end

SnowpointCity_Text_BarryFinally:
	.string "Barry: {PLAYER}! Finally!\p"
	.string "I've been running laps since sunrise.\n"
	.string "Twelve! I counted.\p"
	.string "Okay, maybe nine.\p"
	.string "Did you hear the news this morning?\n"
	.string "Sinnoh has a new Champion!\p"
	.string "That's going to be me someday,\n"
	.string "you'll see!\p"
	.string "The ceremony is today, and nobody\n"
	.string "will tell me what we have to do!\p"
	.string "My mom says it's different\n"
	.string "every year!\p"
	.string "Whatever it is, I'm going to be the\n"
	.string "first one done. No matter what!$"

SnowpointCity_Text_BarryRun:
	.string "Barry: Wait, why are you walking?\n"
	.string "You've got the shoes now, so run!\p"
	.string "Okay, I'm going ahead.\n"
	.string "Race you to the temple!$"

SnowpointCity_Text_BarryTooSlow:
	.string "Barry: Too slow, {PLAYER}!\n"
	.string "Come on!$"

SnowpointCity_Text_SnoruntKid:
	.string "Snorunt are the reason the ice around\n"
	.string "town never fully melts.\p"
	.string "My Snorunt follows me everywhere.\p"
	.string "Snorunt love the cold, so this is the\n"
	.string "best town in Sinnoh for them.$"

SnowpointCity_Text_Snorunt:
	.string "Snorunt: Snoru!$"

SnowpointCity_Text_YoungTrainer:
	.string "Did you see her? Cynthia!\p"
	.string "She was in town last night,\n"
	.string "here in Snowpoint!\p"
	.string "She's probably at the temple\n"
	.string "with the Elder.$"

SnowpointCity_Text_TempleWoman:
	.string "I traveled all the way from Pacifidlog\n"
	.string "Town in Hoenn just to see this temple.\p"
	.string "Back home, there's an old chamber\n"
	.string "under the sea with writing about\l"
	.string "three golems.\p"
	.string "Some say a giant made them. The very\n"
	.string "same giant that sleeps right here.$"

SnowpointCity_Text_OlderMan:
	.string "Cynthia gave up the Champion title\n"
	.string "not long ago.\p"
	.string "Family reasons, people say.\n"
	.string "Her grandmother needs her here.$"

SnowpointCity_Text_Teenager:
	.string "The League held a tournament to choose\n"
	.string "the new Champion.\p"
	.string "One TRAINER fought through every round\n"
	.string "and never lost a single battle.$"

SnowpointCity_Text_GymDoor:
	.string "Snowpoint City POKéMON Gym\n"
	.string "Leader: Elder\p"
	.string "The door won't open.$"

SnowpointCity_Text_RoadIsBuried:
	.string "Whoa there! The road's still buried\n"
	.string "from last night's snow.\p"
	.string "Without a POKéMON you'd get lost\n"
	.string "in the drifts out there.$"

SnowpointCity_Text_RoadIsClear:
	.string "Road's clear! Route 217 is that way.\p"
	.string "Stay close to your POKéMON.\n"
	.string "The snow gets deep fast.$"

SnowpointCity_Text_BarryYouMadeIt:
	.string "Barry: {PLAYER}! You made it!\n"
	.string "The Elder wouldn't start without you!$"

SnowpointCity_Text_ElderWelcome:
	.string "Elder: Welcome, {PLAYER}.\n"
	.string "Welcome, Barry.\p"
	.string "Now that you both are about to start\n"
	.string "your journey, you should be aware of\l"
	.string "the legends of this town.$"

SnowpointCity_Text_ElderAsksCynthia:
	.string "Cynthia, would you tell it?$"

SnowpointCity_Text_CynthiaOfCourse:
	.string "Cynthia: Of course.$"

SnowpointCity_Text_CynthiaLegend:
	.string "Cynthia: According to legend, the\n"
	.string "world was once a single landmass.\p"
	.string "It is said that a colossal titan\n"
	.string "pulled the land apart with its bare\l"
	.string "hands to form our regions.\p"
	.string "But the effort demanded a heavy\n"
	.string "toll, forcing the titan into\l"
	.string "hibernation to recover.\p"
	.string "This temple stands as a sanctuary\n"
	.string "built to watch over the slumbering\l"
	.string "giant, Regigigas.$"

SnowpointCity_Text_ElderCeremony:
	.string "Elder: Every child of this town who\n"
	.string "turns ten takes part in the ceremony.\p"
	.string "Today, that is the two of you.\p"
	.string "Three POKéMON were raised in this\n"
	.string "temple for this day.$"

SnowpointCity_Text_ElderChoose:
	.string "Elder: Take your time, and choose\n"
	.string "the one you feel closest to.$"

SnowpointCity_Text_BarryMeFirst:
	.string "Barry: Me first! Me first!$"

SnowpointCity_Text_ElderPatience:
	.string "Elder: Patience, Barry.\n"
	.string "{PLAYER} may choose first.$"

SnowpointCity_Text_ElderPokemonWaiting:
	.string "Elder: {PLAYER}, where are you going?\n"
	.string "The POKéMON are waiting for you.$"

SnowpointCity_Text_ChooseSnorunt:
	.string "Will you take Snorunt,\n"
	.string "the ICE-type POKéMON?$"

SnowpointCity_Text_ChooseCranidos:
	.string "Will you take Cranidos,\n"
	.string "the ROCK-type POKéMON?$"

SnowpointCity_Text_ChooseTangela:
	.string "Will you take Tangela,\n"
	.string "the GRASS-type POKéMON?$"

SnowpointCity_Text_ReceivedStarter:
	.string "{PLAYER} received the {STR_VAR_1}!$"

SnowpointCity_Text_BarryMyTurn:
	.string "Barry: Then I'll take this one!$"

SnowpointCity_Text_BarryLookAtThat:
	.string "Barry: Look at that! {STR_VAR_2} and I\n"
	.string "are going to be the best!$"

SnowpointCity_Text_RemainingGoesToDawn:
	.string "Elder: The remaining POKéMON will\n"
	.string "go to Dawn.$"

SnowpointCity_Text_RemainingGoesToLucas:
	.string "Elder: The remaining POKéMON will\n"
	.string "go to Lucas.$"

SnowpointCity_Text_BarryGoingToBeChampion:
	.string "Barry: I'm going to be Champion!\n"
	.string "See you later, {PLAYER}!$"

SnowpointCity_Text_ElderAfterCeremony:
	.string "Elder: Treat your partner well,\n"
	.string "{PLAYER}. The road ahead is long.$"

SnowpointCity_Text_CynthiaDuringChoice:
	.string "Cynthia: Don't think too hard.\n"
	.string "Listen to your heart.$"

SnowpointCity_Text_CynthiaAfterCeremony:
	.string "Cynthia: I once stood where you are,\n"
	.string "with a little Gible at my side.\p"
	.string "Look after each other, {PLAYER}.$"

SnowpointCity_Text_Garchomp:
	.string "Garchomp: Grraaoh!$"

SnowpointCity_Text_BarryHurryUp:
	.string "Barry: Come on, {PLAYER}!\n"
	.string "Pick already! I can't wait!$"

SnowpointCity_Text_ElderAboutSnorunt:
	.string "Elder: Snorunt has lived in these\n"
	.string "snows longer than the town has stood.\p"
	.string "Snorunt is patient.$"

SnowpointCity_Text_ElderAboutCranidos:
	.string "Elder: Cranidos was revived from a\n"
	.string "fossil found beneath this temple,\p"
	.string "from the age when the land was still\n"
	.string "being pulled into place.$"

SnowpointCity_Text_ElderAboutTangela:
	.string "Elder: Tangela's vines remind people\n"
	.string "of the old ropes.\p"
	.string "Some say that is no accident.$"

SnowpointCity_Text_ReservedForDawn:
	.string "The POKé BALL left on the altar.\n"
	.string "The Elder is keeping it for Dawn.$"

SnowpointCity_Text_ReservedForLucas:
	.string "The POKé BALL left on the altar.\n"
	.string "The Elder is keeping it for Lucas.$"

SnowpointCity_Text_BarryLetsBattle:
	.string "Barry: That was great!\n"
	.string "But I'm not done.\p"
	.string "Let's battle, {PLAYER}!$"

SnowpointCity_Text_ElderSnowpointSpirit:
	.string "Elder: That's the Snowpoint City\n"
	.string "spirit!$"

SnowpointCity_Text_BarryDefeat:
	.string "You got lucky! I'll get stronger,\n"
	.string "just wait!$"

SnowpointCity_Text_BarryVictory:
	.string "Yes! I won! I told you I'd be\n"
	.string "first at everything!$"

SnowpointCity_Text_CynthiaPokedex:
	.string "Cynthia: Well done, both of you.\p"
	.string "I have something for you, {PLAYER}.\p"
	.string "This is a POKéDEX. It records every\n"
	.string "POKéMON you meet.\p"
	.string "I could use the help with my\n"
	.string "research.$"

SnowpointCity_Text_ReceivedPokedex:
	.string "{PLAYER} received the POKéDEX!$"

SnowpointCity_Text_BarryReceivedPokedex:
	.string "Barry received a POKéDEX too!$"

SnowpointCity_Text_ElderPokeBalls:
	.string "Elder: Here are a few POKé BALLS\n"
	.string "as well.$"

SnowpointCity_Text_ElderGym:
	.string "Elder: The road ahead is long, and it\n"
	.string "ends at my Gym across town.\p"
	.string "Come back when you have earned seven\n"
	.string "Badges, and I'll be waiting.$"
