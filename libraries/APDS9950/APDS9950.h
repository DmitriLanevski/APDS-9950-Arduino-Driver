/**
 * @file    SparkFun_APDS-9950.h
 * @brief   Library for the SparkFun APDS-9950 breakout board
 * @author  Shawn Hymel (SparkFun Electronics)
 *
 * @copyright	This code is public domain but you buy me a beer if you use
 * this and we meet someday (Beerware license).
 *
 * This library interfaces the Avago APDS-9950 to Arduino over I2C. The library
 * relies on the Arduino Wire (I2C) library. to use the library, instantiate an
 * APDS9950 object, call init(), and call the appropriate functions.
 */
 
#ifndef APDS9950_H
#define APDS9950_H

#include <Arduino.h>

/* Debug */
#define DEBUG                   0

/* APDS-9950 I2C address */
#define APDS9950_I2C_ADDR       0x39

/* Gesture parameters */
#define GESTURE_THRESHOLD_OUT   10
#define GESTURE_SENSITIVITY_1   50
#define GESTURE_SENSITIVITY_2   20

/* Error code for returned values */
#define ERROR                   0xFF

/* Acceptable device IDs */
#define APDS9950				0x12


/* Misc parameters */
#define FIFO_PAUSE_TIME         30      // Wait period (ms) between FIFO reads

/* APDS-9950 register addresses */
#define APDS9950_ENABLE         0x00
#define APDS9950_ATIME          0x01
#define APDS9950_WTIME          0x03
#define APDS9950_AILTL          0x04
#define APDS9950_AILTH          0x05
#define APDS9950_AIHTL          0x06
#define APDS9950_AIHTH          0x07

#define APDS9950_PILT           0x89
#define APDS9950_PIHT           0x8B

#define APDS9950_PILTL          0x08
#define APDS9950_PILTH          0x09
#define APDS9950_PIHTL          0x0A
#define APDS9950_PIHTH          0x0B
#define APDS9950_PERS           0x0C
#define APDS9950_CONFIG         0x0D
#define APDS9950_PPULSE         0x0E
#define APDS9950_CONTROL        0x0F
#define APDS9950_ID             0x12
#define APDS9950_STATUS         0x13
#define APDS9950_CDATAL         0x04
#define APDS9950_CDATAH         0x05
#define APDS9950_RDATAL         0x16
#define APDS9950_RDATAH         0x17
#define APDS9950_GDATAL         0x18
#define APDS9950_GDATAH         0x19
#define APDS9950_BDATAL         0x1A
#define APDS9950_BDATAH         0x1B

#define APDS9950_PDATA          0x1C

#define APDS9950_PDATAL         0x1C
#define APDS9950_PDATAH         0x1D
#define APDS9950_POFFSET_UR     0xD
#define APDS9950_POFFSET_DL     0x9E
#define APDS9950_CONFIG3        0x9F
#define APDS9950_GPENTH         0xA0
#define APDS9950_GEXTH          0xA1
#define APDS9950_GCONF1         0xA2
#define APDS9950_GCONF2         0xA3
#define APDS9950_GOFFSET_U      0xA4
#define APDS9950_GOFFSET_D      0xA5
#define APDS9950_GOFFSET_L      0xA7
#define APDS9950_GOFFSET_R      0xA9
#define APDS9950_GPULSE         0xA6
#define APDS9950_GCONF3         0xAA
#define APDS9950_GCONF4         0xAB
#define APDS9950_GFLVL          0xAE
#define APDS9950_GSTATUS        0xAF
#define APDS9950_IFORCE         0xE4
#define APDS9950_PICLEAR        0xE5
#define APDS9950_CICLEAR        0xE6
#define APDS9950_AICLEAR        0xE7
#define APDS9950_GFIFO_U        0xFC
#define APDS9950_GFIFO_D        0xFD
#define APDS9950_GFIFO_L        0xFE
#define APDS9950_GFIFO_R        0xFF

/* Bit fields */
#define APDS9950_PON            0b00000001
#define APDS9950_AEN            0b00000010
#define APDS9950_PEN            0b00000100
#define APDS9950_WEN            0b00001000
#define APSD9950_AIEN           0b00010000
#define APDS9950_PIEN           0b00100000
#define APDS9950_GEN            0b01000000
#define APDS9950_GVALID         0b00000001

/* On/Off definitions */
#define OFF                     0
#define ON                      1

/* Acceptable parameters for setMode */
#define POWER                   0
#define AMBIENT_LIGHT           1
#define PROXIMITY               2
#define WAIT                    3
#define AMBIENT_LIGHT_INT       4
#define PROXIMITY_INT           5
#define GESTURE                 6
#define ALL                     7

/* LED Drive values */
#define LED_DRIVE_100MA         0
#define LED_DRIVE_50MA          1
#define LED_DRIVE_25MA          2
#define LED_DRIVE_12_5MA        3

/* Proximity Gain (PGAIN) values */
#define PGAIN_1X                0
#define PGAIN_2X                1
#define PGAIN_4X                2
#define PGAIN_8X                3

/* ALS Gain (AGAIN) values */
#define AGAIN_1X                0
#define AGAIN_4X                1
#define AGAIN_16X               2
#define AGAIN_64X               3

/* Gesture Gain (GGAIN) values */
#define GGAIN_1X                0
#define GGAIN_2X                1
#define GGAIN_4X                2
#define GGAIN_8X                3

/* LED Boost values */
#define LED_BOOST_100           0
#define LED_BOOST_150           1
#define LED_BOOST_200           2
#define LED_BOOST_300           3    

/* Gesture wait time values */
#define GWTIME_0MS              0
#define GWTIME_2_8MS            1
#define GWTIME_5_6MS            2
#define GWTIME_8_4MS            3
#define GWTIME_14_0MS           4
#define GWTIME_22_4MS           5
#define GWTIME_30_8MS           6
#define GWTIME_39_2MS           7

/* Default values */
#define DEFAULT_ATIME           0xD6     // 101ms
#define DEFAULT_WTIME           0xF6    // 27ms
#define DEFAULT_PROX_PPULSE     0x87    // 16us, 8 pulses
#define DEFAULT_GESTURE_PPULSE  0x89    // 16us, 10 pulses
#define DEFAULT_POFFSET_UR      0       // 0 offset
#define DEFAULT_POFFSET_DL      0       // 0 offset      
#define DEFAULT_CONFIG1         0x60    // No 12x wait (WTIME) factor
#define DEFAULT_LDRIVE          LED_DRIVE_100MA
#define DEFAULT_PGAIN           PGAIN_4X
#define DEFAULT_AGAIN           AGAIN_4X
#define DEFAULT_PILT            0       // Low proximity threshold
#define DEFAULT_PIHT            50      // High proximity threshold
#define DEFAULT_AILT            0xFFFF  // Force interrupt for calibration
#define DEFAULT_AIHT            0
#define DEFAULT_PERS            0x11    // 2 consecutive prox or ALS for int.
#define DEFAULT_CONFIG2         0x01    // No saturation interrupts or LED boost  
#define DEFAULT_CONFIG3         0       // Enable all photodiodes, no SAI
#define DEFAULT_GPENTH          40      // Threshold for entering gesture mode
#define DEFAULT_GEXTH           30      // Threshold for exiting gesture mode    
#define DEFAULT_GCONF1          0x40    // 4 gesture events for int., 1 for exit
#define DEFAULT_GGAIN           GGAIN_4X
#define DEFAULT_GLDRIVE         LED_DRIVE_100MA
#define DEFAULT_GWTIME          GWTIME_2_8MS
#define DEFAULT_GOFFSET         0       // No offset scaling for gesture mode
#define DEFAULT_GPULSE          0xC9    // 32us, 10 pulses
#define DEFAULT_GCONF3          0       // All photodiodes active during gesture
#define DEFAULT_GIEN            0       // Disable gesture interrupts


    /* Initialization methods */
    uint8_t getMode();
    bool setMode(uint8_t mode, uint8_t enable);
    
    /* Turn the APDS-9950 on and off */
    bool enablePower();
    bool disablePower();
    


    /* Raw I2C Commands */
    bool wireWriteByte(uint8_t val);
    bool wireWriteDataByte(uint8_t reg, uint8_t val);
    bool wireWriteDataBlock(uint8_t reg, uint8_t *val, unsigned int len);
    bool wireReadDataByte(uint8_t reg, uint8_t &val);
    int wireReadDataBlock(uint8_t reg, uint8_t *val, unsigned int len);

#endif