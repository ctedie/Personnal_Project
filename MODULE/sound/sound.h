/*
 * sound.h
 *
 *  Created on: 5 déc. 2021
 *      Author: Cedric
 */

#ifndef MODULE_SOUND_SOUND_H_
#define MODULE_SOUND_SOUND_H_

#include <stdint.h>
#include "notes.h"

typedef enum
{
    RONRE,
    BLANCHE,
    NOIRE,
    CROCHE,
    DOUBLE_CROCHE,
    TRIPLE_CROCHE
}style_t;

typedef struct
{
    uint16_t freq;
    style_t style;
}note_t;

typedef struct
{
    char title[30];
    uint8_t BPM;
    note_t *notes;
}music_t;


void SOUND_Init(void);

#endif /* MODULE_SOUND_SOUND_H_ */
