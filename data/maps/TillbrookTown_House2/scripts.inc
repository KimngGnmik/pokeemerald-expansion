TillbrookTown_House2_MapScripts::
	.byte 0

TillbrookTown_House2_EventScript_FriendshipRater::
	lock
	faceplayer
	msgbox TillbrookTown_House2_Text_LetMeSee, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	switch VAR_RESULT
	case FRIENDSHIP_NONE, TillbrookTown_House2_EventScript_DetestsYou
	case FRIENDSHIP_1_TO_49, TillbrookTown_House2_EventScript_VeryWary
	case FRIENDSHIP_50_TO_99, TillbrookTown_House2_EventScript_NotUsedToYou
	case FRIENDSHIP_100_TO_149, TillbrookTown_House2_EventScript_GettingUsedToYou
	case FRIENDSHIP_150_TO_199, TillbrookTown_House2_EventScript_LikesYouQuiteALot
	case FRIENDSHIP_200_TO_254, TillbrookTown_House2_EventScript_VeryHappy
	case FRIENDSHIP_MAX, TillbrookTown_House2_EventScript_AdoresYou
	release
	end

TillbrookTown_House2_EventScript_DetestsYou::
	msgbox TillbrookTown_House2_Text_DetestsYou, MSGBOX_DEFAULT
	release
	end

TillbrookTown_House2_EventScript_VeryWary::
	msgbox TillbrookTown_House2_Text_VeryWary, MSGBOX_DEFAULT
	release
	end

TillbrookTown_House2_EventScript_NotUsedToYou::
	msgbox TillbrookTown_House2_Text_NotUsedToYou, MSGBOX_DEFAULT
	release
	end

TillbrookTown_House2_EventScript_GettingUsedToYou::
	msgbox TillbrookTown_House2_Text_GettingUsedToYou, MSGBOX_DEFAULT
	release
	end

TillbrookTown_House2_EventScript_LikesYouQuiteALot::
	msgbox TillbrookTown_House2_Text_LikesYouQuiteALot, MSGBOX_DEFAULT
	release
	end

TillbrookTown_House2_EventScript_VeryHappy::
	msgbox TillbrookTown_House2_Text_VeryHappy, MSGBOX_DEFAULT
	release
	end

TillbrookTown_House2_EventScript_AdoresYou::
	msgbox TillbrookTown_House2_Text_AdoresYou, MSGBOX_DEFAULT
	release
	end

TillbrookTown_House2_Text_LetMeSee:
	.string "Let me see your Pokémon.\n"
	.string "I can tell how much it likes you.\p"
	.string "Oh! Your Pokémon…$"

TillbrookTown_House2_Text_DetestsYou:
	.string "It doesn't seem to like you at all.\n"
	.string "Have you been treating it badly?$"

TillbrookTown_House2_Text_VeryWary:
	.string "It's still very wary of you.\n"
	.string "Give it time, and a little kindness.$"

TillbrookTown_House2_Text_NotUsedToYou:
	.string "It isn't used to you yet.\n"
	.string "It doesn't like or dislike you.$"

TillbrookTown_House2_Text_GettingUsedToYou:
	.string "It's starting to get used to you.\n"
	.string "It believes in you a little.$"

TillbrookTown_House2_Text_LikesYouQuiteALot:
	.string "It likes you quite a lot.\n"
	.string "It seems to want to be babied.$"

TillbrookTown_House2_Text_VeryHappy:
	.string "It looks very happy.\n"
	.string "It must love being with you.$"

TillbrookTown_House2_Text_AdoresYou:
	.string "It adores you! It can't possibly\n"
	.string "love you any more than it does.\p"
	.string "A Return from that one would hit\n"
	.string "as hard as a Return can.$"
