#include <stdio.h>
#include "p_C_prototypes_IO.h"
#include "p_C_prototypes_update.h"

int i, j, k, x, y, t;

char filename[50], basename[50];
FILE *input_file, *outfile;
int i, j, k, x, y, t;
int output_freq;
int x_size, y_size, num_timesteps;
double temp;
char x_pos_str, y_pos_str;
char x_pos_readin[10], y_pos_readin[10];
int x_pos, y_pos, hold;
int x_max, y_max;
double **heatmap[2];
int  **holdmap[2];


void updateMap(char basename[50], char filename[50], int output_freq, int x_max, int y_max, int x_size, int y_size, double alpha, int num_timesteps, double **heatmap[2], int **holdmap[2]) {
  // printf("in updateMap\n");
  // printf("%d\n", num_timesteps);
  for (t = 1; t <= num_timesteps; t++) {

    // printf("in updateMap 2\n");
    // printf("1 heatmap[0][0][0] = %lf\n", heatmap[0][0][0]);

    //Corners
    //Top left corner
    heatmap[t%2][0][0] = heatmap[(t-1)%2][0][0] + ((holdmap[0][0][0]-1)*-1)*alpha*(heatmap[(t-1)%2][0+1][0] + heatmap[(t-1)%2][0][0+1] + heatmap[(t-1)%2][0+1][0+1] - 3*heatmap[(t-1)%2][0][0]);
    // printf("heatmap[tmod2][0][0] %lf\n", heatmap[t%2][0][0]);
    // printf("heatmap[(t-1)mod2][0][0] %lf\n", heatmap[(t-1)%2][0][0]);
    // printf("((holdmap[0][0][0]-1)*-1), %d\n", ((holdmap[0][0][0]-1)*-1));
    // printf("%lf\n", alpha);
  
    // printf("2 heatmap[0][0][0] = %lf\n", heatmap[0][0][0]);
    // printf("2 holdmap[0][0][0] = %d\n", holdmap[0][0][0]);
    // printf("2 t = %d\n", t);
    // printf("2 timesteps = %d\n", num_timesteps);
    // printf("%lf\n", alpha);

    // printf("1 if writing\n");
    //Bottom left corner
    heatmap[t%2][0][y_max] = heatmap[(t-1)%2][0][y_max] + ((holdmap[0][0][y_max]-1)*-1)*alpha*(heatmap[(t-1)%2][0][y_max-1] + heatmap[(t-1)%2][0+1][y_max-1] + heatmap[(t-1)%2][0+1][y_max] - 3*heatmap[(t-1)%2][0][y_max]);
    // printf("2 if writing\n");
    //Top right corner
    heatmap[t%2][x_max][0] = heatmap[(t-1)%2][x_max][0] + ((holdmap[0][x_max][0]-1)*-1)*alpha*(heatmap[(t-1)%2][x_max-1][0] + heatmap[(t-1)%2][x_max][0+1] + heatmap[(t-1)%2][x_max-1][0+1] - 3*heatmap[(t-1)%2][x_max][0]);
    // printf("3 if writing\n");
    //Bottom right corner
    heatmap[t%2][x_max][y_max] = heatmap[(t-1)%2][x_max][y_max] + ((holdmap[0][x_max][y_max]-1)*-1)*alpha*(heatmap[(t-1)%2][x_max-1][y_max] + heatmap[(t-1)%2][x_max][y_max-1] + heatmap[(t-1)%2][x_max-1][y_max-1] - 3*heatmap[(t-1)%2][x_max][y_max]);
    // printf("x_max = %d\n", x_max);
    // printf("y_max = %d\n", y_max);
    // printf("4 if writing\n");
    //---------------------------------------------

    //Sides
    //Left & right
    for (y = 1; y < y_max; y++) {
      //Left side
      heatmap[t%2][0][y] = heatmap[(t-1)%2][0][y] + ((holdmap[0][0][y]-1)*-1)*alpha*(heatmap[(t-1)%2][0][y-1] + heatmap[(t-1)%2][0+1][y-1] + heatmap[(t-1)%2][0+1][y] + heatmap[(t-1)%2][0][y+1] + heatmap[(t-1)%2][0+1][y+1] - 5*heatmap[(t-1)%2][0][y]);
    // printf("left writing\n");
      //Right side
      heatmap[t%2][x_max][y] = heatmap[(t-1)%2][x_max][y] + ((holdmap[0][x_max][y]-1)*-1)*alpha*(heatmap[(t-1)%2][x_max-1][y-1] + heatmap[(t-1)%2][x_max][y-1] +  heatmap[(t-1)%2][x_max-1][y] + heatmap[(t-1)%2][x_max-1][y+1] + heatmap[(t-1)%2][x_max][y+1] - 5*heatmap[(t-1)%2][x_max][y]);
    // printf("right writing\n");
    }

    //Top & bottom
    for (x = 1; x < x_max; x++) {
    // printf("past left/right writing\n");
      //Top
      heatmap[t%2][x][0] = heatmap[(t-1)%2][x][0] + ((holdmap[0][x][0]-1)*-1)*alpha*(heatmap[(t-1)%2][x-1][0] + heatmap[(t-1)%2][x+1][0] + heatmap[(t-1)%2][x-1][0+1] + heatmap[(t-1)%2][x][0+1] + heatmap[(t-1)%2][x+1][0+1] - 5*heatmap[(t-1)%2][x][0]);
    // printf("top writing\n");
      //Bottom
      heatmap[t%2][x][y_max] = heatmap[(t-1)%2][x][y_max] + ((holdmap[0][x][y_max]-1)*-1)*alpha*(heatmap[(t-1)%2][x-1][y_max-1] + heatmap[(t-1)%2][x][y_max-1] + heatmap[(t-1)%2][x+1][y_max-1] + heatmap[(t-1)%2][x-1][y_max] + heatmap[(t-1)%2][x+1][y_max] - 5*heatmap[(t-1)%2][x][y_max]);
    // printf("bottom writing\n");
    }

    //Middle
    for (x = 1; x < x_max; x++) {
      for (y = 1; y < y_max; y++) {
        heatmap[t%2][x][y] = heatmap[(t-1)%2][x][y] + ((holdmap[0][x][y]-1)*-1)*alpha*(heatmap[(t-1)%2][x-1][y-1] + heatmap[(t-1)%2][x][y-1] + heatmap[(t-1)%2][x+1][y-1] + heatmap[(t-1)%2][x-1][y] + heatmap[(t-1)%2][x+1][y] + heatmap[(t-1)%2][x-1][y+1] + heatmap[(t-1)%2][x][y+1] + heatmap[(t-1)%2][x+1][y+1] - 8*heatmap[(t-1)%2][x][y]);
        // printf("after middle writing\n");
      }
    }

    // printf("after middle writing\n");
    // printf("before while\n");
    //Print results to output file
    if (t%output_freq == 0) {
      // printf("1 in while\n");
      /*if (t != 0) {
        fclose(outfile);
      }*/
      // printf("2 in while\n");
      sprintf(filename, "%s_%04d.dat", basename, t);
      outfile = fopen(filename, "w"); 
      // printf("3 in while\n");
      for (x = 0; x < x_size; x++) {
      // printf("%d\n", i);
      // printf("4 in while\n");
        for (y = 0; y < y_size; y++) {
	  // printf("writing\n");
          // printf("%d %d %lf\n", x, y, heatmap[t%2][x][y]);
          fprintf(outfile, "%d %d %lf\n", x, y, heatmap[t%2][x][y]);
        }
      }
      // printf("done\n");
    }
  }
}
