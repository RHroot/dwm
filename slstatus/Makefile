# slstatus - suckless status monitor (dwm-style Makefile)

include config.mk

SRC = slstatus.c util.c \
	components/cpu.c \
	components/ram.c \
	components/netspeeds.c \
	components/datetime.c \
	components/disk.c \
	components/battery.c \
	# components/cat.c \
	# components/entropy.c \
	# components/hostname.c \
	# components/ip.c \
	# components/kernel_release.c \
	# components/keyboard_indicators.c \
	# components/keymap.c \
	# components/load_avg.c \
	# components/num_files.c \
	# components/run_command.c \
	# components/swap.c \
	# components/temperature.c \
	# components/uptime.c \
	# components/user.c \
	# components/volume.c \
	# components/wifi.c

OBJ = ${SRC:.c=.o}

all: slstatus

.c.o:
	${CC} -c ${CFLAGS} ${CPPFLAGS} $< -o $@

${OBJ}: config.h config.mk

config.h: config.def.h
	cp config.def.h config.h

slstatus: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS} ${LDLIBS}

clean:
	rm -f slstatus ${OBJ} config.h slstatus-${VERSION}.tar.gz

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f slstatus ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/slstatus
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	cp -f slstatus.1 ${DESTDIR}${MANPREFIX}/man1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/slstatus.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/slstatus \
		${DESTDIR}${MANPREFIX}/man1/slstatus.1

.PHONY: all clean install uninstall
