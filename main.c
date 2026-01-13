#include "header.h"
/*
 *--------------------------
 *---------Maman14----------
 * ---By:-------------------
 *-------Roey Yohanan-------
 *--------208585844---------
 *-------Adam Gertzkin------
 *--------301301685---------
 *--------------------------
*/
int main(int argc,char* argv[]) {


    FILE *fp = NULL;
    /*
     * Two global variables that keep track of:
     * The number of instructions to be codded(IC)
     * The amount of data words to be encoded
     */
    int IC = 100;
    int DC = 0;

    if(argc < 2){
        printf("File not found, please check it and try again\n");
        exit(1);
    } else if(argc > 2){
        main(argc - 1 , argv);
    }

    fp = openFile(argv[argc-1],"r",AS_EXTENSION);
    if(!fp){
        printf("File opening error, please check it and try again\n");
    } else {
        /* ---------------------------------------------
		The first Stage - analyze the line  
	   ---------------------------------------------
	*/
        firstPass(fp, &IC, &DC);


	 /* ---------------------------------------------
		The second Stage -  update the addresses  
	   ----------------------------------------------
	*/

        updateSymbols(IC);
	
        /*Update words list addresses*/
        updateAddresses();
        /*update data list addresses*/
        updateDataAddresses(IC);

	secondPass();
 	/* ----------------------------------------------
		The third Stage -  exporting the files  
	   ----------------------------------------------
	*/
        /*If there were no errors, export the files*/
        if (!isError())
        {
            thirdStage(argv[argc-1]);
        }
        /*If there were errors, export the error file*/
        else
        {
	    printf("file --%s-- ",argv[argc-1] );
            printErrors(argv[argc-1]);
            /*Free the errors list*/
            freeErrors();
        }

        /* Cleanup - free all the dynamic allocation */
        freeData();
        freeSymbols();
        freeEntries();
        freeWords();
    }

    return 0;
}
