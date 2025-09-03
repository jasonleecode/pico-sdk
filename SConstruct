import os
import re
import shutil

# 从环境变量或rtconfig获取目标平台
TARGET_PLATFORM = os.getenv('PICO_TARGET_PLATFORM', 'rp2350')  # 默认使用RP2350
TARGET_CPU = os.getenv('PICO_TARGET_CPU', 'cortex-m33')  # 默认使用cortex-m33

# 根据目标平台设置不同的配置
if TARGET_PLATFORM == 'rp2040':
    TARGET_CPU = 'cortex-m0plus'
    PLATFORM_DEFINES = [
        'PICO_BOARD="pico"',
        'PICO_BUILD=1',
        'PICO_NO_HARDWARE=0',
        'PICO_ON_DEVICE=1',
        'PICO_TARGET_PLATFORM=rp2040'
    ]
    PLATFORM_PATHS = [
        'src/rp2_common/boot_stage2/asminclude',
        'src/rp2040/hardware_regs/include',
        'src/rp2_common/hardware_base/include',
        'src/common/pico_base/include',
        'src/boards/include',
        'src/rp2_common/pico_platform/include',
        'src/rp2_common/boot_stage2/include'
    ]
    BOOT_STAGE2_LD = 'src/rp2_common/boot_stage2/boot_stage2.ld'
    BOOT_STAGE2_SRC = 'src/rp2_common/boot_stage2/compile_time_choice.S'
elif TARGET_PLATFORM == 'rp2350':
    TARGET_CPU = 'cortex-m33'
    PLATFORM_DEFINES = [
        'PICO_BOARD="pico"',
        'PICO_BUILD=1',
        'PICO_NO_HARDWARE=0',
        'PICO_ON_DEVICE=1',
        'PICO_TARGET_PLATFORM=rp2350'
    ]
    PLATFORM_PATHS = [
        'src/rp2_common/boot_stage2/asminclude',
        'src/rp2350/hardware_regs/include',
        'src/rp2_common/hardware_base/include',
        'src/common/pico_base/include',
        'src/boards/include',
        'src/rp2_common/pico_platform/include',
        'src/rp2_common/boot_stage2/include'
    ]
    BOOT_STAGE2_LD = 'src/rp2_common/boot_stage2/boot_stage2.ld'
    BOOT_STAGE2_SRC = 'src/rp2_common/boot_stage2/compile_time_choice.S'
else:
    raise ValueError(f"Unsupported target platform: {TARGET_PLATFORM}")

PREFIX = 'arm-none-eabi-'
EXEC_PATH = ''
if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

# 根据CPU架构设置编译选项
if TARGET_CPU == 'cortex-m0plus':
    CPU_FLAGS = '-mcpu=cortex-m0plus -mthumb'
elif TARGET_CPU == 'cortex-m33':
    CPU_FLAGS = '-mcpu=cortex-m33 -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard'
else:
    CPU_FLAGS = f'-mcpu={TARGET_CPU} -mthumb'

env = Environment(
    CC = PREFIX + 'gcc',
    AS = PREFIX + 'gcc',
    AR = PREFIX + 'ar', ARFLAGS = '-rc',
    CXX = PREFIX + 'g++',
    LINK = PREFIX + 'gcc',
    TARGET_EXT = 'elf',
    SIZE = PREFIX + 'size',
    OBJDUMP = PREFIX + 'objdump',
    OBJCPY = PREFIX + 'objcopy',
    CCFLAGS=Split(f'''
{CPU_FLAGS}
-O3 
-DNDEBUG
-Wl,--build-id=none 
--specs=nosys.specs 
-nostartfiles
-Wl,
-Wl,-Map=bs2_default.elf.map
'''),
    LINKFLAGS=Split(f'''
{CPU_FLAGS}
-O3 
-DNDEBUG
--specs=nosys.specs 
-nostartfiles
-T{BOOT_STAGE2_LD}
'''),
    CPPDEFINES = PLATFORM_DEFINES,
    CPPPATH = PLATFORM_PATHS
)
env.PrependENVPath('PATH', EXEC_PATH)

# 生成自动配置头文件
env.Command(
    ['src/common/pico_base/include/pico/config_autogen.h','src/common/pico_base/include/pico/version.h'],
    '',
    'python3 tools/generate_headers.py'
)

# 构建boot stage2
env.Program(
    f'bs2_default_{TARGET_PLATFORM}.elf',
    [BOOT_STAGE2_SRC],
)

# 生成二进制文件
env.Command(
    f'bs2_default_{TARGET_PLATFORM}.bin',
    f'bs2_default_{TARGET_PLATFORM}.elf',
    env['OBJCPY'] + f' -Obinary bs2_default_{TARGET_PLATFORM}.elf bs2_default_{TARGET_PLATFORM}.bin',
)

# 生成带校验和的汇编文件
env.Command(
    f'bs2_default_{TARGET_PLATFORM}_padded_checksummed.S',
    f'bs2_default_{TARGET_PLATFORM}.bin',
    f'python3 src/rp2_common/boot_stage2/pad_checksum -s 0xffffffff bs2_default_{TARGET_PLATFORM}.bin bs2_default_{TARGET_PLATFORM}_padded_checksummed.S',
)

# 打印构建信息
print(f"Building for target platform: {TARGET_PLATFORM}")
print(f"Target CPU: {TARGET_CPU}")
print(f"CPU flags: {CPU_FLAGS}")
