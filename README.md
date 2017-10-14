### 1. Koraki, ki so potrebni, da stvar deluje

#### 1.1 Retarget funkcija - omogoči, da se za izpis na konzolo uporabi 
ukaz `printf()` namesto `HAL_UART_Transmit`.

```C
struct __FILE {
	int dummy;
}; //to se doda nekam na vrh


/*RETARGET FUNKCIJA -> PRINTF v source je potrebno dodati tudi 
syscalls.c datoteko - najdeš na githubu*/
void __io_putchar(uint8_t ch) {
	/**
	 * \brief		__io_putchar - A routine to transmit a 
single character out the serial port
	 * \return		void
	 * \param[in]	ch - uint8_t the character to transmit
	 * \author		andreichichak
	 * \date		Oct 16, 2015
	 * \details		This routine assumes that we will be 
using UART2. A timeout value of 1ms (4th parameter)
	 * 				gives a retry if the transmit 
buffer is full when back to back characters are transmitted,
	 * 				avoiding dropping characters.
	 */

	HAL_UART_Transmit(&huart1, &ch, 1, 1);
}

```

Ampak to še ni vse. Zadeva ne deluje, dokler se v **src** mapo ne doda 
še datoteke _syscalls.c_, ki se jo dobi na githubu. S tem prične `**printf**` delovati.

#### 1.2 Izpis FP spremenljivk
Ko `**printf**` deluje, noče izpisovati fp vrednosti. V linker je potrebno vnesti še en 
ukaz, ki omogoči izpis fp spremenljivk

`Project -> Properties -> Linker -> Miscelalneous -> Linker flags:` dodaš  
**-u_printf_float**

S tem deluje tudi izpis FP spremeljivk.

#### 1.3 Autocomplete 
S kombinacijo tipk **CTRL-SPACE** se pojavi seznam vseh funkcij.

naprimer: HAL_ (CTRL-SPACE) pokaže vse funkcije, ki se začnejo s HAL_

### 13.10.2017 ločena tlačni senzor in senzor rel. vlažnosti zraka, vsak 
v svoji c/h parici - enostavno integriranje v main.

##### 14.10.2017 dodan switch za preklop Win/Lin za izpis stopinj 
cellzija. 
