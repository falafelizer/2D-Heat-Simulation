#include <stdio.h>
#include <stdlib.h> // For exit()
#include "p_C_prototypes_IO.h"
#include "p_C_prototypes_update.h"


int main(int argc, char **argv) {

  char filename[50], basename[50];
  FILE *input_file, *outfile;
  int i, j, k, x, y, t;
  int output_freq;
  int x_size, y_size, num_timesteps;
  double temp;
  double alpha;
  char x_pos_str, y_pos_str;
  char x_pos_readin[10], y_pos_readin[10];
  int x_pos, y_pos, hold;
  int x_max, y_max;
  double **heatmap[2];
  int  **holdmap[2];

  //----------------------------------------------
  
  if(argc != 4) {
    printf("Please provide all arguments.\n");
    exit(0);
  }
  if(argc >= 4) {
    strcpy(basename, argv[3]);
    output_freq = atoi(argv[2]);
    input_file = fopen(argv[1], "r");
  }

  printf("beginning of p_C.c\n");

  //----------------------------------------------

  //----------------------------------------------

  x_size = getxsize(input_file);
  y_size = getysize(input_file);
  fscanf(input_file, "%lf", &alpha);
  num_timesteps = getnumtimesteps(input_file);
  printf("alpha = %lf\n", alpha);
  printf("num_timesteps = %d\n", num_timesteps);


  // fscanf(input_file, "%d", &x_size);
  // fscanf(input_file, "%d", &y_size);
  // fscanf(input_file, "%lf", &alpha);
  // fscanf(input_file, "%d", &num_timesteps);

  //----------------------------------------------

  //Create x and y max variables
  x_max = x_size-1;
  y_max = y_size-1;

  //-----------------------------------------------
  //Allocate holdmap
  //holdmap = (int***)malloc(sizeof(int**)*2);
  holdmap[0] = (int**)malloc(sizeof(int*)*x_size);
    for(j = 0; j < y_size; j++) {
      holdmap[0][j] = (int*)malloc(sizeof(int)*y_size);
    }
  holdmap[1] = (int**)malloc(sizeof(int*)*x_size);
    for(j = 0; j < y_size; j++) {
      holdmap[1][j] = (int*)malloc(sizeof(int)*y_size);
    }

  //Allocate heatmap array
  //heatmap = (double***)malloc(sizeof(double**)*2);
  heatmap[0] = (double**)malloc(sizeof(double*)*x_size);
    for(j = 0; j < y_size; j++) {
      heatmap[0][j] = (double*)malloc(sizeof(double)*y_size);
    }
  heatmap[1] = (double**)malloc(sizeof(double*)*x_size);
    for(j = 0; j < y_size; j++) {
      heatmap[1][j] = (double*)malloc(sizeof(double)*y_size);
    }
  //----------------------------------------------

  //----------------------------------------------

  readValues(input_file, x_size, y_size, heatmap, holdmap);
  updateMap(basename, filename, output_freq, x_max, y_max, x_size, y_size, alpha, num_timesteps, heatmap, holdmap);
  printf("after updateMap\n");


  //Read in all values
    // while(feof(input_file) == 0) {
    //   fscanf(input_file, "%s %s %lf %d", x_pos_readin, y_pos_readin, &temp, &hold);
    //   x_pos_str = x_pos_readin[0];
    //   y_pos_str = y_pos_readin[0];
    //   printf("x_pos_readin[0] = %s\n", &x_pos_readin[0]);
    //   printf("y_pos_readin[0] = %s\n", &y_pos_readin[0]);
    //   if ((x_pos_str == '*') && (y_pos_str == '*')) {
    //     for(i = 0; i < x_size; i++) {
    //       for(y = 0; y < y_size; y++)  {
    //         heatmap[0][i][y] = temp;
    //         holdmap[0][i][y] = hold;
    //         printf("1 map[%d][%d](%d) = ", i, y, hold);
    //         printf("%lf\n", heatmap[0][i][y]);
    //         //printf("%d\n", holdmap[0][i][y]); 
    //       }
    //     }
    //   }
    //   else if (x_pos_str == '*' && y_pos_str != '*') {
    //     for(i = 0; i<x_size; i++) {
    //       for(y = 0; y<y_size; y++)  {
    //         y_pos = atoi(y_pos_readin);
    //         heatmap[0][i][y_pos] = temp;
    //         holdmap[0][i][y_pos] = hold;
    //         printf("2 map[%d][%d](%d) = ", i, y, hold);
    //         printf("%lf\n", heatmap[0][i][y_pos]);
    //         //printf("%d\n", holdmap[0][i][y_pos]); 
    //       }
    //     }
    //   }
    //   else if (y_pos_str == '*' && x_pos_str != '*') {
    //     for(i = 0; i<x_size; i++) {
    //       for(y = 0; y<y_size; y++)  {
	   //  x_pos = atoi(x_pos_readin);
    //         heatmap[0][x_pos][y] = temp;
    //         holdmap[0][x_pos][y] = hold;
    //         printf("3 map[%d][%d](%d) = ", i, y, hold);
    //         printf("%lf\n", heatmap[0][x_pos][y]);
    //         //printf("%d\n", holdmap[0][x_pos][y]); 
    //       }
    //     }
    //   }
    //   else if (y_pos_str != '*' && x_pos_str != '*') {
    //     x_pos = atoi(x_pos_readin);
    //     y_pos = atoi(y_pos_readin);
    //     holdmap[0][x_pos][y_pos] = hold;
    //     heatmap[0][x_pos][y_pos] = temp;
    //     printf("4 map[%d][%d](%d) = ", i, y, hold);
    //     printf("%lf\n", heatmap[0][x_pos][y_pos]);
    //     //printf("%d\n", holdmap[0][x_pos][y_pos]); 
    //  }
    // printf("writing\n");
    //}
  //----------------------------------------------






//   for (t = 1; t <= num_timesteps; t++) {

//     //Corners
//     //Top left corner
//     heatmap[t%2][0][0] = heatmap[(t-1)%2][0][0] + ((holdmap[(t-1)%2][0][0]-1)*-1)*alpha*(heatmap[(t-1)%2][0+1][0] + heatmap[(t-1)%2][0][0+1] + heatmap[(t-1)%2][0+1][0+1] - 3*heatmap[(t-1)%2][0][0]);

//     printf("1 if writing\n");
//     //Bottom left corner
//     heatmap[t%2][0][y_max] = heatmap[(t-1)%2][0][y_max] + ((holdmap[(t-1)%2][0][y_max]-1)*-1)*alpha*(heatmap[(t-1)%2][0][y_max-1] + heatmap[(t-1)%2][0+1][y_max-1] + heatmap[(t-1)%2][0+1][y_max] - 3*heatmap[(t-1)%2][0][y_max]);
//     printf("2 if writing\n");
//     //Top right corner
//     heatmap[t%2][x_max][0] = heatmap[(t-1)%2][x_max][0] + ((holdmap[(t-1)%2][x_max][0]-1)*-1)*alpha*(heatmap[(t-1)%2][x_max-1][0] + heatmap[(t-1)%2][x_max][0+1] + heatmap[(t-1)%2][x_max-1][y+1] - 3*heatmap[(t-1)%2][x_max][0]);
//     printf("3 if writing\n");
//     //Bottom right corner
//     heatmap[t%2][x_max][y_max] = heatmap[(t-1)%2][x_max][y_max] + ((holdmap[(t-1)%2][x_max][y_max]-1)*-1)*alpha*(heatmap[(t-1)%2][x_max-1][y_max] + heatmap[(t-1)%2][x_max][y_max-1] + heatmap[(t-1)%2][x_max-1][y_max-1] - 3*heatmap[(t-1)%2][x_max][y_max]);
//     printf("4 if writing\n");
//     //---------------------------------------------
//     //Sides
//     //Left & right
//     for (y = 1; y < y_max; y++) {
//       //Left side
//       heatmap[t%2][0][y] = heatmap[(t-1)%2][0][y] + ((holdmap[(t-1)%2][0][y]-1)*-1)*alpha*(heatmap[(t-1)%2][0][y-1] + heatmap[(t-1)%2][0+1][y-1] + heatmap[(t-1)%2][0+1][y] + heatmap[(t-1)%2][0][y+1] + heatmap[(t-1)%2][0+1][y+1] - 5*heatmap[(t-1)%2][0][y]);
//     printf("left writing\n");
//       //Right side
//       heatmap[t%2][x_max][y] = heatmap[(t-1)%2][x_max][y] + ((holdmap[(t-1)%2][x_max][y]-1)*-1)*alpha*(heatmap[(t-1)%2][x_max-1][y-1] + heatmap[(t-1)%2][x_max][y-1] +  heatmap[(t-1)%2][x_max-1][y] + heatmap[(t-1)%2][x_max-1][y+1] + heatmap[(t-1)%2][x_max][y+1] - 5*heatmap[(t-1)%2][x_max][y]);
//     printf("right writing\n");
//     }

//     //Top & bottom
//     for (x = 1; x < x_max; x++) {
//     printf("past left/right writing\n");
//       //Top
//       heatmap[t%2][x][0] = heatmap[(t-1)%2][x][0] + ((holdmap[(t-1)%2][x][0]-1)*-1)*alpha*(heatmap[(t-1)%2][x-1][0] + heatmap[(t-1)%2][x+1][0] + heatmap[(t-1)%2][x-1][0+1] + heatmap[(t-1)%2][x][0+1] + heatmap[(t-1)%2][x+1][0+1] - 5*heatmap[(t-1)%2][x][0]);
//     printf("top writing\n");
//       //Bottom
//       heatmap[t%2][x][y_max] = heatmap[(t-1)%2][x][y_max] + ((holdmap[(t-1)%2][x][y_max]-1)*-1)*alpha*(heatmap[(t-1)%2][x-1][y_max-1] + heatmap[(t-1)%2][x][y_max-1] + heatmap[(t-1)%2][x+1][y_max-1] + heatmap[(t-1)%2][x-1][y_max] + heatmap[(t-1)%2][x+1][y_max] - 5*heatmap[(t-1)%2][x][y_max]);
//     printf("bottom writing\n");
//     }

//     //Middle
//     for (x = 1; x < x_max; x++) {
//       for (y = 1; y < y_max; y++) {
//         heatmap[t%2][x][y] = heatmap[(t-1)%2][x][y] + ((holdmap[(t-1)%2][x][y]-1)*-1)*alpha*(heatmap[(t-1)%2][x-1][y-1] + heatmap[(t-1)%2][x][y-1] + heatmap[(t-1)%2][x+1][y-1] + heatmap[(t-1)%2][x-1][y] + heatmap[(t-1)%2][x+1][y] + heatmap[(t-1)%2][x-1][y+1] + heatmap[(t-1)%2][x][y+1] + heatmap[(t-1)%2][x+1][y+1] - 8*heatmap[(t-1)%2][x][y]);
//         printf("after middle writing\n");
//       }
//     }

//     printf("after middle writing\n");
//     printf("before while\n");
//     //Print results to output file
//     if (t%output_freq == 0) {
//       printf("1 in while\n");
//       /*if (t != 0) {
//         fclose(outfile);
//       }*/
//       printf("2 in while\n");
//       sprintf(filename, "%s_%04d.dat", basename, t);
//       outfile = fopen(filename, "w"); 
//       printf("3 in while\n");
//       for (x = 0; x < x_size; x++) {
//       printf("%d\n", i);
//       printf("4 in while\n");
//         for (y = 0; y < y_size; y++) {
// 	  printf("writing\n");
//           printf("%d %d %lf\n", x, y, heatmap[t%2][x][y]);
//           fprintf(outfile, "%d %d %lf\n", x, y, heatmap[t%2][x][y]);
//         }
//       }
//       printf("done\n");
//     }
//   }
//   printf("out\n");
  //----------------------------------------------

  //Free holdmap[0]
  for(j = 0; j<x_size; j++) {
    free(holdmap[0][j]);
  }
  free(holdmap[0]);
  //Free holdmap[1]
  for(j = 0; j<x_size; j++) {
    free(holdmap[1][j]);
  }
  free(holdmap[1]);
  
  //Free heatmap[0]
  for(j = 0; j<y_size; j++) {
    free(heatmap[0][j]);
  }
  free(heatmap[0]);
  //Free heatmap[1]
  for(j = 0; j<y_size; j++) {
    free(heatmap[1][j]);
  }
  free(heatmap[1]);
  //----------------------------------------------

  fclose(input_file);
  return 0;
}
