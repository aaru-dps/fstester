cmake_minimum_required(VERSION 3.10)
project(setter C)

set(CMAKE_C_STANDARD 90)

add_executable(setter src/include/consts.h src/include/defs.h src/main.h src/dosos2.h src/os2_16.h src/os2_32.h src/main.c src/dos.c src/os2_16.c src/os2_32.c src/win32.c src/win32.h src/macos.c src/macos.h src/unix/unix.h src/linux/linux.h src/netware.c src/netware.h src/linux/xattr.c src/linux/xattr.c src/linux/sparse.c src/linux/attr.c src/unix/os.c src/unix/volume.c src/unix/attr.c src/unix/perms.c src/unix/xattr.c src/unix/rsrcfork.c src/unix/filename.c src/unix/time.c src/unix/dirdepth.c src/unix/frag.c src/unix/sparse.c src/unix/links.c src/unix/files.c src/unix/deleted.c src/unix/perms.h src/linux/attr.h)