/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-01-08     JiangChenhui      the first version
 */

#ifndef __SENSOR_GYRO_GY271_H__
#define __SENSOR_GYRO_GY271_H__

#include "sensor.h"
#include "gy271.h"

#define GY271_I2C_ADDR 0x1E

int rt_hw_gy271_init(const char *name, struct rt_sensor_config *cfg);

#endif
