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

