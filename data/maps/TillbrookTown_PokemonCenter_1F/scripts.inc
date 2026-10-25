TillbrookTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TillbrookTown_PokemonCenter_1F_OnTransition
	.byte 0

TillbrookTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_TILLBROOK_TOWN
	end

TillbrookTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_TILLBROOK_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

TillbrookTown_PokemonCenter_1F_EventScript_BoxTrainer::
	msgbox TillbrookTown_PokemonCenter_1F_Text_BoxStorage, MSGBOX_NPC
	end

TillbrookTown_PokemonCenter_1F_Text_BoxStorage:
	.string "That PC lets you store Pokémon.\p"
	.string "Choose someone's PC to open your\n"
	.string "Boxes and organize your Pokémon.\p"
	.string "You can deposit party Pokémon or\n"
	.string "withdraw Pokémon from a Box.\p"
	.string "If your party is full, newly caught\n"
	.string "Pokémon go to a Box automatically!$"
