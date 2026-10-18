SnowpointCity_NeighborsHouse_MapScripts::
	.byte 0

SnowpointCity_NeighborsHouse_EventScript_Neighbor::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_OLD_GATEAU, SnowpointCity_NeighborsHouse_EventScript_MyCeremony
	msgbox SnowpointCity_NeighborsHouse_Text_ThatTimeAlready, MSGBOX_DEFAULT
	giveitem ITEM_OLD_GATEAU
	goto_if_eq VAR_RESULT, FALSE, SnowpointCity_NeighborsHouse_EventScript_BagFull
	setflag FLAG_RECEIVED_OLD_GATEAU
	release
	end

SnowpointCity_NeighborsHouse_EventScript_MyCeremony::
	msgbox SnowpointCity_NeighborsHouse_Text_MyCeremony, MSGBOX_DEFAULT
	release
	end

SnowpointCity_NeighborsHouse_EventScript_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

SnowpointCity_NeighborsHouse_EventScript_Photo::
	msgbox SnowpointCity_NeighborsHouse_Text_Photo, MSGBOX_SIGN
	end

SnowpointCity_NeighborsHouse_Text_ThatTimeAlready:
	.string "Is it that time already? I remember\n"
	.string "when you were learning to walk.\p"
	.string "The ceremony only happens for children\n"
	.string "who turn ten, so some years it's one\l"
	.string "child and some years it's five.\p"
	.string "This year it's you and Barry.\p"
	.string "Here, take this. You'll want something\n"
	.string "warm in your stomach.$"

SnowpointCity_NeighborsHouse_Text_MyCeremony:
	.string "That's my ceremony, twenty years ago.\p"
	.string "I'm the one with the missing tooth.$"

SnowpointCity_NeighborsHouse_Text_Photo:
	.string "A framed photo: a row of children in\n"
	.string "winter coats, lined up on the temple\l"
	.string "steps.$"
