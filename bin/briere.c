
/* Source for fitting life tables with Briére development rate function. Tool included
 in "fittasso".
 
 Created by Luca Rossini on 25/09/2018
 email: luca.rossini@unitus.it
 last update 30/07/2020 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "headers-menu.h"
#include "support.h"
#include "TGraphErrors.h"
#include "TF1.h"


void briere(void) {
    
    // Statement for the logfile
    
    system(" echo \"briere() function started \" >> logfile.log ");
    
    //          ** Variables declaration **

    // char variables
    char statBriere;
    
    // Parameter limitations
    double lowa=0, upa=0, lowT0=0, upT0=0, lowTL=0, upTL=0, lowm=0, upm=0;
    
    // Briere function + max
    double a_=0, T_0=0, T_L=0, m=0, a_r=0, T_0r=0, T_Lr=0, mr=0, ea_=0, eT_0=0, eT_L=0, em=0, brndf=0, T_optB=0, eT_optB=0, Rate_optB=0, eRate_optB=0, eb1=0, eb2=0, eb3=0, eb4=0, eb5=0, ebb1=0, ebb2=0, ebb3=0;
    
    // chi-squared, R-squared, AIC, BIC
    int r=0, r_max=0, r_m=0, cont=0, ch=0, scan=0, cont_chi=0;
    double RSS=0, TSS=0, brchi2=0, AIC=0, BIC=0, R2=0, valut=0, y_med=0, R2_adj=0, somma=0;
    
    // array
    double obs[500][3]={{0}}, tax[500][4]={{0}};
    
    
    
    // Body of briere()
    
                
    // Draw plot 1 (right plot) - it hosts the best fit function
                
    TGraphErrors *graph = new TGraphErrors("./input/LifeTablesRates.txt","%lg %lg %lg %lg");
                
    
    // Fitting operations: definition of the Briere function
                
    TF1 *y = new TF1("y"," [0]*x*(x-[1])*pow(([2]-x), (1/[3]))");
    
                
    //  Assignment of the parameter names
                
    y->SetParName(0, "a_");
    y->SetParName(1, "T_0");
    y->SetParName(2, "T_L");
    y->SetParName(3, "m");
                
    // Asks the initial value for a
                
    printf("%s", "\n  Set initial value for 'a':\n\n");
    clear();
    scanf("%lf", &a_);
                
    // Asks the initial value for T_0
                
    printf("%s", "\n  Set initial value for 'T_L':\n\n");
    clear();
    scanf("%lf", &T_0);
                
    // Asks the initial value for T_L
                
    printf("%s", "\n  Set initial value for 'T_M':\n\n");
    clear();
    scanf("%lf", &T_L);
                
    // Asks the initial value for m
                
    printf("%s", "\n  Set initial value for 'm':\n\n");
    clear();
    scanf("%lf", &m);
                
    // Absorbs the parameters set above
                
    y->SetParameters(a_, T_0, T_L, m);
                
                
    // It limits the parameters in a custom range if needed
                
    printf("%s", "\n  Do you need to limit parameters? y/n \n\n");
    clear();
    scanf("%c", &statBriere);
                
    if (statBriere == 'y'){
                    
        // limits on a
                    
        printf("%s", "\n  Insert the lower value for the parameter 'a': \n\n");
        clear();
        scanf("%lf", &lowa);
                    
        printf("%s", "\n  Insert the upper value for the parameter 'a': \n\n");
        clear();
        scanf("%lf", &upa);
                    
        y->SetParLimits(0,lowa,upa);
                    
        // limits on T_0
                    
        printf("%s", "\n  Insert the lower value for the parameter 'T_0': \n\n");
        clear();
        scanf("%lf", &lowT0);
                    
        printf("%s", "\n  Insert the upper value for the parameter 'T_0': \n\n");
        clear();
        scanf("%lf", &upT0);
                
        y->SetParLimits(1,lowT0,upT0);
                    
        // limits on T_L
                
        printf("%s", "\n  Insert the lower value for the parameter 'T_L': \n\n");
        clear();
        scanf("%lf", &lowTL);
                    
        printf("%s", "\n  Insert the upper value for the parameter 'T_L': \n\n");
        clear();
        scanf("%lf", &upTL);
                    
        y->SetParLimits(2,lowTL,upTL);
                    
        // limits on m
                    
        printf("%s", "\n  Insert the lower value for the parameter 'm': \n\n");
        clear();
        scanf("%lf", &lowm);
                    
        printf("%s", "\n  Insert the upper value for the parameter 'm': \n\n");
        clear();
        scanf("%lf", &upm);
                    
        y->SetParLimits(3,lowm,upm);
                    
    }
                
    else if (statBriere == 'n'){
        goto fitbriere;
    }
                
                
fitbriere: // Here the function continues if no limitations are required for the parameters
                
    // Fitting the experimental data with Briere function
        
    graph->Fit("y", "Q", "S");

                
    // Print results and parameters on the shell
                
    a_r = y->GetParameter(0); // a
    ea_ = y->GetParError(0);  // a error
    T_0r = y->GetParameter(1); // T_0
    eT_0 = y->GetParError(1);  // T_0 error
    T_Lr = y->GetParameter(2); // T_L
    eT_L = y->GetParError(2);  // T_L error
    mr = y->GetParameter(3); // m
    em = y->GetParError(3);  // m error
    brndf = y->GetNDF(); // number of degrees of freedom

                
    // Calculation of the coordinates of the Briere maximum peak (optimal temperature and optimal rate)
                
    T_optB = (2 * mr * T_Lr + T_0r * (mr + 1) + sqrt( 4 * pow(mr,2) * pow(T_Lr,2) + pow(T_0r, 2)*pow((mr+1), 2) - 4 * mr * T_Lr* T_0r) )/(4 * mr + 2);
                
    Rate_optB = a_r * T_optB * (T_optB - T_0r ) * pow((T_Lr - T_optB), (mr));
            
    
    // Error of the optimal temperature
    
    ebb1 = pow(eT_0, 2) * pow( (mr + 1)/(4*mr + 2) + (1/(4*mr + 2)) * ((T_0r * pow((mr + 1), 2) - 2*mr * T_Lr)/(sqrt(4 * mr * mr * T_Lr * T_Lr + T_0r * T_0r * pow(mr+1, 2) - 4*mr * T_Lr * T_0r))) ,2);
                
    ebb2 = pow(eT_L, 2) * pow(mr/(2*mr +1) + (1/(4*mr + 2) * (4*mr*mr * T_Lr - 2*mr * T_Lr)/(sqrt(4*mr*mr * T_Lr*T_Lr + T_0r*T_0r * pow((mr+1), 2) - 4*mr * T_0r * T_Lr))) ,2);
                
    ebb3 = pow(em, 2) * pow(2*T_Lr * ((1/(4*mr + 2)) - ((4*mr)/(pow((4*mr + 2) ,2))) + (T_0r/((pow((4*mr + 2) ,2)))) * ((4*T_Lr*T_Lr * (mr - 2*mr*mr) - T_0r*T_0r * (mr+1) * (4*mr + 3) + T_Lr * T_Lr * (8*mr - 2) )/( (pow((4*mr + 2) ,2)) * sqrt(4*mr*mr * T_Lr*T_Lr + T_0r*T_0r * pow((mr + 1), 2) - 4*mr*T_0r * T_Lr) )) ) ,2);
            
    eT_optB = sqrt(ebb1 + ebb2 + ebb3);
    
        
    // Error of the optimal rate
        
    eb1 = pow(ea_ * T_optB * (T_optB - T_0r) * pow((T_Lr - T_optB), (1/mr)) ,2);
                
    eb2 = pow(eT_0 * a_r * T_optB * pow((T_Lr - T_optB), (1/mr)) ,2);
                
    eb3 = pow(eT_L/mr * a_r * T_optB * (T_optB - T_0r) * pow((T_Lr - T_optB), ((1/mr) - 1)) ,2);
                
    eb4 = pow(em/(mr * mr) * a_r * T_optB * log(T_Lr - T_optB) * (T_optB - T_0r) * pow((T_Lr - T_optB), (1/mr)), 2);
                
    eb5 = pow(eT_optB * a_r * pow((T_Lr - T_optB), (1/mr)) * (2*T_optB - T_0r - (T_optB * (T_optB - T_0r))/(mr * (T_Lr - T_optB))) ,2);
                
    eRate_optB = sqrt(eb1 + eb2 + eb3 + eb4 + eb5);
                
                
    // Calculation of the chi-squared
                
    // Absorbs the experimental life tables
                
    FILE *observed;
        observed = fopen("./input/LifeTablesRates.txt", "r");
                    
        // Report the status of the file into the logfile
        if (observed == 0){
            system(" echo \"Error: briere() function. Failure opening file input/LifeTablesRates.txt \" >> logfile.log ");
        }
        else if (observed != 0){
            system(" echo \"briere() function. File input/LifeTablesRates.txt succesfully opened\" >> logfile.log ");
        }
    
        //Scan the content
        scan=0;
                
        for(r=0; scan != EOF; r++){
                    
            scan = fscanf(observed, "%lf%lf%lf%lf", &tax[r][0], &tax[r][1], &tax[r][2], &tax[r][3]);
            cont_chi = r;
        }
                
    fclose(observed);
                
    // Evaluation of the function with the best fit parameters
                
    TF1 *y1 = new TF1("y1","[0]*x*(x-[1])*pow(([2]-x), (1/[3]))"); // qui si definisce la Briere con i parametri stimati
    y1->SetParName(0, "a_r");
    y1->SetParName(1, "T_0r");
    y1->SetParName(2, "T_Lr");
    y1->SetParName(3, "mr");
    y1->SetParameters(a_r, T_0r, T_Lr, mr);
                
    // Calculates the chi-squared
                
    for(r=0; r<=cont_chi; r++){
                    
        valut = y1->Eval(tax[r][0]);
                    
        if(tax[r][2] == 0){
            brchi2 = brchi2 + 0;
        }
                    
        else{
            brchi2 = brchi2 + (pow(valut - tax[r][1], 2) )/ tax[r][1];
        }
    }
                
    // Calculation of the R-squared (coefficient of determination)
                
    // Count of the rules on LifeTablesRate.txt
                
    FILE *datacount;
        datacount = fopen("./input/LifeTablesRates.txt", "r");
    
        // Report the status of the file into the logfile
        if (datacount == 0){
            system(" echo \"Error: briere() function. Failure opening file input/LifeTablesRates.txt \" >> logfile.log ");
        }
        else if (datacount != 0){
            system(" echo \"briere() function. File input/LifeTablesRates.txt succesfully opened\" >> logfile.log ");
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
        r_m = cont + 1;
                
    fclose(datacount);
                
    // Acquisition of the data to calculate R2
                
    FILE *datas;
     datas = fopen("./input/LifeTablesRates.txt", "r");
    
     // Report the status of the file into the logfile
        if (datas == 0){
            system(" echo \"Error: briere() function. Failure opening file input/LifeTablesRates.txt \" >> logfile.log ");
        }
        else if (datas != 0){
            system(" echo \"briere() function. File input/LifeTablesRates.txt succesfully opened\" >> logfile.log ");
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
        RSS = RSS + pow(obs[r][1] - (a_r * obs[r][0] *(obs[r][0] - T_0r) * pow((T_Lr - obs[r][0]), (1/mr)) ), 2);
    }
                
    // Calculation of R2
                
    R2 = 1 - (RSS/TSS);
                
    // Calculation of R2 adjusted
                
    R2_adj = 1 - (1-R2) * (r_max)/(r_max - 4);
    
    
    // Calculation of the Akaike Information Criterion AIC
    
    AIC = (4 * 2) - 2 * log((RSS/r_m));
    
    
    // Calculation of the Bayesian Information Criterion BIC
    
    BIC = 4 * log(r_m) - 2 * log((RSS/r_m));
    
    
    // Print the results on the shell
                
    printf("%s", "\n  FIT RESULTS:\n\n");
    printf("%s", "   **********************************************************\n\n");
    printf("%s\n", "\t Best fit parameters: \n");
    printf("%s %.4e %s %.4e\n", "\t a   = ", a_r, " +/- ", ea_);
    printf("%s %.4e %s %.4e\n", "\t T_0 = ", T_0r, " +/- ", eT_0);
    printf("%s %.4e %s %.4e\n", "\t T_L = ", T_Lr, " +/- ", eT_L);
    printf("%s %.4e %s %.4e\n\n", "\t m   = ", mr, " +/- ", em);
    printf("%s %.6f\n\n", "\t ChiSquared = ", brchi2);
    printf("%s %.6f\n", "\t Akaike Information Criterion (AIC) = ", AIC);
    printf("%s %.6f\n\n", "\t Bayesian Information Criterion (BIC) = ", BIC);
    printf("%s %.3f\n", "\t Coefficient of determination (R^2) = ", R2);
    printf("%s %.3f\n\n", "\t Adjusted coeff. of determination (R^2_adj) = ", R2_adj);
    printf("%s %.0f\n\n\n", "\t Number of degrees of freedom = ", brndf);
    printf("%s\n", "\t Optimal temperature value:\n");
    printf("%s %4f %s %4f\n", "\t T_opt = ", T_optB, " +/- ", eT_optB);
    printf("%s\n", "\n\t Optimal rate value R[T_opt]:\n");
    printf("%s %4f %s %4f\n\n", "\t R[T_opt] = ", Rate_optB, " +/- ", eRate_optB);
    printf("%s\n", "   **********************************************************\n\n");
                

    // Export the parameters on 'output/briratepar.txt'
                
    FILE *fp;
        fp = fopen("./output/DevelopRates/briratepar.txt","w");
    
        // Report the status of the file into the logfile
        if (fp == 0){
            system(" echo \"Error: briere() function. Failure opening file output/DevelopRates/briratepar.txt \" >> logfile.log ");
        }
        else if (fp != 0){
            system(" echo \"briere() function. File output/DevelopRates/briratepar.txt succesfully opened\" >> logfile.log ");
        }
     
        // Write the content
        fprintf(fp, "%s", "\n\n         Briere FIT FUNCTION: fit with Briere development rate function R[T] = [a]*T*(T-[T_0])*pow(([T_L]-T), (1/[m])) \n \n\n");
                
        fprintf(fp, "%s %.1e\n", "Initial value setted for a = ",a_);
        fprintf(fp, "%s %.1e\n", "Initial value setted for T_L = ",T_0);
        fprintf(fp, "%s %.1e\n", "Initial value setted for T_M = ",T_L);
        fprintf(fp, "%s %.1e\n\n", "Initial value setted for m = ",m);
                
        fprintf(fp, "%s", "\n  FIT RESULTS:\n\n");
        fprintf(fp, "%s", "\t **********************************************************\n\n" );
        fprintf(fp, "%s\n", "\t    Best fit parameters: \n");
        fprintf(fp, "%s %.4e %s %.4e\n", "\t    a =  ", a_r, " +/- ", ea_);
        fprintf(fp, "%s %.4e %s %.4e\n", "\t    T_L =", T_0r, " +/- ", eT_0);
        fprintf(fp, "%s %.4e %s %.4e\n", "\t    T_M =", T_Lr, " +/- ", eT_L);
        fprintf(fp, "%s %.4e %s %.4e\n\n", "\t    m =  ", mr, " +/- ", em);
                
        fprintf(fp, "%s %.6f\n\n", "\t    ChiSquared = ", brchi2);
        fprintf(fp, "%s %.6f\n", "\t    Akaike Information Criterion (AIC) = ", AIC);
        fprintf(fp, "%s %.6f\n\n", "\t    Bayesian Information Criterion (BIC) = ", BIC);
        fprintf(fp, "%s %.3f\n", "\t    Coefficient of determination (R^2) = ", R2);
        fprintf(fp, "%s %.3f\n\n", "\t    Adjusted coeff. of determination (R^2_adj) = ", R2_adj);
        fprintf(fp, "%s %.0f\n\n", "\t    Number of degrees of freedom = ", brndf);
                
        fprintf(fp, "%s", "\n\t    Optimal temperature:\n\n");
        fprintf(fp, "%s %4f %s %4f\n", "\t    T_opt =\t", T_optB, " +/- ", eT_optB);
        fprintf(fp, "%s", "\n\t    Optimal rate value R[T_opt]:\n\n");
        fprintf(fp, "%s %4f %s %4f\n\n", "\t    R[T_opt] =\t", Rate_optB, " +/- ", eRate_optB);
        fprintf(fp, "%s", "\t **********************************************************\n\n");
                
        fprintf(fp, "%s", "\n\n  Created by Luca Rossini \n\n  Universita' degli Studi della Tuscia, Viterbo\n\n\n\n");
    fclose(fp);
                
    
    // Export the parameters for the simulator: the folder .RatePar-simulator is hidden!
    
    FILE *fs;
        fs = fopen("./input/.RatePar-simulator/briratepar.txt", "w");
    
        // Report the status of the file into the logfile
        if (fs == 0){
            system(" echo \"Error: briere() function. Failure opening file input/.RatePar-simulator/briratepar.txt \" >> logfile.log ");
        }
        else if (fs != 0){
            system(" echo \"briere() function. File input/.RatePar-simulator/briratepar.txt succesfully opened\" >> logfile.log ");
        }
        
        // Write the content
        fprintf(fs, "%f\t%f\n", a_r, ea_);
        fprintf(fs, "%f\t%f\n", T_0r, eT_0);
        fprintf(fs, "%f\t%f\n", T_Lr, eT_L);
        fprintf(fs, "%f\t%f\n", mr, em);
        
    fclose(fs);
                
    // Recalling the python part of the program to manage graphics

    system("cd bin/ ; python3 -c 'import graphics; graphics.grafico_briere()' ; rm -rf __pycache__ ; cd ..");

}
