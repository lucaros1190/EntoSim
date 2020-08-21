
/* This is a support file containing functions used by multiple part of the program
 
 Created by Luca Rossini on 29/07/2020
 email: luca.rossini@unitus.it
 last update 29/07/2020 */

#include <stdio.h>
#include <cstdlib>


// Function which clean the cache (such as fflush)

void clear(void){
    
    // Statement for the logfile
    
    system(" echo \"clear() function started \" >> logfile.log ");
    
    while ( getchar() != '\n' );
}


// Logfile creation

void logfile(void){
    
    int elimina_log_old, crea_log;
    
    elimina_log_old = system("rm ./logfile.log");
    crea_log = system("touch ./logfile.log");
    system(" echo \" \" >> logfile.log");
    system(" echo \"  EntoSim logfile. Welcome $(whoami)! $(date)\" >> logfile.log");
    system(" echo \" \" >> logfile.log");
    
    if (elimina_log_old != 0){
        printf("%s", "Unable to remove the old logfile.log\n");
    }
    
    else if (elimina_log_old == 0){
        printf("%s", " ");
    }
    
    if (crea_log != 0){
        printf("%s", "Unable to create logfile.log\n");
    }
    
    else if (crea_log == 0){
        printf("%s", " ");
    }
}
