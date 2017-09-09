#include <eeprom.h>


int32_t  EEMEM NonVolatileChar;
uint32_t EEMEM NonVolatileInt;
uint3_t  EEMEM NonVolatileString[10];

while(1){
	
	//INCREMENTING THE TOTAL & GENDERED COUNTERS	
	if(curr_time - prevTime >= 100){
		if(PIN.state ^ currState){
			total_state_changes++;
			PIN.state ? low_to_his++ : hi_to_lows++;	
	}		
	
	if(total_state_changes != ( hi_to_lows + low_to_his)){
		total_state_changes = 0;
		hi_to_lows = 0;
		low_to_his = 0;

		//Not sure what writing fucntion will be used	
		if(write(SEU_COUNTER, ++*SEU_COUNTER)){
			printfs(stderr,"ERROR WRITING SEU COUNTER");
		}
	}	
}
