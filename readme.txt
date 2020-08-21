*******************************************
*                                         *
*              EntoSim v2.1               *
*                                         *
*   Università degli Studi della Tuscia   *
*                                         *
* *****************************************

Readme file updated to 21 August 2020

***************************
* Developers and contacts *
***************************

Luca Rossini: luca.rossini@unitus.it
Silvia Turco: silvia.turco@unitus.it

**************************
* Background information *
**************************

If you are not familiar with the mathematical models involved in this software, you can find all the information in the following publications:

1. https://doi.org/10.1016/j.ecoinf.2019.02.002
2. https://doi.org/10.1016/j.ecolmodel.2019.108778
3. https://doi.org/10.1007/s11587-020-00489-6
4. https://doi.org/10.1016/j.cropro.2019.105024
5. https://doi.org/10.1016/j.ecoinf.2020.101117
6. https://doi.org/10.1653/024.103.0217

If you are using EntoSim for scientific purposes, you can cite any of these articles. In particular, the state of art of EntoSim is detailed in (1) and (4), while mathematical aspects are detailed in (2), (3), (5) and (6).

****************
* Dependencies *
****************

EntoSim 2.1 requires:

1. ROOT v6.16 or later. Visit https://root.cern/ to download ROOT
2. Python 3.0 or later. Visit https://www.python.org/ to download Python 3
3. Python 3 packages:
    - numpy
    - scipy
    - plotly
    - dash
    - pandas
    - dash-bootstrap-components
3. GNU Make 3.81 or later. Visit https://www.gnu.org/software/make/
4. Linux OS or MacOS

**************************************************
* Compiling binaries and building the executable *
**************************************************

To compile EntoSim 2.1 you can use the Makefile in the main directory. 

1. Open your shell and go to the EntoSim-2.1/ directory
2. Type 'make' to read the Makefile menu
3. Type 'make python.pkg' if you already have Python 3 installed and you need to install the required packages (see dependencies section of this readme file)
4. Type 'make all' to compile and build the executable
5. Type ./entosim.x to run EntoSim

***************
* Directories *
***************

1. bin/ contains the EntoSim binaries
2. lib/ contains the EntoSim libraries
3. input/ contains the .txt files required by 'Fittasso' and 'Simulator' functions within EntoSim. See the dedicated section below for more information.
4. input/validation/ contains the .txt files required by 'Validator' function within EntoSim. See the dedicated section below for more information.
5. output/DevelopRates/ contains the .txt file provided by 'Fittasso'. These file contain the best fit parameters and other results from the non linear regressions
6. output/simresults/ contains the .txt file with the numerical solutions provided by 'Simulatore' function within EntoSim. 
7. output/validation/ contains the .txt file with the results from 'Validator' function within EntoSim
8. Hidden directories:
    - input/.Graphics/ contains the .txt files supporting the graphical representation of EntoSim outputs
    - input/.RatePar-simulator/ contains the .txt files containing the development rate function parameters needed to run the simulations
    - input/.SimStorage/ contains the .txt files containing the numerical output of 'Simulator' needed for the calculations
    - input/.validator contains the .txt file containing the data series for the 'Validator' QQ-plot

**********************
* How to use EntoSim *
**********************

** To start EntoSim, just open your shell, place into EntoSim-2.1/ folder and type ./entosim.x **

EntoSim is organised as follows:

    fittasso
        Fit with 'Logan' function
        Fit with 'Sharpe and De Michele' function
        Fit with 'Briere' function
        Fit with 'Linear' function
        Convert your times in rates
        Draw your rate functions in a single chart
        Go back to EntoSim menu
    simulator
        Manetsch Distributed Delay Model with R(t)
        Manetsch Distributed Delay Model with Q(t)
        Generalized Von Foerster Equation
        Integro-diff Von Foerster Equation
        Go back to EntoSim menu
    validator
        Single comparison - Two data series
        Multiple comparison - More data series
        Go back to EntoSim menu
    info
    exit

The previous map showed all the menu and submenu of EntoSim. Notice that in the main menu you have to type the function to use and press enter: for example typing 'fittasso' (without the apexes) you are selecting the fittasso option, which will open its specific menu. To select the options in each sub-menu, you have just to type the letter corresponding to the operation to do and press enter: for example typing 'a' (without apexes) in the 'fittasso' submenu, you are choosing the 'Fit with Logan function' operation.

***********************
* How to use Fittasso *
***********************

Fittasso is the first block of EntoSim. After its selection from the main EntoSim menu, you can fit experimental data with Logan, Briere, Sharpe and De Michele and Linear rate functions.
First of all, open the file input/LifeTablesTimes.txt and report your data of Temperature, Development time, Temperature error, Development time error separated by a tab space and without any header. This file will looks like:

15	78.17	1	4.222
20	40.24	1	1.022
23	29.24	1	0.474
..  ..      ..  ..

Save the changes and go back to EntoSim. Selecting the option 'e' you will convert automatically the development times in development rates, the real input needed for fitting operations (options 'a', 'b', 'c', 'd'). If you already have you data in Temperature and Development rates, you can insert the data directly into input/LifeTablesRates.txt. Also in this case you have to report the data of Temperature, Development rate, Temperature error, Development time error separated by a tab space and without any header, like:

15.0	0.01279	1.0	0.00069
20.0	0.02485	1.0	0.00063
23.0	0.03420	1.0	0.00055
..      ..      ..  ..

Notice that the errors on the variables are mandatory, hence if you have no experimental errors, just insert '0' values in the last two columns.

Once the input file is set, select the letter corresponding to the function which you wish to use and press enter. At this point, the initial values to start the minimization process are requested: answer to the question typing the values and pressing enter. Once the initial values are inserted, Fittasso asks if the user wants to limit the parameters in some specific range. This option is not mandatory: to skip just type 'n' (without apexes) and press enter, in the other case type 'y'. If 'y' option is selected, the lower and upper values of the ranges are required for each of the parameters of the development rate function selected. Insert the requested values answering to the questions and type enter.

Fittasso reports the results in three ways: for a quick check best fit results and other information are printed on the shell, while a graphical representation of the best fit function overlapped to the experimental points is provided in your internet browser. Please follow the instructions on the screen for a correct visualization, or see the dedicated section in this readme file. The third report of the result is in the specific .txt file contained in output/DevelopRates. 
More specifically:

    - logratepar.txt Fit results from Logan fit, option 'a'
    - SDMratepar.txt Fit results from Sharpe and De Michele fit, option 'b'
    - briratepar.txt Fit results from Briere fit, option 'c'
    - linratepar.txt Fit results from linear fit, option 'd'

Sometimes it can be helpful to visualise the best fit functions and the experimental points superimposed. If you want to plot one or more best fit functions, select the option 'f' of Fittasso. Once this option is selected, Fittasso asks if the user wants to include the function in question within the plot. Answer to the question typing 'y' (without apexes) if you want to include the function, or 'n' if you do not want to include it. Notice that if you want to include a specific function within the plot, you first need to estimate its best fit parameters! These plots are, in fact, built reading the parameters stored in input/.RatePar-simulator/ !!

***************************************
* Open plots in your internet browser *
***************************************

The graphical results of EntoSim are managed by a python script, graphics.py, which uses plotly and dash packages. Once the EntoSim operation is done, follow the intruction printed on the shell:

If you are running EntoSim from a remote server, replace the IP address 0.0.0.0 with your remote server IP. You can see the plots on your browser at the address: http://remote-server-ip:8080

If you are running EntoSim into a local computer, replace the IP 0.0.0.0 with your local machine IP. You can see plots on your browser at the address: http://localhost:8080 or http://127.0.0.1:8080

Then, to come back to EntoSim main menu, press CTRL+C.

************************
* How to use Simulator *
************************

'Simulator' provides the numerical solutions of four models to simulate insect pest life stages. The mathematical details are widely described in the publications reported at the beginning of this readme file, hence only operating instruction about EntoSim will be reported here.
Notice that Simulator subtends that you have already estimated your development rate function parameters with Fittasso, or at least the parameter of the develoment rate function which you are going to use as input into the models.

** Manetsch's Distributed Delay Model in the R(t) and Q(t) variables **

The Manetsch's Distributed Delay Model in the R(t) and Q(t) variables are the first two options of 'Simulatore'. Before to begin, insert in the file input/DailyTemperatures.txt the daily average temperatures that you have measured in the insect's living environment (with a datalogger or a meteo station for example). As well as 'Fittasso', the values have to be reported in columns separated by a tab space and without any header. The first column represents the day (as integer numbers 1, 2, etc), while the second the daily average temperature values. Your file will look like:

1	21.87
2	21.95
3	25.64
4	27.71
5	27.59
6	21.88
7	20.07
8	20.41
9	21.91
10	24.07
..  ..

The other inputs are the development rate function parameters, automatically acquired from the .txt files stored in input/.RatePar-simulator/ directory, and the initial condition files:

    input/InitialCondition-DDM-R.txt if you are using the Distributed Delay Model with R(t) variables
    input/InitialCondition-DDM-Q.txt if you are using the Distributed Delay Model with Q(t) variables

These files are composed by two columns separated by a tab space and without any header. The left column indicates the time variable, while the right one indicates the number of individuals (the initial cohort of eggs, for the most familiar reader). Don't care about this file: if you have some specific data you can change the file, but if you have not a standard one will be automatically generated. Your InitialCondition-DDM-R.txt or InitialCondition-DDM-Q.txt files will look like:

1	0
2	100
3	0
4	0
5	0
6	0
7	0
8	0
9	0
..  ..

Once you have set the input files, type the letter corresponding to the model to use and press enter. As first request, Simulatore asks to the user which development rate function she/he wants to use, and in which temperature ranges. Notice that you can select only one specific range for each development rate function, paying attention to not overlap the subranges; moreover the subrange must be connected each other (no gaps!).
Once selected the development rate functions, the h-value is requested to the user. Insert an integer value and press enter. At this point, Simulatore asks if the user wants the standard cohort file, or, in other words, the standard initial condition file InitialCondition-DDM-R.txt or InitialCondition-DDM-Q.txt. If you have already inserted your custom file, answer 'n' and press enter, otherwise 'y' and Simulatore will create a standard file.
Results are  reported in two ways. Firstly, they are displayed in your internet browser (follow the instructions provided in the specific section of this readme file) in a webpage containing three tabs. The first tab contain a 3D-plot with the population density over time and through the life stages, the second tab reports a plot with an overlap of all the numerical solutions and the third tab contains multiple plots, one for each life stage.
The numerical values, instead, are stored in output/simresults/ directory. In this folder a series of .txt files named 'h=1.txt', 'h=2.txt' etc.. contain the numerical solution of each sigle stage. These files can be copied and saved, to be used in further analyses.

The 

















