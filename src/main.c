#include <zephyr/kernel.h>            
#include <zephyr/device.h>            
#include <zephyr/drivers/gpio.h>      
#include <pwm_z42.h>              


#define TPM_MODULE 1000        
uint16_t duty_1  = TPM_MODULE/2;  
//uint16_t duty_2  = TPM_MODULE/2;  


int main(void)
{
    pwm_tpm_Init(TPM0, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM);
    pwm_tpm_Ch_Init(TPM0, 0, TPM_PWM_H, GPIOD, 0);
    pwm_tpm_CnV(TPM0, 0, duty_1);
    //pwm_tpm_Ch_Init(TPM0, 5, TPM_PWM_H, GPIOD, 5);
    //pwm_tpm_CnV(TPM0, 5, duty_2);


    for (;;)
    {
    }


    return 0;
}