#ifndef GUARD_CONSTANTS_OPPONENTS_H
#define GUARD_CONSTANTS_OPPONENTS_H

#include "constants/battle_partner.h"
#include "constants/opponents_frlg.h"

#define TRAINER_NONE                          0
#define TRAINER_BARRY_SNOWPOINT_SNORUNT       1
#define TRAINER_BARRY_SNOWPOINT_CRANIDOS      2
#define TRAINER_BARRY_SNOWPOINT_TANGELA       3
#define TRAINER_TAD                           4
#define TRAINER_WES                           5
#define TRAINER_DANA                          6
#define TRAINER_BRAM                          7
#define TRAINER_CORA                          8
#define TRAINER_HALE                          9
#define TRAINER_RANCHER_WADE                  10
#define TRAINER_COWGIRL_LILY                  11
#define TRAINER_BARRY_TILLBROOK_SNORUNT       12
#define TRAINER_BARRY_TILLBROOK_CRANIDOS      13
#define TRAINER_BARRY_TILLBROOK_TANGELA       14
#define TRAINER_PAUL_TILLBROOK_SNORUNT        15
#define TRAINER_PAUL_TILLBROOK_CRANIDOS       16
#define TRAINER_PAUL_TILLBROOK_TANGELA        17

// NOTE: Each Trainer uses a flag to record when they are defeated, so only MAX_TRAINERS_COUNT trainers fit in the trainer flag space.
//       More space can be made by shifting flags around in constants/flags.h or changing how trainer flags are handled
//       MAX_TRAINERS_COUNT can be increased but will take up additional saveblock space

#if TESTING
#define TRAINERS_COUNT_EMERALD     MAX_TRAINERS_COUNT_EMERALD // the test suite numbers its own trainers past the game's few
#else
#define TRAINERS_COUNT_EMERALD     18
#endif
#define MAX_TRAINERS_COUNT_EMERALD 864

#if IS_FRLG
#define TRAINERS_COUNT                      TRAINERS_COUNT_FRLG
#define MAX_TRAINERS_COUNT                  MAX_TRAINERS_COUNT_FRLG
#else
#define TRAINERS_COUNT                      TRAINERS_COUNT_EMERALD
#define MAX_TRAINERS_COUNT                  MAX_TRAINERS_COUNT_EMERALD
#endif
#define TRAINER_PARTNER(partner)           (MAX_TRAINERS_COUNT + partner)

#endif  // GUARD_CONSTANTS_OPPONENTS_H
