################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../src/ \
../src/ASF/ \
../src/ASF/avr32/ \
../src/ASF/avr32/boards/ \
../src/ASF/avr32/boards/evk1100/ \
../src/ASF/avr32/drivers/ \
../src/ASF/avr32/drivers/gpio/ \
../src/ASF/avr32/drivers/intc/ \
../src/ASF/avr32/drivers/pwm/ \
../src/ASF/avr32/drivers/pwm/example/ \
../src/ASF/avr32/drivers/pwm/example/at32uc3a0512_evk1100/ \
../src/ASF/avr32/utils/ \
../src/ASF/avr32/utils/header_files/ \
../src/ASF/avr32/utils/linker_scripts/ \
../src/ASF/avr32/utils/linker_scripts/at32uc3a/ \
../src/ASF/avr32/utils/linker_scripts/at32uc3a/0512/ \
../src/ASF/avr32/utils/linker_scripts/at32uc3a/0512/gcc/ \
../src/ASF/avr32/utils/make/ \
../src/ASF/avr32/utils/preprocessor/ \
../src/ASF/avr32/utils/startup/ \
../src/ASF/common/ \
../src/ASF/common/boards/ \
../src/ASF/common/utils/ \
../src/ASF/common/utils/interrupt/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../src/ASF/avr32/boards/evk1100/led.c \
../src/ASF/avr32/drivers/gpio/gpio.c \
../src/ASF/avr32/drivers/intc/intc.c \
../src/ASF/avr32/drivers/pwm/pwm.c \
../src/pwm_example.c


PREPROCESSING_SRCS +=  \
../src/ASF/avr32/drivers/intc/exception.S \
../src/ASF/avr32/utils/startup/startup_uc3.S \
../src/ASF/avr32/utils/startup/trampoline_uc3.S


ASM_SRCS += 


OBJS +=  \
src/ASF/avr32/boards/evk1100/led.o \
src/ASF/avr32/drivers/gpio/gpio.o \
src/ASF/avr32/drivers/intc/exception.o \
src/ASF/avr32/drivers/intc/intc.o \
src/ASF/avr32/drivers/pwm/pwm.o \
src/ASF/avr32/utils/startup/startup_uc3.o \
src/ASF/avr32/utils/startup/trampoline_uc3.o \
src/pwm_example.o

OBJS_AS_ARGS +=  \
src/ASF/avr32/boards/evk1100/led.o \
src/ASF/avr32/drivers/gpio/gpio.o \
src/ASF/avr32/drivers/intc/exception.o \
src/ASF/avr32/drivers/intc/intc.o \
src/ASF/avr32/drivers/pwm/pwm.o \
src/ASF/avr32/utils/startup/startup_uc3.o \
src/ASF/avr32/utils/startup/trampoline_uc3.o \
src/pwm_example.o

C_DEPS +=  \
src/ASF/avr32/boards/evk1100/led.d \
src/ASF/avr32/drivers/gpio/gpio.d \
src/ASF/avr32/drivers/intc/exception.d \
src/ASF/avr32/drivers/intc/intc.d \
src/ASF/avr32/drivers/pwm/pwm.d \
src/ASF/avr32/utils/startup/startup_uc3.d \
src/ASF/avr32/utils/startup/trampoline_uc3.d \
src/pwm_example.d

C_DEPS_AS_ARGS +=  \
src/ASF/avr32/boards/evk1100/led.d \
src/ASF/avr32/drivers/gpio/gpio.d \
src/ASF/avr32/drivers/intc/exception.d \
src/ASF/avr32/drivers/intc/intc.d \
src/ASF/avr32/drivers/pwm/pwm.d \
src/ASF/avr32/utils/startup/startup_uc3.d \
src/ASF/avr32/utils/startup/trampoline_uc3.d \
src/pwm_example.d

OUTPUT_FILE_PATH +=PWM_EXAMPLE1.elf

OUTPUT_FILE_PATH_AS_ARGS +=PWM_EXAMPLE1.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler











src/ASF/avr32/boards/evk1100/%.o: ../src/ASF/avr32/boards/evk1100/%.c
	@echo Building file: $<
	@echo Invoking: AVR32/GNU C Compiler : 4.4.7
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-gcc.exe$(QUOTE)  -x c -DDEBUG -DBOARD=EVK1100  -I"../avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I"../src/ASF/avr32/utils" -I"../src/config" -I"../src/ASF/avr32/boards/evk1100" -I"../src/ASF/common/utils" -I"../src" -I"../src/ASF/avr32/drivers/pwm" -I"../src/ASF/avr32/boards" -I"../src/ASF/avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I"../src/ASF/avr32/drivers/gpio" -I"../src/ASF/common/boards" -I"../src/ASF/avr32/utils/preprocessor" -I"../src/ASF/avr32/drivers/intc"  -O1 -fdata-sections -ffunction-sections -masm-addr-pseudos -g3 -Wall -mpart=uc3a0512 -c -std=gnu99 -fno-strict-aliasing -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -mrelax -mno-cond-exec-before-reload -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/avr32/drivers/gpio/%.o: ../src/ASF/avr32/drivers/gpio/%.c
	@echo Building file: $<
	@echo Invoking: AVR32/GNU C Compiler : 4.4.7
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-gcc.exe$(QUOTE)  -x c -DDEBUG -DBOARD=EVK1100  -I"../avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I"../src/ASF/avr32/utils" -I"../src/config" -I"../src/ASF/avr32/boards/evk1100" -I"../src/ASF/common/utils" -I"../src" -I"../src/ASF/avr32/drivers/pwm" -I"../src/ASF/avr32/boards" -I"../src/ASF/avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I"../src/ASF/avr32/drivers/gpio" -I"../src/ASF/common/boards" -I"../src/ASF/avr32/utils/preprocessor" -I"../src/ASF/avr32/drivers/intc"  -O1 -fdata-sections -ffunction-sections -masm-addr-pseudos -g3 -Wall -mpart=uc3a0512 -c -std=gnu99 -fno-strict-aliasing -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -mrelax -mno-cond-exec-before-reload -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/avr32/drivers/intc/%.o: ../src/ASF/avr32/drivers/intc/%.c
	@echo Building file: $<
	@echo Invoking: AVR32/GNU C Compiler : 4.4.7
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-gcc.exe$(QUOTE)  -x c -DDEBUG -DBOARD=EVK1100  -I"../avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I"../src/ASF/avr32/utils" -I"../src/config" -I"../src/ASF/avr32/boards/evk1100" -I"../src/ASF/common/utils" -I"../src" -I"../src/ASF/avr32/drivers/pwm" -I"../src/ASF/avr32/boards" -I"../src/ASF/avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I"../src/ASF/avr32/drivers/gpio" -I"../src/ASF/common/boards" -I"../src/ASF/avr32/utils/preprocessor" -I"../src/ASF/avr32/drivers/intc"  -O1 -fdata-sections -ffunction-sections -masm-addr-pseudos -g3 -Wall -mpart=uc3a0512 -c -std=gnu99 -fno-strict-aliasing -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -mrelax -mno-cond-exec-before-reload -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/avr32/drivers/pwm/%.o: ../src/ASF/avr32/drivers/pwm/%.c
	@echo Building file: $<
	@echo Invoking: AVR32/GNU C Compiler : 4.4.7
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-gcc.exe$(QUOTE)  -x c -DDEBUG -DBOARD=EVK1100  -I"../avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I"../src/ASF/avr32/utils" -I"../src/config" -I"../src/ASF/avr32/boards/evk1100" -I"../src/ASF/common/utils" -I"../src" -I"../src/ASF/avr32/drivers/pwm" -I"../src/ASF/avr32/boards" -I"../src/ASF/avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I"../src/ASF/avr32/drivers/gpio" -I"../src/ASF/common/boards" -I"../src/ASF/avr32/utils/preprocessor" -I"../src/ASF/avr32/drivers/intc"  -O1 -fdata-sections -ffunction-sections -masm-addr-pseudos -g3 -Wall -mpart=uc3a0512 -c -std=gnu99 -fno-strict-aliasing -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -mrelax -mno-cond-exec-before-reload -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: AVR32/GNU C Compiler : 4.4.7
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-gcc.exe$(QUOTE)  -x c -DDEBUG -DBOARD=EVK1100  -I"../avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I"../src/ASF/avr32/utils" -I"../src/config" -I"../src/ASF/avr32/boards/evk1100" -I"../src/ASF/common/utils" -I"../src" -I"../src/ASF/avr32/drivers/pwm" -I"../src/ASF/avr32/boards" -I"../src/ASF/avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I"../src/ASF/avr32/drivers/gpio" -I"../src/ASF/common/boards" -I"../src/ASF/avr32/utils/preprocessor" -I"../src/ASF/avr32/drivers/intc"  -O1 -fdata-sections -ffunction-sections -masm-addr-pseudos -g3 -Wall -mpart=uc3a0512 -c -std=gnu99 -fno-strict-aliasing -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -mrelax -mno-cond-exec-before-reload -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler

src/ASF/avr32/drivers/intc/%.o: ../src/ASF/avr32/drivers/intc/%.S
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Preprocessing Assembler : 4.4.7
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-gcc.exe$(QUOTE) -x assembler-with-cpp -c -mpart=uc3a0512 -mrelax -DBOARD=EVK1100 -I "../avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I "../src/ASF/avr32/utils" -I "../src/config" -I "../src/ASF/avr32/boards/evk1100" -I "../src/ASF/common/utils" -I "../src" -I "../src/ASF/avr32/drivers/pwm" -I "../src/ASF/avr32/boards" -I "../src/ASF/avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I "../src/ASF/avr32/drivers/gpio" -I "../src/ASF/common/boards" -I "../src/ASF/avr32/utils/preprocessor" -I "../src/ASF/avr32/drivers/intc"  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -Wa,-g   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/avr32/drivers/intc/%.o: ../src/ASF/avr32/drivers/intc/%.x
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Preprocessing Assembler : 4.4.7
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-gcc.exe$(QUOTE) -x assembler-with-cpp -c -mpart=uc3a0512 -mrelax -DBOARD=EVK1100 -I "../avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I "../src/ASF/avr32/utils" -I "../src/config" -I "../src/ASF/avr32/boards/evk1100" -I "../src/ASF/common/utils" -I "../src" -I "../src/ASF/avr32/drivers/pwm" -I "../src/ASF/avr32/boards" -I "../src/ASF/avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I "../src/ASF/avr32/drivers/gpio" -I "../src/ASF/common/boards" -I "../src/ASF/avr32/utils/preprocessor" -I "../src/ASF/avr32/drivers/intc"  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -Wa,-g   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/avr32/drivers/intc/%.o: ../src/ASF/avr32/drivers/intc/%.X
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Preprocessing Assembler : 4.4.7
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-gcc.exe$(QUOTE) -x assembler-with-cpp -c -mpart=uc3a0512 -mrelax -DBOARD=EVK1100 -I "../avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I "../src/ASF/avr32/utils" -I "../src/config" -I "../src/ASF/avr32/boards/evk1100" -I "../src/ASF/common/utils" -I "../src" -I "../src/ASF/avr32/drivers/pwm" -I "../src/ASF/avr32/boards" -I "../src/ASF/avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I "../src/ASF/avr32/drivers/gpio" -I "../src/ASF/common/boards" -I "../src/ASF/avr32/utils/preprocessor" -I "../src/ASF/avr32/drivers/intc"  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -Wa,-g   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/avr32/utils/startup/%.o: ../src/ASF/avr32/utils/startup/%.S
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Preprocessing Assembler : 4.4.7
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-gcc.exe$(QUOTE) -x assembler-with-cpp -c -mpart=uc3a0512 -mrelax -DBOARD=EVK1100 -I "../avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I "../src/ASF/avr32/utils" -I "../src/config" -I "../src/ASF/avr32/boards/evk1100" -I "../src/ASF/common/utils" -I "../src" -I "../src/ASF/avr32/drivers/pwm" -I "../src/ASF/avr32/boards" -I "../src/ASF/avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I "../src/ASF/avr32/drivers/gpio" -I "../src/ASF/common/boards" -I "../src/ASF/avr32/utils/preprocessor" -I "../src/ASF/avr32/drivers/intc"  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -Wa,-g   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/avr32/utils/startup/%.o: ../src/ASF/avr32/utils/startup/%.x
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Preprocessing Assembler : 4.4.7
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-gcc.exe$(QUOTE) -x assembler-with-cpp -c -mpart=uc3a0512 -mrelax -DBOARD=EVK1100 -I "../avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I "../src/ASF/avr32/utils" -I "../src/config" -I "../src/ASF/avr32/boards/evk1100" -I "../src/ASF/common/utils" -I "../src" -I "../src/ASF/avr32/drivers/pwm" -I "../src/ASF/avr32/boards" -I "../src/ASF/avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I "../src/ASF/avr32/drivers/gpio" -I "../src/ASF/common/boards" -I "../src/ASF/avr32/utils/preprocessor" -I "../src/ASF/avr32/drivers/intc"  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -Wa,-g   -o "$@" "$<" 
	@echo Finished building: $<
	

src/ASF/avr32/utils/startup/%.o: ../src/ASF/avr32/utils/startup/%.X
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Preprocessing Assembler : 4.4.7
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-gcc.exe$(QUOTE) -x assembler-with-cpp -c -mpart=uc3a0512 -mrelax -DBOARD=EVK1100 -I "../avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I "../src/ASF/avr32/utils" -I "../src/config" -I "../src/ASF/avr32/boards/evk1100" -I "../src/ASF/common/utils" -I "../src" -I "../src/ASF/avr32/drivers/pwm" -I "../src/ASF/avr32/boards" -I "../src/ASF/avr32/drivers/pwm/example/at32uc3a0512_evk1100" -I "../src/ASF/avr32/drivers/gpio" -I "../src/ASF/common/boards" -I "../src/ASF/avr32/utils/preprocessor" -I "../src/ASF/avr32/drivers/intc"  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -Wa,-g   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR32/GNU Linker : 4.4.7
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -nostartfiles -Wl,-Map="PWM_EXAMPLE1.map" -Wl,--start-group -lm  -Wl,--end-group -Wl,--gc-sections --rodata-writable -Wl,--direct-data -mpart=uc3a0512 -Wl,--relax -T../src/ASF/avr32/utils/linker_scripts/at32uc3a/0512/gcc/link_uc3a0512.lds -Wl,-e,_trampoline  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature "PWM_EXAMPLE1.elf" "PWM_EXAMPLE1.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "PWM_EXAMPLE1.elf" "PWM_EXAMPLE1.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-objdump.exe" -h -S "PWM_EXAMPLE1.elf" > "PWM_EXAMPLE1.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "PWM_EXAMPLE1.elf" "PWM_EXAMPLE1.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR32 GCC\Native\3.4.1057\avr32-gnu-toolchain\bin\avr32-size.exe" "PWM_EXAMPLE1.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "PWM_EXAMPLE1.elf" "PWM_EXAMPLE1.a" "PWM_EXAMPLE1.hex" "PWM_EXAMPLE1.lss" "PWM_EXAMPLE1.eep" "PWM_EXAMPLE1.map" "PWM_EXAMPLE1.srec" "PWM_EXAMPLE1.usersignatures"
	