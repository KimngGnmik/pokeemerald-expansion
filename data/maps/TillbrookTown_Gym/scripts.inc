#ifndef FLAG_DEFEATED_ROXANNE
#define FLAG_DEFEATED_ROXANNE FLAG_DEFEATED_RUSTBORO_GYM
#endif

TillbrookTown_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TillbrookTown_Gym_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, TillbrookTown_Gym_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, TillbrookTown_Gym_OnWarp
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, TillbrookTown_Gym_OnReturn
	.byte 0

TillbrookTown_Gym_OnTransition:
	setflag FLAG_TEMP_HIDE_FOLLOWER
	end

TillbrookTown_Gym_OnLoad:
	special TillbrookGym_Load
	end

TillbrookTown_Gym_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, TillbrookTown_Gym_OnReturn
	.2byte 0

TillbrookTown_Gym_OnReturn:
	special TillbrookGym_RestoreObjects
	end

TillbrookTown_Gym_EventScript_Miltank::
	lock
	faceplayer
	msgbox TillbrookTown_Gym_Text_Miltank, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TillbrookTown_Gym_EventScript_MiltankEnd
	special TillbrookGym_ResetSection
	playse SE_SWITCH
TillbrookTown_Gym_EventScript_MiltankEnd:
	release
	end

TillbrookTown_Gym_EventScript_Reset::
	lockall
	msgbox TillbrookTown_Gym_Text_ResetPrompt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TillbrookTown_Gym_EventScript_ResetEnd
	special TillbrookGym_ResetSection
	playse SE_SWITCH
	msgbox TillbrookTown_Gym_Text_ResetDone, MSGBOX_DEFAULT
TillbrookTown_Gym_EventScript_ResetEnd:
	releaseall
	end

TillbrookTown_Gym_EventScript_Guide::
	lock
	faceplayer
	goto_if_set FLAG_BADGE01_GET, TillbrookTown_Gym_EventScript_GuideWin
	msgbox TillbrookTown_Gym_Text_Guide, MSGBOX_DEFAULT
	release
	end

TillbrookTown_Gym_EventScript_GuideWin:
	msgbox TillbrookTown_Gym_Text_GuideWin, MSGBOX_DEFAULT
	release
	end

TillbrookTown_Gym_EventScript_Wade::
	trainerbattle_single TRAINER_RANCHER_WADE, TillbrookTown_Gym_Text_WadeIntro, TillbrookTown_Gym_Text_WadeDefeat
	msgbox TillbrookTown_Gym_Text_WadeAfter, MSGBOX_AUTOCLOSE
	end

TillbrookTown_Gym_EventScript_Lily::
	trainerbattle_single TRAINER_COWGIRL_LILY, TillbrookTown_Gym_Text_LilyIntro, TillbrookTown_Gym_Text_LilyDefeat
	msgbox TillbrookTown_Gym_Text_LilyAfter, MSGBOX_AUTOCLOSE
	end

TillbrookTown_Gym_EventScript_Hale::
	lock
	faceplayer
	goto_if_set FLAG_BADGE01_GET, TillbrookTown_Gym_EventScript_Return
	trainerbattle_single TRAINER_HALE, TillbrookTown_Gym_Text_HaleIntro, TillbrookTown_Gym_Text_HaleDefeat, TillbrookTown_Gym_EventScript_HaleVictory
	goto TillbrookTown_Gym_EventScript_HaleVictory

TillbrookTown_Gym_EventScript_HaleVictory::
	message TillbrookTown_Gym_Text_Badge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_BADGE01_GET
	setflag FLAG_DEFEATED_ROXANNE
	msgbox TillbrookTown_Gym_Text_BadgeInfo, MSGBOX_DEFAULT
	goto TillbrookTown_Gym_EventScript_Return

TillbrookTown_Gym_EventScript_Return:
	goto_if_set FLAG_TILLBROOK_RETURN_RECEIVED, TillbrookTown_Gym_EventScript_HaleAfter
	giveitem ITEM_TM_RETURN
	goto_if_eq VAR_RESULT, FALSE, TillbrookTown_Gym_EventScript_BagFull
	setflag FLAG_TILLBROOK_RETURN_RECEIVED
	msgbox TillbrookTown_Gym_Text_Return, MSGBOX_DEFAULT
	release
	end

TillbrookTown_Gym_EventScript_BagFull:
	msgbox TillbrookTown_Gym_Text_BagFull, MSGBOX_DEFAULT
	release
	end

TillbrookTown_Gym_EventScript_HaleAfter:
	msgbox TillbrookTown_Gym_Text_HaleAfter, MSGBOX_DEFAULT
	release
	end

TillbrookTown_Gym_Text_Guide:
	.string "Welcome to Hale's barn Gym!\n"
	.string "He trains Normal-type Pokémon.\p"
	.string "Guide each Miltank into its golden\n"
	.string "straw stall to open the next gate.\p"
	.string "Walk into a Miltank to gently push\n"
	.string "it. No HM or Badge is needed here!\p"
	.string "You must stand behind it. You can't\n"
	.string "pull it, so leave room to walk around.\p"
	.string "Stuck? Ring the bell on the post\n"
	.string "in your pen to reset that cow.\p"
	.string "If it blocks the post, talk to the\n"
	.string "Miltank to call it back instead.\p"
	.string "Leaving or reloading resets cows\n"
	.string "that aren't stalled. Open gates stay!\p"
	.string "Fighting moves work well here.\n"
	.string "Ghost moves won't hit Normal types!$"

TillbrookTown_Gym_Text_GuideWin:
	.string "The Furrow Badge suits you!\n"
	.string "You earned every inch of that field.$"

TillbrookTown_Gym_Text_Miltank:
	.string "Miltank: Mooo!\p"
	.string "Call this pen's unstalled Miltank\n"
	.string "back to its starting spot?$"

TillbrookTown_Gym_Text_ResetPrompt:
	.string "A bell hangs from the post.\p"
	.string "Return this pen's unstalled Miltank\n"
	.string "to its starting spot?$"

TillbrookTown_Gym_Text_ResetDone:
	.string "The bell rings softly.\n"
	.string "Stalled Miltank stay settled.$"

TillbrookTown_Gym_Text_WadeIntro:
	.string "A steady hand and a patient heart.\n"
	.string "Show me both!$"

TillbrookTown_Gym_Text_WadeDefeat:
	.string "You've got a good feel for this!$"

TillbrookTown_Gym_Text_WadeAfter:
	.string "Walk around to the other side before\n"
	.string "you push. That's the rancher's way!$"

TillbrookTown_Gym_Text_LilyIntro:
	.string "We work together here!\n"
	.string "Can your team keep up with ours?$"

TillbrookTown_Gym_Text_LilyDefeat:
	.string "Now that's real teamwork!$"

TillbrookTown_Gym_Text_LilyAfter:
	.string "Hale says trust grows like a crop.\n"
	.string "A little care, every single day.$"

TillbrookTown_Gym_Text_HaleIntro:
	.string "Hale: Welcome, {PLAYER}.\n"
	.string "I'm Tillbrook's Gym Leader.\p"
	.string "You treated our Miltank with care.\n"
	.string "That's a fine start.\p"
	.string "Normal-type Pokémon are dependable.\n"
	.string "Give them trust, and they give it back.\p"
	.string "Let's see what you and your partners\n"
	.string "can grow together!$"

TillbrookTown_Gym_Text_HaleDefeat:
	.string "Well tended. Well earned.\n"
	.string "Your bond is strong!$"

TillbrookTown_Gym_Text_Badge:
	.string "{PLAYER} received the Furrow Badge\n"
	.string "from Hale!$"

TillbrookTown_Gym_Text_BadgeInfo:
	.string "The Furrow Badge marks your first\n"
	.string "step as a Pokémon League challenger.\p"
	.string "Like the first furrow in a field,\n"
	.string "it's the beginning of something great.\p"
	.string "It also lets you use Cut outside\n"
	.string "of battle once you've learned it.\p"
	.string "Here. A little something to help\n"
	.string "your friendship bear fruit.$"

TillbrookTown_Gym_Text_Return:
	.string "TM27 contains Return.\p"
	.string "The stronger your friendship with\n"
	.string "your Pokémon, the harder it hits.\p"
	.string "Care for your partners, {PLAYER}.\n"
	.string "They'll always return that kindness.$"

TillbrookTown_Gym_Text_BagFull:
	.string "Your Bag's full. Make room and\n"
	.string "come back. I'll keep your TM safe.$"

TillbrookTown_Gym_Text_HaleAfter:
	.string "A good harvest takes time.\n"
	.string "Keep growing together, {PLAYER}.$"
