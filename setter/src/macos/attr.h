//
// Created by claunia on 12/3/21.
//

#ifndef SETTER_SRC_MACOS_ATTR_H_
#define SETTER_SRC_MACOS_ATTR_H_

const char* noAttributeText   = "This file has all flags bits clear.\r";
const char* desktopText       = "This file is on desktop.\r";
const char* color2Text        = "This file is colored brown.\r";
const char* color4Text        = "This file is colored green.\r";
const char* color6Text        = "This file is colored lilac.\r";
const char* color8Text        = "This file is colored blue.\r";
const char* colorAText        = "This file is colored magenta.\r";
const char* colorCText        = "This file is colored red.\r";
const char* colorEText        = "This file is colored orange.\r";
const char* requireSwitchText = "This file requires switch launch.\r";
const char* sharedText        = "This file is shared.\r";
const char* noInitText        = "This file contains no init.\r";
const char* initedText        = "This file has been inited.\r";
const char* aoceText          = "This file has AOCE bit set.\r";
const char* customIconText    = "This file has a custom icon.\r";
const char* stationeryText    = "This is a stationery.\r";
const char* nameLockText      = "This file has the name locked.\r";
const char* bundleText        = "This file has a BNDL resource.\r";
const char* invisibleText     = "This file is invisible.\r";
const char* aliasText         = "This file is an alias to nowhere.\r";
const char* simpletextText    = "This file has creator 'ttxt'.\r";
const char* aaruText          = "This file has creator 'aaru'.\r";
const char* pos_m32_m32       = "This file position is -32k,-32k.\r";
const char* pos_32_32         = "This file position is 32k,32k.\r";
const char* pos_m1_m1         = "This file position is -1k,-1k.\r";
const char* pos_m1_m32        = "This file position is -1k,-32k.\r";
const char* pos_m1_32         = "This file position is -1k,32k.\r";
const char* pos_m1_1          = "This file position is -1k,1k.\r";
const char* pos_1_m1          = "This file position is 1k,-1k.\r";
const char* pos_1_m32         = "This file position is 1k,-32k.\r";
const char* pos_1_32          = "This file position is 1k,32k.\r";
const char* pos_1_1           = "This file position is 1k,1k.\r";
const char* allText           = "This file has all flags bits set.\r";

enum
{
    kRequireSwitchLaunch = 0x0020,
    kAOCE                = 0x0200
};

#endif // SETTER_SRC_MACOS_ATTR_H_
