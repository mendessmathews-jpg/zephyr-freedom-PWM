#include <zephyr.h>             // Funções básicas do Zephyr (ex: k_msleep)
#include <device.h>             // API  para obter e usar dispositivos
#include <drivers/gpio.h>       // API para controle de GPIO

#define LED_PORT       "GPIO_1" // Nome do controlador GPIO (label no .pio\build\frdm_kl25z\zephyr\zephyr.dts)
#define LED_VRM        18       // Pino PTB18 onde está o LED vermelho
#define LED_VD       19     
#define SLEEP_TIME_MS  500    // Intervalo de piscar (milissegundos)

typedef enum {
	VERDE,
	AMARELO,
	VERMELHO
} EstadoSemaforo;

void main(void)
{
    const struct device *port = device_get_binding(LED_PORT);

    gpio_pin_configure(port, LED_VD, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure(port, LED_VRM, GPIO_OUTPUT_ACTIVE);
	
	EstadoSemaforo estadoAtual = VERDE;
	
    while (1) {
		switch (estadoAtual) {
			case VERDE:
				// Ligar o led verde e delay
				gpio_pin_set(port, LED_VD, 0);
				k_msleep(4000);
				//DESLIGAR LED VERDE
				gpio_pin_set(port, LED_VD, 1);
				estadoAtual = AMARELO;
				break;
			case AMARELO:
				// Ligar o led amarelo e delay
				gpio_pin_set(port, LED_VD, 0);
				gpio_pin_set(port, LED_VRM, 0);
				k_msleep(3000);
				gpio_pin_set(port, LED_VD, 1);
				gpio_pin_set(port, LED_VRM, 1);
				estadoAtual = VERMELHO;
				break;
			case VERMELHO:
				// Ligar o led vermelho e delay
				gpio_pin_set(port, LED_VRM, 0);
				k_msleep(4000);
				estadoAtual = VERDE;
				gpio_pin_set(port, LED_VRM, 1);
				break;
		}
    }
}