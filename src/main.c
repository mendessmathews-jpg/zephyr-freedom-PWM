#include <zephyr/kernel.h>             
#include <zephyr/device.h>             
#include <zephyr/drivers/gpio.h>      
#include <pwm_z42.h>                


#define TPM_MODULE 1000             

int main(void)
{
    
    pwm_tpm_Init(TPM2, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM);

pwm_tpm_Ch_Init(TPM2, 1, TPM_PWM_H, GPIOB, 19);

pwm_tpm_CnV(TPM2, 1, 0);

    for (;;)
    {
        k_msleep(2000);

        pwm_tpm_CnV(TPM2, 1, 0);

         k_msleep(2000);

        pwm_tpm_CnV(TPM2, 1, 1000);
    
    }

    return 0;
}