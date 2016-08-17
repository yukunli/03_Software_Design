################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../CMD/DSP2833x_Headers_nonBIOS.cmd \
../CMD/F28335.cmd 


# Each subdirectory must supply rules for building sources it contributes
CMD/F28335.out: ../CMD/F28335.cmd $(OBJS)
	@echo 'Building file: $<'
	@echo 'Invoking: Linker'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --diag_warning=225 --large_memory_model --float_support=fpu32 -z -m"2_NEW_Data_Process.map" --stack_size=1000 --heap_size=1000 --warn_sections -i"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/lib" -i"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --reread_libs --rom_model -o "$@" "$<" $(ORDERED_OBJS)
	@echo 'Finished building: $<'
	@echo ' '


