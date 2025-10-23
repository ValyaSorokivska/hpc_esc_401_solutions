#ifndef IO_H
#define IO_H

#include "init.h"
#include <fstream>

void write_csv(const char* path, double** A, int nx, int ny);

void output_source(params p, double** f);
void output(params p, int step, double** u_new);

#endif
