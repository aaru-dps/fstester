//
// Created by claunia on 11/3/21.
//

#ifndef SETTER_SRC_WIN32_ATTR_H_
#define SETTER_SRC_WIN32_ATTR_H_

const char* archivedAttributeText   = "This file has the archived attribute set.\n";
const char* encryptedAttributeText  = "This file is encrypted.\n";
const char* hiddenAttributeText     = "This file has the hidden attribute set.\n";
const char* noAttributeText         = "This file has no attribute set.\n";
const char* offlineAttributeText    = "This file is available offline.\n";
const char* readonlyAttributeText   = "This file has the read-only attribute set.\n";
const char* systemAttributeText     = "This file has the system attribute set.\n";
const char* temporaryAttributeText  = "This file is temporary.\n";
const char* compressedAttributeText = "This file is compressed.\n";

BOOL(WINAPI* WinNtEncryptFileA)(LPCSTR);

#endif // SETTER_SRC_WIN32_ATTR_H_
