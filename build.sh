#!/usr/bin/env bash

gcc -fPIC -o pamela.o -c pamela.c \
  && ld --shared -x -lc -o pamela.so pamela.o -lpam \
  && vagrant destroy -f \
  && vagrant up \
  && ssh rotta_f@192.168.33.10
