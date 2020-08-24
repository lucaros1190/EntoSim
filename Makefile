#
# This is a makefile to compile EntoSim
#
# Created by Luca Rossini on 03/08/2020
# email: luca.rossini@unitus.it
# last update 17/08/2020
#


welcome:
	
	@echo " "
	@echo " Building EntoSim - server edition"
	@echo " "
	@echo " Hello $(shell whoami), please select your option:"
	@echo " "
	@echo "    'make all' to build EntoSim"
	@echo "    'make python.pkg to install the required Python 3 packages"
	@echo "    'make clean' to delete the object files '.o'"
	@echo "    'make info' for the list of related publications"
	@echo "    'make contacts' if you want to email us"
	@echo " "

start_compiling:
	
	@echo " "
	@echo " ...Start compiling 'EntoSim'..."
	@echo " "


#	Compile C sources

headers-menu.o: ./bin/headers-menu.c
	@echo " "
	@echo " ...Compiling 'headers-menu.c'..."
	@echo " "
	g++ -c -Wall ./bin/headers-menu.c
	
briere.o: ./bin/briere.c
	@echo " "
	@echo " ...Compiling 'briere.c'..."
	@echo " "
	g++ -c -Wall ./bin/briere.c `root-config --cflags --glibs`
	
logan.o: ./bin/logan.c
	@echo " "
	@echo " ...Compiling 'logan.c'..."
	@echo " "
	g++ -c -Wall ./bin/logan.c `root-config --cflags --glibs`

sdm.o: ./bin/sdm.c
	@echo " "
	@echo " ...Compiling 'sdm.c'..."
	@echo " "
	g++ -c -Wall ./bin/sdm.c `root-config --cflags --glibs`

linear.o: ./bin/linear.c
	@echo " "
	@echo " ...Compiling 'linear.c'..."
	@echo " "
	g++ -c -Wall ./bin/linear.c `root-config --cflags --glibs`

fittasso.o: ./bin/fittasso.c ./bin/fittasso.h
	@echo " "
	@echo " ...Compiling 'fittasso.c'..."
	@echo " "
	g++ -c -Wall ./bin/fittasso.c `root-config --cflags --glibs`

fittasso-support.o: ./bin/fittasso-support.c ./bin/fittasso.h
	@echo " "
	@echo " ...Compiling 'fittasso-support.c'..."
	@echo " "
	g++ -c -Wall ./bin/fittasso-support.c `root-config --cflags --glibs`

support.o: ./bin/support.c ./bin/support.h
	@echo " "
	@echo " ...Compiling 'support.c'..."
	@echo " "
	g++ -c -Wall ./bin/support.c `root-config --cflags --glibs`
	
validator-support.o: ./bin/validator-support.c ./bin/validator-support.h
	@echo " "
	@echo " ...Compiling 'validator-support.c'..."
	@echo " "
	g++ -c -Wall ./bin/validator-support.c `root-config --cflags --glibs`
	
validator.o: ./bin/validator.c
	@echo " "
	@echo " ...Compiling 'validator.c'..."
	@echo " "
	g++ -c -Wall ./bin/validator.c `root-config --cflags --glibs`
	
sim-support.o: ./bin/sim-support.c ./bin/sim-support.h
	@echo " "
	@echo " ...Compiling 'sim-support.c'..."
	@echo " "
	g++ -c -Wall ./bin/sim-support.c `root-config --cflags --glibs`
	
simulatore1.o: ./bin/simulatore1.c ./bin/sim-support.h
	@echo " "
	@echo " ...Compiling 'simulatore1.c'..."
	@echo " "
	g++ -c -Wall ./bin/simulatore1.c `root-config --cflags --glibs`
	
simulatore2.o: ./bin/simulatore2.c ./bin/sim-support.h
	@echo " "
	@echo " ...Compiling 'simulatore2.c'..."
	@echo " "
	g++ -c -Wall ./bin/simulatore2.c `root-config --cflags --glibs`
	
simulatore3.o: ./bin/simulatore3.c ./bin/sim-support.h
	@echo " "
	@echo " ...Compiling 'simulatore3.c'..."
	@echo " "
	g++ -c -Wall ./bin/simulatore3.c `root-config --cflags --glibs`
	
simulatore4.o: ./bin/simulatore4.c ./bin/sim-support.h
	@echo " "
	@echo " ...Compiling 'simulatore4.c'..."
	@echo " "
	g++ -c -Wall ./bin/simulatore4.c `root-config --cflags --glibs`
	
simulatore.o: ./bin/simulatore.c ./bin/sim-support.h
	@echo " "
	@echo " ...Compiling 'simulatore.c'..."
	@echo " "
	g++ -c -Wall ./bin/simulatore.c `root-config --cflags --glibs`

entosim.o: ./bin/entosim.c ./bin/entosim.h
	@echo " "
	@echo " ...Compiling 'entosim.c'..."
	@echo " "
	g++ -c -Wall ./bin/entosim.c `root-config --cflags --glibs`

compiling: headers-menu.o briere.o logan.o sdm.o linear.o fittasso.o fittasso-support.o support.o validator-support.o validator.o sim-support.o simulatore1.o simulatore2.o simulatore3.o simulatore4.o simulatore.o entosim.o


#	Build libraries

libfittasso.a: briere.o logan.o sdm.o linear.o fittasso-support.o
	@echo " "
	@echo " ...Building 'libfittasso.a'..."
	@echo " "
	ar r ./lib/libfittasso.a briere.o logan.o sdm.o linear.o fittasso-support.o
	
libvalidator.a: validator-support.o
	@echo " "
	@echo " ...Building 'libvalidator.a'..."
	@echo " "
	ar r ./lib/libvalidator.a validator-support.o
	
libsimulator.a: simulatore1.o simulatore2.o simulatore3.o simulatore4.o sim-support.o
	@echo " "
	@echo " ...Building 'libsimulator.a'..."
	@echo " "
	ar r ./lib/libsimulator.a simulatore1.o simulatore2.o simulatore3.o simulatore4.o sim-support.o
	
libraries: libfittasso.a libvalidator.a libsimulator.a


#	Build executable .x

exec.x: compiling libraries
	@echo " "
	@echo " ...Linking and build the executable..."
	@echo " "
	g++ -o entosim.x `root-config --cflags --glibs` headers-menu.o entosim.o fittasso.o simulatore.o support.o validator.o -L./lib -lfittasso -lvalidator -lsimulator
	@echo " "
	@echo " Building complete: type './entosim.x' to run EntoSim"
	@echo " "

all: start_compiling compiling libraries hide_input_folders exec.x clean

python.pkg:
	@echo " "
	@echo " ...Installing the Python 3 packages required..."
	@echo " "
	pip3 install plotly numpy scipy pandas dash dash-bootstrap-components

clean:
	@echo " "
	@echo " ...Removing the object files '*.o'..."
	@echo " "
	rm *.o

info:
	@echo " "
	@echo " For more information please read:"
	@echo " "
	@echo "     https://doi.org/10.1016/j.ecoinf.2019.02.002"
	@echo "     https://doi.org/10.1016/j.ecolmodel.2019.108778"
	@echo "     https://doi.org/10.1007/s11587-020-00489-6"
	@echo "     https://doi.org/10.1016/j.cropro.2019.105024"
	@echo "     https://doi.org/10.1016/j.ecoinf.2020.101117"
	@echo " "
	@echo " Thank you for your interest!"
	@echo " "


contacts:
	@echo " "
	@echo " Contacts:"
	@echo " "
	@echo "     Luca Rossini:"
	@echo "     Universita' degli Studi della Tuscia"
	@echo "     luca.rossini@unitus.it"
	@echo " "
	@echo "     Silvia Turco:"
	@echo "     Universita' degli Studi della Tuscia"
	@echo "     silvia.turco@unitus.it"
	@echo " "

hide_input_folders:
	@echo " "
	@echo " ...Hiding input/Graphics folder..."
	@echo " "
	mv ./input/Graphics/ ./input/.Graphics
	@echo " "
	@echo " ...Hiding input/RatePar-simulator folder..."
	@echo " "
	mv ./input/RatePar-simulator/ ./input/.RatePar-simulator
	@echo " "
	@echo " ...Hiding input/SimStorage folder..."
	@echo " "
	mv ./input/SimStorage/ ./input/.SimStorage
	@echo " "
	@echo " ...Hiding input/validator folder..."
	@echo " "
	mv ./input/validator/ ./input/.validator

