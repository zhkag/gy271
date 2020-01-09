/*
* Copyright (c) 2006-2018, RT-Thread Development Team
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date           Author            Notes
* 2020-01-08     JiangChenhui      the first version
*/

#include "sensor_honey_gy271.h"

static rt_err_t sensor_gy271_sample(int argc, char *argv[])
{
    static rt_device_t sensor_dev;         /* 传感器设备句柄 */
    struct rt_sensor_data data;            /* 传感器数据 */

    /* 根据设备名称查找传感器设备，获取设备句柄 */
    sensor_dev = rt_device_find("mag_gy271");
    /* 以只读及轮询模式打开传感器设备 */
    rt_device_open(sensor_dev, RT_DEVICE_FLAG_RDONLY);
    if (rt_device_read(sensor_dev, 0, &data, 1) == 1)
    {
        rt_kprintf("Mag: x:%3dmGa, y:%3dmGa, z:%3dmGa, timestamp:%5d\n", data.data.mag.x, data.data.mag.y, data.data.mag.z, data.timestamp);
    }
    rt_device_close(sensor_dev);

    return RT_EOK;
}

MSH_CMD_EXPORT(sensor_gy271_sample,sensor gy271 sample);

