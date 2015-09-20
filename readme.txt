Zachary Keener's 2-D Space Heat Equation Simulation!

Included files:
p_C.c   : main C program
p_C_*   : any auxilliary C files, appropriately named
p_F     : main Fortran program


Steps for successfully simulatings heat in a 2-D system:
1. Build the program. Use the make commands below to build their corresponding parts:
make c        : builds C executable, called p_C
  NOTE: Recommended to use in c directory
make fortran  : builds Fortran executabe, called p_F
  NOTE: fortran does not compile at this time.
make all      : builds both C and Fortran executables, called p_C and p_F, respectively
make figures  : makes heatmaps with heat range [0:200] using data in the format '*_*.dat'
make clean    : cleans the current directory of all *.o, *.mod, p_C and p_F

2. Run the program
a) Using your own data, or data provided (options below), run the simulation in  using the appropriate executable in the directory containing the files built in step 1:
./<executable> <input_data.dat> <output_frequency> <outputfilename>
Note: Do not use an output name containing an '_'

Sample data provided:
Electric stove top coil:
a) File name: coil.dat
b) Description: Used to simulate a nichrome coil, popular in electric stoves. 5x5 grid with thermal diffusivity (alpha) = 3E-6, timesteps = 1,000,000 , T = 500 at center (2,2), heat spirals outward
c) Recommended output_frequency = 1,000

3. Build heatmaps using: make figures
Heat maps are contained in the ./figures directory

4. Enjoy!

Note: 