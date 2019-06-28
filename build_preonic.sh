#!/bin/bash

sudo sleep 3
sudo CFLAGS="-Wno-error=deprecated" make preonic/rev3:my_keymap:dfu-util

