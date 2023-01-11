//#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "pico/time.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/pio.h"
//#include "pico/mutex.h"
#include "extern/pico-scale/include/scale.h"
#include "extern/hx711-pico-c/include/hx711.h"
#include "extern/hx711-pico-c/include/hx711_noblock.pio.h"

//ml libs

#include "edge-impulse-sdk/classifier/ei_run_classifier.h"
#include "model-parameters/model_metadata.h"


//#include "extern/pico-scale/extern/hx711-pico-c/include/hx711_noblock.pio.h"

static int gpiopin = 14; // made global

//scale init

hx711_t hx;
scale_t sc; // scale lib


void on_pwm_wrap() {
   // static int gpiopin = 14; // made global
    static int fade = 120;
    static bool going_up = true;
    // Clear the interrupt flag that brought us here
    pwm_clear_irq(pwm_gpio_to_slice_num(gpiopin));

    if (going_up) {
        ++fade;
        if (fade > 255) {
            fade = 255;
            going_up = false;
        }
    } else {
        --fade;
        if (fade < 120) {
            fade = 120;
            going_up = true;
        }
    }
    // Square the fade value to make the LED's brightness appear more linear
    // Note this range matches with the wrap value
    pwm_set_gpio_level(gpiopin, fade * fade);
}

// sensor interrupt

void senseitr(uint , uint32_t )
{
 //gpio_put(15,1);   // turn off motor
 gpio_put(14,0);
 gpio_put(20,0); // turn off amber led
}


// weight calc


mass_t maxweightstruct; // struct for maxweight

// motor pwm

int main()
{
 bool waterstatus = false;
 stdio_init_all();
 gpio_init(25); //onboard led
 gpio_set_dir(25,GPIO_OUT);
 gpio_init(15); // pwm pin 1enable
 gpio_init(14);  
 //gpio_set_function(14, GPIO_FUNC_PWM);
 gpio_set_dir(14,GPIO_OUT); // remove later
 gpio_set_dir(15,GPIO_OUT);

 /*
 uint slicenum = pwm_gpio_to_slice_num(14);
 pwm_clear_irq(slicenum); //clear pin interrupts
 
 pwm_set_irq_enabled(slicenum, true); // enables interrupts
 irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
 irq_set_enabled(PWM_IRQ_WRAP, true);
 //pwm_set_wrap(slicenum,500);
 //pwm_set_chan_level(slicenum, PWM_CHAN_A,500); // duty cycle = # / wrap point
// gpio_set_dir(14,GPIO_OUT); 
// pwm_set_enabled(slicenum, true);
pwm_config config = pwm_get_default_config();
    // Set divider, reduces counter clock to sysclock/this value
    pwm_config_set_clkdiv(&config, 32.f);
    // Load the configuration into our PWM slice, and set it running.
    pwm_init(slicenum, &config, false); // starts off
*/
adc_init();// enable adc

adc_gpio_init(26);
   
 adc_select_input(0); // adc on pin 26

    gpio_put(25,1);
    
    gpio_put(15,0); // starts motor
    //gpio_put(14,1);  IGNORE PWM DISABLE

    //pwm_set_gpio_level(gpiopin, 1); // stops motor???

// level sense
 gpio_init(18);
 gpio_set_dir(18,GPIO_IN);
 gpio_set_irq_enabled_with_callback(18,0x02,1,senseitr);



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
uint16_t result; // moved out of loop
gpio_init(21); //blue led on
gpio_set_dir(21,GPIO_OUT);
gpio_put(21,1);

gpio_init(20); //init amber led
gpio_set_dir(20,GPIO_OUT);


while(1)
{
//waterstatus =  gpio_get(18);

   
    const float conversion_factor = 3.3f / (1 << 12);
        result = adc_read();
        
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
    mass.ug = mass.ug * -1; // invert
    mass_to_string(&mass, buff);
    //printf("%s\n", buff);
    

    mass.ug = mass.ug /1000000; // wonky divider to make values match
    printf("%f\n",mass.ug);// for datalogging delete later
    // weight thingy
    if(mass.ug > maxweightstruct.ug) // current mass greater than max weight
    {
       maxweightstruct.ug = mass.ug;
        //printf("new maxweight : %f\n", maxweightstruct.ug);
    }
    if(mass.ug * 1.3 < maxweightstruct.ug && gpio_get(18) == false && mass.ug > 10) // greater than 150 grams
    {
        
        
        gpio_put(14,1); // turns on motor
        gpio_put(20,1);
    }
    else
    {
        gpio_put(20,0);
        
        gpio_put(14,0);// drive pwm pin low
    }
 
}

sleep_ms(500); // 5 mins instead of 500 for datalogging
}


}
