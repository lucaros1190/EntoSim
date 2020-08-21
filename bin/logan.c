
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


void logan(void) {
    
    // Statement for the logfile
    
    system(" echo \"logan() function started \" >> logfile.log ");


    //          ** Variables declaration **

    // char variables
    char statLogan;
    
    // Parameter limitations
    double lowpsi=0, uppsi=0, lowrho=0, uprho=0, lowTM=0, upTM=0, lowDeltaT=0, upDeltaT=0;
    
    // Logan function + max
    double psi=0, rho=0, Delta_T=0, T_m=0, psir=0, rhor=0, Delta_Tr=0, T_mr=0, epsi=0, erho=0, eDelta_T=0, eT_m=0, ndf=0, T_optL=0, eT_optL=0, Rate_optL=0, eRate_optL=0, el1=0, el2=0, el3=0, el4=0, el5=0, eTl1=0, eTl2=0, eTl31=0, eTl32=0, eTl33=0, eTl3=0;
    
    // chi-squared, R-squared, AIC, BIC
    int r=0, r_max=0, r_m=0, cont=0, ch=0, scan=0, cont_chi=0;
    double RSS=0, TSS=0, chi2=0, AIC=0, BIC=0, R2=0, valut=0, y_med=0, R2_adj=0, somma=0;
    
    // array
    double obs[500][3]={{0}}, tax[500][4]={{0}};

    
    
    // Body of logan()
    
            
    // Draw plot 1 (right plot) - it hosts the best fit function
            
    TGraphErrors *graph = new TGraphErrors("./input/LifeTablesRates.txt","%lg %lg %lg %lg");
    
            
    // Fitting operations: definition of the Logan function
            
    TF1 *y = new TF1("y","[0]*(exp([1]*x)-exp([1]*[2] - ([2]-x)/[3]))");
            
            
    //  Assignment of the parameter names
            
    y->SetParName(0, "psi");
    y->SetParName(1, "rho");
    y->SetParName(2, "T_m");
    y->SetParName(3, "Delta_T");
           
    // Asks the initial value for psi
            
    printf("%s", "\n  Set initial value for 'psi':\n\n");
    clear();
    scanf("%lf", &psi);
            
    // Asks the initial value for rho
            
    printf("%s", "\n  Set initial value for 'rho':\n\n");
    clear();
    scanf("%lf", &rho);
            
    // Asks the initial value for T_m
            
    printf("%s", "\n  Set initial value for 'T_m':\n\n");
    clear();
    scanf("%lf", &T_m);
            
    // Asks the initial value for Delta_T
            
    printf("%s", "\n  Set initial value for 'Delta_t':\n\n");
    clear();
    scanf("%lf", &Delta_T);

            
    // Absorbs the parameters set above
            
    y->SetParameters(psi,rho,Delta_T,T_m);
            
    
    // It limits the parameters in a custom range if needed
            
    printf("%s", "\n  Do you need to limit parameters? y/n \n\n");
    clear();
    scanf("%c", &statLogan);
            
    if (statLogan == 'y'){
            
        // limits on psi
                
        printf("%s", "\n  Insert the lower value for the parameter 'psi': \n\n");
        clear();
        scanf("%lf", &lowpsi);
                
        printf("%s", "\n  Insert the upper value for the parameter 'psi': \n\n");
        clear();
        scanf("%lf", &uppsi);
                
        y->SetParLimits(0,lowpsi,uppsi);
                
        // limits on rho
                
        printf("%s", "\n  Insert the lower value for the parameter 'rho': \n\n");
        clear();
        scanf("%lf", &lowrho);
                
        printf("%s", "\n  Insert the upper value for the parameter 'rho': \n\n");
        clear();
        scanf("%lf", &uprho);
                
        y->SetParLimits(1,lowrho,uprho);
                
        // limits on T_M
                
        printf("%s", "\n  Insert the lower value for the parameter 'T_M': \n\n");
        clear();
        scanf("%lf", &lowTM);
                
        printf("%s", "\n  Insert the upper value for the parameter 'T_M': \n\n");
        clear();
        scanf("%lf", &upTM);
                
        y->SetParLimits(2,lowTM,upTM);

        // limits on Delta_T
                
        printf("%s", "\n  Insert the lower value for the parameter 'Delta_T': \n\n");
        clear();
        scanf("%lf", &lowDeltaT);
                
        printf("%s", "\n  Insert the upper value for the parameter 'Delta_T': \n\n");
        clear();
        scanf("%lf", &upDeltaT);
                
        y->SetParLimits(3,lowDeltaT,upDeltaT);
            
    }
            
    else if (statLogan == 'n'){
        goto fitlogan;
    }
            
            
fitlogan: // Here the function continues if no limitations are required for the parameters

    // Fitting the experimental data with Logan function
            
    graph->Fit("y", "Q", "S");
    

    // Print results and parameters on the shell
            
    psir = y->GetParameter(0); // psi
    epsi = y->GetParError(0);  // psi error
    rhor = y->GetParameter(1); // rho
    erho = y->GetParError(1);  // rho error
    T_mr = y->GetParameter(2); // T_m
    eT_m = y->GetParError(2);  // T_m error
    Delta_Tr = y->GetParameter(3); // Delta_T
    eDelta_T = y->GetParError(3);  // Delta_T error
    ndf = y->GetNDF(); // number of degrees of freedom

            
    // Calculation of the chi-squared
            
    // Absorbs the experimental life tables
            
    FILE *observed;
        observed = fopen("./input/LifeTablesRates.txt", "r");
        
        // Report the status of the file into the logfile
        if (observed == 0){
            system(" echo \"Error: logan() function. Failure opening file input/LifeTablesRates.txt \" >> logfile.log ");
        }
        else if (observed != 0){
            system(" echo \"logan() function. File input/LifeTablesRates.txt succesfully opened\" >> logfile.log ");
        }
        
        // Scan the content
        scan=0;
            
        for(r=0; scan != EOF; r++){
            scan = fscanf(observed, "%lf%lf%lf%lf", &tax[r][0], &tax[r][1], &tax[r][2], &tax[r][3]);
            cont_chi = r;
        }
    fclose(observed);
           
    // Evaluation of the function with the best fit parameters
            
    TF1 *y1 = new TF1("y1","[0]*(exp([1]*x)-exp([1]*[2] - ([2]-x)/[3]))");
    y1->SetParName(0, "psir");
    y1->SetParName(1, "rhor");
    y1->SetParName(2, "T_mr");
    y1->SetParName(3, "Delta_Tr");
    y1->SetParameters(psir, rhor, T_mr, Delta_Tr);
            
    // Calculates the chi-squared
        
    for(r=0; r<=cont_chi; r++){
        valut = y1->Eval(tax[r][0]);
        
        if(tax[r][1] == 0){
            chi2 = chi2 + 0;
        }
                
        else{
            chi2 = chi2 + (pow(valut - tax[r][1], 2) )/ tax[r][1];
        }
    }
            
            
    // Calculation of the coordinates of the Logan maximum peak (optimal temperature and optimal rate)
            
    T_optL = T_mr - (Delta_Tr)/(rhor * Delta_Tr - 1) * (log(rhor)+log(Delta_Tr));
            
    Rate_optL = psir * (exp(rhor * T_optL) - exp(rhor * T_mr - (T_mr - T_optL)/Delta_Tr));
            
            
    // Error of the optimal temperature
            
    eTl1 = pow(eT_m, 2);
            
    eTl2 = (pow(eDelta_T, 2) * pow( (1/((rhor * Delta_Tr) - 1)) - ((log(rhor)+log(Delta_Tr))/(pow(((rhor * Delta_Tr) -1), 2))) ,2));
            
    eTl31 = (erho * (pow(Delta_Tr, 2))/rhor);
            
    eTl32 = (rhor-1) / pow((rhor * Delta_Tr -1), 2);
            
    eTl33 = (rhor * log(rhor) + rhor * log(Delta_Tr)) / pow(((rhor * Delta_Tr) - 1), 2);
            
    eTl3 =  pow(eTl31 * (eTl32 - eTl33), 2);
            
    eT_optL = sqrt(eTl1 + eTl2 + eTl3);
            
            
    // Error of the optimal rate
            
    el1 = pow(epsi * ( exp(rhor * T_optL) - exp(rhor * T_mr - (T_mr - T_optL)/Delta_Tr)) ,2);
            
    el2 = pow(erho * psir * (T_optL * exp(rhor * T_optL) - T_mr * exp(rhor * T_mr - (T_mr - T_optL)/Delta_Tr)) ,2);
            
    el3 = pow(eT_m * psir * (rhor - 1/Delta_Tr) * (exp(rhor * T_mr - (T_mr - T_optL)/Delta_Tr)) ,2);
            
    el4 = pow(eDelta_T * psir * (T_mr - T_optL)/pow(Delta_Tr, 2) * exp(rhor * T_mr - (T_mr-T_optL)/Delta_Tr), 2);
            
    el5 = pow(eT_optL * psir * (rhor * exp(rhor * T_optL) - 1/Delta_Tr * exp(rhor * T_mr - (T_mr - T_optL)/Delta_Tr)) ,2);
            
    eRate_optL = sqrt(el1 + el2 + el3 + el4 + el5);
            
            
    // Calculation of the R-squared (coefficient of determination)
            
    // Count of the rules on LifeTablesRate.txt
            
    FILE *datacount;
        datacount = fopen("./input/LifeTablesRates.txt", "r");
    
        // Report the status of the file into the logfile
        if (datacount == 0){
            system(" echo \"Error: logan() function. Failure opening file input/LifeTablesRates.txt \" >> logfile.log ");
        }
        else if (datacount != 0){
            system(" echo \"logan() function. File input/LifeTablesRates.txt succesfully opened\" >> logfile.log ");
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
            system(" echo \"Error: logan() function. Failure opening file input/LifeTablesRates.txt \" >> logfile.log ");
        }
        else if (datas != 0){
            system(" echo \"logan() function. File input/LifeTablesRates.txt succesfully opened\" >> logfile.log ");
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
        RSS = RSS + pow(obs[r][1] - (psir * (exp(rhor * obs[r][0])-exp(rhor * T_mr - (T_mr - obs[r][0])/Delta_Tr))), 2);
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
    printf("%s %.4e %s %.4e\n", "\t psi = ", psir, " +/- ", epsi);
    printf("%s %.4e %s %.4e\n", "\t rho = ", rhor, " +/- ", erho);
    printf("%s %f %s %f\n", "\t T_m = ", T_mr, " +/- ", eT_m);
    printf("%s %f %s %f\n\n", "\t Delta_T = ", Delta_Tr, " +/- ", eDelta_T);
    printf("%s %.6f\n\n", "\t ChiSquared = ", chi2);
    printf("%s %.6f\n", "\t Akaike Information Criterion (AIC) = ", AIC);
    printf("%s %.6f\n\n", "\t Bayesian Information Criterion (BIC) = ", BIC);
    printf("%s %.3f\n", "\t Coefficient of determination (R^2) = ", R2);
    printf("%s %.3f\n\n", "\t Adjusted coeff. of determination (R^2_adj) = ", R2_adj);
    printf("%s %.0f\n\n\n", "\t Number of degrees of freedom = ", ndf);
    printf("%s\n", "\t Optimal temperature value:\n");
    printf("%s %4f %s %4f\n", "\t T_opt = ", T_optL, " +/- ", eT_optL);
    printf("%s\n", "\n\t Optimal rate value R[T_opt]:\n");
    printf("%s %4f %s %4f\n\n", "\t R[T_opt] = ", Rate_optL, " +/- ", eRate_optL);
    printf("%s\n", "   **********************************************************\n");
            
            
    // Export the parameters on 'output/logratepar.txt'
            
    FILE *fp = fopen("./output/DevelopRates/logratepar.txt","w");
    
        // Report the status of the file into the logfile
        if (fp == 0){
            system(" echo \"Error: logan() function. Failure opening file output/DevelopRates/logratepar.txt \" >> logfile.log ");
        }
        else if (fp != 0){
            system(" echo \"logan() function. File output/DevelopRates/logratepar.txt succesfully opened\" >> logfile.log ");
        }
        
        // Write the content
        fprintf(fp, "%s", "\n\n         LOGAN FIT FUNCTION: fit with Logan development rate funcion \n R[T] = [psi]*(exp([rho]*T)-exp([rho]*[T_m] - ([T_m]-T)/[Delta_T]))\n\n");
            
        fprintf(fp, "%s %.1e\n", "Initial value setted for psi = ",psi);
        fprintf(fp, "%s %.1e\n", "Initial value setted for rho = ",rho);
        fprintf(fp, "%s %.1e\n", "Initial value setted for T_m = ",T_m);
        fprintf(fp, "%s %.1e\n\n", "Initial value setted for Delta_T = ",Delta_T);
            
        fprintf(fp, "%s", "\n  FIT RESULTS:\n\n");
        fprintf(fp, "%s", "\t **********************************************************\n\n" );
        fprintf(fp, "%s\n", "\t    Best fit parameters: \n");
        fprintf(fp, "%s %.4e %s %.4e\n", "\t    psi = ", psir, " +/- ", epsi);
        fprintf(fp, "%s %.4e %s %.4e\n", "\t    rho = ", rhor, " +/- ", erho);
        fprintf(fp, "%s %.4e %s %.4e\n", "\t    T_m = ", T_mr, " +/- ", eT_m);
        fprintf(fp, "%s %.4e %s %.4e\n\n", "\t    Delta_T = ", Delta_Tr, " +/- ", eDelta_T);
            
        fprintf(fp, "%s %.6f\n\n", "\t    ChiSquared = ", chi2);
        fprintf(fp, "%s %.6f\n", "\t    Akaike Information Criterion (AIC) = ", AIC);
        fprintf(fp, "%s %.6f\n\n", "\t    Bayesian Information Criterion (BIC) = ", BIC);
        fprintf(fp, "%s %.3f\n", "\t    Coefficient of determination (R^2) = ", R2);
        fprintf(fp, "%s %.3f\n\n", "\t    Adjusted coeff. of determination (R^2_adj) = ", R2_adj);
        fprintf(fp, "%s %.0f\n\n", "\t    Number of degrees of freedom = ", ndf);
            
        fprintf(fp, "%s", "\n\t    Optimal temperature:\n\n");
        fprintf(fp, "%s %f %s %f\n", "\t    T_opt =\t", T_optL, " +/- ", eT_optL);
        fprintf(fp, "%s", "\n\t    Optimal rate value R[T_opt]:\n\n");
        fprintf(fp, "%s %f %s %f\n\n", "\t    R[T_opt] =\t", Rate_optL, " +/- ", eRate_optL);
        fprintf(fp, "%s", "\t **********************************************************\n\n");
            
        fprintf(fp, "%s", "\n\n  Created by Luca Rossini \n\n  Universita' degli Studi della Tuscia, Viterbo\n\n\n\n\n");
    fclose(fp);
            
            
    // Export the parameters for the simulator: the folder .RatePar-simulator is hidden!
    
    FILE *fs = fopen("./input/.RatePar-simulator/logratepar.txt", "w");
    
        // Report the status of the file into the logfile
        if (fs == 0){
            system(" echo \"Error: logan() function. Failure opening file input/.RatePar-simulator/logratepar.txt \" >> logfile.log ");
        }
        else if (fs != 0){
            system(" echo \"logan() function. File input/.RatePar-simulator/logratepar.txt succesfully opened\" >> logfile.log ");
        }
        
        // Write the content
        fprintf(fs, "%f\t%f\n", psir, epsi);
        fprintf(fs, "%f\t%f\n", rhor, erho);
        fprintf(fs, "%f\t%f\n", T_mr, eT_m);
        fprintf(fs, "%f\t%f\n", Delta_Tr, eDelta_T);
    fclose(fs);
    
    // Recalling the python part of the program to manage graphics
    
    system("cd bin/ ; python3 -c 'import graphics; graphics.grafico_logan()' ; rm -rf __pycache__ ; cd ..");

}
