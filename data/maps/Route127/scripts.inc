Route127_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route127_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route127_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route127_OnFrame
	.byte 0

Route127_OnTransition:
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	call_if_eq VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_HideMapNamePopup
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_127_NORTH, AbnormalWeather_StartKyogreWeather
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_127_SOUTH, AbnormalWeather_StartKyogreWeather
	end

Route127_OnLoad:
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_127_NORTH, AbnormalWeather_EventScript_PlaceTilesRoute127North
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_127_SOUTH, AbnormalWeather_EventScript_PlaceTilesRoute127South
	end

Route127_OnFrame:
	map_script_2 VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_EndEventAndCleanup_1
	.2byte 0

Route127_EventScript_Camden::
	msgbox Route127_Text_CamdenPostBattle, MSGBOX_AUTOCLOSE
	end

Route127_EventScript_Donny::
	msgbox Route127_Text_DonnyPostBattle, MSGBOX_AUTOCLOSE
	end

Route127_EventScript_Jonah::
	msgbox Route127_Text_JonahPostBattle, MSGBOX_AUTOCLOSE
	end

Route127_EventScript_Henry::
	msgbox Route127_Text_HenryPostBattle, MSGBOX_AUTOCLOSE
	end

Route127_EventScript_Roger::
	msgbox Route127_Text_RogerPostBattle, MSGBOX_AUTOCLOSE
	end

Route127_EventScript_Aidan::
	msgbox Route127_Text_AidanPostBattle, MSGBOX_AUTOCLOSE
	end

Route127_EventScript_Athena::
	msgbox Route127_Text_AthenaPostBattle, MSGBOX_AUTOCLOSE
	end

Route127_EventScript_Koji::
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route127_EventScript_RematchKoji
	msgbox Route127_Text_KojiPostBattle, MSGBOX_DEFAULT
	release
	end

Route127_EventScript_RegisterKoji::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route127_Text_KojiRegister, MSGBOX_DEFAULT
	release
	end

Route127_EventScript_RematchKoji::
	msgbox Route127_Text_KojiPostRematch, MSGBOX_AUTOCLOSE
	end

