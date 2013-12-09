#!/bin/bash

scp module_rgb librgbfunc.so 192.168.1.98:/dev/shm
ssh 192.168.1.98 'NUM_THREADS=8 /dev/shm/module_rgb /dev/shm/librgbfunc.so' | display -size 960x960 rgb:-

