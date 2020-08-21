
/* This file contains the functions needed by validator tool. It is possible to execute
 a single comparison between two data series or to compare a single data series with
 multiple files. This last is helpful to apply the Manetsch's Distributed Delay Model.
 
Created by Luca Rossini on 13/02/2019
email: luca.rossini@unitus.it
last update 04/08/2020 */



#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include "headers-menu.h"
#include "support.h"


// This function deletes and creates the folder "validation"

void cleaner_validation(void){
    
    // Statement for the logfile
    
    system(" echo \"clener_validation() function started \" >> logfile.log ");
    
    int i, j;
    
    i = system("rm -r ./output/validation");
    if (i != 0){
        
       system(" echo \"Error: cleaner_validation() function. Failure removing /output/validation\" >> logfile.log ");
    }
    
    else if (i==0){
        system(" echo \"cleaner_validation() function. Folder /output/validation succesfully removed\" >> logfile.log ");
    }
    
    j = system("mkdir ./output/validation");
    if (j != 0){
        system(" echo \"Error: cleaner_validation() function. Failure making dir /output/validation\" >> logfile.log ");
    }
    
    else if (j==0){
        system(" echo \"cleaner_validation() function. Folder /output/validation succesfully created\" >> logfile.log ");
    }
}


// This function compares only two series of data and makes a QQ-plot

void validator_single(void){
    
    // Statement for the logfile
    
    system(" echo \"validator_single() function started \" >> logfile.log ");
    
    double valid[500][2]={ }, simul[500][2]={ }, conf[300][3]={ };
    
    int scan=0, r=0, rval=0, rsim=0, i=0, k=0, rlim=0;
    
    double chiquadro=0, y_med=0, TSS=0, ESS=0, RSS=0, R2=0, somma=0;
    
    // Reads the first series of data, considered as validation (experimental) data already inserted into 'input/validation/validation.txt'
    
    FILE *validazione;
        validazione = fopen("./input/validation/validation.txt", "r");
    
        // Report the status of the file into the logfile
        if (validazione == 0){
            system(" echo \"Error: validator_single() function. Failure opening file  input/validation/validation.txt\" >> logfile.log ");
        }
        else if (validazione != 0){
            system(" echo \"validator_single() function. File  input/validation/validation.txt succesfully opened\" >> logfile.log ");
        }
        
        // Scan the content
        for(r=0; scan != EOF; r++){
            scan = fscanf(validazione, "%lf%lf", &valid[r][0], &valid[r][1]);
            rval = r;
        }
    fclose(validazione);

    
    // Reads the second series of data, considered as simulated (theorethical) data already inserted into 'input/validation/simulation.txt'
    
    FILE *simulazione;
        simulazione = fopen("./input/validation/simulation.txt", "r");
        scan=0;
    
        // Report the status of the file into the logfile
        if (simulazione == 0){
            system(" echo \"Error: validator_single() function. Failure opening file  input/validation/simulation.txt\" >> logfile.log ");
        }
        else if (simulazione != 0){
            system(" echo \"validator_single() function. File  input/validation/simulation.txt succesfully opened\" >> logfile.log ");
        }
        
        // Scan the content
        for(r=0; scan != EOF; r++){
            scan = fscanf(simulazione, "%lf%lf", &simul[r][0], &simul[r][1]);
            rsim = r;
        }
    fclose(simulazione);
    
    
    // Compares the days and takes only the y values corresponding to the same day. Here it is assumed that should be more simulated (theorethical) data than validation (experimental) data
    
    if (rsim >= rval) {
        goto ok;
    }
    
    else if (rsim < rval) {
        printf("%s", "\n Please provide more simulation data into input/validation/simulation.txt. Unable to continue!\n\n");
        std::exit(EXIT_SUCCESS);
    }
    
ok: // Continues once assessed that the calculation is possible

    // Compares the series and creates the control file 'calculation' into 'input/.validator'

    FILE *calculation;
        calculation = fopen("./input/.validator/calculation.txt", "w");
    
        // Report the status of the file into the logfile
        if (calculation == 0){
            system(" echo \"Error: validator_single() function. Failure opening file  input/.validator/calculation.txt \" >> logfile.log ");
        }
        else if (calculation != 0){
            system(" echo \"validator_single() function. File  input/.validator/calculation.txt succesfully opened\" >> logfile.log ");
        }
    
        // Write the content
        for(i=0; i < rval; i++){
            for(r=0; r <= rsim; r++){
                if (valid[i][0] == simul[r][0]){
                    
                    // Stops the counter when the if condition is assessed
                    rlim = r;
                    fprintf(calculation, "%.0f\t%lf\t%lf\n", valid[i][0], valid[i][1], simul[rlim][1]);
                    conf[i][0] = valid[i][0];
                    conf[i][1] = valid[i][1];
                    conf[i][2] = simul[rlim][1];
                }
                else {
                    continue;
                }
            }
            k = i+1; // counter for the chi-square calculation
        }
            
    fclose(calculation);

    
    // Creates the folder output/validation: here you can find the reports
    
    cleaner_validation();
    
    
    // Print a hidden file for the QQ-plot
    
    FILE *QQplot;
        QQplot = fopen("./input/.validator/QQplot.txt", "w");
    
        // Report the status of the file into the logfile
        if (QQplot == 0){
            system(" echo \"Error: validator_single() function. Failure opening file  input/.validator/QQplot.txt \" >> logfile.log ");
        }
        else if (QQplot != 0){
            system(" echo \"validator_single() function. File  input/.validator/QQplot.txt succesfully opened\" >> logfile.log ");
        }
        
        // Print the content
        for(i=0; i <= k; i++){
            fprintf(QQplot, "%lf\t%lf\n", conf[i][2], valid[i][1]);
        }
    fclose(QQplot);
    
    
    // Calculate the chi-square
    
    // Calculation
    for(r=0; r<=k; r++){
        // it does not consider values next to zero
        if(conf[r][2] <= 0.001){
            chiquadro = chiquadro + 0;
        }
        
        else{
            chiquadro = chiquadro + (pow(conf[r][1] - conf[r][2], 2) )/ conf[r][2];
        }
    }
    
    
    // Calculate the coefficient of determination R2
    
        // Average of the observed data
    
    for(r=0; r<=k; r++){
        somma = somma + conf[r][1];
    }
    y_med = somma/k;
    
        // Calculation of ESS (needed only for the method below commented)
    
    for(r=0; r<=k; r++){
        ESS = ESS + conf[r][2];
    }
    
        // Calculation of TSS
    
    for(r=0; r<=k; r++){
        TSS = TSS + pow(conf[r][1] - y_med, 2);
    }
    
        // Calulation of RSS
    
    for(r=0; r<=k; r++){
        RSS = RSS + pow(conf[r][1] - conf[r][2], 2);
    }
    
        // Calculation of R2
    
    R2 = 1 - (RSS/TSS);
    
        // Calculation of R2 (alternative method) --> remove comments if you need it
    
        // R2 = (ESS/TSS);

    if (R2 <= 0){
        R2 = 0;
    }
    
    else {
        R2 = 1 - (RSS/TSS);
    }
    

    // Print the report on 'output/validation/single_comparison.txt'
    
    FILE *fp;
        fp = fopen("./output/validation/single_comparison.txt","w");
    
        // Report the status of the file into the logfile
        if (fp == 0){
            system(" echo \"Error: validator_single() function. Failure opening file  output/validation/single_comparison.txt \" >> logfile.log ");
        }
        else if (fp != 0){
            system(" echo \"validator_single() function. File  output/validation/single_comparison.txt succesfully opened\" >> logfile.log ");
        }
        
        // Print the content
        fprintf(fp, "%s", "\n\n\t VALIDATION REPORT: \n \n\n");
        fprintf(fp, "%s %.8f\n", "  ChiSquared = ", chiquadro);
        fprintf(fp, "%s %.4f\n", "  Coefficient of determination (R^2) = ", R2);
        fprintf(fp, "%s", "\n\n\n  Created by Luca Rossini \n  Universita' degli Studi della Tuscia, Viterbo\n\n\n");
    fclose(fp);
    
    
    // Print the values on the shell
    
    printf("%s", "\n\n  VALIDATION RESULTS:\n");
    
    printf("\n%s%f\n", " \tChisquared = ", chiquadro);
    printf("\n%s%f\n\n", " \tCoefficient of determination (R^2) = ", R2);
    
    
    // Recalling the python part of the program to manage graphics
        
    system("cd bin/ ; python3 -c 'import graphics; graphics.QQ_single_validation()' ; rm -rf __pycache__ ; cd ..");

    return;
}


// This function compares multiple series of simulated data, contained in 'output/simresults/' and named 'h=  .txt', with the validation series contained in 'input/validation/validation.txt

void validator_multiple(void){
    
    // Statement for the logfile
    
    system(" echo \"validator_multiple() function started \" >> logfile.log ");

    double valid[500][2]={ }, simul[500][4]={ }, conf[300][3]={ }, storage_array[500][3]={{0}};
        
    int scan=0, r=0, rval=0, rsim=0, i=0, k=0, rlim=0, col_max=0, h=0, j=0, min=0;
        
    double chiquadro=0, y_med=0, TSS=0, ESS=0, RSS=0, R2=0, temp_h=0, temp_chiq=0, temp_R2=0, somma=0;
        
        // Reads the first series of data, considered as validation (experimental) data already inserted into 'input/validation/validation.txt'
        
    FILE *validazione;
        validazione = fopen("./input/validation/validation.txt", "r");
    
        // Report the status of the file into the logfile
        if (validazione == 0){
            system(" echo \"Error: validator_multiple() function. Failure opening file input/validation/validation.txt \" >> logfile.log ");
        }
        else if (validazione != 0){
            system(" echo \"validator_multiple() function. File  input/validation/validation.txt succesfully opened\" >> logfile.log ");
        }
    
        // Scan the content
        for(r=0; scan != EOF; r++){
            scan = fscanf(validazione, "%lf%lf", &valid[r][0], &valid[r][1]);
            rval = r;
        }
    fclose(validazione);

        // Creates the folder output/validation: here you can find the reports
    
    cleaner_validation();
    
    
        // Hidden file in 'input/.validator' called stored_comparisons.txt where the values calculated below are stored
    
    FILE *stored_comparisons;
        stored_comparisons = fopen("./input/.validator/stored_comparisons.txt", "w");
    
        // Report the status of the file into the logfile
        if (stored_comparisons == 0){
            system(" echo \"Error: validator_multiple() function. Failure opening file input/.validator/stored_comparisons.txt \" >> logfile.log ");
        }
        else if (stored_comparisons != 0){
            system(" echo \"validator_multiple() function. File  input/.validator/stored_comparisons.txt succesfully opened\" >> logfile.log ");
        }
    
        
        // Asks how many file you have to compare in ./output/simresults
    
        printf("%s", "\n How many file 'h=' files, stored in 'output/simresults' folder, do you want to compare? \n Please provide the number of 'h=' files to compare with validation data \n\n");
        clear();
        scanf("%d", &col_max);
    
    
        // Cycle to compare the validation data with all the simulation files
    
        for(h=1; h<=col_max; h++){
    
        // Reads the second series of data, considered as simulated (theorethical) data already inserted into 'input/validation/simulation.txt'
        
            FILE *simulazione[h];
                char filename[40]={ };
                sprintf(filename, "./output/simresults/h=%d.txt", h);
                simulazione[h] = fopen(filename, "r");
            
                // Report the status of the file into the logfile
                if (stored_comparisons == 0){
                    char warning_1[200]={ };
                    sprintf(warning_1, " echo \"Error: validator_multiple() function. Failure opening file output/simresults/h=%d.txt \" >> logfile.log ", h);
                    
                    system(warning_1);
                }
                else if (stored_comparisons != 0){
                    char warning_2[200]={ };
                    sprintf(warning_2, " echo \"validator_multiple() function. File  output/simresults/h=%d.txt succesfully opened\" >> logfile.log ", h);
                    system(warning_2);
                }
                
                // Scan the content(s)
                scan=0;
                for(r=0; scan != EOF; r++){
                    scan = fscanf(simulazione[h], "%lf%lf%lf%lf", &simul[r][0], &simul[r][1], &simul[r][2], &simul[r][3]);
                    rsim = r;
                }
            fclose(simulazione[h]);
        
        
        // Compares the days and takes only the y values corresponding to the same day. Here it is assumed that should be more simulated (theorethical) data than validation (experimental) data
        
            if (rsim >= rval) {
                goto ok;
            }
        
            else if (rsim < rval) {
                printf("%s", "\n Please provide more simulation data into input/validation/simulation.txt. Unable to continue!\n\n");
                std::exit(EXIT_SUCCESS);
            }
        
ok: // Continues once assessed that the calculation is possible

        // Compares the series
    
            for(i=0; i < rval; i++){
                for(r=0; r <= rsim; r++){
                    if (valid[i][0] == simul[r][0]){
                        // Stops the counter when the if condition is assessed
                        rlim = r;
                        conf[i][0] = valid[i][0];
                        conf[i][1] = valid[i][1];
                        conf[i][2] = simul[rlim][1];
                    }
                    else {
                        continue;
                    }
                }
                k = i+1; // counter for the chi-square calculation
            }

        
            // Calculate the chi-square
            
            chiquadro = 0; // Initialize the variable
            
            // Calculation
            for(r=0; r<=k; r++){
                
                // it does not consider values next to zero
                if(conf[r][2] <= 0.001){
                    chiquadro = chiquadro + 0;
                }
            
                else{
                    chiquadro = chiquadro + (pow(conf[r][1] - conf[r][2], 2) )/ conf[r][2];
                }
            }
        
        
        // Calculate the coefficient of determination R2
        
            // Average of the observed data
        
            y_med = 0; // Initialize the variable
            somma = 0; // Initialize the variable
            
            // Calculation
            for(r=0; r<=k; r++){
                somma = somma + conf[r][1];
            }
            y_med = somma/k;
            
            // Calculation of ESS (needed only for the method below commented)
            
            ESS = 0; // Initialize the variable
            
            // Calculation
            for(r=0; r<=k; r++){
                ESS = ESS + pow(conf[r][2] - y_med, 2);
            }
        
            // Calculation of TSS
        
            TSS = 0; // Initialize the variable
            
            // Calculation
            for(r=0; r<=k; r++){
                TSS = TSS + pow((conf[r][1] - y_med), 2);
            }
        
            // Calulation of RSS
        
            RSS = 0; // Initialize the variable
            
            //Calculation
            for(r=0; r<=k; r++){
                RSS = RSS + pow((conf[r][1] - conf[r][2]), 2);
            }
        
            // Calculation of R2
        
            R2 = 1 - (RSS/TSS);
        
            // Calculation of R2 (alternative method) --> remove comments if you need it
        
            // R2 = (ESS/TSS);

            if (R2 <= 0 || R2 > 1){
                R2 = 0;
            }

            else {
                R2 = 1 - (RSS/TSS);
            }
        
        
            // Storage of the h value (filename), chi-square, R2 and average distance calculated into the file input/.validator/stored_comparisons.txt
        
            fprintf(stored_comparisons, "%d\t%lf\t%lf\n", h, chiquadro, R2);
            
            // Assignes the values to storage_array.
            
            storage_array[h][0] = h;
            storage_array[h][1] = chiquadro;
            storage_array[h][2] = R2;
        
        } // closes the for cycle for a single acquisition
    
    // closes the storage file
    
    fclose(stored_comparisons);
    

    // The reordered array is saved on output/validation/multiple_comparison.txt
    
    
    FILE *multcomp;
        multcomp = fopen("./output/validation/multiple_comparison.txt","w");
    
        // Report the status of the file into the logfile
        if (multcomp == 0){
            system(" echo \"Error: validator_multiple() function. Failure opening file  /output/validation/multiple_comparison.txt\" >> logfile.log ");
        }
        else if (multcomp !=0){
            system(" echo \"validator_multiple() function. File  /output/validation/multiple_comparison.txt succesfully created\" >> logfile.log ");
        }
    
    
        fprintf(multcomp, "%s", "\n\n\t VALIDATION REPORT: \n\n\n");
        fprintf(multcomp, "%s", "h-file\tChi-sq\tR-sq\n");
    
    
    // This cycle orders in ascending order by chi-squared values the values calculated in the previous cycles.
    
    for (i=1; i<col_max+1; i++){
        
        min=i;
        
        for (j=i+1; j<=col_max; j++){
            
            if(storage_array[j][1] < storage_array[min][1]){
                
                min=j;
            }
        }
                
        // Rewrite h in the right position
        temp_h = storage_array[min][0];
        storage_array[min][0] = storage_array[i][0];
        storage_array[i][0] = temp_h;
                
        // Rewrite chi-square in the right position
        temp_chiq = storage_array[min][1];
        storage_array[min][1] = storage_array[i][1];
        storage_array[i][1] = temp_chiq;
            
        // Rewrite R2 in the right position
        temp_R2 = storage_array[min][2];
        storage_array[min][2] = storage_array[i][2];
        storage_array[i][2] = temp_R2;
        
        fprintf(multcomp, "%.0lf\t%lf\t%lf\n", storage_array[i][0], storage_array[i][1], storage_array[i][2]);
    }
    
        fprintf(multcomp, "%s", "\n\n\n  Created by Luca Rossini \n  Universita' degli Studi della Tuscia, Viterbo\n\n\n");
    fclose(multcomp);
    
    
    printf("%s", "\n\n  Please check 'output/validation/multiple_comparison.txt' to see your results\n");
    
    return;
}
