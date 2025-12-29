# AGENTS.md - AI Agent Guidelines for fstester/setter

## Project Overview

This is the **Filesystem Test Setter** component of the **Aaru Data Preservation Suite**. It's a C application that creates filesystem test scenarios on various platforms to help test and validate filesystem implementations. The tool generates test files with specific attributes, permissions, timestamps, extended attributes, resource forks, and other filesystem features.

## Project Structure

```
setter/
├── CMakeLists.txt          # Main CMake build configuration
├── src/                    # Source code
│   ├── main.c              # Entry point and command-line parsing
│   ├── main.h              # Platform/architecture detection macros
│   ├── log.c/h             # Logging utilities
│   ├── include/            # Shared headers (defs.h, consts.h)
│   ├── unix/               # POSIX/Unix implementations (Linux, BSD, Darwin)
│   │   ├── bsd/            # BSD-specific code (FreeBSD, NetBSD, OpenBSD, DragonFly)
│   │   ├── darwin/         # macOS-specific code
│   │   └── linux/          # Linux-specific code
│   ├── dos/                # MS-DOS implementation
│   ├── win32/              # Windows implementation
│   ├── macos/              # Classic Mac OS (pre-X) implementation
│   ├── amiga/              # AmigaOS/MorphOS/AROS implementation
│   ├── atarist/            # Atari ST/MiNT implementation
│   ├── beos/               # BeOS/Haiku implementation
│   ├── os2/                # OS/2 implementation
│   ├── netware/            # Novell NetWare implementation
│   └── 8bit/               # 8-bit computer implementations (6502, Z80)
├── projects/               # IDE project files and Makefiles
│   ├── borland/            # Borland C++ (1.0 to 5.0, Turbo C++, C++ Builder)
│   ├── watcom/             # Watcom C++ (10, 11, Open Watcom)
│   ├── msvc/               # Microsoft Visual C++ (1.0 to 6.0)
│   ├── msvs/               # Visual Studio (2002 to 2019)
│   ├── msc60/              # Microsoft C 6.0
│   ├── msc70/              # Microsoft C 7.0
│   ├── symantec/           # Symantec C++ 6.0
│   ├── cw/                 # Metrowerks CodeWarrior (Mac OS, BeOS)
│   ├── applepb/            # Apple Project Builder (1.0 to 2.0)
│   ├── xcode/              # Xcode (modern)
│   ├── xcode11/            # Xcode 11
│   └── make/               # Makefiles for various targets
│       ├── 6502/           # CC65 for 6502 computers
│       ├── z80/            # Z88DK for Z80 computers
│       └── ...             # Unix, BeOS, etc.
├── toolchains/             # CMake toolchain files for cross-compilation
├── binaries/               # Pre-built executables for various platforms
└── diskimgs/               # Floppy disk images for distribution
```

## Language and Standards

- **Language**: ANSI C (C90/C89)
- **Standard**: `CMAKE_C_STANDARD 90` - strict C90 compliance for maximum portability
- **Build Systems**: CMake, IDE project files, Makefiles (see projects/ folder)

## Supported Platforms

This project targets an extensive list of platforms:

### Modern Operating Systems (CMake)
- **Linux** (x86, x86_64, ARM, etc.)
- **macOS / Mac OS X** (x86_64, ARM64)
- **Windows** (x86, x86_64, via MinGW/Cygwin)
- **FreeBSD, NetBSD, OpenBSD, DragonFly BSD**
- **Haiku**

### Retro Operating Systems (CMake + IDE projects)
- **MS-DOS** (DJGPP, Watcom, Borland, Microsoft C)
- **OS/2** (16-bit and 32-bit, Watcom, Microsoft C)
- **Windows 3.x/9x/NT** (Watcom, Borland, MSVC)
- **Classic Mac OS** (Retro68, CodeWarrior)
- **AmigaOS** (68k and PPC)
- **MorphOS**
- **AROS**
- **Atari ST / MiNT**
- **BeOS**
- **NeXTStep / Rhapsody**
- **Novell NetWare**

### 8-bit Computers (CC65 for 6502, Z88DK for Z80)

**6502-based (CC65):**
- Apple II, Apple IIe
- Atari 8-bit, Atari XL
- Commodore 64, C128, C16, Plus/4, PET

**Z80-based (Z88DK):**
- Amstrad CPC, PCW40, PCW80
- Amstrad CP/M
- Coleco Adam
- MSX-DOS, MSX-DOS 2
- Sinclair ZX Spectrum +3 (native and CP/M)
- Kaypro 83, 84
- Osborne 1
- Sharp MZ-2500, X1
- NEC PC-8801
- Microbee
- Tatung Einstein
- Bondwell
- Epson QX-10, PX-4
- Tiki-100
- RC700
- Nascom
- Lynx 128
- SMC-777
- Excalibur 64
- Grundy NewBrain
- And many more CP/M machines...

## Compiler/IDE Support

### DOS Compilers
- **DJGPP** (GCC for DOS, 32-bit protected mode)
- **Watcom C++** 10, 11, Open Watcom
- **Borland C++** 1.0, 2.0, 3.1, 4.0, 4.5, 5.0
- **Turbo C++** 1.0, 3.0
- **Microsoft C** 6.0, 7.0
- **Microsoft Visual C++** 1.0
- **Symantec C++** 6.0

### Windows Compilers
- **Watcom C++** (Win32)
- **Borland C++ Builder** 1, 6
- **Microsoft Visual C++** 1.0 to 6.0
- **Visual Studio** 2002, 2005, 2017, 2019
- **MinGW** (x86, x86_64)

### OS/2 Compilers
- **Watcom C++** (16-bit and 32-bit)
- **Microsoft C** 6.0

### Mac Compilers
- **Retro68** (Classic Mac OS, 68k and PPC)
- **CodeWarrior** 6.0, Pro 1.0, Pro 3.0
- **Apple Project Builder** 1.0, 1.1, 2.0
- **Xcode** (modern macOS)

### Other Compilers
- **CC65** (6502 family)
- **Z88DK** (Z80 family)
- **GCC** (various cross-compilation targets)

## Architecture Guidelines

### Platform Abstraction

Each test function is declared in `src/include/defs.h` and implemented per-platform:

```c
void GetOsInfo(void);
void GetVolumeInfo(const char* path, size_t* clusterSize);
void FileAttributes(const char* path);
void FilePermissions(const char* path);
void ExtendedAttributes(const char* path);
void ResourceFork(const char* path);
void Filenames(const char* path);
void Timestamps(const char* path);
void DirectoryDepth(const char* path);
void Fragmentation(const char* path, size_t clusterSize);
void Sparse(const char* path);
void MillionFiles(const char* path);
void DeleteFiles(const char* path);
void Links(const char* path);
```

### Adding Platform Support

1. Create a new directory under `src/` for the platform
2. Implement all functions from `defs.h`
3. Create a `CMakeLists.txt` that conditionally includes the sources based on `CMAKE_SYSTEM_NAME`
4. Use stub implementations (empty functions) for unsupported features

### Code Style

- Use C90-compatible syntax only:
  - No `//` comments (use `/* */`)
  - No variable declarations after statements
  - No C99 features (`_Bool`, `inline`, flexible array members, etc.)
- Include the standard license header in all source files
- Use the `log_write()` function for output instead of direct `printf()`

## Build Instructions

### Native Build (macOS/Linux) with CMake

```bash
mkdir build && cd build
cmake ..
make
```

### Cross-Compilation with CMake

Use toolchain files from `toolchains/`:

```bash
cmake -DCMAKE_TOOLCHAIN_FILE=toolchains/djgpp.cmake ..
```

### Building with IDE Project Files

Many retro compilers don't support CMake. Use the project files in `projects/`:

- **Borland**: Open `.prj` or `.ide` files in the respective Borland IDE
- **Watcom**: Open `.wpj` files in Watcom IDE
- **MSVC**: Open `.mak` files or `.dsp` projects
- **Visual Studio**: Open `.sln` solutions
- **CodeWarrior**: Open `.mcp` projects
- **Project Builder/Xcode**: Open `.pbproj` or `.xcodeproj`

### Building 8-bit Targets

```bash
# 6502 targets (requires CC65)
cd projects/make/6502
./build.sh          # Build all targets
make apple2         # Build specific target

# Z80 targets (requires Z88DK)
cd projects/make/z80
./build.sh          # Build all targets
make amstrad_cpc    # Build specific target
```

## Testing Considerations

- The tool creates files and directories on the target filesystem
- It requires write access to the specified path
- Some tests may require specific filesystem features (extended attributes, resource forks, sparse files)
- The tool logs operations to aid in debugging filesystem implementations

## Important Notes for AI Agents

1. **C90 Compliance is Critical**: This codebase must compile on very old systems. Do not use modern C features.

2. **Platform Detection**: Use the existing macros in `main.h` for platform/architecture detection. Do not create new detection mechanisms.

3. **No External Dependencies**: The code should only use platform-native APIs and standard C library functions.

4. **Stub Functions**: On platforms that don't support a feature, implement an empty function or one that logs "Not supported".

5. **CMake Patterns**: Follow the existing `add_sources()`, `add_sub_definitions()`, and `add_sub_libraries()` macros for adding code.

6. **Cross-Compilation**: Many builds use cross-compilers (DJGPP for DOS, OpenWatcom, Retro68 for Mac OS, etc.). Changes should be tested or at least compile-checked against these toolchains when possible.

7. **File Naming**: Keep filenames short and lowercase for compatibility with older filesystems (8.3 naming on DOS/FAT).

8. **License**: All code is GPLv3+. Include the appropriate license header.

9. **Multiple Build Systems**: Changes to source files may require updates to:
   - CMakeLists.txt files
   - IDE project files in `projects/` (Borland, Watcom, MSVC, etc.)
   - Makefiles for 8-bit targets

10. **8-bit Limitations**: Code in `src/8bit/` has severe constraints (limited memory, no floating point, minimal standard library).

## Common Tasks

### Adding a New Filesystem Test

1. Declare the function in `src/include/defs.h`
2. Call it from `src/main.c` in the appropriate order
3. Implement it in each platform directory (`unix/`, `dos/`, `win32/`, etc.)

### Fixing a Platform-Specific Bug

1. Identify the correct platform directory
2. Check the `CMakeLists.txt` to understand which files are included
3. Make changes only to the platform-specific implementation

### Adding Architecture Detection

Edit `src/main.h` and add appropriate `#if defined()` checks following the existing pattern.
