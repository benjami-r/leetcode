#С пресет в CMakePresets.json (https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html):
# $ rm -rf build; cmake --preset debug && cmake --build --preset debug
# $ cmake ... --verbose - выполнение каждой операции можно увидеть в подробностях (в частности, cmake --build --preset debug --verbose покажет в т.ч. строки запуска компиляторов и линкера со всеми флагами).
#Без пресет (просто пример, ибо в пресете у меня еще ARCHITECTURE):
# $ cmake --toolchain config/toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -B build
# $ cmake --build build
# $ cmake --build build --target MyTarget
#Чистка кэша:
# $ cmake -U, а лучше $ rm -rf build.
# Ибо философия CMake: «один раз настроил (конфигурацию) — много раз собираешь (билд)», поэтому даже если CMakeLists.txt изменен, солюшн переконфигурируется, но без явного изменения им переменных в кэше, кэш не трогается (например, до изменения CMakeLists.txt переменная ARCHITECTURE им устанавливалась, а после изменения - нет, но в кэше она остается установленой, тогда в случае проверки вида if(NOT DEFINED ARCHITECTURE) - она оценивается как установленная, т.к. в кэше сохранилась). Кэш - это "липкая" настройка.
# Отсюда: если мы запускали конфигурацию или сборку через пресет, а затем, не чистя кэш, без пресета (просто cmake . или cmake --build), то все продолжает работать с учетом кэша.
############################################################ PRE-PROJECT
cmake_minimum_required(VERSION 4.2)
if(CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR) #Исключаем сборку в корневую теку
    message(FATAL_ERROR "CMAKE_BINARY_DIR = CMAKE_SOURCE_DIR is not allowed.")
endif()
cmake_path(GET CMAKE_SOURCE_DIR STEM PRJ) #STEM/FILENAME
############################################################ Стандарт. Если не поддерживается - CMake ругнется. Можно себе предварительно проверить официальную поддержку стандарта: $ ./arm-none-eabi-gcc -std=c23 -dM -E - < /dev/null | grep __STDC_VERSION__ если выведет что-то вроде #define __STDC_VERSION__ 202311L - поддержка есть.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) #Устанавливаем флаг генерации файла "compile_commands.json" (Для clangd создает ${CMAKE_BINARY_DIR}/compile_commands.json (потом можно "$ ln -s build/compile_commands.json ." или настроить clangd). Указывается до вызова project().)
set(CMAKE_C_STANDARD                   23) #11, 17 (иначе добавляем флаг "-std=c23")
set(CMAKE_C_STANDARD_REQUIRED          ON)
set(CMAKE_C_EXTENSIONS                 ON)
set(CMAKE_CXX_STANDARD                 23) #11, 17 (иначе добавляем флаг "-std=c++23")
set(CMAKE_CXX_STANDARD_REQUIRED        ON)
set(CMAKE_CXX_EXTENSIONS               ON)
set(CMAKE_C_FLAGS_DEBUG   "")
set(CMAKE_ASM_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_DEBUG "")
############################################################ PROJECT (Водораздел! Все, что нужно для готовности тулчейна (пути, архитектура, check compiler) - до project(), а все, что касается самого проекта - на каком языке и в каком стандарте написаны исходники, какие флаги и библиотеки нужны для их сборки - после.)
project(PRJ_${PRJ} LANGUAGES C CXX ASM) # C CXX ASM
############################################################ COMMON FLAGS
add_library(cmn INTERFACE) #это не библиотека, это интерфейс для передачи общих параметров в цели
target_compile_definitions(cmn INTERFACE #Добавляем разные определения для Debug и Release
    $<$<CONFIG:Debug>:DEBUG>     #Включит ассерты и др.
    $<$<CONFIG:Release>:NDEBUG>  #Выключит ассерты и др.
)
target_compile_options(cmn INTERFACE
    #-fmodules-ts #вродь был нужен для GCC, а clang'у достаточно -std=gnu++20/gnu++23
    -ffunction-sections -fdata-sections# Общие флаги, причем -ffunction-sections и -fdata-sections безполезны без флага линкера -Wl,--gc-sections
    -Wall -Wextra -Wpedantic
    -Wno-gnu-zero-variadic-macro-arguments #понадобился для LOG, когда __VA_ARGS__ пустой (LOG("hello");)
    #-Wno-unused #отключает: -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function (стат.ф.) -Wno-unused-value (выр.) -Wno-unused-label - флаги глобальны, но лучше использовать внутрифайловые настройки: #pragma clang diagnostic push ... в конце pop, а между ними #pragma clang diagnostic ignored "-Wunused-parameter" и пр. флаги
    $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp> #Еще были: -MMD -MP, но для CMake они избыточны, ибо он сам делает Dependency Scanning. Вообще это gcc-флаги: -MD - генерировать файл зависимостей, -MMD - то же, но хидеры учитывать только юзерские, -MP - добавить фиктивную цель для каждой зависимости, так учитываются стертые файлы) (Вообще препроцессор считаем для асм полезным, но рекомендуется ограничиться директивами #include и #define, и не ввязываться в сложные макросы ибо на стадии компиляции и отладки начнутся чудеса с номерами строк и не только.) (-flto для асм не фурычит)
    #=== Debug and other (C and CXX only)
    $<$<AND:$<COMPILE_LANGUAGE:C>,$<NOT:$<CONFIG:Release>>>:-O0 -g3 -fstack-usage> # -save-temps Оптимизация/отладка/диагностика: -O0 - полностью отключает необязательные оптимизации (default), -g3 - extra debug information (включая макросы); -fstack-usage - генерирует файлы .su с анализом стека; -save-temps сохраняет промежуточные компил-файлы (.s (для .c/.cpp), также .o и .i (препроцессированные .S-файлы) - в CMakeFiles/exe.dir/...)
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<CONFIG:Release>>>:-O0 -g3 -fstack-usage> # -save-temps> - дает ошибку при сборе ninja
    #=== Release only (C and CXX only)
    $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:Release>>:-Os -g0 -Werror -flto> #Оптимизация/отладка/диагностика: -Os - optimize for size, -Og - стандартная/оптимальная оптимизация, -Oz - агрессивная оптимизация по размеру в ущерб скорости; -g0 - no debug information; -Werror - рассматривать предупреждения как ошибки. -flto (Link Time Optimization) - добавляет GIMPLE-инфу в объектные файлы для более искусной оптимизации на стадии линковки, требует указания -flto и линкеру.
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Release>>:-Os -g0 -Werror -flto>
)
target_link_options(cmn INTERFACE
    -Wl,--gc-sections #работает в паре с флагами компилятора: -ffunction-sections и -fdata-sections
    #-Wl,-Map=%,--cref #-Map=$<TARGET_FILE:exe>.map - идеально, -Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map; --cref - добавить в .map Cross Reference Table.
    #-Wl,--print-memory-usage
    #-Wl,--print-output-format
    -fuse-ld=lld #используем LLVM LLD (но для STM32 проверить коректно ли понимает .ld. Возможно лучше оставить arm-none-eabi-ld)
    $<$<CONFIG:Release>:-flto> #работает в паре с флагом компилятора: -flto
)
target_include_directories(cmn INTERFACE #Общие Include‑пути (CMSIS?)
    source/core
    source/core/exercises
    source/modules
    source/modules/sys
)
############################################################ TARGET: EXECUTABLE
add_executable(${PRJ})
target_link_libraries(${PRJ} PRIVATE cmn) # наследуем ВСЮ конфигурацию псевдо-библиотеки-интерфейса cmn.
target_sources(${PRJ} 
  PRIVATE
    source/core/main.cpp
    source/core/proba.cpp
    #source/core/exercises/01_two_sum.cpp
  PRIVATE FILE_SET cxx_modules TYPE CXX_MODULES FILES    # порядок: интерфейс, раздел-интерфейсы, раздел-имплементации, имплементации
    # source/modules/sys_io.cppm
  PRIVATE
    #source/modules/sys_string.cpp
)
# set_target_properties(${PRJ} PROPERTIES
#     OUTPUT_NAME "exe" #универсальное имя выходного файла
# )

############################################################ OUTER COMMANDS:
add_custom_target(reconfigure                     # Cleaning cache and reconfiguring project (культурно)
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_CURRENT_BINARY_DIR}/CMakeCache.txt     # Удаляем старый кэш     (радикальнее: rm -rf build)
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles  # Удаляем файлы сборки   (радикальнее: rm -rf build)
    COMMAND ${CMAKE_COMMAND} --preset debug                                              # Конфигурируем
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}                                                #
    COMMENT "Reconfigure"                                                                # 
    USES_TERMINAL                                                                        # подсказка генератору (актуально для Ninja) отображать вывод в реальном времени в терминале, а не буферизовать
)
add_custom_target(run                             # делаем "псевдо-цель" run, не производящую файл, а просто выполняющую команду (обычно ${PROJECT_NAME}
    COMMAND $<TARGET_FILE:${PRJ}>                 # generator expression, подставляющий полный путь к реально собранному исполняемому файлу цели (учитывает платформу, конфигурацию Debug/Release и т.п.) (обычно ${PROJECT_NAME}
    DEPENDS ${PRJ}                                # гарантирует, что перед запуском run сначала выполнится сборка основной цели (обычно ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} # рабочая директория при запуске (обычно — директория сборки)
    COMMENT "Running ${PRJ}"                      # 
    USES_TERMINAL                                 # подсказка генератору (актуально для Ninja) отображать вывод в реальном времени в терминале, а не буферизовать
)
add_custom_target(run_in_konsole
    #COMMAND konsole --profile subl -e bash -lc "$<TARGET_FILE:${PRJ}>; echo; echo 'Process finished. Press any key to close...'; read -n 1"  # 2>/dev/null пришлось убрать. Операторы перенаправления (>, 2>, &&) здесь не сработают. Если все же нужно — обернем всю команду ещё в один слой bash -c: (след. строка)
    #COMMAND konsole --profile subl -e bash -lc "${CMAKE_SOURCE_DIR}/c_run.sh $<TARGET_FILE:${PRJ}>"  # так можно вынести команду в отдельный скрипт (см здесь ниже) и запустить его... (делает неполезный вывод запускаемой оболочки)
    #COMMAND bash -c "konsole --profile dur -e bash -lc '${CMAKE_SOURCE_DIR}/c_run.sh $<TARGET_FILE:${PRJ}>' 2>/dev/null" # или так (покажет команду запуска)
    COMMAND bash -c "konsole --profile dur -e bash -lc \"$<TARGET_FILE:${PRJ}>; echo; echo 'Process finished. Press any key to close...'; read -n 1\" 2>/dev/null"  # ещё в один слой bash -c
    DEPENDS ${PRJ}
    COMMENT "Running ${PRJ} in Konsole"
    USES_TERMINAL
    VERBATIM   # обязателен здесь: без него CMake может по-разному экранировать спецсимволы (;, кавычки) на разных платформах/генераторах, что почти гарантированно сломает вашу составную bash-строку. VERBATIM заставляет CMake передавать аргументы дословно, без собственной интерпретации.
  # Если в команде юзим скрипт c_run.sh, вот его пример:
  # #!/bin/bash
  # "$1"
  # echo
  # echo 'Process finished. Press any key to close...'
  # read -n 1
)

############################################################
############################################################
############################################################
############################################################
############################################################
# Проверка размеров секций - покажет, как распределился код по памяти (Flash и RAM) (text: код и константы (попадет во Flash), data: инициализированные переменные (попадут во Flash, при старте надо копировать в RAM), bss: неинициализированные переменные (резервирует RAM, но нужно "обнулить" в RAM)):
# $ ~/bin/arm-gnu-toolchain/bin/arm-none-eabi-size exe                      - 
# Проверка таблицы векторов и точки входа:
# $ ~/bin/arm-gnu-toolchain/bin/arm-none-eabi-objdump -D exe | head -n 20
############################################################
# # Generator Expressions work, out demonstration
# set(CMD COMMAND "${CMAKE_COMMAND}" -E echo)
# add_custom_command(
#     TARGET exe
#     PRE_BUILD
#     ${CMD} "${My} Target info:"
#     ${CMD} "${My}   Config: $<CONFIG>"
#     ${CMD} "${My}   Platform: $<PLATFORM_ID>"
#     ${CMD} "${My}   Out file: $<TARGET_FILE:exe>"
# )
############################################################
# настройку автоматического создания .bin или .hex файла из полученного .elf
############################################################
# add_executable(${PRJ}) - показываю, что вставляем после add_executable()
# target_precompile_headers(dur PRIVATE 
#     <iostream>
#     <cstdio>
# )
############################################################
