project('uvk5', 'c',
    default_options : ['c_std=c11']
)

if not meson.is_cross_build()
    error('meson must be invoked with --cross-file meson_cross.ini')
endif

objcopy = find_program('arm-none-eabi-objcopy')
size = find_program('arm-none-eabi-size')

sources = []
includes = []
subdir('external')
subdir('driver')
subdir('src')

linkerscript_arg = '-Wl,-T,' + meson.source_root() + '/src/firmware.ld'
startup = files('src/start.S')
main = executable('main',
    [startup, sources],
    name_suffix : 'elf',
    c_args : ['-Os', '-Wall', '-Werror', '-DPRINTF_INCLUDE_CONFIG_H', '-DGIT_HASH="*"'],
    link_args : [linkerscript_arg],
    include_directories : [
        cmsis_includes,
        include_directories('.'),
        includes
    ]
)

main_bin = custom_target('main.bin',
    build_by_default : true,
    command : [objcopy, '-O', 'binary', '-S', main.full_path(), 'main.bin'],
    output : 'main.bin',
    depends : main
)

run_target('size',
    command : [size, main.full_path()],
    depends : main
)
