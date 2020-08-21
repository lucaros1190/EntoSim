
/* This file contains the main() of EntoSim.

Created by Luca Rossini on 11/11/2018
email: luca.rossini@unitus.it
last update 17/08/2020 */


#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include "entosim.h"
#include "headers-menu.h"
#include "support.h"

int main(){
    
    // Statement for the logfile
    
    system(" echo \"entosim() function started \" >> logfile.log ");
    
    entosim();
    
    return 0;
    
}


void entosim(void){
    
    // Statement for the logfile
    
    system(" echo \"entosim() function started \" >> logfile.log ");

    //          ** Variables declaration **
    
    char a[10]={};
    
    
    
    // Body of entosim() - EntoSim

    
    // Print the header
    
    stampa_intest_entosim();

inizio:
    
    // Print the menu
    
    stampa_menu_entosim();

    // Acquisition of the user's choice

    scanf("%s", a);
    
    if (strcmp(a, "fittasso")==0){
        fittasso();
    }

    else if (strcmp(a, "simulator")==0){
       simulatore();
    }
    
    else if (strcmp(a, "validator")==0){
       validator();
    }
    
    else if (strcmp(a, "exit")==0){
        system("cp logfile.log logfilePrevSession.log");
        logfile();
        acknowledgements();
        return;
    }
    
    else if (strcmp(a, "info")==0){
        info();
        goto inizio;
    }

    else if (strcmp(a, "exit")!=0 && strcmp(a, "fittasso")!=0 && strcmp(a, "exit")!=0){
        printf("%s", "\n\n Incorrect choice, please try again");
		goto inizio;
    }
}
