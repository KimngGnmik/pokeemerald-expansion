#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "tillbrook.h"
#include "constants/vars.h"

void Tillbrook_SaveFaintedParty(void)
{
    u32 slot;
    u16 fainted = 0;

    for (slot = 0; slot < PARTY_SIZE; slot++)
    {
        if (GetMonData(&gParties[B_TRAINER_PLAYER][slot], MON_DATA_SPECIES) != SPECIES_NONE
            && GetMonData(&gParties[B_TRAINER_PLAYER][slot], MON_DATA_HP) == 0)
            fainted |= 1 << slot;
    }
    VarSet(VAR_TILLBROOK_PRE_PAUL_FAINTED, fainted);
}

void Tillbrook_RevivePaulCasualties(void)
{
    u32 slot;
    u16 faintedBeforeBattle = VarGet(VAR_TILLBROOK_PRE_PAUL_FAINTED);
    u16 hp = 1;

    for (slot = 0; slot < PARTY_SIZE; slot++)
    {
        if (!(faintedBeforeBattle & (1 << slot))
            && GetMonData(&gParties[B_TRAINER_PLAYER][slot], MON_DATA_SPECIES) != SPECIES_NONE
            && !GetMonData(&gParties[B_TRAINER_PLAYER][slot], MON_DATA_IS_EGG)
            && GetMonData(&gParties[B_TRAINER_PLAYER][slot], MON_DATA_HP) == 0)
            SetMonData(&gParties[B_TRAINER_PLAYER][slot], MON_DATA_HP, &hp);
    }
    VarSet(VAR_TILLBROOK_PRE_PAUL_FAINTED, 0);
}
