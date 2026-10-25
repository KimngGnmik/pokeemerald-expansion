#ifndef GUARD_TILLBROOK_GYM_H
#define GUARD_TILLBROOK_GYM_H

struct ObjectEvent;

bool8 IsTillbrookGymMiltank(const struct ObjectEvent *objectEvent);
void TillbrookGym_OnPushComplete(struct ObjectEvent *objectEvent);
void TillbrookGym_Load(void);
void TillbrookGym_RestoreObjects(void);
void TillbrookGym_ResetSection(void);

#endif
