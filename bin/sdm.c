
/* Source for fitting life tables with Sharpe and De Michele development rate function.
 Tool included in "fittasso".
 
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


void SDM(void) {
    
    // Statement for the logfile
    
    system(" echo \"SDM() function started \" >> logfile.log ");
    
 
    //          ** Variables declaration **

     // char variables
     char statSDM;
     
     // Parameter limitations
     double lowA=0, upA=0, lowB=0, upB=0, lowC=0, upC=0, lowD=0, upD=0, lowE=0, upE=0, lowF=0, upF=0;
     
     // Sharpe and De Michele function
    double A=0, B=0, C=0, D=0, E=0, F=0, Ar=0, Br=0, Cr=0, Dr=0, Er=0, Fr=0, eA=0, eB=0, eC=0, eD=0, eE=0, eF=0, bndf=0, T_opt_SDM=0, Rate_optSDM=0;
     
     // chi-squared, R-squared, AIC, BIC
     int r=0, r_max=0, r_m=0, cont=0, ch=0, scan=0, cont_chi=0;
     double RSS=0, TSS=0, bchi2=0, AIC=0, BIC=0, R2=0, valut=0, y_med=0, R2_adj=0, somma=0;
     
     // array
    double obs[500][3]={{0}}, tax[500][4]={{0}};
     
     
     
     // Body of SDM()
    
   
    // Draw plot 1 (right plot) - it hosts the best fit function
                
    TGraphErrors *graph = new TGraphErrors("./input/LifeTablesRates.txt","%lg %lg %lg %lg");
    
    
    // Fitting operations: definition of the Sharpe and De Michele function
                
    TF1 *y = new TF1("y"," (x*exp([0]-([1]/x)))/(1+exp([2]-([3]/x)) + exp([4]-([5]/x)))");
    
                
    //  Assignment of the parameter names
                
    y->SetParName(0, "A");
    y->SetParName(1, "B");
    y->SetParName(2, "C");
    y->SetParName(3, "D");
    y->SetParName(4, "E");
    y->SetParName(5, "F");
                
    // Asks the initial value for A
                
    printf("%s", "\n  Set initial value for 'A':\n\n");
    clear();
    scanf("%lf", &A);
                
    // Asks the initial value for B
                
    printf("%s", "\n  Set initial value for 'B':\n\n");
    clear();
    scanf("%lf", &B);
                
    // Asks the initial value for C
                
    printf("%s", "\n  Set initial value for 'C':\n\n");
    clear();
    scanf("%lf", &C);
                
    // Asks the initial value for D
                
    printf("%s", "\n  Set initial value for 'D':\n\n");
    clear();
    scanf("%lf", &D);
                
    // Asks the initial value for E
                
    printf("%s", "\n  Set initial value for 'E':\n\n");
    clear();
    scanf("%lf", &E);
                
    // Asks the initial value for F
                
    printf("%s", "\n  Set initial value for 'F':\n\n");
    clear();
    scanf("%lf", &F);
                
    // Absorbs the parameters set above
                
    y->SetParameters(A,B,C,D,E,F);
                

    // It limits the parameters in a custom range if needed
                
    printf("%s", "\n  Do you need to limit parameters? y/n \n\n");
    clear();
    scanf("%c", &statSDM);
                
    if (statSDM == 'y'){
                    
        // limits on A
                    
        printf("%s", "\n  Insert the lower value for the parameter 'A': \n\n");
        clear();
        scanf("%lf", &lowA);
                    
        printf("%s", "\n  Insert the upper value for the parameter 'A': \n\n");
        clear();
        scanf("%lf", &upA);
                    
        y->SetParLimits(0,lowA,upA);
                    
        // limits on B
                    
        printf("%s", "\n  Insert the lower value for the parameter 'B': \n\n");
        clear();
        scanf("%lf", &lowB);
                    
        printf("%s", "\n  Insert the upper value for the parameter 'B': \n\n");
        clear();
        scanf("%lf", &upB);
                    
        y->SetParLimits(1,lowB,upB);
                    
        // limits on C
                    
        printf("%s", "\n  Insert the lower value for the parameter 'C': \n\n");
        clear();
        scanf("%lf", &lowC);
                    
        printf("%s", "\n  Insert the upper value for the parameter 'C': \n\n");
        clear();
        scanf("%lf", &upC);
            
        y->SetParLimits(2,lowC,upC);
                    
        // limits on D
                    
        printf("%s", "\n  Insert the lower value for the parameter 'D': \n\n");
        clear();
        scanf("%lf", &lowD);
                    
        printf("%s", "\n  Insert the upper value for the parameter 'D': \n\n");
        clear();
        scanf("%lf", &upD);
                    
        y->SetParLimits(3,lowD,upD);
                    
        // limits on E
                    
        printf("%s", "\n  Insert the lower value for the parameter 'E': \n\n");
        clear();
        scanf("%lf", &lowE);
                    
        printf("%s", "\n  Insert the upper value for the parameter 'E': \n\n");
        clear();
        scanf("%lf", &upE);
                    
        y->SetParLimits(4,lowE,upE);
                    
        // limits on F
                    
        printf("%s", "\n  Insert the lower value for the parameter 'F': \n\n");
        clear();
        scanf("%lf", &lowF);
                
        printf("%s", "\n  Insert the upper value for the parameter 'F': \n\n");
        clear();
        scanf("%lf", &upF);
                    
        y->SetParLimits(5,lowF,upF);
    }
                
    else if (statSDM == 'n'){
        goto fitsharpedemichele;
    }
                
                
fitsharpedemichele: // Here the function continues if no limitations are required for the parameters
                
    // Fitting the experimental data with Sharpe and De Michele function
                
    graph->Fit("y", "Q", "S"); // "Q" toglie le cose dallo schermo
                
                
    // Print the results on the shell
                
    Ar = y->GetParameter(0); // A
    eA = y->GetParError(0);  // A error
    Br = y->GetParameter(1); // B
    eB = y->GetParError(1);  // B error
    Cr = y->GetParameter(2); // C
    eC = y->GetParError(2);  // C error
    Dr = y->GetParameter(3); // D
    eD = y->GetParError(3);  // D error
    Er = y->GetParameter(4); // E
    eE = y->GetParError(4);  // E error
    Fr = y->GetParameter(5); // F
    eF = y->GetParError(5);  // F error
    bndf = y->GetNDF(); // number of degrees of freedom
            
    
    // Calculation of the chi-squared
                
    // Absorbs the experimental life tables
                
    FILE *observed;
        observed = fopen("./input/LifeTablesRates.txt", "r");
        
        // Report the status of the file into the logfile
        if (observed == 0){
            system(" echo \"Error: sdm() function. Failure opening file input/LifeTablesRates.txt \" >> logfile.log ");
        }
        else if (observed != 0){
            system(" echo \"sdm() function. File input/LifeTablesRates.txt succesfully opened\" >> logfile.log ");
        }

        // Scan the content
        scan=0;
                
        for(r=0; scan != EOF; r++){
            scan = fscanf(observed, "%lf%lf%lf%lf", &tax[r][0], &tax[r][1], &tax[r][2], &tax[r][3]);
            cont_chi = r;
        }
    fclose(observed);
                
    // Rivaluta la funzione con i parametri stimati
                
    TF1 *y1 = new TF1("y1","(x*exp([0]-([1]/x)))/(1+exp([2]-([3]/x)) + exp([4]-([5]/x)))"); // qui si definisce la Sharpe and De Michele con i parametri stimati
    y1->SetParName(0, "Ar");
    y1->SetParName(1, "Br");
    y1->SetParName(2, "Cr");
    y1->SetParName(3, "Dr");
    y1->SetParName(4, "Er");
    y1->SetParName(5, "Fr");
    y1->SetParameters(Ar, Br, Cr, Dr, Er, Fr);
                
    // Calculates the chi-squared
                
    for(r=0; r<=cont_chi; r++){
        valut = y1->Eval(tax[r][0]);
                    
        if(tax[r][1] == 0){
            bchi2 = bchi2 + 0;
        }
                    
        else{
            bchi2 = bchi2 + (pow(valut - tax[r][1], 2) )/ tax[r][1];
        }
    }
             
    
    // Calculation of the coordinates of the Sharpe and De Michele maximum peak (optimal temperature and optimal rate)
    
    T_opt_SDM = y1->GetMaximumX();
    Rate_optSDM = y1->GetMaximum();
    
                
    // Calculation of the R-squared (coefficient of determination)
                
    // Count of the rules on LifeTablesRate.txt
                
    FILE *datacount;
        datacount = fopen("./input/LifeTablesRates.txt", "r");
        
        // Report the status of the file into the logfile
        if (datacount == 0){
            system(" echo \"Error: sdm() function. Failure opening file input/LifeTablesRates.txt \" >> logfile.log ");
        }
        else if (datacount != 0){
            system(" echo \"sdm() function. File input/LifeTablesRates.txt succesfully opened\" >> logfile.log ");
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
            system(" echo \"Error: sdm() function. Failure opening file input/LifeTablesRates.txt \" >> logfile.log ");
        }
        else if (datas != 0){
            system(" echo \"sdm() function. File input/LifeTablesRates.txt succesfully opened\" >> logfile.log ");
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
        RSS = RSS + pow(obs[r][1] - ( (obs[r][0] * exp(Ar - (Br / obs[r][0])))/(1+exp(Cr - (Dr / obs[r][0])) + exp(Er - (Fr / obs[r][0]))) ), 2);
    }
                
    // Calculation of R2
                
    R2 = 1 - (RSS/TSS);
                
    // Calculation of R2 adjusted
                
    R2_adj = 1 - (1-R2) * (r_max)/(r_max - 6);
    
    
    // Calculation of the Akaike Information Criterion AIC
    
    AIC = (6 * 2) - 2 * log((RSS/r_m));
    
    
    // Calculation of the Bayesian Information Criterion BIC
    
    BIC = 6 * log(r_m) - 2 * log((RSS/r_m));
        
                
    // Print the results on the shell
                
    printf("%s", "\n  FIT RESULTS:\n\n");
    printf("%s", "   **********************************************************\n\n");
    printf("%s\n", "\t Best fit parameters: \n");
    printf("%s %.4e %s %.4e\n", "\t A = ", Ar, " +/- ", eA);
    printf("%s %.4e %s %.4e\n", "\t B = ", Br, " +/- ", eB);
    printf("%s %.4e %s %.4e\n", "\t C = ", Cr, " +/- ", eC);
    printf("%s %.4e %s %.4e\n", "\t D = ", Dr, " +/- ", eD);
    printf("%s %.4e %s %.4e\n", "\t E = ", Er, " +/- ", eE);
    printf("%s %.4e %s %.4e\n\n", "\t F = ", Fr, " +/- ", eF);
    printf("%s %.6f\n\n", "\t ChiSquared = ", bchi2);
    printf("%s %.6f\n", "\t Akaike Information Criterion (AIC) = ", AIC);
    printf("%s %.6f\n\n", "\t Bayesian Information Criterion (BIC) = ", BIC);
    printf("%s %.3f\n", "\t Coefficient of determination (R^2) = ", R2);
    printf("%s %.3f\n\n", "\t Adjusted coeff. of determination (R^2_adj) = ", R2_adj);
    printf("%s %.0f\n\n\n", "\t Number of degrees of freedom = ", bndf);
    printf("%s\n", "\t Optimal temperature:\n");
    printf("%s %4f\n", "\t T_opt = ", T_opt_SDM);
    printf("%s\n", "\n\t Optimal rate value R[T_opt]:\n");
    printf("%s %4f\n\n", "\t R[T_opt] = ", Rate_optSDM);
    printf("%s\n", "   **********************************************************\n\n");

                
    // Export the parameters on 'SDMratepar.txt'
                
    FILE *fp;
        fp = fopen("./output/DevelopRates/SDMratepar.txt","w");
    
        // Report the status of the file into the logfile
        if (fp == 0){
            system(" echo \"Error: sdm() function. Failure opening file output/DevelopRates/SDMratepar.txt \" >> logfile.log ");
        }
        else if (fp != 0){
            system(" echo \"sdm() function. File output/DevelopRates/SDMratepar.txt succesfully opened\" >> logfile.log ");
        }
            
        // Print the content
        fprintf(fp, "%s", "\n\n         SharpeDeMichele FIT FUNCTION: fit with Sharpe and De Michele development rate function R[T] = T*exp([A]-([B]/T)))/(1+exp([C]-([D]/T)) + exp([E]-([F]/T)) \n \n\n");
                
        fprintf(fp, "%s %.1e\n", "Initial value setted for A = ",A);
        fprintf(fp, "%s %.1e\n", "Initial value setted for B = ",B);
        fprintf(fp, "%s %.1e\n", "Initial value setted for C = ",C);
        fprintf(fp, "%s %.1e\n", "Initial value setted for D = ",D);
        fprintf(fp, "%s %.1e\n", "Initial value setted for E = ",E);
        fprintf(fp, "%s %.1e\n\n", "Initial value setted for F = ",F);
                
        fprintf(fp, "%s", "\n  FIT RESULTS:\n\n");
        fprintf(fp, "%s", "\t **********************************************************\n\n" );
        fprintf(fp, "%s\n", "\t    Best fit parameters: \n");
        fprintf(fp, "%s %.4e %s %.4e\n", "\t    A = ", Ar, " +/- ", eA);
        fprintf(fp, "%s %.4e %s %.4e\n", "\t    B = ", Br, " +/- ", eB);
        fprintf(fp, "%s %.4e %s %.4e\n", "\t    C = ", Cr, " +/- ", eC);
        fprintf(fp, "%s %.4e %s %.4e\n", "\t    D = ", Dr, " +/- ", eD);
        fprintf(fp, "%s %.4e %s %.4e\n", "\t    E = ", Er, " +/- ", eE);
        fprintf(fp, "%s %.4e %s %.4e\n\n", "\t    F = ", Fr, " +/- ", eF);
                
        fprintf(fp, "%s %.6f\n\n", "\t    ChiSquared = ", bchi2);
        fprintf(fp, "%s %.6f\n", "\t    Akaike Information Criterion (AIC) = ", AIC);
        fprintf(fp, "%s %.6f\n\n", "\t    Bayesian Information Criterion (BIC) = ", BIC);
        fprintf(fp, "%s %.3f\n", "\t    Coefficient of determination (R^2) = ", R2);
        fprintf(fp, "%s %.3f\n\n", "\t    Adjusted coeff. of determination (R^2_adj) = ", R2_adj);
        fprintf(fp, "%s %.0f\n\n", "\t    Number of degrees of freedom = ", bndf);
        fprintf(fp, "%s", "\n\t    Optimal temperature:\n\n");
        fprintf(fp, "%s %f\n", "\t    T_opt =\t", T_opt_SDM);
        fprintf(fp, "%s", "\n\t    Optimal rate value R[T_opt]:\n\n");
        fprintf(fp, "%s %f\n\n", "\t    R[T_opt] =\t", Rate_optSDM);
        fprintf(fp, "%s", "\t **********************************************************\n\n");
                
        fprintf(fp, "%s", "\n\n  Created by Luca Rossini \n\n  Universita' degli Studi della Tuscia, Viterbo\n\n\n\n");
    fclose(fp);
                
                
    // Export the parameters for the simulator: the folder .RatePar-simulator is hidden!
    
    FILE *fs;
        fs = fopen("./input/.RatePar-simulator/SDMratepar.txt", "w");
    
        // Report the status of the file into the logfile
        if (fs == 0){
            system(" echo \"Error: sdm() function. Failure opening file input/.RatePar-simulator/SDMratepar.txt \" >> logfile.log ");
        }
        else if (fs != 0){
            system(" echo \"sdm() function. File input/.RatePar-simulator/SDMratepar.txt succesfully opened\" >> logfile.log ");
        }
        
        // Print the content
        fprintf(fs, "%f\t%f\n", Ar, eA);
        fprintf(fs, "%f\t%f\n", Br, eB);
        fprintf(fs, "%f\t%f\n", Cr, eC);
        fprintf(fs, "%f\t%f\n", Dr, eD);
        fprintf(fs, "%f\t%f\n", Er, eE);
        fprintf(fs, "%f\t%f\n", Fr, eF);
    fclose(fs);
    
    // Recalling the python part of the program to manage graphics
        
    system("cd bin/ ; python3 -c 'import graphics; graphics.grafico_sdm()' ; rm -rf __pycache__ ; cd ..");
    
}
