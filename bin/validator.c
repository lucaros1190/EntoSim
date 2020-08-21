
/* Source of "validator" tool. This file contains the tools to compare with chi-square,
 R-square and average distance two data series. These data series can be a best fit
 function and experimental points, a simulation and a validation data series or just two
 data series.
 
 Created by Luca Rossini on 13/02/2019
 email: luca.rossini@unitus.it
 last update 04/08/2020 */


#include <stdio.h>
#include <cstdlib>
#include "validator-support.h"
#include "entosim.h"
#include "headers-menu.h"
#include "support.h"


void validator(void){
    
    // Statement for the logfile
    
    system(" echo \"validator() function started \" >> logfile.log ");
    
    
    //          ** Variables declaration **
    
    // char variables
    char a;
    
    // Body of validator()
    
    // Print the header on the shell
        
    stampa_intest_validator();
        
        clear();

inizio:
    
    // Print the menu and acquire the user's choice
    
    menu_validator();
    scanf("%c", &a);
    

    // Options availables on the menu
    
    switch (a) {
            
            // Single comparison between two data series
            
        case 'a': {
            validator_single();
            goto fine;
        }

            // Multiple comparisons between one single validation file and more simulation files
            
        case 'b': {
            validator_multiple();
            goto fine;
        }
            
        case 'c':{
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

