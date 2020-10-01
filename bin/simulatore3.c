
/* Source of the function with simulates population densities with the Generalised
 Von Foerster's equation - Rossini PhD thesis
 https://doi.org/10.1016/j.ecolmodel.2019.108778.
 
 Created by Luca Rossini on 07/02/2019
 email: luca.rossini@unitus.it
 last update 17/08/2020 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sim-support.h"
#include "support.h"
#include "headers-menu.h"

#define MAXR 5000
#define MAXRC 300


void simulatore3(void){
    
    // Statement for the logfile
    
    system(" echo \"simulatore3() function started \" >> logfile.log ");
    
    //          ** Dichiarazione delle variabili **
    
    double m=0;
    
    char lin_risp = ' ', briere_risp = ' ', logan_risp = ' ', sharpedemich_risp = ' ', profile_risp = ' ', monitoring_risp = ' ';
    
    double TL_lin, TM_lin, TL_briere, TM_briere, TL_logan, TM_logan, TL_sdm, TM_sdm;
    
    int r=0, scan=0, j=0, i=0, h=0, col=0, col_max=0;
    
    int switch_lineare=0, switch_briere=0, switch_logan=0, switch_sdm=0;
    
    double mat[MAXRC][2]={{0}}, temp[MAXRC][2]={{0}}, initcond[MAXRC][2]={{0}}, boundcond[MAXRC][2]={{0}}, n[MAXRC][MAXRC]={{0}}, errN[MAXRC][MAXRC]={{0}};
    
    
    
    // Body of simulatore3()
    
    
inizio: // If no development rate function is selected, it goes back here
    
    
    // Selection of the development rate functions involved and in which temperature ranges
    
    
    clear();
    printf("%s", "\n Do you want to use the LINEAR rate function? y/n \n\n");
    scanf("%c", &lin_risp);
    
    if(lin_risp == 'y'){
        printf("%s", "\n Insert the temperature range for linear rate function: \n\n");
        
        printf("%s", "T low: \n\n");
        scanf("%lf", &TL_lin);
        printf("%s", "\nT max: \n\n");
        scanf("%lf", &TM_lin);
        switch_lineare = 1;
    }
    
    else if(lin_risp == 'n'){
        switch_lineare = 0;
        goto briere;
    }
    
    else{
        printf("%s", "\n Incorrect choice, please try again!\n");
        goto inizio;
    }
    
    
briere:
    
    clear();
    printf("%s", "\n Do you want to use the BRIERE rate function? y/n \n\n");
    scanf("%c", &briere_risp);
    
    if(briere_risp == 'y'){
        printf("%s", "\n Insert the temperature range for Briére rate function: \n\n");
        
        printf("%s", "T low: \n\n");
        scanf("%lf", &TL_briere);
        printf("%s", "\nT max: \n\n");
        scanf("%lf", &TM_briere);
        switch_briere = 1;
    }
    
    else if(briere_risp == 'n'){
        switch_briere = 0;
        goto logan;
    }
    
    else{
        printf("%s", "\n Incorrect choice, please try again!\n");
        goto briere;
    }
    
    
logan:
    
    clear();
    printf("%s", "\n Do you want to use the LOGAN rate function? y/n \n\n");
    scanf("%c", &logan_risp);
    
    if(logan_risp == 'y'){
        
        printf("%s", "\n Insert the temperature range for Logan rate function: \n\n");
        
        printf("%s", "T low: \n\n");
        scanf("%lf", &TL_logan);
        printf("%s", "\nT max: \n\n");
        scanf("%lf", &TM_logan);
        switch_logan = 1;
    }
    
    else if(logan_risp == 'n'){
        switch_logan = 0;
        goto sharpedemichele;
    }
    
    else{
        printf("%s", "\n Incorrect choice, please try again!\n");
        goto logan;
    }
    
    
sharpedemichele:
    
    clear();
    printf("%s", "\n Do you want to use the SHARPE AND DE MICHELE rate function? y/n \n\n");
    scanf("%c", &sharpedemich_risp);
    
    if(sharpedemich_risp == 'y'){
        
        printf("%s", "\n Insert the temperature range for Sharpe and De Michele rate function: \n\n");
        
        printf("%s", "T low: \n\n");
        scanf("%lf", &TL_sdm);
        printf("%s", "\nT max: \n\n");
        scanf("%lf", &TM_sdm);
        switch_sdm = 1;
    }
    
    else if(sharpedemich_risp == 'n'){
        switch_sdm = 0;
        goto avanti;
    }
    
    else{
        printf("%s", "\n Incorrect choice, please try again!\n");
        goto sharpedemichele;
    }
    
    
avanti:
    
    // Control if at least one development rate function was selected
    
    if(lin_risp == 'y' || briere_risp == 'y' || logan_risp == 'y' || sharpedemich_risp == 'y'){
        goto avanti2;
    }
    
    else{
        goto inizio;
    }
    
    
avanti2:
    
    // Read the daily average temperature values from 'input/DaylyTemperatures.txt'
    
    FILE *daytemp;
        daytemp = fopen("./input/DailyTemperatures.txt", "r");
    
        // Report the status of the file into the logfile
        if (daytemp == 0){
            system(" echo \"Error: simulatore3() function. Failure opening file input/DailyTemperatures.txt \" >> logfile.log ");
        }
        else if (daytemp != 0){
            system(" echo \"simulatore3() function. File input/DailyTemperatures.txt succesfully opened\" >> logfile.log ");
        }
        
        // Scan the content
        for(r=0; scan != EOF; r++){
            scan = fscanf(daytemp, "%lf%lf", &mat[r][0], &mat[r][1]);
            
            // This is the counter of the days involved into the simulation
            
            j=r;
        }
    fclose(daytemp);
    
    
    // This cycle calculates the development rates using the specific function into the specific range selected previously
    
    for(i=0; i<=j; i++){
        
        if(switch_lineare == 1 && mat[i][1] >= TL_lin && mat[i][1] <= TM_lin) {
            temp[i][0] = mat[i][0];
            temp[i][1] = lineare_insim(mat[i][1]);
        }
        
        else if(switch_lineare == 0 || mat[i][1] <= TL_lin || mat[i][1] >= TM_lin){
            goto tbriere;
        }
        
    tbriere:
        
        if(switch_briere == 1 && mat[i][1] >= TL_briere && mat[i][1] <= TM_briere) {
            temp[i][0] = mat[i][0];
            temp[i][1] = briere_insim(mat[i][1]);
        }
        
        else if(switch_briere == 0 || mat[i][1] <= TL_briere || mat[i][1] >= TM_briere){
            goto tlogan;
        }
        
    tlogan:
        
        if(switch_logan == 1 && mat[i][1] >= TL_logan && mat[i][1] <= TM_logan) {
            temp[i][0] = mat[i][0];
            temp[i][1] = logan_insim(mat[i][1]);
        }
        
        else if(switch_logan == 0 || mat[i][1] <= TL_logan || mat[i][1] >= TM_logan){
            goto tsharpedemichele;
        }
        
    tsharpedemichele:
        
        if(switch_sdm == 1 && mat[i][1] >= TL_sdm && mat[i][1] <= TM_sdm) {
            temp[i][0] = mat[i][0];
            temp[i][1] = sharpe_demichele_insim(mat[i][1]);
        }
        
        else if(switch_sdm == 0 || mat[i][1] <= TL_sdm || mat[i][1] >= TM_sdm){
            continue;
        }
        
    }
    
    
    /* NOTE: the array which contains the daily rates calculated previously is temp[i][0] (days) temp[i][1] (rates). The days listed into 'input/dailytemp.txt' will be not used for the further calculations */
    
    cleaner();
    
    // Ask how many observable stages has the species to simulate
    
    clear();
    printf("%s", "\n How many life stages has your insect? \n\n");
    scanf("%d", &col_max);
    
    // Ask the array of the initial condition - If not a standard will be created
    
    clear();
    printf("%s", "\n Do you want the standard initial condition (the initial population profile) file? y/n \n\n");
    scanf("%c", &profile_risp);
    
    if(profile_risp == 'y'){
        InitialCondGVFE(col_max);
    }
    
    else if (profile_risp != 'y'){
        goto avanti3;
    }
    
    
avanti3:
    
    // Ask the array of the boundary condition - If not a standard will be created
    
    clear();
    printf("%s", "\n Do you want the standard boundary condition? (say 'n' if you have previous monitoring) y/n \n");
    scanf("%c", &monitoring_risp);
    
    if(monitoring_risp == 'y'){
        BoundaryCondGVFE(j);
    }
    
    else if (monitoring_risp != 'y'){
        goto avanti4;
    }
    
    
avanti4:
    
    // Read the initial condition from input/InitialCondition-GVFE.txt
    
    FILE *initprofile;
        initprofile = fopen("./input/InitialCondition-GVFE.txt", "r");
        
        // Report the status of the file into the logfile
        if (initprofile == 0){
            system(" echo \"Error: simulatore3() function. Failure opening file input/InitialCondition-GVFE.txt \" >> logfile.log ");
        }
        else if (initprofile != 0){
            system(" echo \"simulatore3() function. File input/InitialCondition-GVFE.txt succesfully opened\" >> logfile.log ");
        }
        
        // Scan the content
        for(col=1; col<=col_max; col++){
            fscanf(initprofile, "%lf\t%lf", &initcond[col][0], &initcond[col][1]);
            n[0][col] = initcond[col][1];
        }
    fclose(initprofile);
    
    // Read the boundary condition from input/BoundaryCondition-GVFE.txt
    
    FILE *monitoring;
        monitoring = fopen("./input/BoundaryCondition-GVFE.txt", "r");
        
        // Report the status of the file into the logfile
        if (monitoring == 0){
            system(" echo \"Error: simulatore3() function. Failure opening file input/BoundaryCondition-GVFE.txt \" >> logfile.log ");
        }
        else if (monitoring != 0){
            system(" echo \"simulatore3() function. File input/BoundaryCondition-GVFE.txt succesfully opened\" >> logfile.log ");
        }
        
        // Scan the content
        for(i=0; i<=j; i++){
            fscanf(monitoring, "%lf\t%lf", &boundcond[i][0], &boundcond[i][1]);
            n[i][0] = boundcond[i][1];
        }
    fclose(monitoring);
    
    
    // Create the hidden file input/.SimStorage/NumericalSolution.txt containing a matrix with all the numbers calculated
    
    
    FILE *simulation1;
        simulation1 = fopen("./input/.SimStorage/NumericalSolution.txt","w");
        
        // Report the status of the file into the logfile
        if (simulation1 == 0){
            system(" echo \"Error: simulatore3() function. Failure opening file input/.SimStorage/NumericalSolution.txt \" >> logfile.log ");
        }
        else if (simulation1 != 0){
            system(" echo \"simulatore3() function. File input/.SimStorage/NumericalSolution.txt succesfully opened\" >> logfile.log ");
        }
        
        // Print the content
    
        // Numerical scheme to solve the Generalised Von Foerster's Equation
    
        // Cycle on the rows
        for(i=0; i<=j-2; i++){
        
            // Cycle on the columns
            for(col=1; col<=col_max; col++){
                
                // Rough estimation of the mortality - To replace in future!
                m = mortality(col);
            
                // Make the calculation
            
                n[i+1][col] =  n[i][col] - (n[i][col] - n[i][col-1])*(i/col)*temp[i][1] - n[i][col]*i*m;
            
                // A filter to exclude negative values on n[i+1][col], the numerical solutions
            
                if (n[i+1][col] >=0){
                    n[i+1][col] =  n[i][col] - (n[i][col] - n[i][col-1])*(i/col)*temp[i][1] - n[i][col]*i*m;
                
                    // Rough evaluation of the error associated with the Euler's finite difference method
                    errN[0][col] = 0;
                    errN[i][col] = fabs(0.5 * n[i+1][col] - n[i][col] + 0.5 * n[i-1][col]);
                }
            
                else if (n[i+1][col] <0){
                    n[i+1][col] = 0;
                    errN[i][col] = 0;
                }
                
                // Print the columns
                fprintf(simulation1, "%f\t", n[i+1][col]);
            }
            // Print the rows
            fprintf(simulation1, "%f\n", n[i+1][col]);
        }
    fclose(simulation1);
    
    
    // This output file is generated for the 3D plot
    
    FILE *simulation3D;
        simulation3D = fopen("./output/simresults/simulation3D.txt", "w");
    
        // Report the status of the file into the logfile
        if (simulation3D == 0){
            system(" echo \"Error: simulatore3() function. Failure opening file output/simresults/simulation3D.txt \" >> logfile.log ");
        }
        else if (simulation3D != 0){
            system(" echo \"simulatore3() function. File output/simresults/simulation3D.txt succesfully opened\" >> logfile.log ");
        }
        
        // Print the content
        for(col=1; col<=col_max; col++){
            for(i=0; i<=j; i++){
                fprintf(simulation3D, "%d\t%d\t%f\n", col, i, n[i][col]);
            }
        }
    fclose(simulation3D);
    
    // Create the single stage population curves (the h-files on output/simresults)
    
    for(h=1; h<=col_max; h++){
        
        FILE *hprint[h];
            char filename[40]={ };
            sprintf(filename, "./output/simresults/h=%d.txt", h);
            hprint[h] = fopen(filename, "w");
        
            // Report the status of the file into the logfile
            if (hprint[col] == 0){
                char warning_1[200]={ };
                sprintf(warning_1, " echo \"Error: simulatore3() function. Failure opening file output/simresults/h=%d.txt \" >> logfile.log ", col);
                
                system(warning_1);
            }
            else if (hprint[col] != 0){
                char warning_2[200]={ };
                sprintf(warning_2, " echo \"simulatore3() function. File  output/simresults/h=%d.txt succesfully opened\" >> logfile.log ", col);
                system(warning_2);
            }
            
            // Print the content(s)
            for(i=0; i<=j; i++){
                fprintf(hprint[h], "%d\t%f\t%d\t%f\n", i, n[i][h], 0, errN[i][h]);
            }
        fclose(hprint[h]);
    }
    
    
    // Prepare the information file for the python part of the program to manage graphics
    
    FILE *InfoPythonGraph;
        InfoPythonGraph = fopen("./input/.SimStorage/SimulatedStages.txt", "w");
        
        // Report the status of the file into the logfile
        if (InfoPythonGraph == 0){
            system(" echo \"Error: simulatore3() function. Failure opening file input/.SimStorage/SimulatedStages.txt \" >> logfile.log ");
        }
        else if (InfoPythonGraph != 0){
            system(" echo \"simulatore3() function. File input/.SimStorage/SimulatedStages.txt succesfully opened\" >> logfile.log ");
        }
        
        // Print the content
        fprintf(InfoPythonGraph, "%s\n", "Model\tSimStages");
        fprintf(InfoPythonGraph, "%d\t%d\n", 3, col_max);
    fclose(InfoPythonGraph);
    
    
    
    // Recalling the python part of the program to manage graphics
        
system("cd bin/ ; python3 -c 'import graphics; graphics.SimPlotter()' ; rm -rf __pycache__ ; cd ..");
    
}

