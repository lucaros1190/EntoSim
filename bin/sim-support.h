
/* This file contains the list of the functions included in "sim-support.c".
 These functions support the simulations provided by "simulatore" tool.

Created by Luca Rossini on 10/08/2020
email: luca.rossini@unitus.it
last update 11/08/2020 */


    // Calculate the linear rate function taking as input temperature from input/dailytemp.txt, angular coefficient and intercept from input/.RatePar-simulator/linratepar.txt

double lineare_insim(double T);


    // Calculate the Briere rate function taking as input temperature from input/dailytemp.txt, function's parameters (a, T_L, T_M, and m) from input/.RatePar-simulator/briratepar.txt

double briere_insim(double T);


    // Calculate the Logan rate function taking as input temperature from input/dailytemp.txt, function's parameters (psi, rho, T_Ml, and delta_T) from input/.RatePar-simulator/logratepar.txt

double logan_insim(double T);


    // Calculate the Sharpe and De Michele rate function taking as input temperature from input/dailytemp.txt, function's parameters (A, B, C, D, E, F) from input/.RatePar-simulator/SDMratepar.txt
                        
double sharpe_demichele_insim(double T);


    // This function delete and create the folder 'output/simresults'

void cleaner(void);


    // This function creates the standard file with the initial condition for the Generalised Von Foerster's equation and the Generalised Von Foerster equation Integro-differential

void InitialCondGVFE(int col_max);


    // This function creates the standard file with the boundary condition for the Generalised Von Foerster's equation and the Generalised Von Foerster equation Integro-differential

void BoundaryCondGVFE(int col_max);


    // This function creates the standard initial cohort for the DDM with Q(t) variables

void InitialCondDDMQ(int d_max);


    // This function creates the standard initial cohort for the DDM with R(t) variables

void InitialCondDDMR(int d_max);


    // This function absorbs the fertility coefficients (lab estimated - no function)

double fertility(int h);


    // This function absorbs the mortality coefficients (lab estimated - no function)

double mortality(int h);
