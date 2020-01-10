# API说明

本章介绍gy271 软件包提供的常用 API.

### 初始化函数

```c
gy271_device_t gy271_init(const char *i2c_bus_name);
```

使用指定的i2c总线初始化 gy271, 并返回控制句柄.

| 参数           | 描述                      |
| -------------- | ------------------------- |
| I2c_bus_name   | i2c总线名称               |
| **返回**       | **描述**                  |
| gy271_device_t | gy271_device 结构体的指针 |
| RT_NULL        | 失败                      |



### 反初始化函数

```c
void gy271_deinit(gy271_device_t dev);
```

释放 gy271 设备占据的内存空间

| 参数     | 描述                                      |
| -------- | ----------------------------------------- |
| dev      | gy271_device_t (gy271_device结构体的指针) |
| **返回** | **描述**                                  |
| 无返回值 |                                           |



### 读取磁力计数据

```C
rt_err_t gy271_read_data(gy271_device_t dev,struct gy271_data  *data);
```

读取磁力计数据 (单位: mGauss)

| 参数     | 描述                      |
| -------- | ------------------------- |
| dev      | gy271_device 结构体的指针 |
| **返回** | **描述**                  |
| RT_EOK   | 成功                      |
| <0       | 失败                      |

3 轴磁力计数据结构体定义如下

```
struct gy271_data
{
    int x;
    int y;
    int z;
};
```

