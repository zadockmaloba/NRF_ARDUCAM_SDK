#ifndef DE716617_F52C_40FC_BF39_32819E00751D
#define DE716617_F52C_40FC_BF39_32819E00751D

#include "ArducamSpi.h"

#define arducamSpiBegin()                 arducamSpiBegin()
#define arducamSpiTransfer(val)           arducamSpiTransfer(val) //  SPI communication sends a byte
#define arducamSpiReadBlock(p_val, count) arducamSpiTransferBlock(p_val, count)
#define arducamSpiCsPinHigh(pin)          arducamSpiCsHigh(pin) // Set the CS pin of SPI to high level
#define arducamSpiCsPinLow(pin)           arducamSpiCsLow(pin)  // Set the CS pin of SPI to low level
#define arducamCsOutputMode(pin)          arducamSpiCsOutputMode(pin)
#define arducamDelayMs(val)               arducamDelayMs(val) //  Delay Ms
#define arducamDelayUs(val)               arducamDelayUs(val) // Delay Us

#endif /*__ARDUINOHAL_H*/

#endif /* DE716617_F52C_40FC_BF39_32819E00751D */
