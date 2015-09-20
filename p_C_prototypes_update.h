#ifndef __UPDPART__
#define __UPDPART__

extern char filename[50], basename[50];
extern FILE *input_file, *outfile;
extern int output_freq;
extern int x_size, y_size, num_timesteps;
extern double alpha, temp;
extern char x_pos_str, y_pos_str;
extern char x_pos_readin[10], y_pos_readin[10];
extern int x_pos, y_pos, hold;
extern int x_max, y_max;
extern double **heatmap[2];
extern int  **holdmap[2];

void updateMap(char basename[50], char filename[50], int output_freq, int x_max, int y_max, int x_size, int y_size, double alpha, int num_timesteps, double **heatmap[2], int **holdmap[2]);

#endif