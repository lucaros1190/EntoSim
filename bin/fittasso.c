
/* Source of "fittasso" tool. This file manages the parameters estimation
 of the functions listed in the "ratefunctionlist.h", and provides a series
 of other tools which could be helpful for life tables analysis
 
 Created by Luca Rossini on 25/09/2018
 email: luca.rossini@unitus.it
 last update 30/07/2020 */

#include <stdio.h>
#include <cstdlib>
#include "fittasso-support.h"
#include "fittasso.h"
#include "headers-menu.h"
#include "entosim.h"
#include "support.h"


void fittasso(void){
    
    // Statement for the logfile
    
    system(" echo \"fittasso() function started \" >> logfile.log ");
    
    
//          ** Variables declaration **
    
    // char variables
    char a;

    

    // Body of fittasso()
    
    
    // Print the header on the shell
    
    stampa_intest();
    
    clear();
    
inizio:
    
    // Print the menu and acquire the user's choice
    
    stampa_menu();
    scanf("%c", &a);


    // Options availables on the menu
    
    switch (a) {
            
            // Logan fit function
            
        case 'a': {
            logan();
            goto fine;
        }

            // Sharpe and De Michele fit function
            
        case 'b': {
            SDM();
            goto fine;
        }
            
            // Briere fit function
            
        case 'c': {
            briere();
            goto fine;
        }
        
            // Linear fit function
        
        case 'd':{
            linear();
            goto fine;
        }
            
            // Conversion of the life tables from times to rates
            
        case 'e':{
            rateconverter();
            goto fine;
        }
            
            // Print an overlapped plot of all the development rate functions
            
        case 'f':{
            system("cd bin/ ; python3 -c 'import graphics; graphics.ratefunctionresume()' ; rm -rf __pycache__ ; cd ..");
            goto fine;
        }
            
        case 'g':{
            goto fine;
        }
        
            // If a wrong choice is selected, it returns to "inizio"
            
        default:{
            printf("%s", "\n\n Incorrect choice, please try again");
            goto inizio;
        }
            
    }
    
fine:
    entosim();
    
}
