/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2020-01-06     JiangChenhui    the first version.
 *
 */

#include "gy271.h"
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <string.h>

#define DBG_ENABLE
#define DBG_SECTION_NAME "GY271"
#define DBG_LEVEL DBG_LOG
#define DBG_COLOR
#include <rtdbg.h>

#ifdef PKG_USING_GY271

#define GY271_ADDR 0x1E

static rt_err_t gy271_write_reg(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t data)
{
    rt_uint8_t buf[2];

    buf[0] = reg;
    buf[1] = data;

    if (rt_i2c_master_send(bus, GY271_ADDR, 0, buf, 2) == 2)
        return RT_EOK;
    else
        return -RT_ERROR;
}

static rt_err_t gy271_read_regs(struct rt_i2c_bus_device *bus, uint8_t reg, rt_uint8_t len, rt_uint8_t *buf)
{
    if (rt_i2c_master_send(bus, GY271_ADDR, 0, &reg, 1) == 1)
    {
        if (rt_i2c_master_recv(bus, GY271_ADDR, 0, buf, len) == len)
        {
            return RT_EOK;
        }
        else
        {
            return -RT_ERROR;
        }
    }
    else
    {
        return -RT_ERROR;
    }
}

gy271_device_t gy271_init(const char *i2c_bus_name)
{
    gy271_device_t dev;

    RT_ASSERT(i2c_bus_name);

    dev = rt_calloc(1, sizeof(struct gy271_device));
    if (dev == RT_NULL)
    {
        LOG_E("Can't allocate memory for gy271 device on '%s' ", i2c_bus_name);
        return RT_NULL;
    }

    dev->i2c = rt_i2c_bus_device_find(i2c_bus_name);
    if (dev->i2c == RT_NULL)
    {
        LOG_E("Can't find gy271 device on '%s' ", i2c_bus_name);
        rt_free(dev);
        return RT_NULL;
    }

    dev->lock = rt_mutex_create("mutex_gy271", RT_IPC_FLAG_FIFO);
    if (dev->lock == RT_NULL)
    {
        LOG_E("Can't create mutex for gy271 device on '%s' ", i2c_bus_name);
        rt_free(dev);
        return RT_NULL;
    }

    gy271_write_reg(dev->i2c, 0x02, 0x00);

    return dev;
}

void gy271_deinit(gy271_device_t dev)
{
    RT_ASSERT(dev);

    rt_mutex_delete(dev->lock);

    rt_free(dev);
}

rt_err_t gy271_read_data(gy271_device_t dev,struct gy271_data  *data)
{
    uint8_t buffer[6];

    rt_err_t result;

    RT_ASSERT(dev);

    result = rt_mutex_take(dev->lock, RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        gy271_read_regs(dev->i2c, 0x03, 6, buffer);
        if (buffer[0] & 0x80)
        {
            buffer[0] = 0xFF - buffer[0];
            buffer[1] = 0xFF - buffer[1];
            data->x = buffer[0] * 256 + buffer[1];
            data->x = data->x * -1;
        }
        else
        {
            data->x = buffer[0] * 256 + buffer[1];
        }
        if (buffer[2] & 0x80)
        {
            buffer[2] = 0xFF - buffer[2];
            buffer[3] = 0xFF - buffer[3];
            data->y = buffer[2] * 256 + buffer[3];
            data->y = data->y * -1;
        }
        else
        {
            data->y = buffer[2] * 256 + buffer[3];
        }

        if (buffer[4] & 0x80)
        {
            buffer[4] = 0xFF - buffer[4];
            buffer[5] = 0xFF - buffer[5];
            data->z = buffer[4] * 256 + buffer[5];
            data->z = data->z * -1;
        }
        else
        {
            data->z = buffer[4] * 256 + buffer[5];
        }
        
        data->x = data->x*1000*1.0/2048;
        data->y = data->y*1000*1.0/2048;
        data->z = data->z*1000*1.0/2048;
    }
    else
    {
        return -RT_ERROR;
        LOG_E("The gy271 could not respond data read at this time. Please try again");
    }
    rt_mutex_release(dev->lock);

    return RT_EOK;
}




#endif
