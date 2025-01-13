CFLAGS = -Wall -Wextra -Werror
CC = gcc
INSTALL_PATH = /usr/local
SCRIPT_PATH = /etc/sddm/scripts

all:
	${CC} ${CFLAGS} *.c -o led_set

install: all
	install -Dm755 led_set ${INSTALL_PATH}/bin/led_set
	install -Dm755 led_init.sh ${SCRIPT_PATH}/mic_mute_fix.sh
	@echo -e "\n\tAdd the following line to your /etc/sddm/Xsetup file:"
	@echo -e "\t${SCRIPT_PATH}/mic_mute_fix.sh\n"

clean:
	rm -f led_set

