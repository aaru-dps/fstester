/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

    Author(s)      : Natalia Portillo

--[ License ] ---------------------------------------------------------------
     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as
     published by the Free Software Foundation, either version 3 of the
     License, or (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------
Copyright (C) 2011-2021 Natalia Portillo
*****************************************************************************/

#ifndef FSSETTER_TEST_SRC_ATARIST_OS_H_
#define FSSETTER_TEST_SRC_ATARIST_OS_H_

struct _stemu_vars
{
    int16_t version; /* e.g. 0x0121 Version 1.21    */
    int32_t unused;  /* 0, currently not used       */
}

struct _tos2win_vars
{
    int16_t len;         /* Length of the structure */
    int16_t version;     /* Version in BCD i.e. $0119 = Version 1.19 */
    int32_t pc_ptr;      /* Offset of the Atari memory in PC memory for recalculation of pointers */
    int32_t features[4]; /* Bit-fields for individual T2W features */
};

typedef struct
{
    int32_t magic;                            /* Has to be 0x87654321       */
    void*   membot;                           /* End of the AES variables   */
    void*   aes_start;                        /* Start address              */
    int32_t magic2;                           /* Is 'MAGX'                  */
    int32_t date;                             /* Creation date              */
    void (*chgres)(int16_t res, int16_t txt); /* Change resolution */
    int32_t (**shel_vector)(void);            /* Resident desktop           */
    int8_t*  aes_bootdrv;                     /* Booting will be from here  */
    int16_t* vdi_device;                      /* Driver used by AES         */
    void*    reservd1;                        /* Reserved                   */
    void*    reservd2;                        /* Reserved                   */
    void*    reservd3;                        /* Reserved                   */
    int16_t  version;                         /* Version (0x0201 is V2.1)   */
    int16_t  release;                         /* 0=alpha..3=release         */
} AESVARS;

typedef struct
{
    int8_t*  in_dos;                  /* Adress of the DOS semaphore  */
    int16_t* dos_time;                /* Adress of the DOS time       */
    int16_t* dos_date;                /* Adress of the DOS date       */
    int32_t  res1;                    /*                              */
    int32_t  res2;                    /*                              */
    int32_t  res3;                    /* is 0L                        */
    void*    act_pd;                  /* Running program              */
    int32_t  res4;                    /*                              */
    int16_t  res5;                    /*                              */
    void*    res6;                    /*                              */
    void*    res7;                    /* Internal DOS memory list     */
    void (*resv_intmem)();            /* Extend DOS memory            */
    int32_t (*etv_critica)();         /* etv_critic of the GEMDOS     */
    int8_t*((*err_to_str)(int8_t e)); /* Conversion code->plain text */
    int32_t res8;                     /*                              */
    int32_t res9;                     /*                              */
    int32_t res10;                    /*                              */
} DOSVARS;

typedef struct
{
    int32_t  config_status;
    DOSVARS* dosvars;
    AESVARS* aesvars;
    void*    res1;
    void*    hddrv_functions;
    int32_t  status_bits;
} MAGX_COOKIE;

#endif // FSSETTER_TEST_SRC_ATARIST_OS_H_
