AC_PREREQ([2.71])
AC_INIT([base-vulkan-gpu], [1.0])
AC_CONFIG_SRCDIR([src/basic.c])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign -Wall -Werror subdir-objects])

AC_PROG_CXX

have_vulkan=no

AC_SEARCH_LIBS([VkCommandBufferAllocateInfo], [vulkan], [have_vulkan=yes])

if test "x$have_vulkan" = xyes; then
    AC_CHECK_HEADERS([vulkan.h], [], [have_vulkan=no])

    if test "x$have_vulkan" = xno; then
        AC_MSG_WARN([
            ---------------------------------
            vulkan.h is missing. 
            You need to install dev package.
            ---------------------------------
        ])
    fi
fi

AC_CONFIG_FILES([Makefile])
AC_OUTPUT