cmake_minimum_required(VERSION 3.8)
project("libport")

include(CheckTypeSize)
include(CheckIncludeFiles)
include(CheckSymbolExists)
include(CheckStructHasMember)
include(CPackComponent)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(source_dir "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(headers_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")

file(GLOB_RECURSE SRCFILES "${source_dir}/*.c" "${source_dir}/*.cpp")
file(GLOB header_files "${headers_dir}/*.h")

check_type_size("long long" LONG_LONG)
if(HAVE_LONG_LONG)
	set(HAVE_LONG_LONG ON)
else()
	set(HAVE_LONG_LONG OFF)
endif()

check_include_files("dlfcn.h" HAVE_DLFCN_H)
check_include_files("float.h" HAVE_FLOAT_H)

check_symbol_exists(isfinite "math.h" HAVE_ISFINITE)
check_symbol_exists(isinf "math.h" HAVE_ISINF)
check_symbol_exists(isnan "tgmath.h" HAVE_ISNAN)

check_symbol_exists(llrint "tgmath.h" HAVE_LLRINT)
check_symbol_exists(lrint "tgmath.h" HAVE_LRINT)
check_symbol_exists(rint "tgmath.h" HAVE_RINT)

# workaround, check_symbol_exists is broken, doesn't detect them even if present
if(NOT UNIX)
	check_symbol_exists(llrintf "tgmath.h" HAVE_LLRINTF)
	check_symbol_exists(lrintf "tgmath.h" HAVE_LRINTF)
	check_symbol_exists(rintf "tgmath.h" HAVE_RINTF)
else()
	set(HAVE_LLRINTF "${HAVE_LLRINT}")
	set(HAVE_LRINTF "${HAVE_LRINT}")
	set(HAVE_RINTF "${HAVE_RINT}")
endif()

check_symbol_exists(_spawnvp "stdio.h" HAVE__SPAWNVP)

check_symbol_exists(fsblkcnt_t "sys/statvfs.h" HAVE_FSBLKCNT_T)
check_symbol_exists(fsfilcnt_t "sys/statvfs.h" HAVE_FSFILCNT_T)
check_struct_has_member("struct statvfs" "f_blocks" "sys/statvfs.h" HAVE_STRUCT_STATVFS_F_BLOCKS LANGUAGE C)

check_symbol_exists(fstatvfs "sys/statvfs.h" HAVE_FSTATVFS)
check_symbol_exists(statvfs "sys/statvfs.h" HAVE_STATVFS)

check_include_files("sys/statfs.h" HAVE_SYS_STATFS_H)
if(HAVE_SYS_STATFS_H)
	check_struct_has_member("struct statfs" "f_avail" "sys/statfs.h" HAVE_STRUCT_STATFS_F_FAVAIL LANGUAGE C)
	check_struct_has_member("struct statfs" "f_free" "sys/statfs.h" HAVE_STRUCT_STATFS_F_FFREE LANGUAGE C)
	check_struct_has_member("struct statfs" "f_bavail" "sys/statfs.h" HAVE_STRUCT_STATFS_F_BAVAIL LANGUAGE C)
	check_struct_has_member("struct statfs" "f_bfree" "sys/statfs.h" HAVE_STRUCT_STATFS_F_BFREE LANGUAGE C)
	check_struct_has_member("struct statfs" "f_frsize" "sys/statfs.h" HAVE_STRUCT_STATFS_F_FRSIZE LANGUAGE C)
	check_struct_has_member("struct statfs" "f_namelen" "sys/statfs.h" HAVE_STRUCT_STATFS_F_NAMELEN LANGUAGE C)
endif()

check_include_files("sys/mount.h" HAVE_SYS_MOUNT_H)
check_include_files("sys/vfs.h" HAVE_SYS_VFS_H)
if(HAVE_SYS_VFS_H)
	check_symbol_exists(statfs "sys/vfs.h" HAVE_STATFS)
	check_symbol_exists(fstatfs "sys/vfs.h" HAVE_FSTATFS)
endif()

check_include_files("sys/param.h" HAVE_SYS_PARAM_H)
check_include_files("sys/wait.h" HAVE_SYS_WAIT_H)
check_include_files("ieeefp.h" HAVE_IEEEFP_H)

check_symbol_exists(select "sys/select.h" HAVE_SELECT)
check_symbol_exists(poll "sys/poll.h" HAVE_POLL)

check_include_files("string.h" HAVE_STRING_H)
if(HAVE_STRING_H)
	check_symbol_exists(memmove "string.h" HAVE_MEMMOVE)
	check_symbol_exists(memset "string.h" HAVE_MEMSET)
	check_symbol_exists(strcasecmp "string.h" HAVE_STRCASECMP)
	check_symbol_exists(strchr "string.h" HAVE_STRCHR)
	check_symbol_exists(strdup "string.h" HAVE_STRDUP)
	check_symbol_exists(strerror "string.h" HAVE_STRERROR)
	check_symbol_exists(strncasecmp "string.h" HAVE_STRNCASECMP)
	check_symbol_exists(strrchr "string.h" HAVE_STRRCHR)
	check_symbol_exists(strtol "string.h" HAVE_STRTOL)
	check_symbol_exists(strtoul "string.h" HAVE_STRTOUL)
	check_symbol_exists(strtoull "string.h" HAVE_STRTOULL)
else()
	set(HAVE_MEMMOVE OFF)
	set(HAVE_MEMSET OFF)
	set(HAVE_STRCASECMP OFF)
	set(HAVE_STRCHR OFF)
	set(HAVE_STRDUP OFF)
	set(HAVE_STRERROR OFF)
	set(HAVE_STRNCASECMP OFF)
	set(HAVE_STRRCHR OFF)
	set(HAVE_STRTOL OFF)
	set(HAVE_STRTOUL OFF)
	set(HAVE_STRTOULL OFF)
endif()

check_include_files("strings.h" HAVE_STRINGS_H)
if(HAVE_STRINGS_H)
	check_symbol_exists(ffs "strings.h" HAVE_FFS)
	check_symbol_exists(strnlen "strings.h" HAVE_STRNLEN)
endif()

check_include_files("stdlib.h" HAVE_STDLIB_H)
if(HAVE_STDLIB_H)
	check_symbol_exists(atexit "stdlib.h" HAVE_ATEXIT)
	check_symbol_exists(mkstemps "stdlib.h" HAVE_MKSTEMPS)
endif()

check_include_files("stdbool.h" HAVE_STDBOOL_H)
if(HAVE_STDBOOL_H)
	set(HAVE__BOOL ON)
else()
	check_type_size("_Bool" _BOOL)
	if(HAVE__BOOL)
		set(HAVE__BOOL ON)
	else()
		set(HAVE__BOOL OFF)
	endif()
endif()

check_include_files("fcntl.h" HAVE_FCNTL_H)
check_include_files("inttypes.h" HAVE_INTTYPES_H)
check_include_files("io.h" HAVE_IO_H)
check_include_files("libintl.h" HAVE_LIBINTL_H)
check_include_files("limits.h" HAVE_LIMITS_H)
check_include_files("malloc.h" HAVE_MALLOC_H)
check_include_files("memory.h" HAVE_MEMORY_H)
check_include_files("stdbool.h" HAVE_STDBOOL_H)
check_include_files("stddef.h" HAVE_STDDEF_H)
check_include_files("stdint.h" HAVE_STDINT_H)

if(HAVE_STDDEF_H AND HAVE_INTTYPES_H AND HAVE_FLOAT_H AND HAVE_STRING_H AND HAVE_STDLIB_H AND HAVE_STDINT_H  AND HAVE_DLFCN_H AND HAVE_STRINGS_H)
	set(STDC_HEADERS 1)
else()
	set(STDC_HEADERS 0)
endif()


check_include_files("sys/time.h" HAVE_SYS_TIME_H)
if(HAVE_SYS_TIME_H)
	check_symbol_exists(gettimeofday "sys/time.h" HAVE_GETTIMEOFDAY)
endif()

check_include_files("sys/types.h" HAVE_SYS_TYPES_H)


check_include_files("sys/stat.h" HAVE_SYS_STAT_H)
if(HAVE_SYS_STAT_H)
	check_symbol_exists(lstat "sys/stat.h" HAVE_LSTAT)
endif()

check_include_files("unistd.h" HAVE_UNISTD_H)
if(HAVE_UNISTD_H)
	check_symbol_exists(close "unistd.h" HAVE_CLOSE)
	check_symbol_exists(pread "unistd.h" HAVE_PREAD)
	check_symbol_exists(pwrite "unistd.h" HAVE_PWRITE)
	check_symbol_exists(readlink "unistd.h" HAVE_READLINK)
	check_symbol_exists(symlink "unistd.h" HAVE_SYMLINK)
	check_symbol_exists(usleep "unistd.h" HAVE_USLEEP)
else()
	SET(HAVE_CLOSE OFF)
	SET(HAVE_PREAD OFF)
	SET(HAVE_PWRITE OFF)
	SET(HAVE_READLINK OFF)
	SET(HAVE_SYMLINK OFF)
	SET(HAVE_USLEEP OFF)
	SET(HAVE_GETOPT_LONG_ONLY OFF)
endif()

check_include_files("getopt.h" HAVE_GETOPT_H)
if(HAVE_GETOPT_H)
	check_symbol_exists(getopt_long_only "getopt.h" HAVE_GETOPT_LONG_ONLY)
else()
	set(HAVE_GETOPT_LONG_ONLY OFF)
endif()

check_struct_has_member("struct option" "name" "unistd.h" HAVE_STRUCT_OPTION_NAME LANGUAGE C)

configure_file("${source_dir}/config.h.in" "${headers_dir}/wine/config.h")

add_library("libport" SHARED ${SRCFILES})
set(LIB_FILE_NAME "port_wine")
set_target_properties(libport PROPERTIES OUTPUT_NAME "${LIB_FILE_NAME}")
target_include_directories("libport" PUBLIC "$<BUILD_INTERFACE:${headers_dir}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")


set(CPACK_PACKAGE_NAME "wine-libport")
set(CPACK_PACKAGE_VENDOR "Wine, MinGW-w64 and ReactOS developers")
set(CPACK_PACKAGE_VERSION_MAJOR "5")
set(CPACK_PACKAGE_VERSION_MINOR "18")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set("CPACK_PACKAGE_VERSION" "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")


set_target_properties(libport PROPERTIES
	SOVERSION "${CPACK_PACKAGE_VERSION}"
)

set(CPACK_PACKAGE_DESCRIPTION "Wine portability library")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/KOLANICH/wine-port")
set(CPACK_PACKAGE_MAINTAINER "${CPACK_PACKAGE_VENDOR}")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_MAINTAINER}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.md")
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_NSIS_COMPONENT_INSTALL ON)
set("PKG_CONFIG_NAME" "libport-wine")
set(CPACK_DEBIAN_PACKAGE_NAME "${PKG_CONFIG_NAME}")
set(CPACK_RPM_PACKAGE_NAME "${PKG_CONFIG_NAME}")
set(CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS ON)
set(CPACK_RPM_ENABLE_COMPONENT_DEPENDS ON)
set(CPACK_DEBIAN_COMPRESSION_TYPE "xz")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS ON)
set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS_POLICY ">=")

cpack_add_component(libport
	DISPLAY_NAME "library"
	DESCRIPTION "The library itself"
	REQUIRED
)

cpack_add_component(libport_dev
	DISPLAY_NAME "Development files"
	DESCRIPTION "Headers and other files needed for using the lib in own software"
	DEPENDS "libport"
)

# strangely, not populated automatically correctly
set(CPACK_COMPONENTS_ALL "libport;libport_dev")

set(CMAKE_EXPORT_NAME "WinePort")

install(TARGETS libport
	LIBRARY
	COMPONENT "libport"
)
set("CPACK_DEBIAN_LIBPORT_PACKAGE_NAME" "${CPACK_DEBIAN_PACKAGE_NAME}")
set("CPACK_RPM_LIBPORT_PACKAGE_NAME" "${CPACK_RPM_PACKAGE_NAME}")

install(DIRECTORY "${headers_dir}/wine"
	TYPE INCLUDE
	COMPONENT "libport_dev"
)
install(TARGETS libport
	ARCHIVE
	COMPONENT "libport_dev"
)

set(PKG_CONFIG_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/${PKG_CONFIG_NAME}.pc")
configure_file("${source_dir}/pkgconfig.pc.in" "${PKG_CONFIG_FILE_NAME}" @ONLY)
install(FILES "${PKG_CONFIG_FILE_NAME}"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
	COMPONENT "libport_dev"
)

set(CMAKE_CONFIG_FILE_BASENAME "${CMAKE_EXPORT_NAME}Config.cmake")
set(CMAKE_CONFIG_VERSION_FILE_BASENAME "${CMAKE_EXPORT_NAME}ConfigVersion.cmake")
set(CMAKE_CONFIG_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CONFIG_FILE_BASENAME}")
configure_package_config_file("${source_dir}/CMakeConfig.cmake.in" "${CMAKE_CONFIG_FILE_NAME}"
	INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
)


set(CMAKE_CONFIG_VERSION_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CONFIG_VERSION_FILE_BASENAME}")
write_basic_package_version_file(
	"${CMAKE_CONFIG_VERSION_FILE_NAME}"
	VERSION "100500.100500.100500"  # any version of same bitness suits. CMake cannot compare to infinity, so use a large number we expect to be greater than any future version
	COMPATIBILITY AnyNewerVersion
)

install(FILES "${CMAKE_CONFIG_FILE_NAME}" "${CMAKE_CONFIG_VERSION_FILE_NAME}"
	#DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/wine"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_EXPORT_NAME}"
	COMPONENT "libport_dev"
)

set("CPACK_DEBIAN_LIBPORT_DEV_PACKAGE_NAME" "${CPACK_DEBIAN_LIBPORT_PACKAGE_NAME}-dev")
set("CPACK_RPM_LIBPORT_DEV_PACKAGE_NAME" "${CPACK_RPM_LIBPORT_PACKAGE_NAME}-devel")

include(CPack)
