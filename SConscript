Import('rtconfig')
from building import *
import shutil

src = ['perf_counter.c', 'os/perf_os_patch_rt_thread.c']
cwd = GetCurrentDir()
path = [cwd]
CPPDEFINES = ['__PERF_COUNT_PLATFORM_SPECIFIC_HEADER__=<rtthread.h>', '__perf_counter_printf__=rt_kprintf', '__PERF_CNT_USE_RTOS__']

#delate unused files
try:
    shutil.rmtree(os.path.join(cwd,'.github'))
    shutil.rmtree(os.path.join(cwd,'.vscode'))
    shutil.rmtree(os.path.join(cwd,'CI'))
    shutil.rmtree(os.path.join(cwd,'cmsis-pack'))
    shutil.rmtree(os.path.join(cwd,'lib'))
    shutil.rmtree(os.path.join(cwd,'example'))
    os.remove(os.path.join(cwd,'systick_wrapper_gcc.s'))
    os.remove(os.path.join(cwd,'systick_wrapper_ual.s'))
except:
    pass

group = DefineGroup('perf_counter', src, depend = ['PKG_USING_PERF_COUNTER'], CPPDEFINES = CPPDEFINES, CPPPATH = path)

Return('group')
