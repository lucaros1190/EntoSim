
/* Source of the function with simulates population densities with the Manetsch's
 Distributed Delay Model in the R(t) variables.
 
 Created by Luca Rossini on 07/02/2019
 email: luca.rossini@unitus.it
 last update 14/08/2020 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sim-support.h"
#include "support.h"
#include "headers-menu.h"

#define MAXR 5000
#define MAXRC 300


void simulatore1(void){
    
    // Statement for the logfile
    
    system(" echo \"simulatore1() function started \" >> logfile.log ");
    
    //          ** Variables declaration **
    
    double m=0;
    
    char lin_risp = ' ', briere_risp = ' ', logan_risp = ' ', sharpedemich_risp = ' ', monitoring_risp = ' ';
    
    double TL_lin, TM_lin, TL_briere, TM_briere, TL_logan, TM_logan, TL_sdm, TM_sdm;
    
    int r=0, scan=0, j=0, i=0, col=0, col_max=0;
    
    int switch_lineare=0, switch_briere=0, switch_logan=0, switch_sdm=0;
    
    double mat[MAXRC][2]={{0}}, temp[MAXRC][2]={{0}}, initcond[MAXRC][2]={{0}}, n[MAXRC][MAXRC]={{0}}, AA[MAXRC]={0}, BB[MAXRC]={0}, errN[MAXRC][MAXRC]={{0}};
    
    

    // Body of simulatore1()
    

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
            system(" echo \"Error: simulatore1() function. Failure opening file input/DailyTemperatures.txt \" >> logfile.log ");
        }
        else if (daytemp != 0){
            system(" echo \"simulatore1() function. File input/DailyTemperatures.txt succesfully opened\" >> logfile.log ");
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
    
    // Ask the h value for the Manetsch's DDM model R(t) version
    
    clear();
    printf("%s", "\n Insert the h value: \n\n");
    scanf("%d", &col_max);
    
    // Ask the array of the initial cohort - If not a standard will be created
    
    clear();
    printf("%s", "\n Do you want the standard cohort file? y/n \n\n");
    scanf("%c", &monitoring_risp);
    
    if(monitoring_risp == 'y'){
        InitialCondDDMR(j);
    }
    
    else if (monitoring_risp != 'y'){
        goto avanti3;
    }
    
    
avanti3:
    
    // Read the initial condition from input/InitialCondition-DDM-R.txt
    
    FILE *monitoring;
        monitoring = fopen("./input/InitialCondition-DDM-R.txt", "r");
        
        // Report the status of the file into the logfile
        if (monitoring == 0){
            system(" echo \"Error: simulatore1() function. Failure opening file input/InitialCondition-DDM-R.txt \" >> logfile.log ");
        }
        else if (monitoring != 0){
            system(" echo \"simulatore1() function. File input/InitialCondition-DDM-R.txt succesfully opened\" >> logfile.log ");
        }
        
        // Scan the content
        for(i=0; i<=j; i++){
            fscanf(monitoring, "%lf\t%lf", &initcond[i][0], &initcond[i][1]);
            n[i][0] = initcond[i][1];
        }
    fclose(monitoring);
    
    
    // Creates the hidden file input/.SimStorage/NumericalSolution.txt containing a matrix with all the numbers calculated
    
    FILE *simulation1;
        simulation1 = fopen("./input/.SimStorage/NumericalSolution.txt","w");
    
        // Report the status of the file into the logfile
        if (simulation1 == 0){
            system(" echo \"Error: simulatore1() function. Failure opening file input/.SimStorage/NumericalSolution.txt \" >> logfile.log ");
        }
        else if (simulation1 != 0){
            system(" echo \"simulatore1() function. File input/.SimStorage/NumericalSolution.txt succesfully opened\" >> logfile.log ");
        }
        
        // Print the content
    
        // Numerical scheme to solve the Manetsch's DDM in R(t) variables
    
        // Cycle on the rows
        for(i=2; i<=j-2; i++){
        
            // Cycle on the columns
            for(col=1; col<=col_max+10; col++){
                
                // Rough estimation of the mortality - To replace in future!
                m = mortality(col);
            
                // Statement which avoid the division by zero if the rate temp[i][1] is zero
            
                if (temp[i][1] >= 0){
            
                    AA[i] =  col_max * temp[i][1];
                    BB[i] =  AA[i] - (temp[i-1][1]/temp[i][1]) + m;
                }
            
                else if(temp[i][1] <= 0){
                    AA[i] =  col_max * temp[i][1];
                    BB[i] =  AA[i] - (temp[i-1][1]/(temp[i][1]+0.0000001)) + m;
                }
                
                // Make the caculation after the previous check
            
                n[i+1][col] =  n[i][col-1] * AA[i] - BB[i] * n[i][col];
            
                // A filter to exclude negative values on n[i+1][col], the numerical solutions
            
                if (n[i+1][col] >=0){
                    n[i+1][col] =  n[i][col-1] * AA[i] - BB[i] * n[i][col];
                
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
            system(" echo \"Error: simulatore1() function. Failure opening file output/simresults/simulation3D.txt \" >> logfile.log ");
        }
        else if (simulation3D != 0){
            system(" echo \"simulatore1() function. File output/simresults/simulation3D.txt succesfully opened\" >> logfile.log ");
        }
        
        // Print the content
        for(col=1; col<=col_max+10; col++){
            for(i=0; i<=j; i++){
                fprintf(simulation3D, "%d\t%d\t%f\n", col, i, n[i][col]);
            }
        }
    fclose(simulation3D); 
    

    // Create the single stage population curves (the h-files on output/simresults)

    for(col=1; col<=col_max+10; col++){
        
        FILE *hprint[col];
            char filename[40]={ };
            sprintf(filename, "./output/simresults/h=%d.txt", col);
            hprint[col] = fopen(filename, "w");
        
            // Report the status of the file into the logfile
            if (hprint[col] == 0){
                char warning_1[200]={ };
                sprintf(warning_1, " echo \"Error: simulatore1() function. Failure opening file output/simresults/h=%d.txt \" >> logfile.log ", col);
                
                system(warning_1);
            }
            else if (hprint[col] != 0){
                char warning_2[200]={ };
                sprintf(warning_2, " echo \"simulatore1() function. File  output/simresults/h=%d.txt succesfully opened\" >> logfile.log ", col);
                system(warning_2);
            }
            
            // Print the content(s)
            for(i=0; i<=j; i++){
                fprintf(hprint[col], "%d\t%f\t%d\t%f\n", i, n[i][col], 0, errN[i][col]);
            }
        fclose(hprint[col]);
    }
    
    // Prepare the information file for the python part of the program to manage graphics
    
    FILE *InfoPythonGraph;
        InfoPythonGraph = fopen("./input/.SimStorage/SimulatedStages.txt", "w");
    
        // Report the status of the file into the logfile
        if (InfoPythonGraph == 0){
            system(" echo \"Error: simulatore1() function. Failure opening file input/.SimStorage/SimulatedStages.txt \" >> logfile.log ");
        }
        else if (InfoPythonGraph != 0){
            system(" echo \"simulatore1() function. File input/.SimStorage/SimulatedStages.txt succesfully opened\" >> logfile.log ");
        }
        
        // Print the content
        fprintf(InfoPythonGraph, "%s\t%s\n", "Model", "SimStages");
        fprintf(InfoPythonGraph, "%d\t%d\n", 1, col_max);
    fclose(InfoPythonGraph);
    
    
    // Recalling the python part of the program to manage graphics
        
    system("cd bin/ ; python3 -c 'import graphics; graphics.SimPlotter()' ; rm -rf __pycache__ ; cd ..");

}

