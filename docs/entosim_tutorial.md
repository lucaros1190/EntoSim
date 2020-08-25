## EntoSim tutorial

### Directories 
Inside *EntoSim-2.1* directory you will find:

1. *bin/* contains the EntoSim binaries
2. *lib/* contains the EntoSim libraries
3. *input/* contains the .txt files required by [Fittasso](https://github.com/lucaros1190/EntoSim-2.1/blob/master/docs/entosim_tutorial.md#how-to-use-fittasso) and [Simulator](https://github.com/lucaros1190/EntoSim-2.1/blob/master/docs/entosim_tutorial.md#how-to-use-simulator) functions.  
4. *input/validation/* contains the .txt files required by [Validator](https://github.com/lucaros1190/EntoSim-2.1/blob/master/docs/entosim_tutorial.md#how-to-use-validator) function. 
5. *output/DevelopRates/* contains the .txt file provided by Fittasso. These file contain the best fit parameters and other results from the non linear regressions.
6. *output/simresults/* contains the .txt file with the numerical solutions provided by *Simulatore* function. 
7. *output/validation/* contains the .txt file with the results from Validator function.
8. Hidden directories:
    - *input/.Graphics/* contains the .txt files supporting the graphical representation of EntoSim outputs.
    - *input/.RatePar-simulator/* contains the .txt files containing the development rate function parameters needed to run the simulations.
    - *input/.SimStorage/* contains the .txt files containing the numerical output of 'Simulator' needed for the calculations.
    - *input/.validator* contains the .txt file containing the data series for the 'Validator' QQ-plot.
9. Notice that the hidden directories will be automatically hidden by the 'make all' command within Makefile, when you compile and build the executable of EntoSim. On this git repository they are not hidden.
******************************************************************************

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
******************************************************************************

### How to use Fittasso
Fittasso is the first block of EntoSim. After its selection from the main EntoSim menu, you can fit experimental data with Logan, Briere, Sharpe and De Michele and Linear rate functions.
First of all, you need to create a file named LifeTablesTimes.txt to be copied inside your *input* folder, where you report data of temperature, development time, temperature error and development time error separated by a tab space and without any header. 
There is already one in the *input* folder that you may modify with [vi](http://ex-vi.sourceforge.net/ex.html) and it looks like this:

|      |      |     |     |
|:----:|:----:|:---:|:---:|
|  15  | 78.17 |  1  |4.222|
| 20   | 40.24 |  1  |1.022|
| 23   | 29.24 |  1  |0.474| 
| 15   | 78.17 |  1  |4.222|
| 20   | 40.24 |  1  |1.022|
| 23   | 29.24 |  1  |0.474|  

Selecting the option 'e' you will convert automatically the development times in development rates, the real input needed by Fittasso for fitting operations (options 'a', 'b', 'c', 'd'). If you already have your data in Temperature and Development rates format (already converted), you can insert the data directly into input/LifeTablesRates.txt. Also in this case you have to report the data of Temperature, Development rate, Temperature error, Development time error separated by a tab space and without any header, as shown in the file example inside */input*.

Notice that the errors on the variables are mandatory, hence if you have no experimental errors, just insert '0' values in the last two columns.

Once the input file is set, select the letter corresponding to the function you wish to use and press enter.      
At this point, the initial values to start the minimization process are requested: answer to the question typing the values and pressing enter.  
Once the initial values are inserted, Fittasso asks if the user wants to limit the parameters in some specific range. This option is not mandatory: to skip it, just type 'n' (without apexes) and press enter, in the other case type 'y'.   
If 'y' option is selected, the lower and upper values of the ranges are required for each of the parameters of the development rate function selected. Insert the requested values answering to the questions and type enter.

Fittasso reports the results in three ways: for a quick check, best fit results and other information are printed on the shell, while a graphical representation of the best fit function overlapped to the experimental points is provided in your internet browser. Please follow the instructions on the screen for a correct visualization, or see the dedicated section in this readme file. The third way to store and visualize results is in the specific .txt file contained in output/DevelopRates. 
More specifically:

    - logratepar.txt Fit results from Logan fit, option 'a'
    - SDMratepar.txt Fit results from Sharpe and De Michele fit, option 'b'
    - briratepar.txt Fit results from Briere fit, option 'c'
    - linratepar.txt Fit results from linear fit, option 'd'

Sometimes it can be helpful to visualise the best fit functions and the experimental points superimposed.  
If you want to plot one or more best fit functions, select the option 'f' of Fittasso. Once this option is selected, Fittasso asks if the user wants to include the function in question within the plot. Answer to the question typing 'y' (without apexes) if you want to include the function, or 'n' if you do not want to include it.  
Notice that if you want to include a specific function within the plot, you first need to estimate its best fit parameters! These plots are, in fact, built reading the parameters stored in input/.RatePar-simulator/ !!

***************************************

### Open plots in your internet browser
The graphical results of EntoSim are managed by a python script, graphics.py into the *bin/* folder, which uses 'plotly' and 'dash' packages.  
Once the EntoSim operation is done, follow the intruction printed on the shell:

If you are running EntoSim from a remote server, replace the IP address 0.0.0.0 with your remote server IP. You can see the plots on your browser at the address: http://remote-server-ip:8080

If you are running EntoSim into a local computer, replace the IP 0.0.0.0 with your local machine IP. You can see plots on your browser at the address: http://localhost:8080 or http://127.0.0.1:8080

Then, to come back to EntoSim main menu, press CTRL+C.
***************************************

### How to use Simulator
'Simulator' provides the numerical solutions of four models to simulate insect pest life stages.
Notice that Simulator subtends that you have already estimated your development rate function parameters with Fittasso, or at least the parameter of the develoment rate function which you are going to use as input into the models.

##### Manetsch's Distributed Delay Model in the R(t) and Q(t) variables

The Manetsch's Distributed Delay Model in the R(t) and Q(t) variables are the first two options of 'Simulatore'. Before to begin, insert into the input/DailyTemperatures.txt file the daily average temperatures that you have measured in the insect's living environment (with a datalogger or a meteo station for example). As well as 'Fittasso', the values have to be reported in columns separated by a tab space and without any header. The first column represents the day (as integer numbers: 1, 2, etc), while the second the daily average temperature values. Your file will look like:

|      |      |  
|:----:|:----:|
| 1    |21.87|
|2|	21.95|
|3|25.64|
|4|27.71|
|5|	27.59|
|6|	21.88|
|7|	20.07|
|8|	20.41|
|9|	21.91|
|10|24.07|

Notice that this file is fundamental to determine the total duration (in days) of the simulation. In fact, the model's assumptions provide for a temperature value in input in each day.  
A counter into Simulatore scan the values and calculate the last day of simulation. If you want to simulate the population for more days, insert other values into DailyTemperatures.txt file on the basis, for example, of weather forecasts.  
Other inputs needed by Simulatore, are the development rate function parameters, automatically acquired from the .txt files stored in *input/.RatePar-simulator/* directory, and the initial condition files:

    input/InitialCondition-DDM-R.txt if you are using the Distributed Delay Model with R(t) variables
    input/InitialCondition-DDM-Q.txt if you are using the Distributed Delay Model with Q(t) variables

These files are composed by two columns separated by a tab space and without any header. The left column indicates the time variable, while the right one indicates the number of individuals (the initial cohort of eggs, for the most familiar reader). Don't care about this file: if you have some specific data you can change the values into the file, otherwise a standard one will be automatically generated. Your InitialCondition-DDM-R.txt or InitialCondition-DDM-Q.txt files will look like:

|      |      |  
|:----:|:----:|
| 1    |0|
|1	|0|
|2	|100|
|3	|0|
|4	|0|
|5	|0|
|6	|0|
|7	|0|
|8	|0|
|9	|0|

Another input file to fill before to select the model and start the simulations, is *input/MortalityRates.txt*.   
This file is composed by two columns separated by a tab space, and without any header. The first column represents the life stage, while the second one its corresponding mortality coefficient (a constant usually provided by laboratory experiments). This is just a rough estimatin of the mortality, and we hope to improve this part of EntoSim providing an analytical function in future develops. By the way, your MortalityRates.txt file should be like:

|      |      |  
|:----:|:----:|
|1|0.10|
|2|0.01|
|3|0.09|
|4|0.11|
|5|0.07|
|6|0.05|

If you do not want to consider mortality within simulations, replace the values in the right column with '0'. 
Once you have set the input files, type the letter corresponding to the model to use and press enter.  
As first request, Simulatore asks to the user which development rate function she/he wants to use, and in which temperature ranges.   
Notice that you can select only one specific range for each development rate function, paying attention to not overlap the subranges; moreover the subrange must be connected each other (no gaps!).  
Once selected the development rate functions, the h-value is requested to the user. Insert an integer value and press enter.  
At this point, Simulatore asks if the user wants the 'standard cohort file', or, in other words, 'the standard initial condition' file. If you have selected the model 'a', the initial condition file is InitialCondition-DDM-R.txt, if you have selected the model 'b', the initial condition file is InitialCondition-DDM-Q.txt, as stated above. If you have already inserted your custom file, answer 'n' and press enter, otherwise 'y' and Simulatore will create a standard file.

Simulatore has two ways to report simulation results. Firstly, they are displayed in your [internet browser](https://github.com/lucaros1190/EntoSim-2.1/blob/master/docs/entosim_tutorial.md#open-plots-in-your-internet-browser) and more specifically in a webpage containing three tabs.  
The first tab contains a 3D-plot with the population density over time and through the life stages, the second tab reports a plot with an overlap of all the numerical solutions and the third tab contains multiple plots, one for each life stage simulated.  
The numerical values, instead, are stored in output/simresults/ directory. In this folder a series of .txt files named 'h=1.txt', 'h=2.txt' etc.. contain the numerical solution of each sigle stage. The number after 'h=' in the file names, represent the simulated life stage; hence if the user is interested in a particular stage, she/he can recognise quickly the file of interest. These files, moreover, can be copied and saved, to be used in further analyses.

##### The Generalised Von Foerster's equation and the Generalised Von Foerster integro-differential Equation 

The Generalised Von Foerster's equation model, the options 'c' of Simulator, and the Generalised Von Foerster's integro-differential Equation, option 'd', have the same requirements of the Manetsch DDMs discussed above (options, 'a' and 'b'). Hence, take a look above, before to read this section. Mortality rates are contained into input/MortalityRates.txt.
An additional input is required by the Generalised Von Foerster's integro-differential Equation (option 'd'): the fertility rates.  
Fertility rates are stored into input/FertilityRates.txt and this file have to be filled in the same way of input/MortalityRates.txt. 
Hence, FertilityRates.txt should look like:

|      |      |  
|:----:|:----:|
|1|	0|
|2|	0|
|3|	0|
|4|	0|
|5|	0.1|
|6|	0|

The model in 'c' and 'd' shares the same file for the initial condition, namely input/InitialCondition-GVFE.txt: this file can be customized; if not, a standard file is provided if the user answer 'y' to the specific question.   
The left column of this file represents the life stage, while the right one the number of individuals who are in that particular stage at the beginning of the simulation. It can be associable to a field survey where individuals are divided in age classes in a specific day.  
Since the Generalised Von Foerster's models are partial differential equations based, a boundary condition is needed.  
The latter is stored into input/BoundaryCondition-GVFE.txt file.   
This file contains the time (expressed in days) in the left column, while in the right one the number of individuals; columns are tab spaced and without any header. This file can be considered as a rough newborn profile (or an oviposition curve over time).
***************************************

### How to use Validator
Validator provides a comparison of two or more data series using the chi square and the coefficient of determination (R square) as indicators.  
The single validation, option 'a' of Validator, requires two input files: the first input file is input/validation/simulation.txt and it is composed by two columns tab spaced without any header.   
In the first column it can be reported the time variable, while on the right the simulated population. Notice that this tool can be used to compare any data series, not only populations. The first column should represent the independent variable, while the right one the dependent variable. In this context, moreover, simulation.txt represents a predicted value.  
The second input file is input/validation/validation.txt and has the same composition of simulation.txt. This file, however, should be filled with experimental data provided for example by field monitoring. A numerical value of the chi square and R square is privided as result: printed on the shell and stored in an output file output/validation/single_comparison.txt. In addition a QQ-plot is printed on your internet browser (see the graphics section for more information).  

The second option of Validator ('b') provides for a multiple comparison, considering also in this case the chi square and R square values.   
In particular, this file compares the data series contained in input/validation/validation.txt with the h-files produced by 'Simulatore' and stored in output/simresults. This option was ideated to support validation with the Distributed Delay Model(s) ('a' and 'b' options of Simulatore): for this reason the number of h files to compare with the series contained in validation.txt is requested.   
The output is stored into output/validation/multiple_comparison.txt: this file contains the chi square and R square values of each comparison, ordered in ascending order (on the basis of the chi square value).
***************************************

### Logfiles
EntoSim has two Logfiles, located in the main directory. More specifically, the logfile of the current session is 'logfile.log', but once the user quit EntoSim, this contenent is copied into 'logfilePrevSession.log'. 

