Route217_RestCabin_MapScripts::
	.byte 0

@ The only place to heal on Route 217.
Route217_RestCabin_EventScript_OldWoman::
	lock
	faceplayer
	msgbox Route217_RestCabin_Text_LetThemRest, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox Route217_RestCabin_Text_CeremonyOver, MSGBOX_DEFAULT
	release
	end

Route217_RestCabin_Text_LetThemRest:
	.string "Cold out there, isn't it?\n"
	.string "Let your Pokémon rest a minute.$"

Route217_RestCabin_Text_CeremonyOver:
	.string "I watched you walk down from\n"
	.string "Snowpoint. So the ceremony is\l"
	.string "over already?\p"
	.string "Good luck on the road.$"
