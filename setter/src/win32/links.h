//
// Created by claunia on 11/3/21.
//

#ifndef SETTER_SRC_WIN32_LINKS_H_
#define SETTER_SRC_WIN32_LINKS_H_

#include "win32.h"

static BOOL(WINAPI* WinNtCreateHardLinkA)(LPCSTR, LPCSTR, LPSECURITY_ATTRIBUTES);
static BOOL(WINAPI* WinNtCreateSymbolicLinkA)(LPCSTR, LPCSTR, DWORD);

#endif // SETTER_SRC_WIN32_LINKS_H_
