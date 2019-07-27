#!/bin/bash

sudo sleep 3
sudo CFLAGS="-Wno-error=deprecated" make planck/rev6:my_keymap:dfu-util

