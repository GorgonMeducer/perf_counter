Import('rtconfig')
from building import *

src = ['perf_counter.c', 'os/perf_os_patch_rt_thread.c']

cwd = GetCurrentDir()
path = [cwd]
group = []

group = DefineGroup('perf_counter', src, depend = ['PKG_USING_PERF_COUNTER'], CPPDEFINES = ['__PERF_CNT_USE_RTOS__'], CPPPATH = path)

Return('group')
