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

#define DBG_TAG "sensor.honey.gy271"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SENSOR_GYRO_RANGE_MAX (8)
#define SENSOR_GYRO_RANGE_MIN (-8)

#define PKG_USING_GY271
static struct gy271_device *temp_honey_dev;

static rt_err_t _gy271_init(struct rt_sensor_intf *intf)
{
    temp_honey_dev = gy271_init(intf->dev_name);
    if (temp_honey_dev == RT_NULL)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_size_t _gy271_polling_get_data(rt_sensor_t sensor, struct rt_sensor_data *data)
{
    gy271_data_t mag_data;
    rt_err_t result;
    if(sensor->info.type = RT_SENSOR_CLASS_MAG)
    {
        result = gy271_read_data(temp_honey_dev,&mag_data);
        if(result == RT_EOK)
        {
            data->data.mag.x = mag_data.x;
            data->data.mag.y = mag_data.y;
            data->data.mag.z = mag_data.z;
            data->timestamp = rt_sensor_get_ts();
        }
        else
        {
            LOG_E('gy271 read data error!');
        }
        
    }
    else
    {
        LOG_E("Expect info type is RT_SENSOR_CLASS_mag!");
    }

    return 1;
}

static rt_size_t gy271_fetch_data(struct rt_sensor_device *sensor, void *buf, rt_size_t len)
{
    RT_ASSERT(buf);

    if(sensor->config.mode == RT_SENSOR_MODE_POLLING)
    {
        return _gy271_polling_get_data(sensor, buf);
    }
    else
    {
        return 0;
    }
}

static rt_err_t gy271_control(struct rt_sensor_device *sensor, int cmd, void *args)
{
    rt_err_t result = RT_EOK;

    return result;
}

static struct rt_sensor_ops sensor_ops = 
{
    gy271_fetch_data,
    gy271_control
};

int rt_hw_gy271_init(const char *name,struct rt_sensor_config *cfg)
{
    rt_int8_t result;
    rt_sensor_t sensor_mag = RT_NULL;

#ifdef PKG_USING_GY271

    /* magnetism  sensor register */
    sensor_mag = rt_calloc(1, sizeof(struct rt_sensor_device));
    if(sensor_mag == RT_NULL)
        return -1;
    
    sensor_mag->info.type           = RT_SENSOR_CLASS_MAG;
    sensor_mag->info.vendor         = RT_SENSOR_VENDOR_UNKNOWN;
    sensor_mag->info.model          = "gy271";
    sensor_mag->info.unit           = RT_SENSOR_UNIT_MGAUSS;
    sensor_mag->info.range_max      = SENSOR_GYRO_RANGE_MAX;
    sensor_mag->info.range_min      = SENSOR_GYRO_RANGE_MIN;
    sensor_mag->info.period_min     = 5;

    rt_memcpy(&sensor_mag->config, cfg,sizeof(struct rt_sensor_config));
    sensor_mag->ops = &sensor_ops;

    result = rt_hw_sensor_register(sensor_mag, name, RT_DEVICE_FLAG_RDONLY, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("device register err code: %d", result);
        goto __exit;
    }

#endif
    _gy271_init(&cfg->intf);
    return RT_EOK;

__exit:
    if(sensor_mag)
        rt_free(sensor_mag);
    if(temp_honey_dev)
        gy271_deinit(temp_honey_dev);
    return -RT_ERROR;
}

static int rt_hw_gy271_port(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.dev_name = "i2c1";
    rt_hw_gy271_init("gy271",&cfg);

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_gy271_port);

