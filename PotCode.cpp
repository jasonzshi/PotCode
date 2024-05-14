//#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "pico/time.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/pio.h"
#include "hardware/rtc.h"
#include "pico/util/datetime.h"
//#include "pico/mutex.h"
#include "extern/pico-scale/include/scale.h"
#include "extern/hx711-pico-c/include/hx711.h"
#include "extern/hx711-pico-c/include/hx711_noblock.pio.h"

// sd libs
#include "ff.h"
#include "sd_card.h"
#include "hw_config.h"
#include "diskio.h" //???
//#include "sd_spi.h"
#include "f_util.h"
//ml libs

//#include "model-parameters/model_metadata.h"
//#include "edge-impulse-sdk/dsp/numpy_types.h" // dunno if needed


/* uncomment later (commented out for debugging speed)
#include "edge-impulse-sdk/classifier/ei_run_classifier.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"
#include "edge-impulse-sdk/classifier/ei_classifier_types.h"
*/

//#include "extern/pico-scale/extern/hx711-pico-c/include/hx711_noblock.pio.h"

// FreeRTOS

#include <FreeRTOS.h>
#include <task.h>


static int gpiopin = 14; // made global
bool pumptomax = false; // boolean flag to pump to max
mass_t waterused; // mass_t to hold water used in grams
mass_t totalwateravailable; // init function below in setup to define weight of water
const double AvailableWaterinGrams = 700; // 700 grams available 
bool nowater =false; // bool for if water reservoir is empty

//scale init
hx711_t hx;
scale_t sc; // scale lib
// weight calc
mass_t maxweightstruct; // struct for maxweight

/*

static spi_t spis[] = {  // One for each SPI.
    {
        .hw_inst = spi0,  // SPI component
        .miso_gpio = 4, // GPIO number (not pin number)
        .mosi_gpio = 3,
        .sck_gpio = 2,
        .baud_rate = 12500 * 1000,  
        //.baud_rate = 25 * 1000 * 1000, // Actual frequency: 20833333. 
    }
};

// Hardware Configuration of the SD Card "objects"
static sd_card_t sd_cards[] = {  // One for each SD card
    {
        .pcName = "0:",   // Name used to mount device
        .spi = &spis[0],  // Pointer to the SPI driving this card
        .ss_gpio = 5,    // The SPI slave select GPIO for this SD card
        .use_card_detect = false,
        //.card_detect_gpio = 13,   // Card detect
        //.card_detected_true = -1  // What the GPIO read returns when a card is
                                 // present. Use -1 if there is no card detect.
    }};

*/



// sensor interrupt
void senseitr(uint , uint32_t) // change to cpp vers
{
 //gpio_put(15,1);   // turn off motor
 gpio_put(14,0);
 gpio_put(20,0); // turn off amber led
 printf("levelsense Triggered");
}






// ML MODEL
int datain;
static float features[]={
-0.7685, -0.6435, -0.6273
};

int raw_feature_get_data(size_t offset, size_t length, float *out_ptr)
{   
    /*
    for (int i =0; i<6; i++)
    {
        features[i]=datain;
    }
    */
    
  memcpy(out_ptr, features + offset, length * sizeof(float));
  return 0;
}

void BLedhandler(void* parameter); //function prototype CURRENTLY UNUSED

typedef struct weightstructs // structs to hold both mass values to pass into rtos function CURRENTLY UNUSED
{
    mass_t currmass;
    mass_t maxmass; 
}twoweights; 



//setup loop 

void initweightsetup(mass_t mass, scale_options_t opt){ // 30 second setup loop before using 

gpio_put(20,1); // turn on amber led

double val;
    datetime_t t = {
            .year  = 2023,
            .month = 1,
            .day   = 1,
            .dotw  = 0, 
            .hour  = 00,
            .min   = 00,
            .sec   = 00
    };

    rtc_init();
    rtc_set_datetime(&t);
   // rtc_get_datetime(&t);
   char datetime_buf[256]; // hold rtc data
   char *datetime_str = &datetime_buf[0];

    printf("clock initialized\n");

        if(scale_weight(&sc, &mass, &opt)) { // gets weight
        double val;
        mass_get_value(&mass, &val);
        char buff[MASS_TO_STRING_BUFF_SIZE];
        mass.ug = mass.ug * -1; // invert values
        mass_to_string(&mass, buff);
        //printf("%s\n", buff);
        mass.ug = mass.ug /1000000; // wonky divider to make values match
        datain = mass.ug;
        }
    bool initweightset = false; // bool for if a weight is set
    while(mass.ug < 10 && t.sec < 30 ){ // while still under min threshold and less than 30 seconds

        if(scale_weight(&sc, &mass, &opt)) { // gets weight again
        double val;
        mass_get_value(&mass, &val);
        char buff[MASS_TO_STRING_BUFF_SIZE];
        mass.ug = mass.ug * -1; // invert values
        mass_to_string(&mass, buff);
        //printf("%s\n", buff);
        mass.ug = mass.ug /1000000; // wonky divider to make values match
        datain = mass.ug;
        }
        printf("its loopin time\n");
        datetime_to_str(datetime_str, sizeof(datetime_buf), &t);
        printf("\r%s      ", datetime_str);
        printf("mass : %f\n",mass.ug);
        rtc_get_datetime(&t);
        sleep_ms(100);
        //get weight updates
        
        if (maxweightstruct.ug < mass.ug) // sets new weight if current weight is higher than maxweight
        { 
            sleep_ms(420); // bounce delay for settling IMPORTANT !!!!
                if(scale_weight(&sc, &mass, &opt)) { // gets weight
                double val;
                mass_get_value(&mass, &val);
                char buff[MASS_TO_STRING_BUFF_SIZE];
                mass.ug = mass.ug * -1; // invert values
                mass_to_string(&mass, buff);
                //printf("%s\n", buff);
                mass.ug = mass.ug /1000000; // wonky divider to make values match
                datain = mass.ug;
                }
            initweightset = true;
            if (maxweightstruct.ug < mass.ug) // just in case user lifts off object in those 300 ms
            {
                maxweightstruct.ug = mass.ug;
                //initweightset = false; // double check if this logic works 
            }
            
        }
        //blink
            
            
    }
    printf("initmaxweight: %f\n", maxweightstruct.ug);
    while(t.sec < 30 && initweightset == true) // adds grace period to pick up if user waters after putting the pot down
            {
               if(scale_weight(&sc, &mass, &opt)) { // gets weight
                double val;
                mass_get_value(&mass, &val);
                char buff[MASS_TO_STRING_BUFF_SIZE];
                mass.ug = mass.ug * -1; // invert values
                mass_to_string(&mass, buff); 
                //printf("%s\n", buff);
                mass.ug = mass.ug /1000000; // wonky divider to make values match
                datain = mass.ug;
                }
                rtc_get_datetime(&t);
                sleep_ms(100);
                if (mass.ug < maxweightstruct.ug * 1.33 && mass.ug > maxweightstruct.ug) // 33% increase tolerance
                {
                   maxweightstruct.ug = mass.ug; 
                }
            }
    //lock maxweight
    gpio_put(20,0); // turn off amber led
    printf("final maxweight: %f\n", maxweightstruct.ug);
    //const mass_t maxweightstruct = maxweightstruct; // see if this is ok
    mass_init(&totalwateravailable, mass_g,AvailableWaterinGrams); // init as micro grams & set as 500 FIELD FOR ADJUSTING TOTAL AVAILABLE WATER
    totalwateravailable.ug = totalwateravailable.ug/1000000; // weird scaling thing again
    //twoweights bothweights= {mass,maxweightstruct}; // pass mass values into weight struct
    //xTaskCreate(BLedhandler,"BlueLEDTask",128,&bothweights,2,NULL); //thing to handle blue led

   // xTaskCreate(drymotorstopper,"DryStop",configMINIMAL_STACK_SIZE, &params, 1, NULL);
}

//haha

/* might not need
// Scale params to be passed to RTOS Function
struct ScaleParams{
    scale_t passsc; // passed scale object
    scale_options_t passopt; //passed options
    mass_t passmass; // mass passed 
};
// RTOS get weight function dunno if I should do this

void getweight (void *params) 
{
   ScaleParams *passedparams = static_cast<ScaleParams*>(params);

}
*/
// RTOS function for monitoring and stopping motor if it is dry
void drymotorstopper (void *params) // check if datetime is correct
{
    static bool IsSetup = false;
    if (!IsSetup) // single run setup loop
    {
        IsSetup = true;
    }

    mass_t dryloopmass;
    scale_options_t opt = SCALE_DEFAULT_OPTIONS;
    mass_t initweight; 
   //Poll Weight
   
   if(scale_weight(&sc, &dryloopmass, &opt)) { // gets weight again 
        double val;
        mass_get_value(&dryloopmass, &val);
        char buff[MASS_TO_STRING_BUFF_SIZE];
        dryloopmass.ug = dryloopmass.ug * -1; // invert values
        mass_to_string(&dryloopmass, buff);
        dryloopmass.ug = dryloopmass.ug /1000000; // wonky divider to make values match
        }
    // establish init weight
   if (initweight.ug) // checks if has value and, if not, assigns one
   {
        initweight = dryloopmass;
   } 
   
   vTaskDelay(pdMS_TO_TICKS(1000)); //allow time to pass
   // take weight again
   /*
    if (); // badadad needs work
    {
        gpio_put(14,0);
    }
    */
}


int main()
{ 
bool waterstatus = false;

int ret; // unused?
char buf[100]; // unused?
char filename[] = "test3.csv";

 stdio_init_all();
 gpio_init(25); //onboard led
 gpio_set_dir(25,GPIO_OUT);
 gpio_init(15); // pwm pin 1enable
 gpio_init(14);  
 //gpio_set_function(14, GPIO_FUNC_PWM);
 gpio_set_dir(14,GPIO_OUT); // remove later
 gpio_set_dir(15,GPIO_OUT);


adc_init();// enable adc

adc_gpio_init(26);
   
 adc_select_input(0); // adc on pin 26

    gpio_put(25,1);
    
    gpio_put(14,0); // starts motor

    //gpio_put(14,1);  IGNORE PWM DISABLE

    //pwm_set_gpio_level(gpiopin, 1); // stops motor???

// level sense
 gpio_init(18);
 gpio_set_dir(18,GPIO_IN);
 //gpio_pull_up(18); // added since thin sensor needs a pullup, remove for round sensor
 gpio_set_irq_enabled_with_callback(18,0x01,1,senseitr);  // switched event masks from high 0x02 to low 0x01



// 1. Initialise the HX711
hx711_init(
    &hx,
    11, // Pico GPIO pin connected to HX711's clock pin
    10, // Pico GPIO pin connected to HX711's data pin
    pio0, // the RP2040 PIO to use (either pio0 or pio1)
    &hx711_noblock_program, // the state machine program
    &hx711_noblock_program_init
    ); // the state machine program init function



hx711_set_power(&hx, hx711_pwr_up);


// test vals
mass_unit_t scaleUnit = mass_g;
int32_t refUnit = -432;
int32_t offset = -367539;

scale_init(
    &sc,
    &hx, // pass a pointer to the hx711_t
    scaleUnit,
    refUnit,
    offset);
scale_options_t opt = SCALE_DEFAULT_OPTIONS;
scale_zero(&sc, &opt);

//max weight
mass_init(&maxweightstruct, mass_g,0); // init as grams & set as 0 g
mass_t mass;
uint16_t result; // moved out of loop, delete later??
gpio_init(21); //blue led on
gpio_set_dir(21,GPIO_OUT);

gpio_init(20); //init amber led
gpio_set_dir(20,GPIO_OUT);

// sd section
FATFS fs;
FIL fil;
FRESULT fr; 
bool sd_ready = false;
sleep_ms(5000);
//initialize sd
if(!sd_init_driver()){ 
    gpio_put(21,1); // turn on blue led // REMOVE LATER
    printf("SD driver Init Failed");
}else {
    fr = f_mount(&fs, "0:", 0); // Filesystem Mount
    if (fr != FR_OK){
    gpio_put(21,1); // turn on blue led /// REMOVE LATER
    printf("SD Filesystem Mount Fail");
    }else {
        fr = f_open(&fil, filename, FA_OPEN_APPEND | FA_WRITE); // File Open
        if (fr == FR_OK || fr == FR_EXIST) {
            sd_ready = true; // SD card is ready to use
        } else {
            gpio_put(21,1); // turn on blue led /// REMOVE LATER
            printf("Failed to open file: %s\n", FRESULT_str(fr));
            //panic("f_open(%s) error: %s (%d)\n", filename, FRESULT_str(fr), fr); // panic might be stopping code, we'll comment it out for now
            
            

        }
        
        }
    }   


initweightsetup(mass,opt); // call function for initial setup

while(1)
{
//waterstatus =  gpio_get(18);

   
    const float conversion_factor = 3.3f / (1 << 12);
        result = adc_read();
        printf(" %f \n", result * conversion_factor);// remove later for datalogging (I think this is for the motor current feedback)
        //printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
        
    
    
 // scale weight test remove later
if(scale_weight(&sc, &mass, &opt)) {
 
    // mass will contain the weight on the scale obtanined and interpreted
    // according to the given options and be in the unit defined by the
    // mass_unit_t 'scaleUnit' variable above
    //
    // you can now:
 
    // get the weight as a numeric value according to the mass_unit_t
    double val;
    mass_get_value(&mass, &val);
    
    // convert the mass to a string
    char buff[MASS_TO_STRING_BUFF_SIZE];
    mass.ug = mass.ug * -1; // invert values
    mass_to_string(&mass, buff);
    //printf("%s\n", buff);
    
    
    mass.ug = mass.ug /1000000; // wonky divider to make values match
    datain = mass.ug;
    printf("mass: %f\n",mass.ug);// for datalogging delete later

    //try polling for if curreweight ==  maxweight to set blue light here.

    
    // weight thingy
    if(mass.ug > maxweightstruct.ug && mass.ug - maxweightstruct.ug <= maxweightstruct.ug * .05 ) // current mass greater than max weight && add reasonable increase threshold so that anomalies can be ignored (5%)
    {
        
       maxweightstruct.ug = mass.ug;
       printf("new maxweight : %f\n", maxweightstruct.ug);
      
    }
    else if(mass.ug * 1.3 < maxweightstruct.ug && gpio_get(18) != false  && mass.ug > 15 /* || pumptomaxweightflag true && wait if levelsense tripped timer is complete is true*/ ) // greater than 150 grams // changed pin 18 to != for npn sensor
    {
      bool pumptomax = true;
       mass_t lowestweight;
       lowestweight.ug = mass.ug; // used to get weight in water used (IF DOESNT WORK CHANGE INT TO MASS_T)
       mass_t highestweight;

        while (pumptomax == true && mass.ug > 15) 
        {
        gpio_put(14,1); // turns on motor
        gpio_put(20,1);


       if(scale_weight(&sc, &mass, &opt)) { // gets weight
        double val;
        mass_get_value(&mass, &val);
        char buff[MASS_TO_STRING_BUFF_SIZE];
        mass.ug = mass.ug * -1; // invert values
        mass_to_string(&mass, buff);
        mass.ug = mass.ug /1000000; // wonky divider to make values match
        datain = mass.ug;
        }
        printf("mass : %f\n",mass.ug); // test delete later
        
        if (sd_ready) // only save to sd if sd gets init
        {
        if (f_printf(&fil, "%f,\n",mass.ug) < 0) { // write to sd
        printf("f_printf failed\n");
        } else {
            fr = f_sync(&fil); // sync file.
            if (fr != FR_OK) {
                // f_sync failed
                printf("f_sync failed with error code %d\n", fr);
             }
        }
        }

        if ( mass.ug >= maxweightstruct.ug /*add range of acceptable values*/)
        {
            pumptomax = false;
            gpio_put(14,0); // turn off pump
            gpio_put(20,0); // turn off amber led
          
            // This segment is depreciated water runout calculation/ newer RTOS version is replacing this
            /*
            highestweight.ug = mass.ug; // used to get difference for water used CHANGE TO MASS_T IF DOESNT WORK
                // do difference of water to get water used
                waterused.ug = highestweight.ug - lowestweight.ug;
                printf("water used : %f\n", waterused.ug);
                totalwateravailable.ug = totalwateravailable.ug - waterused.ug;
                printf("water left : %f\n", totalwateravailable.ug);
                if (totalwateravailable.ug <= 0)
                {
                    gpio_put(21,1); // turn on blue led 
                    nowater = true; // bool for empty tank
                }
            */
            break; // break out of while loop
            
        
        }
        }
       
       //  sleep_ms(100);
    }
    else if(gpio_get(14)!=0) // sets pin low only if pin is high
    {
        
        gpio_put(20,0);
        
        gpio_put(14,0);// drive pwm pin low

        // sleep_ms(100);

    }
 
}

sleep_ms(500); // 5 mins instead of 500 for datalogging
/*
//ml
 ei_impulse_result_t impulseresult;
  ei_printf("Edge Impulse standalone inferencing (Raspberry Pi Pico)\n");

    if (sizeof(features) / sizeof(float) != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE)
    {
      ei_printf("The size of your 'features' array is not correct. Expected %d items, but had %u\n",
                EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, sizeof(features) / sizeof(float));
      return 1;
    }
      // the features are stored into flash, and we don't want to load everything into RAM
      signal_t features_signal;
      features_signal.total_length = sizeof(features) / sizeof(features[0]);
      features_signal.get_data = &raw_feature_get_data;

      // invoke the impulse
      EI_IMPULSE_ERROR res = run_classifier(&features_signal, &impulseresult, false);

      ei_printf("run_classifier returned: %d\n", res);

      if (res != 0)
        return 1;

      ei_printf("Predictions (DSP: %d ms., Classification: %d ms., Anomaly: %d ms.): \n",
                impulseresult.timing.dsp, impulseresult.timing.classification, impulseresult.timing.anomaly);

      // print the predictions
      ei_printf("[");
      for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++)
      {
        ei_printf("%.5f", impulseresult.classification[ix].value);
#if EI_CLASSIFIER_HAS_ANOMALY == 1
        ei_printf(", ");
#else
        if (ix != EI_CLASSIFIER_LABEL_COUNT - 1)
        {
          ei_printf(", ");
        }
#endif
      }
#if EI_CLASSIFIER_HAS_ANOMALY == 1
      printf("%.3f", impulseresult.anomaly);
#endif
      printf("]\n");
       // human-readable predictions
        for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
            ei_printf("    %s: %.5f\n", impulseresult.classification[ix].label, impulseresult.classification[ix].value);
        }
    #if EI_CLASSIFIER_HAS_ANOMALY == 1
        ei_printf("    anomaly score: %.3f\n", impulseresult.anomaly);
    #endif
       
        sleep_ms(500);
 //

 */


}


}


