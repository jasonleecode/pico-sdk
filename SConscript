import os
from building import *

# 从rtconfig.h读取SOC配置
def get_soc_config():
    """从rtconfig.h读取SOC配置"""
    rtconfig_path = os.path.join(os.getcwd(), 'rtconfig.h')
    if os.path.exists(rtconfig_path):
        with open(rtconfig_path, 'r') as f:
            content = f.read()
            if 'SOC_RP2350A' in content:
                return 'rp2350'
            elif 'SOC_RP2040' in content:
                return 'rp2040'
    return 'rp2350'  # 默认使用RP2350

# 从rtconfig.py读取stdio配置
def get_stdio_config():
    """从rtconfig.py读取stdio配置"""
    try:
        # 导入rtconfig模块
        import sys
        sys.path.insert(0, os.getcwd())
        import rtconfig
        return getattr(rtconfig, 'PICO_STDIO_OUTPUT', 'uart')
    except:
        return 'uart'  # 默认使用UART

# 获取目标平台配置
TARGET_PLATFORM = get_soc_config()

# 获取stdio配置
STDIO_OUTPUT = get_stdio_config()

# 根据目标平台设置不同的配置
if TARGET_PLATFORM == 'rp2040':
    TARGET_CPU = 'cortex-m0plus'
    PLATFORM_SRC_DIR = 'src/rp2040'
    PLATFORM_DEFINES = [
        'PICO_BOARD="pico"',
        'PICO_BUILD=1',
        'PICO_NO_HARDWARE=0',
        'PICO_ON_DEVICE=1',
        'PICO_TARGET_PLATFORM=rp2040'
    ]
elif TARGET_PLATFORM == 'rp2350':
    TARGET_CPU = 'cortex-m33'
    PLATFORM_SRC_DIR = 'src/rp2350'
    PLATFORM_DEFINES = [
        'PICO_BOARD="pico"',
        'PICO_BUILD=1',
        'PICO_NO_HARDWARE=0',
        'PICO_ON_DEVICE=1',
        'PICO_TARGET_PLATFORM=rp2350'
    ]
else:
    raise ValueError(f"Unsupported target platform: {TARGET_PLATFORM}")

# 设置编译选项
if TARGET_CPU == 'cortex-m0plus':
    CPU_FLAGS = '-mcpu=cortex-m0plus -mthumb'
elif TARGET_CPU == 'cortex-m33':
    CPU_FLAGS = '-mcpu=cortex-m33 -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard'
else:
    CPU_FLAGS = f'-mcpu={TARGET_CPU} -mthumb'

# 根据stdio配置设置编译宏
STDIO_DEFINES = []
if STDIO_OUTPUT == 'uart':
    STDIO_DEFINES = ['LIB_PICO_STDIO_UART=1', 'LIB_PICO_STDIO_USB=0']
elif STDIO_OUTPUT == 'usb':
    STDIO_DEFINES = ['LIB_PICO_STDIO_UART=0', 'LIB_PICO_STDIO_USB=1']

# 设置编译环境 - 使用与主工程相同的工具链
env = Environment()
env.Append(CCFLAGS = CPU_FLAGS)
env.Append(CPPDEFINES = PLATFORM_DEFINES + STDIO_DEFINES + ['PICO_SDK_SOURCE'])

# 使用与主工程相同的工具链
env['CC'] = 'arm-none-eabi-gcc'
env['AS'] = 'arm-none-eabi-gcc'
env['AR'] = 'arm-none-eabi-ar'
env['LINK'] = 'arm-none-eabi-gcc'

# 导出环境变量
Export('env')
Export('TARGET_PLATFORM')
Export('TARGET_CPU')
Export('PLATFORM_SRC_DIR')

cwd = GetCurrentDir()

# 调用src目录下的SConscript文件
print(f"Building pico-sdk for {TARGET_PLATFORM} (SOC: {TARGET_PLATFORM.upper()})")
print(f"STDIO output: {STDIO_OUTPUT.upper()}")
objs = SConscript('src/SConscript')

Return('objs')