//
// Created by claunia on 12/3/21.
//

#ifndef SETTER_SRC_MACOS_LINKS_H_
#define SETTER_SRC_MACOS_LINKS_H_

#if defined(HAVE_ALIASES_H) || !defined(HAVE_MULTIVERSE_H)
#include <Aliases.h>
#endif

#include <Files.h>
#include <MacTypes.h>

static pascal OSErr CreateAliasFile(FSSpec* targetFile, FSSpec* aliasFile, OSType fileCreator, OSType fileType);

const char* targetText = "This file is the target of an alias.\r";

#endif // SETTER_SRC_MACOS_LINKS_H_
