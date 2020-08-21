
/* This is a support file for 'simulatore tools'. Contains additional functions.
 
 Created by Luca Rossini on 29/09/2018
 email: luca.rossini@unitus.it
 last update 10/08/2020 */

#include <stdio.h>
#include <stdlib.h>
#include "TF1.h"

// Calculate the linear rate function taking as input temperature from input/dailytemp.txt, angular coefficient and intercept from input/.RatePar-simulator/linratepar.txt

double lineare_insim(double T){
    
    // Statement for the logfile
    
    system(" echo \"lineare_insim() function started \" >> logfile.log ");
    
    double m=0, er_m=0, q=0, er_q=0, R=0, b=0;
    
    FILE *linratepar;
        linratepar = fopen("./input/.RatePar-simulator/linratepar.txt", "r");
    
        // Report the status of the file into the logfile
        if (linratepar == 0){
            system(" echo \"Error: lineare() function. Failure opening file input/.RatePar-simulator/linratepar.txt \" >> logfile.log ");
        }
        else if (linratepar != 0){
            system(" echo \"lineare() function. File input/.RatePar-simulator/linratepar.txt succesfully opened\" >> logfile.log ");
        }
        
        // Scan the content
        fscanf(linratepar, "%lf\t%lf\n", &m, &er_m);
        fscanf(linratepar,"%lf\t%lf", &q, &er_q);
    fclose(linratepar);
    
        
    TFormula *lin = new TFormula("lin", "[0]*x + [1]");
    lin->SetParName(0, "m");
    lin->SetParName(1, "q");
    lin->SetParameters(m,q);
    
    b = q/m;  // Control if the daily temperature is higher than the minimum for the species development
    
    if(T >= b){
        R = lin->Eval(T);
    }
    
    else{
        R = 0;
    }
    
    // Control that the rates are higher than zero. If not it considers rate = 0
    if(R >=0 ){
        goto fine_lin;
    }
    
    else if(R<=0){
        R=0;
    }
    
fine_lin:
    return(R);
}


// Calculate the Briere rate function taking as input temperature from input/dailytemp.txt, function's parameters (a, T_L, T_M, and m) from input/.RatePar-simulator/briratepar.txt

double briere_insim(double T){
    
    // Statement for the logfile
    
    system(" echo \"briere_insim() function started \" >> logfile.log ");
    
    double a=0, er_a=0, T_L=0, er_T_L=0, T_Mb=0, er_T_Mb=0, mb=0, er_mb=0, R=0;
    
    FILE *briratepar;
        briratepar = fopen("./input/.RatePar-simulator/briratepar.txt", "r");
    
        // Report the status of the file into the logfile
        if (briratepar == 0){
            system(" echo \"Error: briere() function. Failure opening file input/.RatePar-simulator/briratepar.txt \" >> logfile.log ");
        }
        else if (briratepar != 0){
            system(" echo \"briere() function. File input/.RatePar-simulator/briratepar.txt succesfully opened\" >> logfile.log ");
        }
        
        // Scan the content
        fscanf(briratepar, "%lf\t%lf\n", &a, &er_a);
        fscanf(briratepar, "%lf\t%lf\n", &T_L, &er_T_L);
        fscanf(briratepar, "%lf\t%lf\n", &T_Mb, &er_T_Mb);
        fscanf(briratepar, "%lf\t%lf\n", &mb, &er_mb);
    fclose(briratepar);
    
    
    TFormula *bri = new TFormula("bri", "([0]*x*(x-[1])*pow(([2]-x), (1/[3])))");
    bri->SetParName(0, "a");
    bri->SetParName(1, "T_L");
    bri->SetParName(2, "T_Mb");
    bri->SetParName(3, "mb");
    bri->SetParameters(a, T_L, T_Mb, mb);
    
    if(T >= T_L && T <= T_Mb){  // Control if the daily temperature is higher than the minimum for the species development and lower than the maximum
        R = bri->Eval(T);
    }
    
    else{
        R = 0;
    }
    
    // Control that the rates are higher than zero. If not it considers rate = 0
    if(R >=0 ){
        goto fine_briere;
    }
    
    else if(R<=0){
        R=0;
    }
    
fine_briere:
    return(R);
}


// Calculate the Logan rate function taking as input temperature from input/dailytemp.txt, function's parameters (psi, rho, T_Ml, and delta_T) from input/.RatePar-simulator/logratepar.txt

double logan_insim(double T){
    
    // Statement for the logfile
    
    system(" echo \"logan_insim() function started \" >> logfile.log ");
    
    double R=0, psi=0, epsi=0, rho=0, erho=0, T_Ml=0, eT_Ml=0, delta_T=0, edelta_T=0;
    
    FILE *logratepar;
        logratepar = fopen("./input/.RatePar-simulator/logratepar.txt", "r");
        
        // Report the status of the file into the logfile
        if (logratepar == 0){
            system(" echo \"Error: logan() function. Failure opening file input/.RatePar-simulator/logratepar.txt \" >> logfile.log ");
        }
        else if (logratepar != 0){
            system(" echo \"logan() function. File input/.RatePar-simulator/logratepar.txt succesfully opened\" >> logfile.log ");
        }
        
        // Scan the content
        fscanf(logratepar, "%lf\t%lf\n", &psi, &epsi);
        fscanf(logratepar, "%lf\t%lf\n", &rho, &erho);
        fscanf(logratepar, "%lf\t%lf\n", &T_Ml, &eT_Ml);
        fscanf(logratepar, "%lf\t%lf\n", &delta_T, &edelta_T);
    fclose(logratepar);
    
    
    TFormula *log = new TFormula("log", "[0]*(exp([1]*x)-exp([1]*[2] - ([2]-x)/[3]))");
    log->SetParName(0, "psi");
    log->SetParName(1, "rho");
    log->SetParName(2, "T_Ml");
    log->SetParName(3, "Delta_T");
    log->SetParameters(psi, rho, T_Ml, delta_T);
    
    if(T <= T_Ml){ // Control if the daily temperature is higher than the minimum for the species development
        R = log->Eval(T);
    }
    
    else {
        R = 0;
    }
    
    // Control that the rates are higher than zero. If not it considers rate = 0
    if(R >=0 ){
        goto fine_logan;
    }
    
    else if(R<=0){
        R=0;
    }
    
fine_logan:
    return(R);
}
              

// Calculate the Sharpe and De Michele rate function taking as input temperature from input/dailytemp.txt, function's parameters (A, B, C, D, E, F) from input/.RatePar-simulator/SDMratepar.txt
                    
double sharpe_demichele_insim(double T){
    
    // Statement for the logfile
    
    system(" echo \"sharpe_demichele_insim() function started \" >> logfile.log ");
                        
    double R=0, A=0, eA=0, B=0, eB=0, C=0, eC=0, D=0, eD=0, E=0, eE=0, F=0, eF=0;
                        
    FILE *ShDeMratepar;
        ShDeMratepar = fopen("./input/.RatePar-simulator/SDMratepar.txt", "r");
        
        // Report the status of the file into the logfile
        if (ShDeMratepar == 0){
            system(" echo \"Error: sharpe_demichele() function. Failure opening file input/.RatePar-simulator/SDMratepar.txt \" >> logfile.log ");
        }
        else if (ShDeMratepar != 0){
            system(" echo \"sharpe_demichele() function. File input/.RatePar-simulator/SDMratepar.txt succesfully opened\" >> logfile.log ");
        }
        
        // Scan the content
        fscanf(ShDeMratepar, "%lf\t%lf\n", &A, &eA);
        fscanf(ShDeMratepar, "%lf\t%lf\n", &B, &eB);
        fscanf(ShDeMratepar, "%lf\t%lf\n", &C, &eC);
        fscanf(ShDeMratepar, "%lf\t%lf\n", &D, &eD);
        fscanf(ShDeMratepar, "%lf\t%lf\n", &E, &eE);
        fscanf(ShDeMratepar, "%lf\t%lf\n", &F, &eF);
    fclose(ShDeMratepar);
                        
                        
    TFormula *sdm = new TFormula("sdm", "(x*exp([0]-([1]/x)))/(1+exp([2]-([3]/x)) + exp([4]-([5]/x)))");
    sdm->SetParName(0, "A");
    sdm->SetParName(1, "B");
    sdm->SetParName(2, "C");
    sdm->SetParName(3, "D");
    sdm->SetParName(4, "E");
    sdm->SetParName(5, "F");
    sdm->SetParameters(A, B, C, D, E, F);
    
    R = sdm->Eval(T);
                        
    if(R >=0 ){// Control that the rates are higher than zero. If not it considers rate = 0
        goto fine_sdm;
    }
                        
    else if(R<=0){
        R=0;
    }
                        
fine_sdm:
    return(R);
}


// This function delete and create the folder 'output/simresults'

void cleaner(void){
    
    // Statement for the logfile
    
    system(" echo \"cleaner() function started \" >> logfile.log ");
    
    int i, j;
    
   i = system("rm -rf ./output/simresults");
    if (i != 0){
        system(" echo \"Error: cleaner() function. Failure removing folder output/simresults \" >> logfile.log ");
    }
    
    else if (i==0){
        system(" echo \"cleaner() function. Folder output/simresults succesfully removed \" >> logfile.log ");
    }
    
   j = system("mkdir ./output/simresults");
    if (j != 0){
        system(" echo \"Error: cleaner() function. Failure creating folder output/simresults \" >> logfile.log ");
    }
    
    else if (j==0){
        system(" echo \"cleaner() function. Folder output/simresults succesfully created \" >> logfile.log ");
    }
}


// This function creates the standard file with the initial condition for the Generalised Von Foerster's equation and the Generalised Von Foerster equation Integro-differential

void InitialCondGVFE(int col_max){
    
    // Statement for the logfile
    
    system(" echo \"InitialCondGVFE() function started \" >> logfile.log ");
    
    int d;
    
    FILE *initprofile = fopen("./input/InitialCondition-GVFE.txt", "w");
        
        // Report the status of the file into the logfile
        if (initprofile == 0){
            system(" echo \"Error: InitialCondGVFE() function. Failure opening file input/InitialCondition-GVFE.txt \" >> logfile.log ");
        }
        else if (initprofile != 0){
            system(" echo \"InitialCondGVFE() function. File input/InitialCondition-GVFE.txt succesfully opened\" >> logfile.log ");
        }
        
        // Print the content
        fprintf(initprofile, "%s\t%s\n", "1", "100");

        for (d=2; d<=col_max; d++){
            fprintf(initprofile, "%d\t%s\n", d, "0");
        }
    fclose(initprofile);
}


// This function creates the standard file with the boundary condition for the Generalised Von Foerster's equation and the Generalised Von Foerster equation Integro-differential

void BoundaryCondGVFE(int d_max){
    
    // Statement for the logfile
    
    system(" echo \"BoundaryCondGVFE() function started \" >> logfile.log ");
    
    int d;
    
    FILE *initprofile = fopen("./input/BoundaryCondition-GVFE.txt", "w");
        
        // Report the status of the file into the logfile
        if (initprofile == 0){
            system(" echo \"Error: profilemaker() function. Failure opening file input/InitProfile.txt \" >> logfile.log ");
        }
        else if (initprofile != 0){
            system(" echo \"profilemaker() function. File input/InitProfile.txt succesfully opened\" >> logfile.log ");
        }
        
        // Print the content
            fprintf(initprofile, "%s\t%s\n", "1", "0");
            fprintf(initprofile, "%s\t%s\n", "2", "100");
        
            for (d=2; d<=d_max; d++){
                fprintf(initprofile, "%d\t%s\n", d+1, "0");
            }
    fclose(initprofile);
}


// This function creates the standard initial condition file for the DDM with Q(t) variables

void InitialCondDDMQ(int d_max){
    
    // Statement for the logfile
    
    system(" echo \"InitialCondDDMQ() function started \" >> logfile.log ");
    
    int d;
    
    FILE *monitoring = fopen("./input/InitialCondition-DDM-Q.txt", "w");
    
        // Report the status of the file into the logfile
        if (monitoring == 0){
            system(" echo \"Error: InitialCondDDMQ() function. Failure opening file input/InitialCondition-DDM-Q.txt \" >> logfile.log ");
        }
        else if (monitoring != 0){
            system(" echo \"InitialCondDDMQ() function. File input/InitialCondition-DDM-Q.txt succesfully opened\" >> logfile.log ");
        }
        
        // Print the content
        fprintf(monitoring, "%s\t%s\n", "1", "0");
        fprintf(monitoring, "%s\t%s\n", "2", "100");
    
        for (d=2; d<=d_max; d++){
            fprintf(monitoring, "%d\t%s\n", d+1, "0");
        }
    fclose(monitoring);
}


// This function creates the standard initial condition file for the DDM with R(t) variables

void InitialCondDDMR(int d_max){
    
    // Statement for the logfile
    
    system(" echo \"InitialCondDDMR() function started \" >> logfile.log ");
    
    int d;
    
    FILE *monitoring1 = fopen("./input/InitialCondition-DDM-R.txt", "w");
    
        // Report the status of the file into the logfile
        if (monitoring1 == 0){
            system(" echo \"Error: InitialCondDDMR() function. Failure opening file input/InitialCondition-DDM-R.txt \" >> logfile.log ");
        }
        else if (monitoring1 != 0){
            system(" echo \"InitialCondDDMR() function. File input/InitialCondition-DDM-R.txt succesfully opened\" >> logfile.log ");
        }
        
        // Print the content
        fprintf(monitoring1, "%s\t%s\n", "1", "0");
        fprintf(monitoring1, "%s\t%s\n", "2", "0");
        fprintf(monitoring1, "%s\t%s\n", "3", "100");
    
        for (d=4; d<=d_max; d++){
            fprintf(monitoring1, "%d\t%s\n", d, "0");
        }
    fclose(monitoring1);
}


// This function absorbs the fertility coefficients (lab estimated - no function)

double fertility(int h){
    
    // Statement for the logfile
    
    system(" echo \"fertility() function started \" >> logfile.log ");
    
    double fert[300][300]={{0}};
    double f=0;
    int i=0;
    
    if(i<h){
        FILE *fertility;
            fertility = fopen("./input/FertilityRates.txt", "r");
        
            // Report the status of the file into the logfile
            if (fertility == 0){
                system(" echo \"Error: fertility() function. Failure opening file input/fertilityrate.txt \" >> logfile.log ");
            }
            else if (fertility != 0){
                system(" echo \"fertility() function. File input/fertilityrate.txt succesfully opened\" >> logfile.log ");
            }
        
            // Print the content
            for(i=1; i<=h; i++){
                fscanf(fertility, "%lf%lf", &fert[i][0], &fert[i][1]);
            }
        fclose(fertility);
        f = fert[h][1];
    }
    
    else if(i>h){
        f=0;
    }
    
    return f;
}


// This function absorbs the mortality coefficients (lab estimated - no function)

double mortality(int h){
    
    // Statement for the logfile
    
    system(" echo \"mortality() function started \" >> logfile.log ");
    
    double mort[300][300]={{0}};
    double m=0;
    int i=0;
    
    if(i<h){
        FILE *mortality;
            mortality = fopen("./input/MortalityRates.txt", "r");
    
            // Report the status of the file into the logfile
            if (mortality == 0){
                system(" echo \"Error: mortality() function. Failure opening file input/mortalityrate.txt \" >> logfile.log ");
            }
            else if (mortality != 0){
                system(" echo \"mortality() function. File input/mortalityrate.txt succesfully opened\" >> logfile.log ");
            }
            
            // Print the content
            for(i=1; i<=h; i++){
                fscanf(mortality, "%lf%lf", &mort[i][0], &mort[i][1]);
            }
        fclose(mortality);
        m = mort[h][1];
    }
    
    else if(i>h){
        m=1;
    }
    
    return m;
}

