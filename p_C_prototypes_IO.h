#ifndef __UPDPART__
#define __UPDPART__

int getxsize(FILE *input_file);

int getysize(FILE *input_file);

double getalpha(FILE *input_file);

int getnumtimesteps(FILE *input_file);

void readValues(FILE *input_file, int x_size, int y_size, double **heatmap[2], int **holdmap[2]);

#endif