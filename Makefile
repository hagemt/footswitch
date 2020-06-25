CFLAGS ?= -std=c99 -Wall -Wextra -Werror
LDLIBS := -lhidapi

PREFIX ?= /usr/local
SYSTEM := $(shell uname)

ifeq ($(SYSTEM), Darwin)
CFLAGS += -DOSX $(shell pkg-config --cflags hidapi)
LDLIBS := $(shell pkg-config --libs hidapi)
endif

ifeq ($(SYSTEM), Linux)
CFLAGS += $(shell pkg-config --cflags hidapi-libusb)
LDLIBS := $(shell pkg-config --libs hidapi-libusb)
endif

default: sane
	@make footswitch scythe
	@echo '-- next: make test && sudo make install'
.PHONY: default

footswitch: footswitch.c common.c debug.c
scythe: scythe.c common.c debug.c

install: default
	install footswitch scythe "$(PREFIX)/bin"
ifeq ($(SYSTEM), Linux)
	install -m 644 19-footswitch.rules /etc/udev/rules.d
endif
.PHONY: install

uninstall: 
	$(RM) "$(PREFIX)/bin/footswitch" "$(PREFIX)/bin/scythe"
ifeq ($(SYSTEM), Linux)
	$(RM) /etc/udev/rules.d/19-footswitch.rules
endif
.PHONY: uninstall

clean:
	$(RM) scythe footswitch *.o
.PHONY: clean

sane:
	@xcode-select -p || xcode-select --install || xcode-select -r --install
	@pkg-config --cflags --libs hidapi || brew install hidapi pkg-config
.PHONY: sane

test: sane footswitch
	./footswitch -r
.PHONY: test

# configure macOS screenshot
shot: sane footswitch
	./footswitch -m command -m shift -k 3
.PHONY: shot

# configure left arrow
back: sane footswitch
	./footswitch -S 50
.PHONY: back
