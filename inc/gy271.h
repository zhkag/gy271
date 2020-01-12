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

#ifndef __GY271_H__
#define __GY271_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

/**
 * @description: gy271 device struct
 * @param {type} 
 * @return: 
 */
struct gy271_device
{
    struct rt_i2c_bus_device *i2c;
    rt_mutex_t lock;
};
typedef struct  gy271_device *gy271_device_t;

struct gy271_data
{
    int x;
    int y;
    int z;
};
typedef struct gy271_data  gy271_data_t;

/**
 * @description: gy271 device init
 * @param i2c bus name  
 * @return: gy271 device handler
 */
gy271_device_t gy271_init(const char *i2c_bus_name);

/**
 * @description: gy271 device deinit
 * @param gy271 device handler 
 * @return: none
 */
void gy271_deinit(gy271_device_t dev);

/**
 * @description: gy271 read data;
 * @param gy271 device, gy271_data struct pointer
 * @return: error code
 */
rt_err_t gy271_read_data(gy271_device_t dev,struct gy271_data  *data);

#endif

