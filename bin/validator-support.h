
/* This header file contains all the declarations of the functions included in "validator-support.c".
 
 Created by Luca Rossini on 13/02/2019
 email: luca.rossini@unitus.it
 last update 04/08/2020 */


    // This function deletes and creates the folder "validation"

void cleaner_validation(void);


    // This function compares only two series of data and makes a QQ-plot

void validator_single(void);


    // This function compares multiple series of simulated data, contained in 'output/simresults/' and named 'h=  .txt', with the validation series contained in 'input/validation/validation.txt

void validator_multiple(void);
