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
*   create datetype for architecture word size "word"
* 
* AUTHOR :    Owen McLeod   START DATE :    9/9/2017
*
* CHANGES :
*   VERSION DATE    WHO     DETAIL
*   9/9/17          O.M.    Initiliazing and converting psuedocode
*H*/

#define testSize 99999
volatile word testMemArray[testSize];
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
    next_write = nextwrite ^ 0xFFFFFFFF;
    for(j = 0; j<testSize;j++) {
        read = testMemArray[j];
        if (read != previous_write) 
            printf("delayed read %0x %0x %0x\n",j,read,previous_write);
        testMemArray[j]= next_write;
        read = testMemArray[j];
        if (read != next_write) 
            printf("instant read %0x %0x %0x\n",j,read,previous_write);
    }
}

#define FLASHSIZE 888888
#define FLASHCHECKSUM 0x45678945678

word *p = 0xFFFF0000 //What is starting address of flash??  

void flash_test() {
    unsigned int j, sum = 0;
    for(j; j<FLASHSIZE;j++){
        sum += p[j];
    }
    sum-= FLASHCHECKSUM;
    if(sum)
        printf("flash checksum delta %x\n",sum); 
}



main() {
    int iteration = 0;
    #define EVER 1
    while(1) {
        //pet_watchdog();
        printf("ARM iteration %d\n",iteration);
        ram_test();
        flash_test();
    }
}

