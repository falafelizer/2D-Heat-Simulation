info:
	@echo "C executable is called p_C"
	@echo "Fotrant executable is called p_F"

#foo: foo.o bar.o
#	icc -o foo foo.c bar.o

# template rule
#OPT = 2
#%.o: %.c
#	icc -c $< -0${OPT} -o $@
# $@ is the target


#----------------------------

all: p_C.o p_F.o p_C_functions_IO.o p_C_functions_update.o p_F_module.o
	icc -o p_C p_C.o p_C_functions_IO.o p_C_functions_update.o
	ifort -o hw4F hw4F.o hw4_module.o


# all: hw4.o hw4F.o hw4_funcs.o hw4_module.o
# 	icc -o hw4C hw4.o hw4_funcs.o
# 	ifort -o hw4F hw4F.o hw4_module.o

c: p_C.o p_C_functions_IO.o p_C_functions_update.o
	icc -o p_C p_C.o p_C_functions_IO.o p_C_functions_update.o

# c: hw4.o hw4_funcs.o
# 	icc -o hw4C hw4.o hw4_funcs.o

%.o: %.c
	icc -c $< -o $@

p_C.o hp_C_functions_IO.o p_C_functions_update.o: p_C_prototypes_IO.h p_C_prototypes_update.h



fortran: hw4F.o hw4_module.o
	ifort -o hw4F hw4F.o hw4_module.o

hw4F.o: hw4F.f90
	ifort -c hw4F.f90

hw4_module.o: hw4_module.f90
	ifort -c hw4_module.f90


figures: project.gplot project.sh
	./project.sh

#fortran: hw4.o hw4_module.o hw4_module.mod
#	ifort -o hw4F hw4.f90 hw4_module.f90

#%.f90: 


# dependency without commands
#foo.o bar.o: bar.h

#^target: ^prerequisite
#'I want this' 'In order to get this, then you need that'

# a cleanup rule

.PHONY: clean figures

clean:
	rm -f *.o *.mod p_C p_F
