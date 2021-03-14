//
// Created by claunia on 12/3/21.
//

#ifndef SETTER_SRC_MACOS_RETRO68_H_
#define SETTER_SRC_MACOS_RETRO68_H_

enum
{
    fsRtParID = 1,
    fsRtDirID = 2
};

#define FOUR_CHAR_CODE(x) (x)

/************** PC-DOS applications and FileTypes **************/
enum
{
    ftGenericDocumentPC = FOUR_CHAR_CODE('TEXT'), /*    word processor formats */
};

/* Finder flags (finderFlags, fdFlags and frFlags) */
/* Any flag reserved or not specified should be set to 0. */
/* If a flag applies to a file, but not to a folder, make sure to check */
/* that the item is not a folder by checking ((ParamBlockRec.ioFlAttrib & ioDirMask) == 0) */
enum
{
    kIsOnDesk = 0x0001, /* Files and folders (System 6) */
    kColor    = 0x000E, /* Files and folders */
    /* bit 0x0020 was kRequireSwitchLaunch, but is now reserved for future use*/
    kIsShared = 0x0040, /* Files only (Applications only) */
    /* If clear, the application needs to write to */
    /* its resource fork, and therefore cannot be */
    /* shared on a server */
    kHasNoINITs = 0x0080, /* Files only (Extensions/Control Panels only) */
    /* This file contains no INIT resource */
    kHasBeenInited = 0x0100, /* Files only */
    /* Clear if the file contains desktop database */
    /* resources ('BNDL', 'FREF', 'open', 'kind'...) */
    /* that have not been added yet. Set only by the Finder */
    /* Reserved for folders - make sure this bit is cleared for folders */
    /* bit 0x0200 was the letter bit for AOCE, but is now reserved for future use */
    kHasCustomIcon = 0x0400, /* Files and folders */
    kIsStationery  = 0x0800, /* Files only */
    kNameLocked    = 0x1000, /* Files and folders */
    kHasBundle     = 0x2000, /* Files only */
    kIsInvisible   = 0x4000, /* Files and folders */
    kIsAlias       = 0x8000  /* Files only */
};

typedef uint64_t UInt64;

#if defined(NO_PBXGETVOLINFO)
#define PBXGetVolInfo(pb, async) ((async) ? PBXGetVolInfoAsync(pb) : PBXGetVolInfoSync(pb))

typedef UniversalProcPtr IOCompletionUPP;

struct XVolumeParam
{
    QElemPtr        qLink;
    short           qType;
    short           ioTrap;
    Ptr             ioCmdAddr;
    IOCompletionUPP ioCompletion;
    volatile OSErr  ioResult;
    StringPtr       ioNamePtr;
    short           ioVRefNum;
    unsigned long   ioXVersion; /* this XVolumeParam version (0) */
    short           ioVolIndex;
    unsigned long   ioVCrDate;
    unsigned long   ioVLsMod;
    short           ioVAtrb;
    unsigned short  ioVNmFls;
    unsigned short  ioVBitMap;
    unsigned short  ioAllocPtr;
    unsigned short  ioVNmAlBlks;
    unsigned long   ioVAlBlkSiz;
    unsigned long   ioVClpSiz;
    unsigned short  ioAlBlSt;
    unsigned long   ioVNxtCNID;
    unsigned short  ioVFrBlk;
    unsigned short  ioVSigWord;
    short           ioVDrvInfo;
    short           ioVDRefNum;
    short           ioVFSID;
    unsigned long   ioVBkUp;
    short           ioVSeqNum;
    unsigned long   ioVWrCnt;
    unsigned long   ioVFilCnt;
    unsigned long   ioVDirCnt;
    long            ioVFndrInfo[8];
    UInt64          ioVTotalBytes; /* total number of bytes on volume */
    UInt64          ioVFreeBytes;  /* number of free bytes on volume */
};
typedef struct XVolumeParam XVolumeParam;
typedef XVolumeParam*       XVolumeParamPtr;

#if defined(TWOWORDINLINE)
EXTERN_API(OSErr) PBXGetVolInfoSync(XVolumeParamPtr paramBlock) TWOWORDINLINE(0x7012, 0xA060);
EXTERN_API(OSErr) PBXGetVolInfoAsync(XVolumeParamPtr paramBlock) TWOWORDINLINE(0x7012, 0xA460);
#elif defined(M68K_INLINE)
pascal OSErr PBXGetVolInfoSync(XVolumeParamPtr paramBlock) M68K_INLINE(0x7012, 0xA060);
pascal OSErr PBXGetVolInfoAsync(XVolumeParamPtr paramBlock) M68K_INLINE(0x7012, 0xA460);
#endif // TWOWORDINLINE

#endif // NO_PBXGETVOLINFO

enum
{
    gestaltAliasMgrPresent = 0, /* True if the Alias Mgr is present */
};

enum
{
    gestaltHasHFSPlusAPIs = 12, /* file system supports HFS Plus APIs */
};

enum
{
    gestaltFSSupports2TBVols = 5, /* file system supports 2 terabyte volumes */
};

/*MemoryDispatch errors*/
enum
{
    notEnoughMemoryErr = -620, /*insufficient physical memory*/
};

enum
{
    ftPICTFile = FOUR_CHAR_CODE('PICT')
};

enum
{
    rAliasType = FOUR_CHAR_CODE('alis') /* Aliases are stored as resources of this type */
};

#endif // SETTER_SRC_MACOS_RETRO68_H_
