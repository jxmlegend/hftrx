/* $Id$ */
/* board-specific CPU attached signals */
//
// Проект HF Dream Receiver (КВ приёмник мечты)
// автор Гена Завидовский mgs2001@mail.ru
// UA1ARN
//

// Приёмник "Воронёнок". up-conversion,  AD9951 + ADF4001, AD9834

#ifndef ARM_ATSAM3S_CPUSTYLE_V8A_H_INCLUDED
#define ARM_ATSAM3S_CPUSTYLE_V8A_H_INCLUDED 1

//#define HARDWARE_ARM_USEUSART0 1		// USART0: PA5/PA6 pins - WITHUART1HW
#define HARDWARE_ARM_USEUSART1 1		// USART1: PA21/PA22 pins - WITHUART2HW
//#define HARDWARE_ARM_USEUART0 1		// UART0: PA9/PA10 pins - WITHUART1HW
//#define HARDWARE_ARM_USEUART1 1		// UART1: PB2/PB3 pins - WITHUART2HW

//#define WITHUART0HW	1	/* Используется периферийный контроллер последовательного порта #0 */
#define WITHUART1HW	1	/* Используется периферийный контроллер последовательного порта #1 */

//#define WITHUSBHW	1	/* Используется встроенная в процессор поддержка USB */
//#define WITHUSBDEV_VBUSSENSE	1	/* используется предопределенный вывод VBUS_SENSE */
//#define WITHUSBDEV_HSDESC	1	/* Требуется формировать дескрипторы как для HIGH SPEED */

//#define WITHCAT_CDC		1	/* использовать виртуальный последовательный порт на USB соединении */
#define WITHCAT_USART2		1
#define WITHDEBUG_UART2	1
#define WITHMODEM_UART2	1

#define WITHSPI16BIT	1		/* возможно использование 16-ти битных слов при обмене по SPI */
#define WITHSPIHW 		1	/* Использование аппаратного контроллера SPI */
#define WITHSPIHWDMA 	1	/* Использование DMA при обмене по SPI */
//#define WITHSPISW 	1	/* Использование программного управления SPI. */

#define WITHTWIHW 	1	/* Использование аппаратного контроллера TWI (I2C) */
//#define WITHTWISW 	1	/* Использование программного контроллера TWI (I2C) */
#define WITHCPUADCHW 	1	/* использование ADC */

#define LS020_RS_INITIALIZE() \
	do { \
		arm_hardware_pioa_outputs(LS020_RS, LS020_RS); \
		arm_hardware_pioa_only(LS020_RS); \
	} while (0)

#define LS020_RESET_INITIALIZE() \
	do { \
		arm_hardware_pioa_outputs(LS020_RESET, LS020_RESET); \
		arm_hardware_pioa_only(LS020_RESET); \
	} while (0)

#define LS020_RS_SET(v) do { \
		if ((v) != 0) LS020_RS_PORT_S(LS020_RS); \
		else  LS020_RS_PORT_C(LS020_RS); \
	} while (0)

#define LS020_RESET_SET(v) do { \
		if ((v) != 0) LS020_RESET_PORT_S(LS020_RESET); \
		else  LS020_RESET_PORT_C(LS020_RESET); \
	} while (0)

#if LCDMODE_ILI9320 || LCDMODE_S1D13781

	#define LS020_RESET_PORT_S(v)		do { PIOA->PIO_SODR = (v); __DSB(); } while (0)
	#define LS020_RESET_PORT_C(v)		do { PIOA->PIO_CODR = (v); __DSB(); } while (0)
	#define LS020_RESET				PIO_PA8			// D6 signal in HD44760 socket

#elif LCDMODE_UC1608

	// Эти контроллеры требуют RESET и RS, а так же положительный чипселект (формируется на том же выводе что и EE РВ44780
	#define UC1608_CSP_PORT_S(v)		do { PIOA->PIO_SODR = (v); __DSB(); } while (0)
	#define UC1608_CSP_PORT_C(v)		do { PIOA->PIO_CODR = (v); __DSB(); } while (0)
	#define UC1608_CSP 			PIO_PA10		// E signal on HD44780 socket - positive chipselect (same as LCD_STROBE_BIT)
	#define SPI_CSEL255			255				// по этому чипселекту выбираем положительным сигналом

	#define LS020_RESET_PORT_S(v)		do { PIOA->PIO_SODR = (v); __DSB(); } while (0)
	#define LS020_RESET_PORT_C(v)		do { PIOA->PIO_CODR = (v); __DSB(); } while (0)
	#define LS020_RESET			PIO_PA8			// D6 signal in HD44760 socket

	#define LS020_RS_PORT_S(v)		do { PIOA->PIO_SODR = (v); __DSB(); } while (0)
	#define LS020_RS_PORT_C(v)		do { PIOA->PIO_CODR = (v); __DSB(); } while (0)
	#define LS020_RS			PIO_PA9			// D7 signal in HD44760 socket

	#define UC1608_CSP_INITIALIZE() do { \
			arm_hardware_pioa_outputs(UC1608_CSP, 0); \
		} while (0)

#elif LCDMODE_LS020 || LCDMODE_LPH88 || LCDMODE_S1D13781 || LCDMODE_ILI9225 || LCDMODE_ST7735 || LCDMODE_ST7565S || LCDMODE_ILI9163 || LCDMODE_ILI9163

	// Эти контроллеры требуют RESET и RS
	#define LS020_RESET_PORT_S(v)		do { PIOA->PIO_SODR = (v); __DSB(); } while (0)
	#define LS020_RESET_PORT_C(v)		do { PIOA->PIO_CODR = (v); __DSB(); } while (0)
	#define LS020_RESET			PIO_PA8			// D6 signal in HD44760 socket

	#define LS020_RS_PORT_S(v)		do { PIOA->PIO_SODR = (v); __DSB(); } while (0)
	#define LS020_RS_PORT_C(v)		do { PIOA->PIO_CODR = (v); __DSB(); } while (0)
	#define LS020_RS			PIO_PA9			// D7 signal in HD44760 socket

#elif LCDMODE_HD44780 && (LCDMODE_SPI == 0)

	// Выводы подключения ЖКИ индикатора WH2002 или аналогичного HD44780.
	//#define LCD_DATA_PORT			PIOA->PIO_ODSR		// enabled by PIO_OWSR bits can be written was PORTA
	#define LCD_DATA_PORT_S(v)		do { PIOA->PIO_SODR = (v); } while (0)
	#define LCD_DATA_PORT_C(v)		do { PIOA->PIO_CODR = (v); } while (0)
	#define LCD_DATA_INPUT			PIOA->PIO_PDSR

	//#define LCD_DIRECTION_PORT			PIOA->PIO_OSR
	#define LCD_DATA_DIRECTION_S		PIOA->PIO_OER
	#define LCD_DATA_DIRECTION_C		PIOA->PIO_ODR

	// E (enable) bit
	#define LCD_STROBE_DIRECTION_S		PIOA->PIO_OER
	#define LCD_STROBE_DIRECTION_C		PIOA->PIO_ODR
	#define LCD_STROBE_PORT_S(v)		do { PIOA->PIO_SODR = (v); } while (0)
	#define LCD_STROBE_PORT_C(v)		do { PIOA->PIO_CODR = (v); } while (0)

	// RS bit
	#define LCD_RS_DIRECTION_S		PIOA->PIO_OER
	#define LCD_RS_DIRECTION_C		PIOA->PIO_ODR
	#define LCD_RS_PORT_S(v)		do { PIOA->PIO_SODR = (v); } while (0)
	#define LCD_RS_PORT_C(v)		do { PIOA->PIO_CODR = (v); } while (0)

	// WE bit
	#define LCD_WE_DIRECTION_S		PIOA->PIO_OER
	#define LCD_WE_DIRECTION_C		PIOA->PIO_ODR
	#define LCD_WE_PORT_S(v)		do { PIOA->PIO_SODR = (v); } while (0)
	#define LCD_WE_PORT_C(v)		do { PIOA->PIO_CODR = (v); } while (0)

	#define LCD_STROBE_BIT			PIO_PA10
	#define WRITEE_BIT PIO_PA1
	#define ADDRES_BIT PIO_PA0
	#define LCD_DATAS_BITS (PIO_PA9 | PIO_PA8 | PIO_PA7 | PIO_PA6)
	#define LCD_DATAS_BIT_LOW 6		// какой бит данных младший в слове считанном с порта

	#define DISPLAY_BUS_DATA_GET() ((LCD_DATA_INPUT & LCD_DATAS_BITS) >> LCD_DATAS_BIT_LOW) /* получить данные с шины LCD */
	#define DISPLAY_BUS_DATA_SET(v) do { /* выдача данных (не сдвинуьых) */ \
			const portholder_t t = (portholder_t) (v) << LCD_DATAS_BIT_LOW; \
			LCD_DATA_PORT_S(LCD_DATAS_BITS & t); \
			LCD_DATA_PORT_C(LCD_DATAS_BITS & ~ t); \
		} while (0)

	/* инициализация управляющих выходов процессора для управления HD44780 - полный набор выходов */
	#define LCD_CONTROL_INITIALIZE() \
		do { \
			arm_hardware_pioa_outputs(LCD_STROBE_BIT | WRITEE_BIT | ADDRES_BIT, 0); \
		} while (0)
	/* инициализация управляющих выходов процессора для управления HD44780 - WE=0 */
	#define LCD_CONTROL_INITIALIZE_WEEZERO() \
		do { \
			arm_hardware_pioa_outputs(LCD_STROBE_BIT | WRITEE_BIT_ZERO | ADDRES_BIT, 0); \
		} while (0)
	/* инициализация управляющих выходов процессора для управления HD44780 - WE отсутствует - сигнал к индикатору заземлён */
	#define LCD_CONTROL_INITIALIZE_WEENONE() \
		do { \
			arm_hardware_pioa_outputs(LCD_STROBE_BIT | ADDRES_BIT, 0); \
		} while (0)

	#define LCD_DATA_INITIALIZE_READ() \
		do { \
			arm_hardware_pioa_inputs(LCD_DATAS_BITS);	/* переключить порт на чтение с выводов */ \
		} while (0)

	#define LCD_DATA_INITIALIZE_WRITE(v) \
		do { \
			arm_hardware_pioa_outputs(LCD_DATAS_BITS, (v) << LCD_DATAS_BIT_LOW);	/* открыть выходы порта */ \
		} while (0)

#elif LCDMODE_UC1601 || LCDMODE_PCF8535

	//#define WITHTWIHW 	1	/* Использование аппаратного контроллера TWI (I2C) */

#endif

#if WITHENCODER
	// Выводы подключения енкодера

	//#define ENCODER_TARGET_PORT_S			PIOA->PIO_SODR	// was PORTA, now - port for set bits
	//#define ENCODER_TARGET_PORT_C			PIOA->PIO_CODR	// was PORTA, now - port for clear bits
	//#define ENCODER_TARGET_PORT			PIOA->PIO_ODSR

	#define ENCODER_DIRECTION_PORT_S			PIOA->PIO_OER	// was DDRA
	#define ENCODER_DIRECTION_PORT_C			PIOA->PIO_ODR	// was DDRA
	//#define KBD_TARGET_DDR			PIOA->PIO_OSR	// was DDRA

	#define ENCODER_INPUT_PORT			PIOA->PIO_PDSR // was PINA 

	#define ENCODER_BITS (PIO_PA26 | PIO_PA25)
	#define ENCODER_SHIFT 25

	#define ENCODER_INITIALIZE() \
		do { \
			arm_hardware_pioa_inputs(ENCODER_BITS); \
			arm_hardware_pioa_updown(_xMask, ENCODER_BITS, 0); \
			arm_hardware_pioa_onchangeinterrupt(ENCODER_BITS, ENCODER_BITS, ENCODER_BITS, ARM_OVERREALTIME_PRIORITY, TARGETCPU_OVRT); \
		} while (0)

#endif /* WITHENCODER */

/* Распределение битов в ARM контроллерах */
#if WITHCAT

	// CAT control lines
	#define FROMCAT_TARGET_DDR_RTS_C	PIOA->PIO_ODR	// was DDRA
	#define FROMCAT_TARGET_PIN_RTS		PIOA->PIO_PDSR // was PINA 
	#define FROMCAT_BIT_RTS				PIO_PA24	/* сигнал RTS от FT232RL	*/

	/* манипуляция от порта RS-232, сигнал PPS от GPS/GLONASS/GALILEO модуля */
	#define FROMCAT_TARGET_DDR_DTR_C	PIOA->PIO_ODR	// was DDRA
	#define FROMCAT_TARGET_PIN_DTR		PIOA->PIO_PDSR // was PINA 
	#define FROMCAT_BIT_DTR				PIO_PA27	/* сигнал DTR от FT232RL	*/

	/* манипуляция от порта RS-232 */
	#define FROMCAT_RTS_INITIALIZE() \
		do { \
			arm_hardware_pioa_inputs(FROMCAT_BIT_RTS); \
			arm_hardware_pioa_updown(_xMask, FROMCAT_BIT_RTS, 0); \
		} while (0)

	/* переход на передачу от порта RS-232 */
	#define FROMCAT_DTR_INITIALIZE() \
		do { \
			arm_hardware_pioa_inputs(FROMCAT_BIT_DTR); \
			arm_hardware_pioa_updown(_xMask, FROMCAT_BIT_DTR, 0); \
		} while (0)

	/* сигнал PPS от GPS/GLONASS/GALILEO модуля */
	#define NMEA_INITIALIZE() \
		do { \
			arm_hardware_pioa_inputs(FROMCAT_BIT_DTR); \
			arm_hardware_pioa_onchangeinterrupt(FROMCAT_BIT_DTR, FROMCAT_BIT_DTR, FROMCAT_BIT_DTR, ARM_SYSTEM_PRIORITY); \
		} while (0)

#endif

#if WITHTX

	// txpath outputs

	#define TXPATH_TARGET_DDR_S			PIOA->PIO_OER	// was DDRA
	//#define TXPATH_TARGET_DDR_C		PIOA->PIO_ODR	// was DDRA
	#define TXPATH_TARGET_PORT_S(v)		do { PIOA->PIO_SODR = (v); __DSB(); } while (0)
	#define TXPATH_TARGET_PORT_C(v)		do { PIOA->PIO_CODR = (v); __DSB(); } while (0)

	// Управление передатчиком - сигналы TXPATH_ENABLE (PA11) и TXPATH_ENABLE_CW (PA10) - активны при нуле на выходе.
	#define TXPATH_BIT_ENABLE_SSB		PIO_PA16
	#define TXPATH_BIT_ENABLE_CW		PIO_PA23
	#define TXPATH_BITS_ENABLE	(TXPATH_BIT_ENABLE_SSB | TXPATH_BIT_ENABLE_CW)

	// Подготовленные управляющие слова
	#define TXGFV_RX		0
	#define TXGFV_TRANS		0			// переход между режимами приёма и передачи
	#define TXGFV_TX_SSB	TXPATH_BIT_ENABLE_SSB
	#define TXGFV_TX_CW		TXPATH_BIT_ENABLE_CW
	#define TXGFV_TX_AM		TXPATH_BIT_ENABLE_CW
	#define TXGFV_TX_NFM	TXPATH_BIT_ENABLE_CW

	// Управление передатчиком - сигналы TXPATH_ENABLE (PA11) и TXPATH_ENABLE_CW (PA10) - активны при нуле на выходе.
	// Установка начального стстояния выходов
	#define TXPATH_INITIALIZE() \
	do { \
		arm_hardware_pioa_opendrain(TXPATH_BITS_ENABLE, TXPATH_BITS_ENABLE); \
	} while (0)

	// PTT input

	#define PTT_TARGET_PIN				(PIOA->PIO_PDSR) // was PINA 
	#define PTT_BIT_PTT					PIO_PA31

	#define HARDWARE_GET_PTT() ((PTT_TARGET_PIN & PTT_BIT_PTT) == 0)
	#define PTT_INITIALIZE() \
		do { \
			arm_hardware_pioa_inputs(PTT_BIT_PTT); \
			arm_hardware_pioa_updown(PTT_BIT_PTT, PTT_BIT_PTT, 0); \
		} while (0)

#endif /* WITHTX */

#if WITHELKEY
	// Electronic key inputs

	#define ELKEY_TARGET_PIN			(PIOA->PIO_PDSR) // was PINA 
	#define ELKEY_BIT_LEFT				PIO_PA28
	#define ELKEY_BIT_RIGHT				PIO_PA29

	#define HARDWARE_GET_ELKEY_LEFT() 	((ELKEY_TARGET_PIN & ELKEY_BIT_LEFT) == 0)
	#define HARDWARE_GET_ELKEY_RIGHT() 	((ELKEY_TARGET_PIN & ELKEY_BIT_RIGHT) == 0)


	#define ELKEY_INITIALIZE() \
		do { \
			arm_hardware_pioa_inputs(ELKEY_BIT_LEFT | ELKEY_BIT_RIGHT); \
			arm_hardware_pioa_updown(ELKEY_BIT_LEFT | ELKEY_BIT_RIGHT, ELKEY_BIT_LEFT | ELKEY_BIT_RIGHT, 0); \
		} while (0)
#endif

// SPI control pins

#define SPI_TARGET_MOSI_PORT_S(v)	do { PIOA->PIO_SODR = (v); __DSB(); } while (0)
#define SPI_TARGET_MOSI_PORT_C(v)	do { PIOA->PIO_CODR = (v); __DSB(); } while (0)
#define SPI_TARGET_MISO_PORT_S(v)	do { PIOA->PIO_SODR = (v); __DSB(); } while (0)
#define SPI_TARGET_MISO_PORT_C(v)	do { PIOA->PIO_CODR = (v); __DSB(); } while (0)
#define SPI_TARGET_SCLK_PORT_S(v)	do { PIOA->PIO_SODR = (v); __DSB(); } while (0)
#define SPI_TARGET_SCLK_PORT_C(v)	do { PIOA->PIO_CODR = (v); __DSB(); } while (0)

#define SPI_TARGET_MOSI_DDR_S			(PIOA->PIO_OER)
#define SPI_TARGET_MOSI_DDR_C			(PIOA->PIO_ODR)
#define SPI_TARGET_MISO_DDR_S			(PIOA->PIO_OER)
#define SPI_TARGET_MISO_DDR_C			(PIOA->PIO_ODR)
#define SPI_TARGET_SCLK_DDR_S			(PIOA->PIO_OER)
#define SPI_TARGET_SCLK_DDR_C			(PIOA->PIO_ODR)

// биты вывода адреса чипселект дешифратора
#define SPI_ADDRESS_PORT_S(v)		do { PIOA->PIO_SODR = (v); __DSB(); } while (0)
#define SPI_ADDRESS_PORT_C(v)		do { PIOA->PIO_CODR = (v); __DSB(); } while (0)
#define SPI_ADDRESS_DDR_S			(PIOA->PIO_OER)	// was DDRA
#define SPI_ADDRESS_DDR_C			(PIOA->PIO_ODR)	// was DDRA

#define SPI_IOUPDATE_PORT_S(v)	do { PIOA->PIO_SODR = (v); __DSB(); } while (0)
#define SPI_IOUPDATE_PORT_C(v)	do { PIOA->PIO_CODR = (v); __DSB(); } while (0)
#define SPI_IOUPDATE_BIT PIO_PA5

#define SPI_NAEN_PORT_S(v)		do { PIOA->PIO_SODR = (v); __DSB(); } while (0)
#define SPI_NAEN_PORT_C(v)		do { PIOA->PIO_CODR = (v); __DSB(); } while (0)
#define SPI_NAEN_DDR_S			(PIOA->PIO_OER)	// was DDRA
#define SPI_NAEN_DDR_C			(PIOA->PIO_ODR)	// was DDRA

#define SPI_NAEN_BIT PIO_PA11A_NPCS0	// PIO_PA11
#define SPI_ALLCS_BITS	0		// требуется для указания того, что работа с прямым выбором CS (без дешифратора) не требуется

#define SPI_A0 (PIO_PA0)			// биты адреса для дешифратора SPI
#define SPI_A1 (PIO_PA1)
#define SPI_A2 (PIO_PA2)

/* инициализация лиий выбора периферийных микросхем */
#define SPI_ALLCS_INITIALIZE() \
	do { \
		/* arm_hardware_pioa_outputs(SPI_ALLCS_BITS, SPI_ALLCS_BITS); */ \
	} while (0)
/* инициализация сигналов управлдения дешифратором CS */
#define SPI_ADDRESS_AEN_INITIALIZE() \
	do { \
		/* arm_hardware_pioa_outputs(SPI_AEN_BIT | SPI_ADDRESS_BITS, 0);  */\
	} while (0)
/* инициализация сигналов управлдения дешифратором CS */
#define SPI_ADDRESS_NAEN_INITIALIZE() \
	do { \
		arm_hardware_pioa_outputs(SPI_NAEN_BIT | SPI_ADDRESS_BITS, SPI_NAEN_BIT); \
	} while (0)
/* инициализация сигнала IOUPDATE на DDS */
/* начальное состояние = 1 */
#define SPI_IOUPDATE_INITIALIZE() \
	do { \
		arm_hardware_pioa_outputs(SPI_IOUPDATE_BIT, SPI_IOUPDATE_BIT); \
	} while (0)
/* инициализация сигнала IOUPDATE на DDS */
/* начальное состояние = 0 */
#define SPI_IORESET_INITIALIZE() \
	do { \
		/* arm_hardware_pioa_outputs(SPI_IORESET_BIT, 0); */ \
	} while (0)


#define	SPI_SCLK_BIT			PIO_PA14A_SPCK	// бит, через который идет синхронизация SPI
#define	SPI_MOSI_BIT			PIO_PA13A_MOSI	// бит, через который идет вывод (или ввод в случае двунаправленного SPI).

#define SPI_TARGET_MISO_PIN		PIOA->PIO_PDSR // was PINA 
#define	SPI_MISO_BIT			PIO_PA12A_MISO	// бит, через который идет ввод с SPI.

#define SPIIO_INITIALIZE() do { \
		arm_hardware_pioa_outputs(SPI_MOSI_BIT | SPI_SCLK_BIT, SPI_MOSI_BIT | SPI_SCLK_BIT); \
		arm_hardware_pioa_inputs(SPI_MISO_BIT); \
		arm_hardware_pioa_only(SPI_MOSI_BIT | SPI_SCLK_BIT | SPI_MISO_BIT); /* disconnect from peripherials */ \
	} while (0)

#if WITHSPIHW

	#define HARDWARE_SPI_CONNECT() do { \
			arm_hardware_pioa_peripha(SPI_MOSI_BIT | SPI_SCLK_BIT | SPI_MISO_BIT);	/* PIO disable */ \
		} while (0)
	#define HARDWARE_SPI_DISCONNECT() do { \
			arm_hardware_pioa_only(SPI_MOSI_BIT | SPI_SCLK_BIT | SPI_MISO_BIT);	/* PIO enable */ \
		} while (0)

	#define HARDWARE_SPI_CONNECT_MOSI() do { \
			arm_hardware_pioa_peripha(SPI_MOSI_BIT);	/* PIO disable for MOSI bit (SD CARD read support) */ \
		} while (0)
	#define HARDWARE_SPI_DISCONNECT_MOSI() do { \
			arm_hardware_pioa_only(SPI_MOSI_BIT);	/* PIO enable for MOSI bit (SD CARD read support)  */ \
		} while (0)

#endif /* WITHSPIHW */

#define SIDETONE_TARGET_PORT_S	PIOA->PIO_SODR	/* Порт процессора, на котором находится вывод тона самоконтроля */
#define SIDETONE_TARGET_PORT_C	PIOA->PIO_CODR	/* Порт процессора, на котором находится вывод тона самоконтроля */
#define SIDETONE_TARGET_DDR_S	PIOA->PIO_OER
#define SIDETONE_TARGET_DDR_C	PIOA->PIO_ODR
#define SIDETONE_TARGET_BIT		PIO_PA15B_TIOA1

#define HARDWARE_SIDETONE_INITIALIZE() do { \
	arm_hardware_pioa_outputs(SIDETONE_TARGET_BIT, 0); \
	arm_hardware_pioa_periphb(SIDETONE_TARGET_BIT); \
	} while (0)
#define HARDWARE_SIDETONE_CONNECT() do { \
	arm_hardware_pioa_periphb(SIDETONE_TARGET_BIT);  /* pin connected to timer */ \
	} while (0)
#define HARDWARE_SIDETONE_DISCONNECT() do { \
	arm_hardware_pioa_only(SIDETONE_TARGET_BIT);  /* pin connected to PIOA */ \
	} while (0)


#if 1 // WITHTWISW
//#if CPUSTYLE_ATMEGA
	//#define TARGET_TWI_PORT PORTC
	//#define TARGET_TWI_DDR DDRC
	//#define TARGET_TWI_TWCK	(1U << PC0)
	//#define TARGET_TWI_TWD	(1U << PC1)
//#elif CPUSTYLE_ARM
	#define TARGET_TWI_TWCK_PORT_C(v)	do { PIOA->PIO_CODR = (v); __DSB(); } while (0)
	#define TARGET_TWI_TWCK_PORT_S(v)	do { PIOA->PIO_SODR = (v); __DSB(); } while (0)
	#define TARGET_TWI_TWD_PORT_C(v)	do { PIOA->PIO_CODR = (v); __DSB(); } while (0)
	#define TARGET_TWI_TWD_PORT_S(v)	do { PIOA->PIO_SODR = (v); __DSB(); } while (0)
	#define TARGET_TWI_PIN		(PIOA->PIO_PDSR)
	#define TARGET_TWI_TWCK		PIO_PA4A_TWCK0
	#define TARGET_TWI_TWD		PIO_PA3A_TWD0

	// Инициализация битов портов ввода-вывода для программной реализации I2C
	#define	TWISOFT_INITIALIZE() do { \
			enum { WORKMASK = TARGET_TWI_TWCK | TARGET_TWI_TWD };		/* битовая маска, определяет каким выводом шевелить */ \
			arm_hardware_pioa_opendrain(WORKMASK, WORKMASK);	/* The user must not program TWD and TWCK as open-drain. It is already done by the hardware. */ \
			arm_hardware_pioa_only(WORKMASK); /* disconnect from peripherials */ \
		} while (0) 

	// Инициализация битов портов ввода-вывода для аппаратной реализации I2C
	// присоединение выводов к периферийному устройству
	#define	TWIHARD_INITIALIZE() do { \
			enum { WORKMASK = TARGET_TWI_TWCK | TARGET_TWI_TWD };		/* битовая маска, определяет каким выводом шевелить */ \
			arm_hardware_pioa_peripha(WORKMASK); \
		} while (0) 

//#endif
#endif

#if HARDWARE_ARM_USEUSART0
	#define HARDWARE_UART0_INITIALIZE() do { \
		arm_hardware_pioa_inputs(PIO_PA5A_RXD0); \
		arm_hardware_pioa_outputs(PIO_PA6A_TXD0, PIO_PA6A_TXD0); \
		arm_hardware_pioa_peripha(PIO_PA5A_RXD0 | PIO_PA6A_TXD0); \
		} while (0)
#elif HARDWARE_ARM_USEUSART1
	#define HARDWARE_UART1_INITIALIZE() do { \
		arm_hardware_pioa_inputs(PIO_PA21A_RXD1); \
		arm_hardware_pioa_outputs(PIO_PA22A_TXD1, PIO_PA22A_TXD1); \
		arm_hardware_pioa_peripha(PIO_PA21A_RXD1 | PIO_PA22A_TXD1); \
		} while (0)
#elif HARDWARE_ARM_USEUART0
	#define HARDWARE_UART0_INITIALIZE() do { \
		arm_hardware_pioa_inputs(PIO_PA9A_URXD0); \
		arm_hardware_pioa_outputs(PIO_PA10A_UTXD0, PIO_PA10A_UTXD0); \
		arm_hardware_pioa_peripha(PIO_PA9A_URXD0 | PIO_PA10A_UTXD0); \
		} while (0)
#elif HARDWARE_ARM_USEUART1
	#define HARDWARE_UART1_INITIALIZE() do { \
		arm_hardware_piob_inputs(PIO_PB2A_URXD1); \
		arm_hardware_piob_outputs(PIO_PB3A_UTXD1, PIO_PB3A_UTXD1); \
		arm_hardware_piob_peripha(PIO_PB2A_URXD1 | PIO_PB3A_UTXD1); \
		} while (0)
#endif

	#if KEYBOARD_USE_ADC
		#define HARDWARE_KBD_INITIALIZE() do { \
			} while (0)
	#else
		#define HARDWARE_KBD_INITIALIZE() do { \
			arm_hardware_pioa_inputs(KBD_MASK); \
			} while (0)
	#endif

#endif /* ARM_ATSAM3S_CPUSTYLE_V8A_H_INCLUDED */
