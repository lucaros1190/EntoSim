
/* Source for fitting life tables with Logan development rate function. Tool included
 in "fittasso".
 
 Created by Luca Rossini on 25/09/2018
 email: luca.rossini@unitus.it
 last update 29/07/2020 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "headers-menu.h"
#include "support.h"
#include "TGraphErrors.h"
#include "TF1.h"


void linear(void) {
    
    // Statement for the logfile
    
    system(" echo \"linear() function started \" >> logfile.log ");
    
    
    //          ** Variables declaration **

     // char variables
     char statLin;
     
     // Parameter limitations
     double lowq=0, upq=0, lowml=0, upml=0;
     
     // Linear function
    double ml=0, ql=0, mlr=0, eml=0, qlr=0, eql=0;
     
     // chi-squared, R-squared, AIC, BIC
     int r=0, r_max=0, r_m=0, cont=0, ch=0, scan=0, cont_chi=0;
     double RSS=0, TSS=0, chi2lin=0, ndflin=0, AIC=0, BIC=0, R2=0, valut=0, y_med=0, somma=0;
     
     // array
    double obs[500][3]={{0}}, tax[500][4]={{0}};

     
     
     // Body of linear()
    

    // Draw plot 1 (right plot) - it hosts the best fit function
    
    TGraphErrors *graph = new TGraphErrors("./input/LifeTablesRates.txt","%lg %lg %lg %lg");
    
                
    // Fitting operations: definition of the linear function
                
    TF1 *y = new TF1("y","([0]+[1]*x)");
                
    
    //  Assignment of the parameter names
        
    y->SetParName(0, "q");
    y->SetParName(1, "m");
                
    // Asks the initial value for m
                
    printf("%s", "\n  Set initial value for m:\n\n");
    clear();
    scanf("%lf", &ml);
                
    // Asks the initial value for q
                
    printf("%s", "\n  Set initial value for q:\n\n");
    clear();
    scanf("%lf", &ql);
    
                
    // Absorbs the parameters set above
                
    y->SetParameters(ql,ml);
                
    // It limits the parameters in a custom range if needed
                
    printf("%s", "\n  Do you need to limit parameters? y/n \n\n");
    clear();
    scanf("%c", &statLin);
                
    if (statLin == 'y'){
                    
        // limits on m
                    
        printf("%s", "\n  Insert the lower value for the parameter 'm': \n\n");
        clear();
        scanf("%lf", &lowml);
                    
        printf("%s", "\n  Insert the upper value for the parameter 'm': \n\n");
        clear();
        scanf("%lf", &upml);
                    
        y->SetParLimits(1,lowml,upml);
                    
        // limits on q
                    
        printf("%s", "\n  Insert the lower value for the parameter 'q': \n\n");
        clear();
        scanf("%lf", &lowq);
                    
        printf("%s", "\n  Insert the upper value for the parameter 'q': \n\n");
        clear();
        scanf("%lf", &upq);
                    
        y->SetParLimits(0,lowq,upq);
    }
                
    else if (statLin == 'n'){
        goto fitlineare;
    }
                
fitlineare: // Here the function continues if no limitations are required for the parameters
                
    // Fitting the experimental data with linear function
                
    graph->Fit("y", "Q", "S");
                
   
    // Print results and parameters on the shell
                
    mlr = y->GetParameter(1); // m
    eml = y->GetParError(1);  // m error
    qlr = y->GetParameter(0); // q
    eql = y->GetParError(0);  // q error
           
    ndflin = y->GetNDF(); // number of degrees of freedom
                
    // Calculation of the chi-squared
                
    // Absorbs the experimental life tables
                
    FILE *observed;
        observed = fopen("./input/LifeTablesRates.txt", "r");
    
        // Report the status of the file into the logfile
        if (observed == 0){
            system(" echo \"Error: linear() function. Failure opening file input/LifeTablesRates.txt \" >> logfile.log ");
        }
        else if (observed != 0){
            system(" echo \"linear() function. File input/LifeTablesRates.txt succesfully opened\" >> logfile.log ");
        }
    
        // Scan the content
        scan=0;
                
        for(r=0; scan != EOF; r++){
            scan = fscanf(observed, "%lf%lf%lf%lf", &tax[r][0], &tax[r][1], &tax[r][2], &tax[r][3]);
            cont_chi = r;
        }
                
    fclose(observed);
                
    // Evaluation of the function with the best fit parameters
                
    TF1 *y1 = new TF1("y1","([0]+[1]*x)");
    y1->SetParName(0, "qlr");
    y1->SetParName(1, "mlr");
    y1->SetParameters(qlr, mlr);
                
    // Calculates the chi-squared
                
    for(r=0; r<=cont_chi; r++){
                    
        valut = y1->Eval(tax[r][0]);
                    
        if(tax[r][2] == 0){
            chi2lin = chi2lin + 0;
        }
                    
        else{
            chi2lin = chi2lin + (pow(valut - tax[r][1], 2) )/ tax[r][1];
        }
    }
               
    
    // Calculation of the R-squared (coefficient of determination)
                
    // Count of the rules on LifeTablesRate.txt
                
    FILE *datacount;
        datacount = fopen("./input/LifeTablesRates.txt", "r");
            
        // Report the status of the file into the logfile
        if (datacount == 0){
            system(" echo \"Error: linear() function. Failure opening file input/LifeTablesRates.txt \" >> logfile.log ");
        }
        else if (datacount != 0){
            system(" echo \"linear() function. File input/LifeTablesRates.txt succesfully opened\" >> logfile.log ");
        }
            
        // Scan the content
        cont = 0;
    
        while (1){
            ch = fgetc(datacount);
            if (ch == '\n')
                ++cont;
                    
            if (ch == EOF)
                break;
        }
                
        r_max = cont ;
        r_m = r_max + 1;
              
    fclose(datacount);
                
    // Acquisition of the data to calculate R2
                
    FILE *datas;
        datas = fopen("./input/LifeTablesRates.txt", "r");
        
        // Report the status of the file into the logfile
        if (datas == 0){
            system(" echo \"Error: linear() function. Failure opening file input/LifeTablesRates.txt \" >> logfile.log ");
        }
        else if (datas != 0){
            system(" echo \"linear() function. File input/LifeTablesRates.txt succesfully opened\" >> logfile.log ");
        }
        
        // Scan the content
        for(r=0; r<=r_max; r++){
            fscanf(datas, "%lf%lf%lf%lf", &obs[r][0], &obs[r][1], &obs[r][2], &obs[r][3]);
        }
                
    fclose(datas);
                
    // Calculation of the average of the points y_med
                
    for(r=0; r<=r_max; r++){
        somma = somma + obs[r][1];
    }
    y_med = somma/r_m;
                
    // Calculation of TSS
                
    for(r=0; r<=r_max; r++){
        TSS = TSS + pow(obs[r][1] - y_med, 2);
    }
                
    // Calculation of RSS
                
    for(r=0; r<=r_max; r++){
        RSS = RSS + pow(obs[r][1] - (mlr*obs[r][0] + qlr), 2);
    }
                
    // Calculation of R2
                
    R2 = 1 - (RSS/TSS);
    
    // Calculation of the Akaike Information Criterion AIC
    
    AIC = (4 * 2) - 2 * log((RSS/r_m));
    
    
    // Calculation of the Bayesian Information Criterion BIC
    
    BIC = 4 * log(r_m) - 2 * log((RSS/r_m));
    
    
    // Print the results on the shell
                
    printf("%s", "\n  FIT RESULTS:\n\n");
    printf("%s", "   **********************************************************\n\n");
    printf("%s\n", "\t Best fit parameters: \n");
    printf("%s %f %s %f\n", "\t m = ", mlr, " +/- ", eml);
    printf("%s %f %s %f\n\n", "\t q = ", qlr, " +/- ", eql);
    printf("%s %.6f\n\n", "\t ChiSquared = ", chi2lin);
    printf("%s %.6f\n", "\t Akaike Information Criterion (AIC) = ", AIC);
    printf("%s %.6f\n\n", "\t Bayesian Information Criterion (BIC) = ", BIC);
    printf("%s %.3f\n", "\t Coefficient of determination (R^2) = ", R2);
    printf("%s %.0f\n\n", "\t Number of degrees of freedom = ", ndflin);
    printf("%s", "   **********************************************************\n\n");
                
    
    // Export the parameters on 'output/linratepar.txt'
                
    FILE *fp;
        fp = fopen("./output/DevelopRates/linratepar.txt","w");
           
        // Report the status of the file into the logfile
        if (fp == 0){
            system(" echo \"Error: linear() function. Failure opening file output/DevelopRates/linratepar.txt \" >> logfile.log ");
        }
        else if (fp != 0){
            system(" echo \"linear() function. File output/DevelopRates/linratepar.txt succesfully opened\" >> logfile.log ");
        }
        
        // Write the content
        fprintf(fp, "%s", "\n\n         LINEAR FIT FUNCTION: fit with linear development rate function R[T] = m*T+q\n \n\n");
                
        fprintf(fp, "%s %.1e\n", "Initial value setted for m = ",ml);
        fprintf(fp, "%s %.1e\n\n", "Initial value setted for q = ",ql);
                
        fprintf(fp, "%s", "\n  FIT RESULTS:\n\n");
        fprintf(fp, "%s", "\t **********************************************************\n\n" );
        fprintf(fp, "%s\n", "\t    Best fit parameters: \n");
        fprintf(fp, "%s %f %s %f\n", "\t    m =\t", mlr, "  +/-  ", eml);
        fprintf(fp, "%s %f %s %f\n\n", "\t    q =\t", qlr, "  +/-  ", eql);
        fprintf(fp, "%s %.6f\n\n", "\t    ChiSquared = ", chi2lin);
        fprintf(fp, "%s %.6f\n", "\t    Akaike Information Criterion (AIC) = ", AIC);
        fprintf(fp, "%s %.6f\n\n", "\t    Bayesian Information Criterion (BIC) = ", BIC);
        fprintf(fp, "%s %.3f\n", "\t    Coefficient of determination (R^2) = ", R2);
        fprintf(fp, "%s %.0f\n\n", "\t    Number of degrees of freedom = ", ndflin);
        fprintf(fp, "%s", "\t **********************************************************\n\n");
   
        fprintf(fp, "%s", "\n\n  Created by Luca Rossini \n\n  Universita' degli Studi della Tuscia, Viterbo\n\n\n");
    fclose(fp);
                
    // Export the parameters for the simulator: the folder .RatePar-simulator is hidden!
    
    FILE *fs;
        fs = fopen("./input/.RatePar-simulator/linratepar.txt", "w");
        
        // Report the status of the file into the logfile
        if (fs == 0){
            system(" echo \"Error: linear() function. Failure opening file input/.RatePar-simulator/linratepar.txt \" >> logfile.log ");
        }
        else if (fs != 0){
            system(" echo \"linear() function. File input/.RatePar-simulator/linratepar.txt succesfully opened\" >> logfile.log ");
        }
    
        // Print the content
        fprintf(fs, "%f\t%f\n", mlr, eml);
        fprintf(fs, "%f\t%f\n", qlr, eql);
    fclose(fs);
    
    // Recalling the python part of the program to manage graphics
        
    system("cd bin/ ; python3 -c 'import graphics; graphics.grafico_lineare()' ; rm -rf __pycache__ ; cd ..");

}
