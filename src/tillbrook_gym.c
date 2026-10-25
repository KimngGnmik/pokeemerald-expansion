#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_camera.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "overworld.h"
#include "sound.h"
#include "tillbrook_gym.h"
#include "constants/event_objects.h"
#include "constants/flags.h"
#include "constants/maps.h"
#include "constants/songs.h"
#include "constants/species.h"

// Local IDs 1-3 are the cows. Coordinates exclude MAP_OFFSET.
static const struct
{
    u16 flag;
    u8 startX, startY;
    u8 stallX, stallY;
    u8 gateY;
} sStalls[] =
{
    {FLAG_TILLBROOK_STALL_1, 4, 23, 2, 22, 20},
    {FLAG_TILLBROOK_STALL_2, 6, 16, 8, 15, 13},
    {FLAG_TILLBROOK_STALL_3, 4,  9, 2,  8,  6},
};

static bool8 sRestoreObjects;

static bool8 IsGym(void)
{
    return gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_TILLBROOK_TOWN_GYM)
        && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_TILLBROOK_TOWN_GYM);
}

static void UpdateGate(u32 stall)
{
    // Original Petalburg Gym timber railing and plank floor.
    MapGridSetMetatileIdAt(5 + MAP_OFFSET, sStalls[stall].gateY + MAP_OFFSET,
                         FlagGet(sStalls[stall].flag) ? 0x201 : 0x203 | MAPGRID_COLLISION_MASK);
}

bool8 IsTillbrookGymMiltank(const struct ObjectEvent *objectEvent)
{
    return IsGym()
        && objectEvent->localId >= 1
        && objectEvent->localId <= ARRAY_COUNT(sStalls)
        && objectEvent->graphicsId == OBJ_EVENT_GFX_SPECIES(MILTANK)
        && !FlagGet(sStalls[objectEvent->localId - 1].flag);
}

void TillbrookGym_OnPushComplete(struct ObjectEvent *objectEvent)
{
    u32 stall;

    if (!IsTillbrookGymMiltank(objectEvent))
        return;

    stall = objectEvent->localId - 1;
    SetObjEventTemplateCoords(objectEvent->localId,
                             objectEvent->currentCoords.x - MAP_OFFSET,
                             objectEvent->currentCoords.y - MAP_OFFSET);
    objectEvent->initialCoords = objectEvent->currentCoords;
    if (objectEvent->currentCoords.x == sStalls[stall].stallX + MAP_OFFSET
     && objectEvent->currentCoords.y == sStalls[stall].stallY + MAP_OFFSET)
    {
        FlagSet(sStalls[stall].flag);
        UpdateGate(stall);
        DrawWholeMapView();
        PlaySE(SE_PIN);
    }
}

void TillbrookGym_Load(void)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sStalls); i++)
    {
        bool8 solved = FlagGet(sStalls[i].flag);
        SetObjEventTemplateCoords(i + 1, solved ? sStalls[i].stallX : sStalls[i].startX,
                                        solved ? sStalls[i].stallY : sStalls[i].startY);
        UpdateGate(i);
    }
    sRestoreObjects = TRUE;
}

static void RestoreCow(u32 i)
{
    u8 objectEventId;
    bool8 solved = FlagGet(sStalls[i].flag);
    s16 x = solved ? sStalls[i].stallX : sStalls[i].startX;
    s16 y = solved ? sStalls[i].stallY : sStalls[i].startY;
    struct ObjectEvent *player = &gObjectEvents[gPlayerAvatar.objectEventId];

    // Don't put the cow on top of the player.
    if (!solved && player->currentCoords.x == x + MAP_OFFSET
     && player->currentCoords.y == y + MAP_OFFSET)
        x = 5;

    SetObjEventTemplateCoords(i + 1, x, y);
    if (!TryGetObjectEventIdByLocalIdAndMap(i + 1, MAP_NUM(MAP_TILLBROOK_TOWN_GYM),
                                           MAP_GROUP(MAP_TILLBROOK_TOWN_GYM), &objectEventId))
    {
        struct ObjectEvent *cow = &gObjectEvents[objectEventId];
        MoveObjectEventToMapCoords(cow, x + MAP_OFFSET, y + MAP_OFFSET);
        cow->initialCoords = cow->currentCoords;
    }
}

void TillbrookGym_RestoreObjects(void)
{
    u32 i;

    if (!sRestoreObjects)
        return;

    for (i = 0; i < ARRAY_COUNT(sStalls); i++)
        RestoreCow(i);
    sRestoreObjects = FALSE;
}

void TillbrookGym_ResetSection(void)
{
    u32 i;
    s16 y = gObjectEvents[gPlayerAvatar.objectEventId].currentCoords.y - MAP_OFFSET;

    for (i = 0; i < ARRAY_COUNT(sStalls); i++)
    {
        if (y > sStalls[i].gateY && y <= sStalls[i].startY + (i == 0 ? 3 : 2)
         && !FlagGet(sStalls[i].flag))
            RestoreCow(i);
    }
}
