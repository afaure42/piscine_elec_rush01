#include "rtc.h"


uint8_t rtc_set_register(uint8_t register_select, uint8_t data)
{
	i2c_start(RTC_ADDRESS, TW_WRITE);
	if (TW_STATUS != TW_MT_SLA_ACK)
	{
		i2c_stop();
		return (1);
	}
	
	i2c_send_byte(&register_select, 1);
	if (TW_STATUS != TW_MT_DATA_ACK)
	{
		i2c_stop();
		return (1);
	}
	
	i2c_send_byte(&data, 1);
	if (TW_STATUS != TW_MT_DATA_ACK)
	{
		i2c_stop();
		return (1);
	}
	
	i2c_stop();
	return (0);
}

uint8_t rtc_get_register(uint8_t register_select, uint8_t *dest)
{
	i2c_start(RTC_ADDRESS, TW_WRITE);
	if (TW_STATUS != TW_MT_SLA_ACK)
	{
		i2c_stop();
		return (1);
	}

	i2c_send_byte(&register_select, 1);
	if (TW_STATUS != TW_MT_DATA_ACK)
	{
		i2c_stop();
		return (1);
	}

	i2c_start(RTC_ADDRESS, TW_READ);
	if (TW_STATUS != TW_MR_SLA_ACK)
	{
		i2c_stop();
		return (1);
	}

	i2c_read_byte(dest, 1);
	if (TW_STATUS != TW_MR_DATA_NACK)
	{
		i2c_stop();
		return (1);
	}

	i2c_stop();
	return (0);
}

rtc_set_time()
