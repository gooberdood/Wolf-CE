# ----------------------------
# Makefile Options
# ----------------------------

NAME = WOLFCE
ICON = icon.png
DESCRIPTION = "Wolfenstein 3D by ID-Software, port by gooberdev"
COMPRESSED = YES
COMPRESSED_MODE = zx0
ARCHIVED = YES
PREFER_OS_CRT = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
