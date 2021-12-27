/*
 * music.h
 *
 *  Created on: 22 d�c. 2021
 *      Author: Cedric
 */

#ifndef MODULE_SOUND_MUSIC_H_
#define MODULE_SOUND_MUSIC_H_

#include <stdint.h>
#include "sound.h"

note_t g_tSong[32]=
{
        {DO, NOIRE},
        {PAUSE, TRIPLE_CROCHE},
        {FA, NOIRE},
        {PAUSE, TRIPLE_CROCHE},
        {FA, CROCHE},
        {PAUSE, TRIPLE_CROCHE},
        {FA, CROCHE},
        {PAUSE, NOIRE},
        {DO, NOIRE},
        {PAUSE, TRIPLE_CROCHE},
        {RE, NOIRE},
        {PAUSE, TRIPLE_CROCHE},
        {RE, CROCHE},
        {PAUSE, TRIPLE_CROCHE},
        {RE, CROCHE},
        {PAUSE, NOIRE},
        {DO, NOIRE},
        {PAUSE, TRIPLE_CROCHE},
        {MI, NOIRE},
        {PAUSE, TRIPLE_CROCHE},
        {MI, CROCHE},
        {PAUSE, TRIPLE_CROCHE},
        {MI, CROCHE},
        {PAUSE, NOIRE},
        {DO, NOIRE},
        {PAUSE, TRIPLE_CROCHE},
        {FA, NOIRE},
        {PAUSE, TRIPLE_CROCHE},
        {FA, CROCHE},
        {PAUSE, TRIPLE_CROCHE},
        {FA, CROCHE},
        {STOP, NOIRE}
};



note_t g_ptPapaNoel[] =
{
 {DO, NOIRE},
 {PAUSE, TRIPLE_CROCHE},

 {FA, NOIRE},
 {PAUSE, TRIPLE_CROCHE},
 {FA, NOIRE},
 {PAUSE, TRIPLE_CROCHE},
 {FA, NOIRE},
 {PAUSE, TRIPLE_CROCHE},
 {SOL, NOIRE},
 {PAUSE, TRIPLE_CROCHE},

 {FA, BLANCHE},
 {PAUSE, TRIPLE_CROCHE},
 {FA, CROCHE},
 {PAUSE, TRIPLE_CROCHE},
 {SOL, CROCHE},
 {PAUSE, TRIPLE_CROCHE},

 {LA, NOIRE},
 {PAUSE, TRIPLE_CROCHE},
 {LA, NOIRE},
 {PAUSE, TRIPLE_CROCHE},
 {LA, NOIRE},
 {PAUSE, TRIPLE_CROCHE},
 {SI, NOIRE},
 {PAUSE, TRIPLE_CROCHE},

 {LA, BLANCHE},
 {PAUSE, TRIPLE_CROCHE},
 {SOL, NOIRE},
 {PAUSE, TRIPLE_CROCHE},

 {FA, NOIRE},
 {PAUSE, TRIPLE_CROCHE},
 {FA, CROCHE},
 {PAUSE, TRIPLE_CROCHE},
 {FA, CROCHE},
 {PAUSE, TRIPLE_CROCHE},
 {FA, CROCHE},
 {PAUSE, TRIPLE_CROCHE},
 {MI, CROCHE},
 {PAUSE, TRIPLE_CROCHE},
 {RE, CROCHE},
 {PAUSE, TRIPLE_CROCHE},

 {DO, BLANCHE},
 {PAUSE, TRIPLE_CROCHE},
 {DO, CROCHE},
 {PAUSE, TRIPLE_CROCHE},
 {DO, CROCHE},
 {PAUSE, TRIPLE_CROCHE},

 {FA, BLANCHE},
 {PAUSE, TRIPLE_CROCHE},
 {FA, CROCHE},
 {PAUSE, TRIPLE_CROCHE},
 {FA, CROCHE},
 {PAUSE, TRIPLE_CROCHE},
 {SOL, CROCHE},
 {PAUSE, TRIPLE_CROCHE},
 {SOL, CROCHE},
 {PAUSE, TRIPLE_CROCHE},

 {FA, BLANCHE},
 {STOP, NOIRE}
};



//73BPM
note_t g_ptMonBeauSapin[] =
{
 {DO_FREQUENCY_3, STYLE_NOIRE, false},

 {FA_FREQUENCY_3, STYLE_CROCHE, true},
 {FA_FREQUENCY_3, STYLE_DOUBLE_CROCHE, false},
 {FA_FREQUENCY_3, STYLE_NOIRE, false},
 {SOL_FREQUENCY_3, STYLE_NOIRE, false},

 {LA_FREQUENCY_3, STYLE_CROCHE, true},
 {LA_FREQUENCY_3, STYLE_DOUBLE_CROCHE, false},
 {LA_FREQUENCY_3, STYLE_NOIRE, true},
 {LA_FREQUENCY_3, STYLE_CROCHE, false},

 {SOL_FREQUENCY_3, STYLE_CROCHE, false},
 {LA_FREQUENCY_3, STYLE_CROCHE, false},
 {SIb_FREQUENCY_3, STYLE_NOIRE, false},
 {MI_FREQUENCY_3, STYLE_NOIRE, false},

 {SOL_FREQUENCY_3, STYLE_NOIRE, false},
 {FA_FREQUENCY_3, STYLE_NOIRE, false},

 {NULL, NULL, NULL}
};

note_t g_ptHappyBirthday[] =
{
     {DO_FREQUENCY_3, STYLE_CROCHE, true},
     {DO_FREQUENCY_3, STYLE_CROCHE, false},

     {RE_FREQUENCY_3, STYLE_NOIRE, false},
     {DO_FREQUENCY_3, STYLE_NOIRE, false},
     {FA_FREQUENCY_3, STYLE_NOIRE, false},

     {MI_FREQUENCY_3, STYLE_BLANCHE, false},
     {DO_FREQUENCY_3, STYLE_CROCHE, true},
     {DO_FREQUENCY_3, STYLE_CROCHE, false},

     {RE_FREQUENCY_3, STYLE_NOIRE, false},
     {DO_FREQUENCY_3, STYLE_NOIRE, false},
     {SOL_FREQUENCY_3, STYLE_NOIRE, false},


     {FA_FREQUENCY_3, STYLE_BLANCHE, false},
     {DO_FREQUENCY_3, STYLE_CROCHE, true},
     {DO_FREQUENCY_3, STYLE_CROCHE, false},

     {DO_FREQUENCY_4, STYLE_NOIRE, false},
     {LA_FREQUENCY_3, STYLE_NOIRE, false},
     {FA_FREQUENCY_3, STYLE_NOIRE, false},

     {MI_FREQUENCY_3, STYLE_NOIRE, false},
     {RE_FREQUENCY_3, STYLE_NOIRE, false},  //<-- A verifier
     {SIb_FREQUENCY_3, STYLE_CROCHE, true},
     {SIb_FREQUENCY_3, STYLE_CROCHE, false},

     {LA_FREQUENCY_3, STYLE_NOIRE, false},
     {FA_FREQUENCY_3, STYLE_NOIRE, false},
     {SOL_FREQUENCY_3, STYLE_NOIRE, false},

     {FA_FREQUENCY_3, STYLE_NOIRE, false},
     {FA_FREQUENCY_3, STYLE_BLANCHE, false},

     {NULL, NULL, NULL}
};




#endif /* MODULE_SOUND_MUSIC_H_ */
