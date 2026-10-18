SnowpointCity_PlayersHouse_2F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SnowpointCity_PlayersHouse_2F_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SnowpointCity_PlayersHouse_2F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SnowpointCity_PlayersHouse_2F_OnFrame
	.byte 0

SnowpointCity_PlayersHouse_2F_OnLoad:
	call_if_eq VAR_SNOWPOINT_INTRO_STATE, 0, SnowpointCity_PlayersHouse_2F_EventScript_TurnOnTV
	end

SnowpointCity_PlayersHouse_2F_EventScript_TurnOnTV::
	setmetatile 2, 3, METATILE_PlayersRoom_TV_On_Left, TRUE
	setmetatile 3, 3, METATILE_PlayersRoom_TV_On_Right, TRUE
	return

SnowpointCity_PlayersHouse_2F_OnWarp:
	map_script_2 VAR_SNOWPOINT_INTRO_STATE, 0, SnowpointCity_PlayersHouse_2F_EventScript_FaceTV
	.2byte 0

SnowpointCity_PlayersHouse_2F_EventScript_FaceTV::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

SnowpointCity_PlayersHouse_2F_OnFrame:
	map_script_2 VAR_SNOWPOINT_INTRO_STATE, 0, SnowpointCity_PlayersHouse_2F_EventScript_MorningNews
	.2byte 0

SnowpointCity_PlayersHouse_2F_EventScript_MorningNews::
	lockall
	delay 30
	msgbox SnowpointCity_PlayersHouse_2F_Text_LeagueNews, MSGBOX_DEFAULT
	msgbox SnowpointCity_PlayersHouse_2F_Text_Weather, MSGBOX_DEFAULT
	closemessage
	delay 20
	playse SE_PC_OFF
	setmetatile 2, 3, METATILE_PlayersRoom_TV_Off_Left, TRUE
	setmetatile 3, 3, METATILE_PlayersRoom_TV_Off_Right, TRUE
	special DrawWholeMapView
	waitse
	setvar VAR_SNOWPOINT_INTRO_STATE, 1
	releaseall
	end

@ The bedroom PC is the player's own: item storage only, no POKéMON boxes.
SnowpointCity_PlayersHouse_2F_EventScript_PC::
	lockall
	playse SE_PC_ON
	msgbox gText_PlayerHouseBootPC, MSGBOX_DEFAULT
	special PlayerPC
	waitstate
	playse SE_PC_OFF
	releaseall
	end

SnowpointCity_PlayersHouse_2F_EventScript_Notebook::
	msgbox SnowpointCity_PlayersHouse_2F_Text_Notebook, MSGBOX_SIGN
	end

SnowpointCity_PlayersHouse_2F_EventScript_TV::
	msgbox SnowpointCity_PlayersHouse_2F_Text_TV, MSGBOX_SIGN
	end

SnowpointCity_PlayersHouse_2F_EventScript_GameConsole::
	msgbox SnowpointCity_PlayersHouse_2F_Text_GameConsole, MSGBOX_SIGN
	end

SnowpointCity_PlayersHouse_2F_EventScript_Map::
	msgbox SnowpointCity_PlayersHouse_2F_Text_Map, MSGBOX_SIGN
	end

SnowpointCity_PlayersHouse_2F_EventScript_Bookshelf::
	msgbox SnowpointCity_PlayersHouse_2F_Text_Bookshelf, MSGBOX_SIGN
	end

SnowpointCity_PlayersHouse_2F_EventScript_Bed::
	msgbox SnowpointCity_PlayersHouse_2F_Text_Bed, MSGBOX_SIGN
	end

SnowpointCity_PlayersHouse_2F_EventScript_Wastebasket::
	msgbox SnowpointCity_PlayersHouse_2F_Text_Wastebasket, MSGBOX_SIGN
	end

SnowpointCity_PlayersHouse_2F_EventScript_Dresser::
	msgbox SnowpointCity_PlayersHouse_2F_Text_Dresser, MSGBOX_SIGN
	end

SnowpointCity_PlayersHouse_2F_EventScript_Kotatsu::
	msgbox SnowpointCity_PlayersHouse_2F_Text_Kotatsu, MSGBOX_SIGN
	end

SnowpointCity_PlayersHouse_2F_Text_LeagueNews:
	.string "In League news, Sinnoh has a new\n"
	.string "Champion.\p"
	.string "We'll have more on the TRAINER who won\n"
	.string "the title after the weather.$"

SnowpointCity_PlayersHouse_2F_Text_Weather:
	.string "Snow will continue through the day in\n"
	.string "the north, so bundle up if you're\l"
	.string "heading out.$"

SnowpointCity_PlayersHouse_2F_Text_Notebook:
	.string "It's {PLAYER}'s notebook.\p"
	.string "“Things to do today:\n"
	.string "1. Wake up early.”\p"
	.string "That one's been crossed out…$"

SnowpointCity_PlayersHouse_2F_Text_TV:
	.string "It's the weather report again.\p"
	.string "Snow, snow, and more snow…\n"
	.string "Still no word on the new Champion.$"

SnowpointCity_PlayersHouse_2F_Text_GameConsole:
	.string "It's a game console.\p"
	.string "Better not start playing now.\n"
	.string "The Elder is waiting!$"

SnowpointCity_PlayersHouse_2F_Text_Map:
	.string "It's a map of the Sinnoh region.\p"
	.string "Snowpoint City sits all the way\n"
	.string "up at the northern tip.$"

SnowpointCity_PlayersHouse_2F_Text_Bookshelf:
	.string "It's crammed with books about\n"
	.string "POKéMON and old Snowpoint legends.$"

SnowpointCity_PlayersHouse_2F_Text_Bed:
	.string "{PLAYER}'s bed.\n"
	.string "It's still warm…$"

SnowpointCity_PlayersHouse_2F_Text_Wastebasket:
	.string "Crumpled drawings of Regigigas…\n"
	.string "None of them look quite right.$"

SnowpointCity_PlayersHouse_2F_Text_Dresser:
	.string "{PLAYER}'s dresser.\p"
	.string "The top drawer is all wool socks\n"
	.string "and scarves.$"

SnowpointCity_PlayersHouse_2F_Text_Kotatsu:
	.string "A low table with a heated blanket\n"
	.string "tucked underneath.\p"
	.string "It's the warmest spot in the house.$"
