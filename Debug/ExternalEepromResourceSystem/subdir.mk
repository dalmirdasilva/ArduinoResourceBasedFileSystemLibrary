################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ExternalEepromResourceSystem/ExternalEepromResourceSystem.cpp 

OBJS += \
./ExternalEepromResourceSystem/ExternalEepromResourceSystem.o 

CPP_DEPS += \
./ExternalEepromResourceSystem/ExternalEepromResourceSystem.d 


# Each subdirectory must supply rules for building sources it contributes
ExternalEepromResourceSystem/%.o: ../ExternalEepromResourceSystem/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/work/opensource/personal/microcontroller/arduino/library/rbfs/ArduinoResourceBasedFileSystemLibrary/ArrayResourceSystem" -I"/work/opensource/personal/microcontroller/arduino/library/rbfs/ArduinoResourceBasedFileSystemLibrary/ExternalEepromResourceSystem" -I"/work/opensource/personal/microcontroller/arduino/library/rbfs/ArduinoResourceBasedFileSystemLibrary/Resource" -I"/work/opensource/personal/microcontroller/arduino/library/rbfs/ArduinoResourceBasedFileSystemLibrary/ResourceSystem" -I"/work/opensource/personal/microcontroller/arduino/library/rbfs/ArduinoResourceBasedFileSystemLibrary/VirtualResourceSystem" -I"/work/opensource/personal/microcontroller/arduino/driver/memory" -I"/work/opensource/personal/microcontroller/arduino/driver/memory/ExternalEeprom" -I"/work/opensource/personal/microcontroller/rbfs" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


