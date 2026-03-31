cmake_minimum_required(VERSION 3.16)

project(AVL_tree_in_C LANGUAGES C)

# 1. Define your sources and headers
# It is good practice to keep them in a list for readability
set(SOURCES
    main.c
    source/avl_tree.c
    source/queue.c
    headers/avl_tree.h
    headers/queue.h
)

# 2. Create the executable
add_executable(AVL_tree_in_C ${SOURCES})

# 3. CRITICAL FIX: Tell CMake where to find your .h files
# This allows you to write #include "avl_tree.h" instead of "../../headers/avl_tree.h"
target_include_directories(AVL_tree_in_C PRIVATE headers)

# 4. Installation setup (stays the same)
include(GNUInstallDirs)
install(TARGETS AVL_tree_in_C
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)