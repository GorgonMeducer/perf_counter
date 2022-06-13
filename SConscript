Import('rtconfig')
from building import *

src = ['perf_counter.c', 'os/rt-thread/perf_os_patch_rt_thread.c']

if rtconfig.PLATFORM in ['armcc', 'armclang']: # Keil-MDK
    src += ['systick_wrapper_ual.s']

if rtconfig.PLATFORM == 'gcc':
    src += ['systick_wrapper_gcc.s']

cwd = GetCurrentDir()
path = [cwd]
group = []

group = DefineGroup('perf_counter', src, depend = ['PKG_USING_PERFCOUNTER'], CPPPATH = path)

Return('group')
