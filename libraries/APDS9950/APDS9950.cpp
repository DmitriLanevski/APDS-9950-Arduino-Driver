 #include <Arduino.h>
 #include <Wire.h>
 
 #include "APDS9950.h"
 /**
	* @brief Constructor - Instantiates APDS9950 object
*/
APDS9950::APDS9950()
{

}

/**
	* @brief Destructor
*/
APDS9950::~APDS9950()
{
	
}
/**
	* @brief Configures I2C communications and initializes registers to defaults
	*
	* @return True if initialized successfully. False otherwise.
	*/
	bool APDS9950::init()
	{
    uint8_t id;
	
    /* Initialize I2C */
    Wire.begin();
	
    /* Read ID register and check against known values for APDS-9960 */
    if( !wireReadDataByte(APDS9950_ID, id) ) {
	return false;
    }
    if( !(id == APDS9950_ID_1 || id == APDS9950_ID_2) ) {
	return false;
    }
	
    /* Set ENABLE register to 0 (disable all features) */
    if( !setMode(ALL, OFF) ) {
	return false;
    }
    
	#if 0
    /* Gesture config register dump */
    uint8_t reg;
    uint8_t val;
	
    for(reg = 0x00; reg <= 0xAF; reg++) {
	if( (reg != 0x02) && \
	(reg != 0x0A) && \
	(reg != 0x11) && \
	(reg != 0xA8) && \
	(reg != 0xAC) && \
	(reg != 0xAD) )
	{
	wireReadDataByte(reg, val);
	Serial.print(reg, HEX);
	Serial.print(": 0x");
	Serial.println(val, HEX);
	}
    }
	
    for(reg = 0xE4; reg <= 0xE7; reg++) {
	wireReadDataByte(reg, val);
	Serial.print(reg, HEX);
	Serial.print(": 0x");
	Serial.println(val, HEX);
    }
	#endif
	
    return true;
	}
 
 /*******************************************************************************
 * Public methods for controlling the APDS-9950
 ******************************************************************************/

/**
 * @brief Reads and returns the contents of the ENABLE register
 *
 * @return Contents of the ENABLE register. 0xFF if error.
 */
uint8_t APDS9950::getMode()
{
	uint8_t enable_value;
	
	Wire.requestFrom(APDS9950_I2C_ADDR, 1);
    while (Wire.available()) {
        enable_value = Wire.read();
    }

    return enable_value;
}

/**
 * @brief Enables or disables a feature in the APDS-9950
 *
 * @param[in] mode which feature to enable
 * @param[in] enable ON (1) or OFF (0)
 * @return True if operation success. False otherwise.
 */
bool APDS9950::setMode(uint8_t mode, uint8_t enable)
{
    uint8_t reg_val;

    /* Read current ENABLE register */
    reg_val = getMode();
    if( reg_val == ERROR ) {
        return false;
    }
    
    /* Change bit(s) in ENABLE register */
    enable = enable & 0x01;
    if( mode >= 0 && mode <= 6 ) {
        if (enable) {
            reg_val |= (1 << mode);
        } else {
            reg_val &= ~(1 << mode);
        }
    } else if( mode == ALL ) {
        if (enable) {
            reg_val = 0x7F;
        } else {
            reg_val = 0x00;
        }
    }
        
    /* Write value back to ENABLE register */
    if( !wireWriteDataByte(APDS9950_ENABLE, reg_val) ) {
        return false;
    }
        
    return true;
}

/**
 * Turn the APDS-9950 on
 *
 * @return True if operation successful. False otherwise.
 */
bool APDS9950::enablePower()
{
    if( !setMode(POWER, 1) ) {
        return false;
    }
    
    return true;
}

/**
 * Turn the APDS-9950 off
 *
 * @return True if operation successful. False otherwise.
 */
bool APDS9950::disablePower()
{
    if( !setMode(POWER, 0) ) {
        return false;
    }
    
    return true;
}

/*******************************************************************************
 * Raw I2C Reads and Writes
 ******************************************************************************/

/**
 * @brief Writes a single byte to the I2C device (no register)
 *
 * @param[in] val the 1-byte value to write to the I2C device
 * @return True if successful write operation. False otherwise.
 */
bool APDS9950::wireWriteByte(uint8_t val)
{
    Wire.beginTransmission(APDS9950_I2C_ADDR);
    Wire.write(val);
    if( Wire.endTransmission() != 0 ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Writes a single byte to the I2C device and specified register
 *
 * @param[in] reg the register in the I2C device to write to
 * @param[in] val the 1-byte value to write to the I2C device
 * @return True if successful write operation. False otherwise.
 */
bool APDS9950::wireWriteDataByte(uint8_t reg, uint8_t val)
{
    Wire.beginTransmission(APDS9950_I2C_ADDR);
    Wire.write(reg);
    Wire.write(val);
    if( Wire.endTransmission() != 0 ) {
        return false;
    }

    return true;
}

/**
 * @brief Writes a block (array) of bytes to the I2C device and register
 *
 * @param[in] reg the register in the I2C device to write to
 * @param[in] val pointer to the beginning of the data byte array
 * @param[in] len the length (in bytes) of the data to write
 * @return True if successful write operation. False otherwise.
 */
bool APDS9950::wireWriteDataBlock(  uint8_t reg, 
                                        uint8_t *val, 
                                        unsigned int len)
{
    unsigned int i;

    Wire.beginTransmission(APDS9950_I2C_ADDR);
    Wire.write(reg);
    for(i = 0; i < len; i++) {
        Wire.beginTransmission(val[i]);
    }
    if( Wire.endTransmission() != 0 ) {
        return false;
    }

    return true;
}

/**
 * @brief Reads a single byte from the I2C device and specified register
 *
 * @param[in] reg the register to read from
 * @param[out] the value returned from the register
 * @return True if successful read operation. False otherwise.
 */
bool APDS9950::wireReadDataByte(uint8_t reg, uint8_t &val)
{
    
    /* Indicate which register we want to read from */
    if (!wireWriteByte(reg)) {
        return false;
    }
    
    /* Read from register */
    Wire.requestFrom(APDS9950_I2C_ADDR, 1);
    while (Wire.available()) {
        val = Wire.read();
    }

    return true;
}

/**
 * @brief Reads a block (array) of bytes from the I2C device and register
 *
 * @param[in] reg the register to read from
 * @param[out] val pointer to the beginning of the data
 * @param[in] len number of bytes to read
 * @return Number of bytes read. -1 on read error.
 */
int APDS9950::wireReadDataBlock(   uint8_t reg, 
                                        uint8_t *val, 
                                        unsigned int len)
{
    unsigned char i = 0;
    
    /* Indicate which register we want to read from */
    if (!wireWriteByte(reg)) {
        return -1;
    }
    
    /* Read block data */
    Wire.requestFrom(APDS9950_I2C_ADDR, len);
    while (Wire.available()) {
        if (i >= len) {
            return -1;
        }
        val[i] = Wire.read();
        i++;
    }

    return i;
}