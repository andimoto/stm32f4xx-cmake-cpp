# add the sources here
set(HAL_UC_DIR hal_uc)
set(HAL_PCB_DIR hal_pcb)

set(sources
    main.cpp
    lcd_oneInch.cpp
    func.cpp
    leds.cpp
    keyPad.cpp
)

set(sources ${sources}
    ${HAL_UC_DIR}/rng.cpp
    ${HAL_UC_DIR}/timer.cpp
    ${HAL_UC_DIR}/gpio.cpp
    ${HAL_UC_DIR}/flash.cpp
)

set(sources ${sources}
    ${HAL_PCB_DIR}/keyPad4x4.cpp
    ${HAL_PCB_DIR}/led8Array.cpp
)

target_include_directories(stm32f4xx PUBLIC inc)
target_include_directories(stm32f4xx PUBLIC ${HAL_UC_DIR}/inc)
target_include_directories(stm32f4xx PUBLIC ${HAL_PCB_DIR}/inc)


# GCC optimization level: use -O0 in debug build, otherwise -O2
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(opt_level -O0)
#  set(opt_level -O2) DOES NOT WORK!! WRONG JUMP AT FOR(;;) LOOP?!
else()
  set(opt_level -Os)
endif()

# set some project constants
set(elf_file ${application_name}.elf)
set(bin_file ${application_name}.bin)
set(hex_file ${application_name}.hex)
set(map_file ${application_name}.map)
set(lss_file ${application_name}.lss)

# add sources to elf file
add_executable(${elf_file} ${sources})

# link StdPeriph library to project
target_link_libraries(${elf_file} PUBLIC stm32f4xx)

# set additional for compiler and linker: optimization and generate map file
set(additional_compiler_flags ${opt_level})
set(additional_linker_flags -Wl,-Map=${map_file},--cref,--no-warn-mismatch,--print-memory-usage)
target_compile_options(${elf_file} PRIVATE ${additional_compiler_flags})
target_link_libraries(${elf_file} PRIVATE ${additional_linker_flags})

# remove unused sections
target_link_libraries(${elf_file} PUBLIC "-g -Wl,--gc-sections")

# link with linker file
target_link_libraries(${elf_file} PUBLIC -T${LINKER_SCRIPT})

# generate extended listing
add_custom_target(${lss_file} DEPENDS ${elf_file} COMMAND ${ARM_OBJDUMP_EXECUTABLE} -S ${elf_file} > ${lss_file})

# create binary and hex files
add_custom_target(${hex_file} DEPENDS ${elf_file} COMMAND ${ARM_OBJCOPY_EXECUTABLE} -Oihex ${elf_file} ${hex_file})
add_custom_target(${bin_file} DEPENDS ${elf_file} COMMAND ${ARM_OBJCOPY_EXECUTABLE} -Obinary ${elf_file} ${bin_file})
add_custom_target(${application_name} ALL DEPENDS ${elf_file}-size ${bin_file} ${hex_file} ${lss_file})

# show size of resulting firmware image
add_custom_target(${elf_file}-size DEPENDS ${elf_file} COMMAND ${ARM_SIZE_EXECUTABLE} -B ${elf_file})

# OpenOCD targets
#add_custom_target(flash DEPENDS ${elf_file} COMMAND ${OPENOCD_EXECUTABLE}
#  -f ${OPENOCD_CONFIG}
#  --command "program ${elf_file} reset exit")
