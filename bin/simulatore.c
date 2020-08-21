
/* Source of "simulatore" tool. This file manages the simulations with the models listed
  in "simulatore.h"
 
 Created by Luca Rossini on 19/09/2018
 email: luca.rossini@unitus.it
 last update 13/08/2020 */

#include <stdio.h>
#include <stdlib.h>
#include "support.h"
#include "entosim.h"
#include "sim-support.h"
#include "simulatore.h"
#include "headers-menu.h"


void simulatore(void){
    
    // Statement for the logfile
    
    system(" echo \"simulatore() function started \" >> logfile.log ");
    

//          ** Variables declaration **
    
    // char variables
    char a;
    
    
    
    // Body of simulatore()
    
    
    // Print the header on the shell
    
    stampa_intest_sim();
    clear();
    
inizio:
    
    // Print the menu and acquire the user's choice
    
    menu_sim();
    scanf("%c", &a);
    

    // Options available on the menu
    
    switch (a){
          
        case 'a': {
            simulatore1();
            goto fine;
        }
            
        case 'b': {
            simulatore2();
            goto fine;
        }
            
        case 'c': {
            simulatore3();
            goto fine;
        }
            
        case 'd':{
            simulatore4();
            goto fine;
        }
            
        case 'e':{
            goto fine;
        }
            
        default:{
            printf("%s", "\n\n Incorrect choice, please try again");
            goto inizio;
        }

    }
    
fine:
    entosim();

}
