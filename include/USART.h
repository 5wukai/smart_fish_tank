#ifndef __USART_H
#define	__USART_H

#define UART_BUFF_SIZE 100
#define U_SLEEP_TIME 1000000

void Uart1GpioInit(void);
void Uart1Config(void);
void UartTask(const char* data);

#endif /* __USART_H */