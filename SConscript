import rtconfig
from building import *

from building import *
Import('rtconfig')

src   = []
cwd   = GetCurrentDir()

# add gy271 src files.
if GetDepend('PKG_USING_GY271'):
    src += Glob('src/gy271.c')

if GetDepend('RT_USING_SENSOR'):
    src += Glob('src/sensor_honey_gy271.c')

if GetDepend('PKG_USING_GY271_SAMPLE'):
    src += Glob('samples/gy271_sample.c')

# add mpu6xxx include path.
path  = [cwd + '/inc']

# add src and include to group.
group = DefineGroup('gy271', src, depend = ['PKG_USING_GY271'], CPPPATH = path)

Return('group')
