#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// grouping the 8 bits  for displaying on console
int receivingBits[8];
// counter for grouping the bits
int static counter=0;
// to check if the received is first bit
int firstBit=0;

//Initialize the port and pin as outputs.
void GPIOinitOut(uint8_t portNum, uint32_t pinNum)
{
	if (portNum == 0)
	{
		LPC_GPIO0->FIODIR |= (1 << pinNum);
	}
	else if (portNum == 1)
	{
		LPC_GPIO1->FIODIR |= (1 << pinNum);
	}
	else if (portNum == 2)
	{
		LPC_GPIO2->FIODIR |= (1 << pinNum);
	}
	else
	{
		puts("Not a valid port!\n");
	}
}

//Initialize the port and pin as outputs.
void GPIOinitIn(uint8_t portNum, uint32_t pinNum)
{
	if (portNum == 0)
	{
		LPC_GPIO0->FIODIR &= ~ (1 << pinNum);
	}
	else if (portNum == 1)
	{
		LPC_GPIO1->FIODIR &= ~ (1 << pinNum);
	}
	else if (portNum == 2)
	{
		LPC_GPIO2->FIODIR &= ~ (1 << pinNum);
	}
	else
	{
		puts("Not a valid port!\n");
	}
}


// activate the pins
void setGPIO(uint8_t portNum, uint32_t pinNum)
{
	if (portNum == 0)
	{
		LPC_GPIO0->FIOSET = (1 << pinNum);
	}
	//Can be used to set pins on other ports for future modification
	else
	{
		puts("Only port 0 is used, try again!\n");
	}
}

//Deactivate the pin
void clearGPIO(uint8_t portNum, uint32_t pinNum)
{
	if (portNum == 0)
	{
		LPC_GPIO0->FIOCLR = (1 << pinNum);
	}
	//Can be used to clear pins on other ports for future modification
	else
	{
		puts("Only port 0 is used, try again!\n");
	}
}


// start transmitting the bit after converting into binary
void trasmitData(char data[23]){
	//Converting the data in to binary
	int bits[184]={};
		int bitCount=0;
		int i;
		  for (i=0;i<strlen(data);i++){
			  int absNum=abs(data[i]);
			  int binary[8]={};
			  int itr;
			  for (itr=8;itr>0;itr--){
			  	binary[itr-1]=(absNum%2);
			  	absNum=absNum/2;
			  }
			  for (itr=0;itr<8;itr++){
				  bits[bitCount]=binary[itr];
				  bitCount++;
			  }
			}
		 // transmitting the data on GPIO
			int sizeOfArray=sizeof(bits)/sizeof(int);
			i=0;
			printf("Transmitting bits");
		    while(i<sizeOfArray)
		    {
		    	clearGPIO(0,3);
		    	printf("%d", bits[i]);
		    	if (bits[i] == 1){
		    			//Activate pin 0.2
		    			setGPIO(0,2);
		    		}
		    		else
		    		{	//De activate pin
		    			clearGPIO(0,2);
		    		}
		    	setGPIO(0,3);
		    	int delay=0;
		    	for(delay=0;delay<2000000;delay++){}
				i++;
		    }
}
// point of start for the transmitter
void StartTransmitter(){
	//Set pin 0.2 as output
	GPIOinitOut(0,2);
	//Set pin 0.3 as output
	GPIOinitOut(0,3);
	// maintianing data in the array
	char data[23];
	printf("please enter the data that has to be transferred to the receiver(less than 23 characters)\n");
	scanf(" %[^\n]s",data);
	trasmitData(data);
}
// interrupt handler
void EINT3_IRQHandler() {
	if(firstBit>0){
	int PinState;
	if((LPC_GPIOINT->IO0IntStatR >> 3) & 1){
		PinState = (LPC_GPIO0->FIOPIN >> 2) & 1;

		if(counter>6){
			receivingBits[counter]=PinState;
			int itr=0;
			int mulFactor=7;
			int asval=0;
			for(itr=0;itr<8;itr++){
				//printf("%d \n",receivingBits[itr]);
			asval=asval+receivingBits[itr]*pow(2,mulFactor);
			mulFactor--;
			}
			printf("%c",asval);
			counter=0;
		}
		else{

			receivingBits[counter]=PinState;
			counter++;
		}

		}
	}
	firstBit++;
	LPC_GPIOINT->IO0IntClr |= (1 << 3);
}
// initialize the interrupt
void receiver(uint8_t portNum, uint32_t pinNum)
{
		if (portNum == 0)
			{
			// Enable Rising Edge Interrupt on P0[3]
			LPC_GPIOINT->IO0IntEnR |= (1 << pinNum);
			// Enable Rising Edge Interrupt on P0[3]
			NVIC_EnableIRQ(EINT3_IRQn);
			}
}
// start the receiver
void StartReceiver(){
	GPIOinitIn(0,2);
	GPIOinitIn(0,3);
	receiver(0,3);
}

int main(void)
{
	int selection;
	printf("In which mode do you want to run microController in \n select 1 for transmitter \n select 2 for receiver");
	scanf("%d",&selection);
	if(selection==1){
		StartTransmitter();
	}
	else if(selection==2){
		StartReceiver();
	}
    return 0;
}
