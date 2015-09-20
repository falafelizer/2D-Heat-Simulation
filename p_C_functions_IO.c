#include <stdio.h>
#include "p_C_prototypes_IO.h"
#include "p_C_prototypes_update.h"

int i, j, k, x, y, t;

char filename[50], basename[50];
FILE *input_file, *outfile;
int i, j, k, x, y, t;
int output_freq;
int x_size, y_size, num_timesteps;
double alpha, temp;
char x_pos_str, y_pos_str;
char x_pos_readin[10], y_pos_readin[10];
int x_pos, y_pos, hold;
int x_max, y_max;
double **heatmap[2];
int  **holdmap[2];


// Get basic values
int getxsize(FILE *input_file) {
  int f_x_size;

  // printf("in getxsize\n");

  fscanf(input_file, "%d", &f_x_size);

  return f_x_size;
}

int getysize(FILE *input_file) {

	int f_y_size;

	 fscanf(input_file, "%d", &f_y_size);

	 return f_y_size;
}

double getalpha(FILE *input_file) {

  double f_alpha;

  fscanf(input_file, "%lf", &f_alpha);

  return f_alpha;
 }

int getnumtimesteps(FILE *input_file) {

  int f_num_timesteps;

  fscanf(input_file, "%d", &f_num_timesteps);

  return f_num_timesteps;
}





void readValues(FILE *input_file, int x_size, int y_size, double **heatmap[2], int **holdmap[2]){


  // printf("in readValues\n");

	while(feof(input_file) == 0) {
      fscanf(input_file, "%s %s %lf %d", x_pos_readin, y_pos_readin, &temp, &hold);
      // printf("%lf\n", temp);
      x_pos_str = x_pos_readin[0];
      y_pos_str = y_pos_readin[0];
      // printf("x_pos_readin[0] = %s\n", &x_pos_readin[0]);
      // printf("y_pos_readin[0] = %s\n", &y_pos_readin[0]);
      if ((x_pos_str == '*') && (y_pos_str == '*')) {
        for(i = 0; i < x_size; i++) {
          for(y = 0; y < y_size; y++)  {
            heatmap[0][i][y] = temp;
            holdmap[0][i][y] = hold;
            // printf("1 map[%d][%d](%d) = ", i, y, hold);
            // printf("%lf\n", heatmap[0][i][y]);
            // printf("1 %d\n", holdmap[0][i][y]); 
          }
        }
      }
      else if (x_pos_str == '*' && y_pos_str != '*') {
        for(i = 0; i<x_size; i++) {
          for(y = 0; y<y_size; y++)  {
            y_pos = atoi(y_pos_readin);
            heatmap[0][i][y_pos] = temp;
            holdmap[0][i][y_pos] = hold;
            // printf("2 map[%d][%d](%d) = ", i, y, hold);
            // printf("%lf\n", heatmap[0][i][y_pos]);
            // printf("2 y_pos, %d\n", y_pos);
            // printf("2 %d\n", holdmap[0][i][y_pos]); 
          }
        }
      }
      else if (x_pos_str != '*' && y_pos_str == '*') {
        for(i = 0; i<x_size; i++) {
          for(y = 0; y<y_size; y++)  {
	          x_pos = atoi(x_pos_readin);
            heatmap[0][x_pos][y] = temp;
            holdmap[0][x_pos][y] = hold;
            // printf("3 map[%d][%d](%d) = ", i, y, hold);
            // printf("%lf\n", heatmap[0][x_pos][y]);
            // printf("3 %d\n", holdmap[0][x_pos][y]); 
          }
        }
      }
      else if (x_pos_str != '*' && y_pos_str != '*') {
        x_pos = atoi(x_pos_readin);
        y_pos = atoi(y_pos_readin);
        holdmap[0][x_pos][y_pos] = hold;
        heatmap[0][x_pos][y_pos] = temp;
        // printf("4 map[%d][%d](%d) = ", i, y, hold);
        // printf("%lf\n", heatmap[0][x_pos][y_pos]);
        // printf("4 %d\n", holdmap[0][x_pos][y_pos]); 
     }
    }
}


