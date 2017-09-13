/*H**********************************************************************
* FILENAME :        dut.c             DESIGN REF: TRIUMF 2017 psuedocode
*
* DESCRIPTION :
*      Operations code for the DUT at TRIUMF 2017 testing. 
*
* PUBLIC FUNCTIONS :
*       int     FM_CompressFile( FileHandle )
*       int     FM_DecompressFile( FileHandle )
*
* todo :
*   - ensure word is proper length, is it 16 or 8 bits for respective boards.
*   -swap the flashSpace array for the actual flash starting addres
*   -with above, adjust FLASHSIZE to the proper flash  size
*   
* 
* AUTHOR :    Owen McLeod   START DATE :    9/9/2017
*
* CHANGES :
*   VERSION DATE    WHO     DETAIL
*   0       9/9/17  O.M.    Initiliazing and converting psuedocode
*   1       9/9/17  O.M.    Set up word typedef temporarily. Is it 8 or 16?
*   2       11/9/17 O.M.    Added in flash and ram error counters and output in main() func
*
*H*/

typedef unsigned int word;
	

#define testSize 99999
volatile word testMemArray[testSize];
long int ram_errors;
word previous_write, next_write;

void ram_init() {
    int j = 0;
    next_write = 0;
    for(j; j<testSize;j++) {
        testMemArray[j] = 0;
    }
}

void ram_test() {
    long int read, j;
    previous_write = next_write;
    next_write = next_write ^ 0xFFFFFFFF;
    for(j = 0; j<testSize;j++) {
        read = testMemArray[j];
        if (read != previous_write) {
            printf("delayed read %0x %0x %0x\n",j,read,previous_write);
			ram_errors++;	
	}
        testMemArray[j]= next_write;
        read = testMemArray[j];
        if (read != next_write) {
            printf("instant read %0x %0x %0x\n",j,read,previous_write);
			ram_errors++;
		}
    }
}

#define FLASHSIZE 888888
#define FLASHCHECKSUM 0x45678945678
//What is starting address of flash??  
//word *p = 0xFFFF0000; 
volatile word flashSpace[FLASHSIZE];
long int flash_errors;

void flash_test() {
    unsigned int j, sum = 0;
    for(j; j<FLASHSIZE;j++){
        sum += flashSpace[j];
    }
    sum-= FLASHCHECKSUM;
    if(sum){
        printf("flash checksum delta %x\n",sum); 
		flash_errors++;
	}
}



main() {
    int iteration = 0;
    #define EVER 1
    printf("ARM alive");
    ram_init();

    while(1) {
        //pet_watchdog();
     	printf("ARM iteration %d, %d ram errors, %d flash errors\n",iteration,ram_errors, flash_errors); 
        ram_test();
        flash_test();
		iteration++;
    }
}

