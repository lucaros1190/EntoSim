## EntoSim tutorial

### Directories 
Inside EntoSim directory you will find:

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

### How to use Entosim

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

The previous map showed all the EntoSim menu and submenu. Notice that in the main menu you have to type the function to use and press enter: for example typing 'fittasso' (without the apexes) you are selecting the fittasso option, which will open its specific menu. To select the options in each sub-menu, you have just to type the letter corresponding to the operation to do and press enter: for example typing 'a' (without apexes) in the 'fittasso' submenu, you are choosing the 'Fit with Logan function' operation.

### How to use Fittasso
Fittasso is the first block of EntoSim. After its selection from the main EntoSim menu, you can fit experimental data with Logan, Briere, Sharpe and De Michele and Linear rate functions.
First of all, open the file input/LifeTablesTimes.txt and report your data of Temperature, Development time, Temperature error and Development time error separated by a tab space and without any header. This file will look like:

15	78.17	1	4.222
20	40.24	1	1.022
23	29.24	1	0.474
..  ..      ..  ..

Save the changes and go back to EntoSim. Selecting the option 'e' you will convert automatically the development times in development rates, the real input needed by Fittasso for fitting operations (options 'a', 'b', 'c', 'd'). If you already have your data in Temperature and Development rates format (aldready converted), you can insert the data directly into input/LifeTablesRates.txt. Also in this case you have to report the data of Temperature, Development rate, Temperature error, Development time error separated by a tab space and without any header, like:

15.0	0.01279	1.0	0.00069
20.0	0.02485	1.0	0.00063
23.0	0.03420	1.0	0.00055
..      ..      ..  ..

Notice that the errors on the variables are mandatory, hence if you have no experimental errors, just insert '0' values in the last two columns.

Once the input file is set, select the letter corresponding to the function which you wish to use and press enter. At this point, the initial values to start the minimization process are requested: answer to the question typing the values and pressing enter. Once the initial values are inserted, Fittasso asks if the user wants to limit the parameters in some specific range. This option is not mandatory: to skip it, just type 'n' (without apexes) and press enter, in the other case type 'y'. If 'y' option is selected, the lower and upper values of the ranges are required for each of the parameters of the development rate function selected. Insert the requested values answering to the questions and type enter.

Fittasso reports the results in three ways: for a quick check, best fit results and other information are printed on the shell, while a graphical representation of the best fit function overlapped to the experimental points is provided in your internet browser. Please follow the instructions on the screen for a correct visualization, or see the dedicated section in this readme file. The third way to store and visualize results is in the specific .txt file contained in output/DevelopRates. 
More specifically:

    - logratepar.txt Fit results from Logan fit, option 'a'
    - SDMratepar.txt Fit results from Sharpe and De Michele fit, option 'b'
    - briratepar.txt Fit results from Briere fit, option 'c'
    - linratepar.txt Fit results from linear fit, option 'd'

Sometimes it can be helpful to visualise the best fit functions and the experimental points superimposed. If you want to plot one or more best fit functions, select the option 'f' of Fittasso. Once this option is selected, Fittasso asks if the user wants to include the function in question within the plot. Answer to the question typing 'y' (without apexes) if you want to include the function, or 'n' if you do not want to include it. Notice that if you want to include a specific function within the plot, you first need to estimate its best fit parameters! These plots are, in fact, built reading the parameters stored in input/.RatePar-simulator/ !!

***************************************
