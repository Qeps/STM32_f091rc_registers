/*
 * Ten plik to prosty "most" między biblioteką czujnika LIS3MDL a sprzętem STM32 na płytce.
 * Tutaj deklarujemy funkcje, które inicjalizują czujnik i pozwalają odczytać dane z magnetometru.
 * Kod właściwy jest w lis3mdl_conf.c.
 */

#ifndef LIS3MDL_CONF_H
#define LIS3MDL_CONF_H

#include "lis3mdl.h"
#include "b_l475e_iot01a2_bus.h"   // obsługa I2C/SPI z BSP

#ifdef __cplusplus
extern "C" {
#endif

extern LIS3MDL_Object_t lis3mdl;   // obiekt czujnika

void LIS3MDL_Platform_Init(void);  // inicjalizacja czujnika
void LIS3MDL_Read_Magnetic(void);  // odczyt i wysyłka danych po UART

#ifdef __cplusplus
}
#endif
#endif
