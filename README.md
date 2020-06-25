[![Build Status](https://travis-ci.org/rgerganov/footswitch.svg?branch=master)](https://travis-ci.org/rgerganov/footswitch)

Foot Switch
-----------

Command line utilities for programming [PCsensor][1] and Scythe foot switches.
There is support for both single pedal devices and three pedal devices.
Use the `footswitch` binary for the following vendor + product IDs:

 * `0c45:7403`
 * `0c45:7404`
 * `413d:2107`

Scythe switches w/ IDs: `0426:3011` are programmable with the `scythe` binary.
On macOS: `brew install lsusb`. On Windows, read libusb or Microsoft's docs.
You can find the vendor / product IDs of your device using the `lsusb`.

These foot switches are also used for building the popular [vim clutch][2].

Building
--------

Targets link dynamically with the [hidapi][3] library and are tested on macOS:

    git clone https://github.com/hagemt/footswitch.git
    make test -C footswitch
    sudo make install -C footswitch

This works on most BSD + *nix variants (and maybe even Windows 10 via Cygwin):
* install your distribution's packaged HID library or build from source
* `sudo apt-get install libhidapi-dev` or `sudo pacman -S hidapi` on Arch

Read https://cygwin.com/install.html w/ `git`, a C compiler like `gcc`, and:
* pkg-config + modern hid.dll (development versions / debug symbols optional)
* Note: Official (better-supported) GUIs from the hardware supplier may exist.

Usage
-----
    footswitch [-123] [-r] [-s <string>] [-S <raw_string>] [-ak <key>] [-m <modifier>] [-b <button>] [-xyw <XYW>]
       -r          - read all pedals
       -1          - program the first pedal
       -2          - program the second pedal (default)
       -3          - program the third pedal
       -s string   - append the specified string
       -S rstring  - append the specified raw string (hex numbers delimited with spaces)
       -a key      - append the specified key
       -k key      - write the specified key
       -m modifier - ctrl|shift|alt|win
       -b button   - mouse_left|mouse_middle|mouse_right
       -x X        - move the mouse cursor horizontally by X pixels
       -y Y        - move the mouse cursor vertically by Y pixels
       -w W        - move the mouse wheel by W

    You cannot mix -sSa options with -kmbxyw options for one and the same pedal
_

    scythe [-123] [-r] [-a <key>] [-m <modifier>] [-b <button>]
       -r          - read all pedals
       -1          - program the first pedal
       -2          - program the second pedal (default)
       -3          - program the third pedal
       -a key      - append the specified key
       -m modifier - ctrl|shift|alt|win
       -b button   - mouse_left|mouse_double|mouse_right

    You cannot mix -a and -m options with -b option for one and the same pedal

Examples for PCsensor
--------
    footswitch -r
        read the persisted function in each pedal and print it on the console
    footswitch -k a
        program the second pedal to print the letter 'a' (also work for single pedal devices);
        as a general rule you don't need to specify -1, -2 or -3 if you have only one pedal
    footswitch -1 -k a -2 -k b -3 -k c
        program the first pedal to print 'a', second pedal to print 'b' and third pedal to print 'c'
    footswitch -1 -k esc -2 -k enter
        program the first pedal as Escape key and the second pedal as Enter key
    footswitch -1 -m ctrl -k a -3 -m alt -k f4
        program the first pedal as Ctrl+a and the third pedal as Alt+F4
    footswitch -m ctrl -b mouse_middle
        program the second pedal as Ctrl+<middle_mouse_click>
    footswitch -s 'hello world'
        program the second pedal to print 'hello world'
    footswitch -s 'hello' -s ' ' -s 'world'
        this will also program the second pedal to print 'hello world';
        you can specify multiple -s options and each option will append to the resulting string
    footswitch -a esc -a i
        program the second pedal to produce Escape and then the letter 'i'
    footswitch -s ls -a enter
        program the second pedal to print 'ls' and then hit Enter
    footswitch -S '29 C'
        program the second pedal with the specified 'raw' string (hex numbers delimited with spaces);
        you can find the hex code for each key at http://www.freebsddiary.org/APC/usb_hid_usages.php
    footswitch -1 -x 10 -2 -w 15 -3 -y -10
        program first pedal to move the mouse cursor 10 pixels left;
        second pedal to move mouse wheel 15 units up;
        third pedal to move the mouse cursor 10 pixels right

Examples for Scythe
--------
    scythe -r
        read the persisted function in each pedal and print it on the console
    scythe -1 -a a -2 -a b -3 -a c
        program the first pedal to print 'a', second pedal to print 'b' and third pedal to print 'c'
    scythe -1 -m ctrl -a h -a o -2 -m alt -a f4 -3 -b mouse_double
        program the first pedal as Ctrl+h+o, the second pedal as Alt+F4 and the third pedal as double click

Hardware issues
--------
Several people have reported misbehaviors with the PCsensor footswitch due to hardware issues.
If the pedal is continuously sending a keypress without being pressed, then most probably some of
the elements do not make good contact with the PCB. Follow the [instructions][4] contributed by @krasiyan
on how to verify and fix this.

Author
-------
[Radoslav Gerganov](mailto:rgerganov@gmail.com)

Contributors
-------
* [Daniel Manjarres](mailto:danmanj@gmail.com)
* Meng Zhang (wsxiaoys)
* Tor Hagemann (hagemt)

[1]: http://www.pcsensor.com/index.php?_a=viewCat&catId=2
[2]: https://github.com/alevchuk/vim-clutch
[3]: https://github.com/libusb/hidapi
[4]: https://github.com/rgerganov/footswitch/issues/26#issuecomment-401429709
