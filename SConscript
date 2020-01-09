import rtconfig
from building import *

cwd     = GetCurrentDir()
src     = ['gy271.c', 'sensor_honey_gy271.c']
path    = [cwd]

if GetDepend(['PKG_USING_GY271_SAMPLE']):
    src += ['gy271_sample.c']

group = DefineGroup('gy271', src, depend = ['PKG_USING_GY271'], CPPPATH = path)

Return('group')
