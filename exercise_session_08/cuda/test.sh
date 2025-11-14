#!/bin/bash

for B in 60 120 180 240 300 360 420 600; do
  for T in 16 32 48 64 80 96 112 128 144 160; do
    echo "Running B=$B T=$T"
    srun -A uzh8 -p normal -C gpu -n 1 ./cpi_cuda $B $T | \
      sed "s/^/B=$B T=$T : /"
  done
done
