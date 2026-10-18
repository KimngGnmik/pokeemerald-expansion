Route134_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Route134_OnResume
	.byte 0

Route134_OnResume:
	setdivewarp MAP_UNDERWATER_ROUTE134, 8, 6
	end

Route134_EventScript_Jack::
	msgbox Route134_Text_JackPostBattle, MSGBOX_AUTOCLOSE
	end

Route134_EventScript_Laurel::
	msgbox Route134_Text_LaurelPostBattle, MSGBOX_AUTOCLOSE
	end

Route134_EventScript_Alex::
	msgbox Route134_Text_AlexPostBattle, MSGBOX_AUTOCLOSE
	end

Route134_EventScript_Aaron::
	msgbox Route134_Text_AaronPostBattle, MSGBOX_AUTOCLOSE
	end

Route134_EventScript_Hitoshi::
	msgbox Route134_Text_HitoshiPostBattle, MSGBOX_AUTOCLOSE
	end

Route134_EventScript_Hudson::
	msgbox Route134_Text_HudsonPostBattle, MSGBOX_AUTOCLOSE
	end

Route134_EventScript_Reyna::
	msgbox Route134_Text_ReynaPostBattle, MSGBOX_AUTOCLOSE
	end

Route134_EventScript_Marley::
	msgbox Route134_Text_MarleyPostBattle, MSGBOX_AUTOCLOSE
	end

Route134_EventScript_Kelvin::
	msgbox Route134_Text_KelvinPostBattle, MSGBOX_AUTOCLOSE
	end

