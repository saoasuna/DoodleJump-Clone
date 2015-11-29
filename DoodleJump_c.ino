extern "C" {
#include <delay.h>
#include <FillPat.h>
#include <I2CEEPROM.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
}
#define DEMO_0		0
#define DEMO_1		1
#define DEMO_2		2
#define DEMO_3		3
#define NUM_TILES       5
typedef struct{
    int h,w,x,y;
}tile;
int collisiondetection(int size, tile blocks[], int player_x,int player_y,int dx,int dy);
char	CurrentSwitch;
char	PreviousSwitch;
bool	ClearLED;
int size = 0;

// Define the top left corner of Person  
int	xPlayerStart 	= 40; 
int	yPlayerStart	= 10;
int	PlayerWidth 	= 16;
int	PlayerHeight 	= 16;

int     PlatformHeight = 8;
int     PlatformWidth = 4;

char rgBMPPlayer[] = {0x00, 0x40, 0x40, 0x40, 0xF0, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0x00, 0xF0, 0x90, 0x80, 0x80, 0x00,
0x00, 0x02, 0x02, 0x02, 0x0F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x00, 0x0F, 0x09, 0x01, 0x01, 0x00};
char rgBMPBlock[]={0xFF,0xFF};
tile blocks[NUM_TILES];

int countloop=0;
unsigned long SCORE=0;
unsigned long HISCORE=0;
char hiscorec[50];
void setup()
{ 
   DeviceInit();
   doodleInit();
}

void loop()
{

  char bDemoState = 0;
  volatile uint32_t ui32Loop;
  for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
  {
  }
  
  bDemoState = CheckSwitches();
  switch(bDemoState) {
  case DEMO_0:
    OrbitDemo0();
    break;
  case DEMO_1:
    OrbitDemo1();
    break;
  case DEMO_2:
    OrbitDemo2();
    break;
  case DEMO_3:
    OrbitDemo3();
    break;
  default:
    OrbitDemo0();
    break;
  }  
}

void flash(int start){
  if (start == 1){
    GPIOPinWrite(LED1Port, LED1, LED1);
  }
  else if (start == 2){
    GPIOPinWrite(LED2Port, LED2, LED2);
  }
  else if (start == 3){ 
    GPIOPinWrite(LED3Port, LED3, LED3);
  }
  else if (start == 4){
    GPIOPinWrite(LED4Port, LED4, LED4);
  }
}

void off (){
    GPIOPinWrite(LED1Port, LED1, LOW);
    GPIOPinWrite(LED2Port, LED2, LOW);
    GPIOPinWrite(LED3Port, LED3, LOW);
    GPIOPinWrite(LED4Port, LED4, LOW);
}


int getStart(){
  
   uint32_t	ulAIN0;
  long 			lBtn1;
  long 			lBtn2;
  char			szAIN[6] = {
    0            };
  char			cMSB = 0x00;
  char			cMIDB = 0x00;
  char			cLSB = 0x00;
  
 ADCProcessorTrigger(ADC0_BASE, 0);

 //while(!ADCIntStatus(ADC0_BASE, 0, false));

 ADCSequenceDataGet(ADC0_BASE, 0, &ulAIN0);

  /*
   * Process data
   */ 
  cMSB = (0xF00 & ulAIN0) >> 8;
  cMIDB = (0x0F0 & ulAIN0) >> 4;
  cLSB = (0x00F & ulAIN0);

  szAIN[0] = '0';
  szAIN[1] = 'x';
  szAIN[2] = (cMSB > 9) ? 'A' + (cMSB - 10) : '0' + cMSB;
  szAIN[3] = (cMIDB > 9) ? 'A' + (cMIDB - 10) : '0' + cMIDB;
  szAIN[4] = (cLSB > 9) ? 'A' + (cLSB - 10) : '0' + cLSB;
  szAIN[5] = '\0';
  
  if ((int)szAIN[2] <= 52 && (int)szAIN[2] > 48){
  return 1;}
  if ((int)szAIN[2] <= 56 && (int)szAIN[2] > 52) {
  return 2;}
  if ((int)szAIN[2] <= 66 && (int)szAIN[2] > 56){
  return 3;}
  if ((int)szAIN[2] <= 70 && (int)szAIN[2] > 66){
  return 4;}
}

void space(){
  delay(2000);
}
//1 unit is half a second
void a(){
  getStart();
  flash(getStart());
  delay(500);
  off();
  delay(1000);
  flash(getStart());
  delay(1500);
  off();
}
void b(){
  getStart(); 
  flash(getStart());
  delay(1500);
  off();
  delay (500);
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
}
void c(){
   getStart(); 
  flash(getStart());
  delay(1500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(1500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
}


void d(){
   getStart(); 
  flash(getStart());
  delay(1500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
}
void e(){
   getStart(); 
  flash(getStart());
  delay(500);
  off();
}
void f(){
   getStart(); 
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(1500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
}
void g(){
   getStart(); 
  flash(getStart());
  delay(1500);
  off();
  delay(500);
  flash(getStart());
  delay(1500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
}

void h(){
   getStart(); 
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
}
void iqwe(){
   getStart(); 
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
}
void j(){
   getStart(); 
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
}
void k(){
   getStart(); 
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
}

void l(){
   getStart(); 
   flash(getStart());
   delay(500);
   off();
   delay(500);
   flash(getStart());
   delay(1500);
   off();
   delay(500);
   flash(getStart());
   delay(500);
   off();
   delay(500);
   flash(getStart());
   delay(500);
   off();
}
void m(){
  getStart(); 
  flash(getStart());
  delay(1500);
  off();
  delay (500);
  flash(getStart());
  delay(1500);
  off();
}

void n(){
  getStart(); 
  flash(getStart());
  delay(1500);
  off();
  delay (500);
  flash(getStart());
  delay(500);
  off();
}

void o(){
  getStart(); 
  flash(getStart());
  delay(1500);
  off();
  delay (500);
  flash(getStart());
  delay(1500);
  off();
  delay(500);
  flash(getStart());
  delay(1500);
  off();
}

void p(){
  getStart(); 
  flash(getStart());
  delay(500);
  off();
  delay (500);
  flash(getStart());
  delay(1500);
  off();
  delay(500);
  flash(getStart());
  delay(1500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
}

void q(){
  getStart(); 
  flash(getStart());
  delay(1500);
  off();
  delay (500);
  flash(getStart());
  delay(1500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(1500);
  off();
}

void r(){
  getStart(); 
  flash(getStart());
  delay(500);
  off();
  delay (500);
  flash(getStart());
  delay(1500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
}

void s(){
  getStart(); 
  flash(getStart());
  delay(500);
  off();
  delay (500);
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
}

void t(){
  getStart(); 
  flash(getStart());
  delay(1500);
  off();
}

void u(){
  getStart(); 
  flash(getStart());
  delay(500);
  off();
  delay (500);
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(1500);
  off();
}

void v(){
  getStart(); 
  flash(getStart());
  delay(500);
  off();
  delay (500);
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(1500);
  off();
}

void w(){
  getStart(); 
  flash(getStart());
  delay(500);
  off();
  delay (500);
  flash(getStart());
  delay(1500);
  off();
  delay(500);
  flash(getStart());
  delay(1500);
  off();
}

void x(){
  getStart(); 
  flash(getStart());
  delay(1500);
  off();
  delay (500);
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(1500);
  off();
}

void y(){
  getStart(); 
  flash(getStart());
  delay(1500);
  off();
  delay (500);
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(1500);
  off();
  delay(500);
  flash(getStart());
  delay(1500);
  off();
}

void z(){
  getStart(); 
  flash(getStart());
  delay(1500);
  off();
  delay (500);
  flash(getStart());
  delay(1500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
  delay(500);
  flash(getStart());
  delay(500);
  off();
}
void one(){
   getStart(); 
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
}

void two(){
   getStart(); 
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
}

void three(){
   getStart(); 
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
}

void four(){
   getStart(); 
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
}

void five(){
   getStart(); 
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
}

void six(){
   getStart(); 
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
}

void seven(){
   getStart(); 
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
}

void eight(){
   getStart(); 
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(500);
off();
delay(500);
flash(getStart());
delay(500);
off();
}

void nine(){
 getStart(); 
  flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(1500);
off();
delay(500);
flash(getStart());
delay(500);
off();
}

void zero(){
   getStart(); 
   flash(getStart());
   delay(1500);
   off();
   delay(500);
   flash(getStart());
   delay(1500);
   off();
   delay(500);
    flash(getStart());
   delay(1500);
   off();
   delay(500);
   
    flash(getStart());
   delay(1500);
   off();
   delay(500);
   
    flash(getStart());
   delay(1500);
   off();
}
   
   


bool I2CGenIsNotIdle() {
  return !I2CMasterBusBusy(I2C0_BASE);
}

int collisiondetection(int size, tile blocks[], int player_x,int player_y,int dx,int dy){ //dx, dy= falling speed, player_x,y = position of the player
    for(int i=0; i<size; i++){
      if(player_x+dx==blocks[i].x+blocks[i].w && ((player_y+16>=blocks[i].y && player_y+16<=blocks[i].y+blocks[i].h)
      ||(player_y<=blocks[i].y+blocks[i].h && player_y>=blocks[i].y)||(player_y<=blocks[i].y && player_y+16>=blocks[i].y+blocks[i].h))){
       return -1; //will collide
      }
    }
return 0; //will not collide 
}
void doodleInit(){
    SCORE=0;
    OrbitOledClear();
    OrbitOledMoveTo(10,0);
    OrbitOledSetCursor(0,0);
    for ( int i = 0; i < NUM_TILES; i++ ) 
    {
        tile block = {PlatformHeight, PlatformWidth, i*38, rand_interval(0,26)};
       	blocks[i] = block;
   } 
}
unsigned int rando() {
  return rand_interval(0, 16);
}

unsigned int rand_interval(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}
  
void DeviceInit()
{
  /*
   * First, Set Up the Clock.
   * Main OSC		  -> SYSCTL_OSC_MAIN
   * Runs off 16MHz clock -> SYSCTL_XTAL_16MHZ
   * Use PLL		  -> SYSCTL_USE_PLL
   * Divide by 4	  -> SYSCTL_SYSDIV_4
   */
  SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_4);

  /*
   * Enable and Power On All GPIO Ports
   */
  //SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOA | SYSCTL_PERIPH_GPIOB | SYSCTL_PERIPH_GPIOC |
  //						SYSCTL_PERIPH_GPIOD | SYSCTL_PERIPH_GPIOE | SYSCTL_PERIPH_GPIOF);

  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOA );
  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOB );
  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOC );
  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOD );
  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOE );
  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOF );
  /*
   * Pad Configure.. Setting as per the Button Pullups on
   * the Launch pad (active low).. changing to pulldowns for Orbit
   */
  GPIOPadConfigSet(SWTPort, SWT1 | SWT2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

  GPIOPadConfigSet(BTN1Port, BTN1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
  GPIOPadConfigSet(BTN2Port, BTN2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

  GPIOPadConfigSet(LED1Port, LED1, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED2Port, LED2, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED3Port, LED3, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED4Port, LED4, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);

  /*
   * Initialize Switches as Input
   */
  GPIOPinTypeGPIOInput(SWTPort, SWT1 | SWT2);

  /*
   * Initialize Buttons as Input
   */
  GPIOPinTypeGPIOInput(BTN1Port, BTN1);
  GPIOPinTypeGPIOInput(BTN2Port, BTN2);

  /*
   * Initialize LEDs as Output
   */
  GPIOPinTypeGPIOOutput(LED1Port, LED1);
  GPIOPinTypeGPIOOutput(LED2Port, LED2);
  GPIOPinTypeGPIOOutput(LED3Port, LED3);
  GPIOPinTypeGPIOOutput(LED4Port, LED4);

  /*
   * Enable ADC Periph
   */
  SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

  GPIOPinTypeADC(AINPort, AIN);

  /*
   * Enable ADC with this Sequence
   * 1. ADCSequenceConfigure()
   * 2. ADCSequenceStepConfigure()
   * 3. ADCSequenceEnable()
   * 4. ADCProcessorTrigger();
   * 5. Wait for sample sequence ADCIntStatus();
   * 6. Read From ADC
   */
  ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
  ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);
  ADCSequenceEnable(ADC0_BASE, 0);

  /*
   * Initialize the OLED
   */
  OrbitOledInit();

  /*
   * Reset flags
   */
  CurrentSwitch = 0;
  PreviousSwitch = 0;
  ClearLED = true;

}
char CheckSwitches() {

  long 	switch1;
  long 	switch2;

  PreviousSwitch = CurrentSwitch;

  switch1 = GPIOPinRead(SWT1Port, SWT1);
  switch2 = GPIOPinRead(SWT2Port, SWT2);

  CurrentSwitch = (switch1 | switch2) >> 6;

  if(CurrentSwitch != PreviousSwitch) {
    ClearLED = true;
  }

  return CurrentSwitch;
}

void OrbitDemo0() {
    OrbitOledClear();
    OrbitOledMoveTo(0,0);
    OrbitOledSetCursor(0,0);
  
    char temp[100];
  int counter = 0;
  char C; 
  int num1 = 0;
  int num2 = 0; 
  char operat;  
  int result = 0;
  char resultc[100];
  int resultCounter = 0; 
  boolean negative = false; 
  
  	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);  // Set up Clock

	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);		// Enable UART hardware
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);		// Enable Pin hardware

	GPIOPinConfigure(GPIO_PA0_U0RX);		// Configure GPIO pin for UART RX line
	GPIOPinConfigure(GPIO_PA1_U0TX);		// Configure GPIO Pin for UART TX line
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);     // Set Pins for UART

	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,		// Configure UART to 8N1 at 115200bps
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));




while (CheckSwitches() == DEMO_0) //only works for positive numbers and integer division (ie always rounds down if decimal) 
	{
                while (1){ //insert breaks for checkswitches at places, and also make it work for backspace?
		C = UARTCharGet(UART0_BASE);
                temp[counter] = C;
                UARTCharPut(UART0_BASE, temp[counter]);
                if (CheckSwitches() != DEMO_0){
                  break;
                }
                if ((int)temp[counter] == 127){
                  counter -= 3; 
                }
                if ((int)temp[counter] == 32){
                  counter--;
                  break;
                }
                counter++;
                if (counter < 0){
                  counter = 0;
                }
                }
                if (CheckSwitches() != DEMO_0){
                  break;
                }
                for (int i = (counter); i >= 0; i--){
                  if ((int)temp[counter-i] == 48){
                  num1 += (int)pow(10, i)*0; 
                  }
                  else if ((int)temp[counter-i] == 49){
                    num1 += (int)pow(10, i)*1;
                  }
                  else if ((int)temp[counter-i] == 50){
                    num1 += (int)pow(10, i)*2;
                  }
                  else if ((int)temp[counter-i] == 51){
                    num1 += (int)pow(10, i)*3;
                  }
                  else if ((int)temp[counter-i] == 52){
                    num1 += (int)pow(10,i)*4;
                  }
                  else if ((int)temp[counter-i] == 53){
                    num1 += (int)pow(10,i)*5;
                  }
                  else if ((int)temp[counter-i] == 54){
                    num1 += (int)pow(10,i)*6;
                  }
                  else if ((int)temp[counter-i] == 55){
                    num1 += (int)pow(10,i)*7;
                  }
                  else if ((int)temp[counter-i] == 56){
                    num1 += (int)pow(10,i)*8;
                  }
                  else if ((int)temp[counter-i] == 57){
                    num1 += (int)pow(10,i)*9;
                  }
                }
                counter = 0;
                operat = UARTCharGet(UART0_BASE); //fuck this, no backspaces for spaces and operators 
                UARTCharPut(UART0_BASE, operat);
                if (CheckSwitches() != DEMO_0){
                  break;
                }
                temp[0] = UARTCharGet(UART0_BASE); //iffy, doesnt check for nonspaces
                UARTCharPut (UART0_BASE, temp[0]);
                if (CheckSwitches() != DEMO_0){
                  break;
                }
                while (1){ 
		C = UARTCharGet(UART0_BASE);
                temp[counter] = C;
                UARTCharPut(UART0_BASE, temp[counter]);
                if (CheckSwitches() != DEMO_0){
                  break;
                }
                if ((int)temp[counter] == 127){
                  counter -= 3; 
                }
                if ((int)temp[counter] == 13){
                  counter--;
                  break;}
                counter++;
                if (counter < 0){
                  counter = 0;
                }
                }
                if (CheckSwitches() != DEMO_0){
                  break;
                }
                for (int i = (counter); i >= 0; i--){
                  if ((int)temp[counter-i] == 48){
                  num2 += (int)pow(10,i)*0; 
                  }
                  else if ((int)temp[counter-i] == 49){
                    num2 += (int)pow(10,i)*1;
                  }
                  else if ((int)temp[counter-i] == 50){
                    num2 += (int)pow(10,i)*2;
                  }
                  else if ((int)temp[counter-i] == 51){
                    num2 += (int)pow(10,i)*3;
                  }
                  else if ((int)temp[counter-i] == 52){
                    num2 += (int)pow(10,i)*4;
                  }
                  else if ((int)temp[counter-i] == 53){
                    num2 += (int)pow(10,i)*5;
                  }
                  else if ((int)temp[counter-i] == 54){
                    num2 += (int)pow(10,i)*6;
                  }
                  else if ((int)temp[counter-i] == 55){
                    num2 += (int)pow(10,i)*7;
                  }
                  else if ((int)temp[counter-i] == 56){
                    num2 += (int)pow(10,i)*8;
                  }
                  else if ((int)temp[counter-i] == 57){
                    num2 += (int)pow(10,i)*9;
                  }  
                }
                if ((int)operat == 43){
                    result = num1 + num2;
                }
                else if ((int)operat == 45){
                    result = num1 - num2;
                    if (result < 0){
                      negative = true;
                      result *= -1;
                    }
                }
                else if ((int)operat == 42){
                    result = num1 * num2;
                }
                else if ((int)operat == 47){
                  result = num1 / num2;
                }
                                    OrbitOledClear();
    OrbitOledMoveTo(0,0);
    OrbitOledSetCursor(0,0);
                                if (result == 0){
                  OrbitOledPutChar('0');
                }    
                while (result > 0){
                      if (result % 10 == 0){
                        resultc[resultCounter] = 48;
                      }
                      else if (result % 10 == 1){
                        resultc[resultCounter] = 49;
                      }
                      else if (result % 10 == 2){
                        resultc[resultCounter] = 50;
                      }
                      else if (result % 10 == 3){
                        resultc[resultCounter] = 51;
                      }
                      else if (result % 10 == 4){
                        resultc[resultCounter] = 52;
                      }
                      else if (result % 10 == 5){
                        resultc[resultCounter] = 53;
                      }
                      else if (result % 10 == 6){
                        resultc[resultCounter] = 54;
                      }
                      else if (result % 10 == 7){
                        resultc[resultCounter] = 55;
                      }
                      else if (result % 10 == 8){
                        resultc[resultCounter] = 56;
                      }
                      else if (result % 10 == 9){
                        resultc[resultCounter] = 57;
                      }
                      result /= 10;
                      resultCounter++;
                    }
                    resultCounter--;
                                        if (negative == true){
                      OrbitOledPutChar('-');
                    }
                for (int i = 0; i <= resultCounter; i++){
                 OrbitOledPutChar(resultc[resultCounter-i]);
                }
                counter = 0;
                resultCounter = 0;
                negative = false; 
                num1 = 0;
                num2 = 0;
                UARTCharPut(UART0_BASE, '\n');
                }
	}
//find where the blank screen after death is 
//write is character array to store, number of characters to store, 1
//read is character array to receive, 1, number of characters to receive

void OrbitDemo1(){
   OrbitOledClear();
    OrbitOledMoveTo(0,0);
    OrbitOledSetCursor(0,0);
    ClearLED = false;
  
  	char temp[100]; 		// Temp Character holder
        int counter = 0; 
        char C; 

	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);  // Set up Clock

	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);		// Enable UART hardware
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);		// Enable Pin hardware

	GPIOPinConfigure(GPIO_PA0_U0RX);		// Configure GPIO pin for UART RX line
	GPIOPinConfigure(GPIO_PA1_U0TX);		// Configure GPIO Pin for UART TX line
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);     // Set Pins for UART

	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,		// Configure UART to 8N1 at 115200bps
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

        getStart(); // ryan is a frigging genius

	while (CheckSwitches() == DEMO_1)
	{
		C = UARTCharGet(UART0_BASE);
                temp[counter] = C;
                counter++;
                UARTCharPut(UART0_BASE, temp[counter-1]);
                if (CheckSwitches() != DEMO_1){
                        break;}
                if ((int)temp[counter-1] == 127){
                  counter -= 2;
                }
                if ((int)temp[counter-1] == 13){
                  if (CheckSwitches() != DEMO_1){
                        break;}
                  for (int i = 0; i < counter-1; i++){ 
                    if ((int)temp[i] == 97 || (int)temp[i] == 65){
                      a();
                    }
                    else if ((int)temp[i] == 98 || (int)temp[i] == 66){
                      b();
                    }
                    
                    else if ((int)temp[i] == 99 || (int)temp[i] == 67){
                      c();
                    }
                    
                    else if ((int)temp[i] == 100 || (int)temp[i] == 68){
                      d();
                    }
                    
                    else if ((int)temp[i] == 101 || (int)temp[i] == 69){
                      e();
                    }
                    
                    else if ((int)temp[i] == 102 || (int)temp[i] == 70){
                      f();
                    }
                    
                    else if ((int)temp[i] == 103 || (int)temp[i] == 71){
                      g();
                    }
                    
                    else if ((int)temp[i] == 104 || (int)temp[i] == 72){
                      h();
                    }
                    
                    else if ((int)temp[i] == 105 || (int)temp[i] == 73){
                      iqwe();
                    }
                    
                    else if ((int)temp[i] == 106 || (int)temp[i] == 74){
                      j();
                    }
                    else if ((int)temp[i] == 107 || (int)temp[i] == 75){
                      k();
                    }
                    else if ((int)temp[i] == 108 || (int)temp[i] == 76){
                      l();
                    }
                    
                    else if ((int)temp[i] == 109 || (int)temp[i] == 77){
                      m();
                    }
                    
                    else if ((int)temp[i] == 110 || (int)temp[i] == 78){
                      n();
                    }
                    
                    else if ((int)temp[i] == 111 || (int)temp[i] == 79){
                      o();
                    }
                    
                    else if ((int)temp[i] == 112 || (int)temp[i] == 80){
                      p();
                    }
                    
                    else if ((int)temp[i] == 113 || (int)temp[i] == 81){
                      q();
                    }
                    
                    else if ((int)temp[i] == 114 || (int)temp[i] == 82){
                      r();
                    }
                    
                    else if ((int)temp[i] == 115 || (int)temp[i] == 83){
                      s();
                    }
                    
                    else if ((int)temp[i] == 116 || (int)temp[i] == 84){
                      t();
                    }
                    
                    else if ((int)temp[i] == 117 || (int)temp[i] == 85){
                      u();
                    }
                    
                    else if ((int)temp[i] == 118 || (int)temp[i] == 86){
                      v();
                    }
                    
                    else if ((int)temp[i] == 119 || (int)temp[i] == 87){
                      w();
                    }
                    
                    else if ((int)temp[i] == 120 || (int)temp[i] == 88){
                      x();
                    }
                    else if ((int)temp[i] == 121 || (int)temp[i] == 89){
                      y();
                    }
                    
                    else if ((int)temp[i] == 122 || (int)temp[i] == 90){
                      z();
                    }
                    
                    else if ((int)temp[i] == 49){
                      one();
                    }
                    
                    else if ((int)temp[i] == 50){
                      two();
                    }
                    
                    else if ((int)temp[i] == 51){
                      three();
                    }
                    else if ((int)temp[i] == 52){
                      four();
                    }
                    
                    else if ((int)temp[i] == 53){
                      five();
                    }
                    
                    else if ((int)temp[i] == 54){
                      six();
                    }
                    
                    else if ((int)temp[i] == 55){
                      seven();
                    }
                    
                    else if ((int)temp[i] == 56){
                      eight();
                    }
                    
                    else if ((int)temp[i] == 57){
                      nine();
                    }
                    
                    else if ((int)temp[i] == 48){
                      zero();
                    }
                    
                    else if ((int)temp[i] == 32){
                      space();
                    }
                    else{
                       GPIOPinWrite(LED1Port, LED1, LED1);
                        GPIOPinWrite(LED2Port, LED2, LED2);
                         GPIOPinWrite(LED3Port, LED3, LED3);
                          GPIOPinWrite(LED4Port, LED4, LED4);
                          delay(2000);
                          off();
                    }
                    if (CheckSwitches() != DEMO_1){
                        break;}
                    delay(1500);
                    if (CheckSwitches() != DEMO_1){
                        break;}
                  }
                  counter = 0;
                  UARTCharPut(UART0_BASE, '\n');
                }
	}
}


void OrbitDemo2() {
   char printVal[10];
   char printHighVal[10];
  short	dataY;
  char 	chPwrCtlReg = 0x2D;
  char  chY0Addr = 0x34;
  char 	rgchReadAccl[] = {0, 0, 0};
  char 	rgchWriteAccl[] = {0, 0};
  int	xPlayer = xPlayerStart;
  int 	yPlayer = yPlayerStart;
  int	yDirThreshPos = 60;
  int	yDirThreshNeg = -60;
  int   jumph=40; //Jump Height
  int   gravity = jumph;
  int   dx=-1;
  bool fDir = true;
  if(ClearLED == true) {
    OrbitOledClear();
    OrbitOledMoveTo(0,0);
    OrbitOledSetCursor(0,0);
    ClearLED = false;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
    GPIOPinTypeI2C(I2CSDAPort, I2CSDA_PIN);
    GPIOPinTypeI2CSCL(I2CSCLPort, I2CSCL_PIN);
    GPIOPinConfigure(I2CSCL);
    GPIOPinConfigure(I2CSDA);
    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);
    I2CEEPROMInit();
    GPIOPinTypeGPIOInput(ACCL_INT2Port, ACCL_INT2);
    rgchWriteAccl[0] = chPwrCtlReg;
    rgchWriteAccl[1] = 1 << 3;		// sets Accl in measurement mode
    I2CGenTransmit(rgchWriteAccl, 1, WRITE, ACCLADDR);
  }
  doodleInit();
  while(CheckSwitches() == DEMO_2) 
  {     
    if (SCORE == 0){
      size = 1;
    }
    else{
    size = floor(log10(abs(SCORE)))+1;
    }
    sprintf(printVal, "%d", SCORE);
    OrbitOledSetCursor(16-size,0);
    OrbitOledPutString(printVal);
    rgchReadAccl[0] = chY0Addr;
    I2CGenTransmit(rgchReadAccl, 2, READ, ACCLADDR);
    dataY = (rgchReadAccl[2] << 8) | rgchReadAccl[1];

    if(dataY > 0 && dataY > yDirThreshPos) {//RIGHT
        if(yPlayer >= 32-16){
          yPlayer=32-16;
        }
        else {yPlayer++;}
   }
    else if(dataY < 0 && dataY < yDirThreshNeg){//LEFT
        if(yPlayer<=0){
          yPlayer=0;
        }
        else {yPlayer--;}
    }
    if(dx<=0){ //DOWN
      if(collisiondetection(NUM_TILES,blocks,xPlayer,yPlayer,-2,0)==0){
        xPlayer--;
      }
      else{dx=1;gravity=jumph;}
    }
    else{//UP
                SCORE++;
                 xPlayer++;
		if(gravity--==0){
			dx=-1;
		} else if ( xPlayer >= 40 ) {	// if the screen needs to be moved
                        if(countloop%2==0){xPlayer--;}		// move the player down
			for ( int i = 0; i < NUM_TILES; i++ ) {		// move all the tiles down
                                blocks[i].x--;
				if (blocks[i].x <= 10) {		// if the tile will move off the screen, move it to the top at a random position
					blocks[i].x = 70+rando();
					blocks[i].y = rando();
                                        OrbitOledClear();
				}
			}
		}
	}
      if(xPlayer<=0){
    OrbitOledClear();
    OrbitOledMoveTo(0,0);
    OrbitOledSetCursor(0,0);
    if (SCORE > HISCORE){
      HISCORE = SCORE;
    }
    sprintf(printHighVal, "%d", HISCORE);
    OrbitOledPutString ("Hiscore: ");
    OrbitOledPutString (printHighVal);
    OrbitOledMoveTo(0,1);
    OrbitOledSetCursor(0,1);
    OrbitOledPutString ("Score: ");
    OrbitOledPutString (printVal);
    delay(3000);
     if (CheckSwitches() != DEMO_2){
      break;
     } 
         doodleInit();
         xPlayer=xPlayerStart;
         yPlayer=yPlayerStart;
      }
      PersonMove(xPlayer, yPlayer);
      for(int i=0; i<NUM_TILES; i++){tileMove(blocks[i].x,blocks[i].y);}
  }
}

void PersonMove(int xcoUpdate, int ycoUpdate) {
  OrbitOledMoveTo(xcoUpdate, ycoUpdate);
  OrbitOledPutBmp(PlayerWidth, PlayerHeight, rgBMPPlayer); 
  OrbitOledUpdate();
}
void tileMove(int x,int y){
  OrbitOledMoveTo(x, y);
  OrbitOledPutBmp(PlatformWidth, PlatformHeight, rgBMPBlock);
  OrbitOledUpdate();
}
char I2CGenTransmit(char * pbData, int cSize, bool fRW, char bAddr) {
  int i;
  char *pbTemp;
  pbTemp = pbData;
  I2CMasterSlaveAddrSet(I2C0_BASE, bAddr, WRITE);
  I2CMasterDataPut(I2C0_BASE, *pbTemp);
  I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
  DelayMs(1);
  while(I2CGenIsNotIdle());
  pbTemp++;
  if(fRW == READ) {
    I2CMasterSlaveAddrSet(I2C0_BASE, bAddr, READ);
    while(I2CMasterBusy(I2C0_BASE));
    for(i = 0; i < cSize; i++) {
      if(cSize == i + 1 && cSize == 1) {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
        DelayMs(1);
        while(I2CMasterBusy(I2C0_BASE));
      }
      else if(cSize == i + 1 && cSize > 1) {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
        DelayMs(1);
        while(I2CMasterBusy(I2C0_BASE));
      }
      else if(i == 0) {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
        DelayMs(1);
        while(I2CMasterBusy(I2C0_BASE));
        while(I2CGenIsNotIdle());
      }
      else {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
        DelayMs(1);
        while(I2CMasterBusy(I2C0_BASE));
        while(I2CGenIsNotIdle());
      }
      while(I2CMasterBusy(I2C0_BASE));
      *pbTemp = (char)I2CMasterDataGet(I2C0_BASE);
      pbTemp++;
    }
  }
  else if(fRW == WRITE) {
    for(i = 0; i < cSize; i++) {
      I2CMasterDataPut(I2C0_BASE, *pbTemp);
      while(I2CMasterBusy(I2C0_BASE));
      if(i == cSize - 1) {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
        DelayMs(1);
        while(I2CMasterBusy(I2C0_BASE));
      }
      else {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
        DelayMs(1);
        while(I2CMasterBusy(I2C0_BASE));
        while(I2CGenIsNotIdle());
      }
      pbTemp++;
    }
  }
  return 0x00;
}
 

void OrbitDemo3() {
   OrbitOledClear();
    OrbitOledMoveTo(0,0);
    OrbitOledSetCursor(0,0);
        ClearLED = true;
           OrbitOledPutString("lol nothing here");
        while (CheckSwitches() == DEMO_3){

        }
}

