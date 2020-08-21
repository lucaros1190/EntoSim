
/* This file contains all the functions which print menu and other stuff on
 the linux shell
 
 Created by Luca Rossini on 27/07/2020
 email: luca.rossini@unitus.it
 last update 27/07/2020 */


#include <stdio.h>
#include <cstdlib>


// Print the header of "fittasso" on the shell

void stampa_intest(void){
    
    // Statement for the logfile
    
    system(" echo \"stampa_intest() function started \" >> logfile.log ");
    
    printf("%s", " \n\n \t\t ******************************************************* \n\n");
    printf("%s", "\t\t\t\t      Fittasso 5.0  \n\n");
    printf("%s", "\t\t\t    Fitting development rate functions \n\n");
    printf("%s", "\t\t      Universita' degli Studi della Tuscia, Viterbo \n\n");
    printf("%s", " \t\t ******************************************************* \n");
    
}


// Print the menu of "fittasso" on the shell

void stampa_menu(void){
    
    // Statement for the logfile
    
    system(" echo \"stampa_menu() function started \" >> logfile.log ");
    
    printf("%s", "\n\n\t Type the letter corresponding to the development rate function to use: \n\n");
    printf("%s", "\t      a     Fit with 'Logan' function\n");
    printf("%s", "\t      b     Fit with 'Sharpe e De Michele' function\n");
    printf("%s", "\t      c     Fit with 'Briere' function\n");
    printf("%s", "\t      d     Fit with 'Linear' function\n");
    printf("%s", "\t      e     Convert your times in rates\n");
    printf("%s", "\t      f     Draw your rate functions in a single chart\n");
    printf("%s", "\t      g     Go back to EntoSim menu\n\n");
    
}


// Print the header of "simulatore" on the shell

void stampa_intest_sim(void){
    
    // Statement for the logfile
    
    system(" echo \"stampa_intest_sim() function started \" >> logfile.log ");
    
    printf("%s", " \n\n \t\t ******************************************************* \n\n");
    printf("%s", " \t\t\t             Simulatore 5.1 \n\n");
    printf("%s", "\t\t\t      Simulate ectotherm populations \n\n");
    printf("%s", "\t\t      Universita' degli Studi della Tuscia, Viterbo \n\n");
    printf("%s", " \t\t ******************************************************* \n ");
        
}


// Print the menu of "simulatore" on the shell

void menu_sim(void){
    
    // Statement for the logfile
    
    system(" echo \"menu_sim() function started \" >> logfile.log ");
    
    printf("%s", "\n\n\t Type the letter corresponding to the model to use: \n\n");
    printf("%s", "\t      a     Manetsch Distributed Delay Model with R(t) \n");
    printf("%s", "\t      b     Manetsch Distributed Delay Model with Q(t) \n");
    printf("%s", "\t      c     Generalized Von Foerster Equation\n");
    printf("%s", "\t      d     Integro-diff Von Foerster Equation\n");
    printf("%s", "\t      e     Go back to EntoSim menu\n\n");
    
}


// Print the acknowledgements on the shell

void acknowledgements(void){
    
    // Statement for the logfile
    
    system(" echo \"acknowledgements() function started \" >> logfile.log ");
    
    printf("%s", "\n\n\t\t             Created by Luca Rossini \n\n");
    printf("%s", "\t\t   Universita' degli Studi della Tuscia, Viterbo \n\n");
    printf("%s", "\t\t              luca.rossini@unitus.it \n\n");
    printf("%s", " \t\t\t  \n\n\n ");

}


// Print the EntoSim header on the shell

void stampa_intest_entosim(void){
    
    // Statement for the logfile
    
    system(" echo \"stampa_intest_entosim() function started \" >> logfile.log ");
    
    printf("%s", " \n\n \t\t ******************************************************* \n\n");
    printf("%s", " \t\t\t\t      EntoSim 2.1 \n\n");
    printf("%s", " \t\t\t      Modelling ectotherm populations \n\n");
    printf("%s", "\t\t      Universita' degli Studi della Tuscia, Viterbo \n\n");
    printf("%s", " \t\t ******************************************************* \n\n\n");
           
    printf("%s", "EntoSim: estimate your rate function parameter, run your simulation and validate your data!\n");
    system("echo \"\n\t Welcome $(whoami)!! Today is $(date) \"");
    
}


// Print the EntoSim menu on the shell

void stampa_menu_entosim(void){
    
    // Statement for the logfile
    
    system(" echo \"stampa_menu_entosim() function started \" >> logfile.log ");
    
    printf("%s", "\n\n\t Type the name of the function to use: \n\n");
    printf("%s", "\t     1. 'fittasso'     Fit development rate functions\n");
    printf("%s", "\t     2. 'simulator'    Simulate ectotherm populations\n");
    printf("%s", "\t     3. 'validator'    Compare two or more data series\n");
    printf("%s", "\t     4. 'info'         Information and contacts\n");
    printf("%s", "\t     5. 'exit'         Quit\n\n");
    
}


// Print the header of "validator" on the shell

void stampa_intest_validator(void){
    
    // Statement for the logfile
    
    system(" echo \"stampa_intest_validator() function started \" >> logfile.log ");
    
    printf("%s", " \n\n \t\t ******************************************************* \n\n");
    printf("%s", " \t\t\t\t      Validator 2.0  \n\n");
    printf("%s", "\t\t\t\t  Comparing data series \n\n");
    printf("%s", "\t\t      Universita' degli Studi della Tuscia, Viterbo \n\n");
    printf("%s", " \t\t ******************************************************* \n");
    
}


// Print the menu of "validator" on the shell

void menu_validator(void){
    
    // Statement for the logfile
    
    system(" echo \"menu_validator() function started \" >> logfile.log ");
    
    printf("%s", "\n\n\t Please type the letter corresponding to the operation needed: \n\n");
    printf("%s", "\t      a     Single comparison - Two data series \n");
    printf("%s", "\t      b     Multiple comparison - More data series \n");
    printf("%s", "\t      c     Go back to EntoSim menu\n\n");
    
}


// Print the information if "info" is typed in EntoSim menu

void info(void){
    
    printf("%s", "\n\n\t For more information please read: \n\n");
    
    printf("%s", "\t      https://doi.org/10.1016/j.ecoinf.2019.02.002 \n");
    printf("%s", "\t      https://doi.org/10.1016/j.ecolmodel.2019.108778 \n");
    printf("%s", "\t      https://doi.org/10.1007/s11587-020-00489-6 \n");
    printf("%s", "\t      https://doi.org/10.1016/j.cropro.2019.105024 \n");
    printf("%s", "\t      https://doi.org/10.1016/j.ecoinf.2020.101117 \n");
    
    printf("%s", "\n\n\t Contact us: \n\n");
    
    printf("%s", "\t      Luca Rossini:\n");
    printf("%s", "\t      Universita' degli Studi della Tuscia \n");
    printf("%s", "\t      luca.rossini@unitus.it \n\n");
    
    printf("%s", "\t      Silvia Turco:\n");
    printf("%s", "\t      Universita' degli Studi della Tuscia \n");
    printf("%s", "\t      silvia.turco@unitus.it \n");

}
