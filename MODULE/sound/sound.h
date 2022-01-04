/*
 * sound.h
 *
 *  Created on: 5 déc. 2021
 *      Author: Cedric
 */

#ifndef MODULE_SOUND_SOUND_H_
#define MODULE_SOUND_SOUND_H_

#include <stdint.h>
#include <stdbool.h>
#include "notes.h"

typedef enum
{
    STYLE_TRIPLE_CROCHE = 1,
    STYLE_DOUBLE_CROCHE,
    STYLE_CROCHE,
    STYLE_NOIRE,
    STYLE_BLANCHE,
    STYLE_RONDE,
}style_t;

typedef struct
{
    double freq;
    style_t style;
    uint8_t ITRestante;
}note_t;

typedef struct
{
    char title[30];
    uint8_t BPM;
    note_t *notes;
}music_t;

bool SOUND_bPlaying;

void SOUND_Init(void);
void SOUD_Activate(void);
void SOUND_Deactivate(void);
void SOUND_PlayMusic(music_t* tMusic);
void SOUND_MusicStop(void);

#endif /* MODULE_SOUND_SOUND_H_ */
