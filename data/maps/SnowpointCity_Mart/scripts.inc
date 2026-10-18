SnowpointCity_Mart_MapScripts::
	.byte 0

@ The Mart opens once the ceremony is over (VAR_SNOWPOINT_INTRO_STATE reaches 10).
SnowpointCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	goto_if_ge VAR_SNOWPOINT_INTRO_STATE, 10, SnowpointCity_Mart_EventScript_Shop
	msgbox SnowpointCity_Mart_Text_AfterTheCeremony, MSGBOX_DEFAULT
	release
	end

SnowpointCity_Mart_EventScript_Shop::
	message SnowpointCity_Mart_Text_Welcome
	waitmessage
	pokemart SnowpointCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SnowpointCity_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	pokemartlistend

SnowpointCity_Mart_Text_AfterTheCeremony:
	.string "Oh, it's you. I'll open after the\n"
	.string "ceremony.\p"
	.string "Everyone in town is going to be there,\n"
	.string "myself included.\p"
	.string "I took part in the ceremony forty years\n"
	.string "ago. I won't spoil it for you.\p"
	.string "I will say this. Bring a warm coat.$"

SnowpointCity_Mart_Text_Welcome:
	.string "Welcome! Snowpoint doesn't get many\n"
	.string "travelers, but I have what you need.$"
