OBJS = borlandmm_win32.obj
BCCFLAGS = -6

all: borlandmm_win32.dll

borlandmm_win32.dll: $(OBJS) borlandmm.def
	ilink32 /Tpd $(OBJS), $@, , import32.lib cp32mti.lib, borlandmm.def

.c.obj:
	bcc32 $(BCCFLAGS) -c $<