MODULE := engines/made

MODULE_OBJS = \
	database.o \
	detection.o \
	graphics.o \
	made.o \
	music.o \
	pmvplayer.o \
	redreader.o \
	resource.o \
	screen.o \
	script.o \
	scriptfuncs_lgop2.o \
	scriptfuncs_mhne.o \
	scriptfuncs_rtz.o \
	sound.o


# This module can be built as a plugin
ifeq ($(ENABLE_MADE), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
