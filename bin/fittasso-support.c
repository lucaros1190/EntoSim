
/* This is a support file for 'fittasso tool'. Contains additional functions.
 
 Created by Luca Rossini on 25/09/2018
 email: luca.rossini@unitus.it
 last update 27/07/2020 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Convert the average development times in average development rate (life tables)

void rateconverter(void){
    
    // Statement for the logfile
    
    system(" echo \"rateconverter() function started \" >> logfile.log ");
    
    void acknowledgements(void);
    double tempi[500][4]={ }, tassi[500][4]={ };
    int scan=0, count=0, i=0;
    
    
    FILE *times;
        times = fopen("./input/LifeTablesTimes.txt", "r");
        
        // Report the status of the file into the logfile
        if (times == 0){
            system(" echo \"Error: rateconverter() function. Failure opening file input/LifeTablesTimes.txt \" >> logfile.log ");
        }
        else if (times != 0){
            system(" echo \"rateconverter() function. File input/LifeTablesTimes.txt succesfully opened\" >> logfile.log ");
        }
        
        // Scan the content
        for(i=0; scan != EOF; i++){
            scan = fscanf(times, "%lf%lf%lf%lf", &tempi[i][0], &tempi[i][1], &tempi[i][2], &tempi[i][3]);
            count = i-1;
        }
    fclose(times);
    
    for(i=0; i<=count; i++){
        tassi[i][0] = tempi[i][0];
        tassi[i][1] = 1/tempi[i][1];
        tassi[i][2] = tempi[i][2];
        tassi[i][3] = (1/(pow(tempi[i][1], 2))) * tempi[i][3];
    }
    
    FILE *rates;
        rates = fopen("./input/LifeTablesRates.txt", "w");
    
        // Report the status of the file into the logfile
        if (times == 0){
            system(" echo \"Error: rateconverter() function. Failure opening file input/LifeTablesRates.txt \" >> logfile.log ");
        }
        else if (times != 0){
            system(" echo \"rateconverter() function. File input/LifeTablesRates.txt succesfully opened\" >> logfile.log ");
        }
        
        // Print the content
        for(i=0; i<=count; i++){
            fprintf(rates, "%.1lf\t%.5lf\t%.1lf\t%.5lf\n", tassi[i][0], tassi[i][1], tassi[i][2], tassi[i][3]);
        }
    fclose(rates);

}



