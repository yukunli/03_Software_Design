################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
E:/01_Master_project/Water_Detection_Project/04_Software_Design/lab22-SCIB/CMD/28335_RAM_lnk.cmd \
E:/01_Master_project/Water_Detection_Project/04_Software_Design/lab22-SCIB/CMD/DSP2833x_Headers_nonBIOS.cmd 


# Each subdirectory must supply rules for building sources it contributes
CMD/28335_RAM_lnk.out: E:/01_Master_project/Water_Detection_Project/04_Software_Design/lab22-SCIB/CMD/28335_RAM_lnk.cmd $(OBJS)
	@echo 'Building file: $<'
	@echo 'Invoking: Linker'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --large_memory_model --float_support=fpu32 --obj_directory="E:/01_Master_project/Water_Detection_Project/04_Software_Design/lab22-SCIB/Debug" -z -m"E:/01_Master_project/Water_Detection_Project/04_Software_Design/lab22-SCIB/CMD/Debug/SCI.map" --stack_size=1000 --heap_size=1000 --warn_sections -i"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/lib" -i"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" -i"E:/01_Master_project/Water_Detection_Project/04_Software_Design/lab22-SCIB/SCI" -i"E:/01_Master_project/Water_Detection_Project/04_Software_Design/lab22-SCIB" --reread_libs --absolute_exe --rom_model -o "$@" "$<" $(ORDERED_OBJS)
	@echo 'Finished building: $<'
	@echo ' '

CMD/DSP2833x_Headers_nonBIOS.out: E:/01_Master_project/Water_Detection_Project/04_Software_Design/lab22-SCIB/CMD/DSP2833x_Headers_nonBIOS.cmd $(OBJS)
	@echo 'Building file: $<'
	@echo 'Invoking: Linker'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --large_memory_model --float_support=fpu32 --obj_directory="E:/01_Master_project/Water_Detection_Project/04_Software_Design/lab22-SCIB/Debug" -z -m"E:/01_Master_project/Water_Detection_Project/04_Software_Design/lab22-SCIB/CMD/Debug/SCI.map" --stack_size=1000 --heap_size=1000 --warn_sections -i"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/lib" -i"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" -i"E:/01_Master_project/Water_Detection_Project/04_Software_Design/lab22-SCIB/SCI" -i"E:/01_Master_project/Water_Detection_Project/04_Software_Design/lab22-SCIB" --reread_libs --absolute_exe --rom_model -o "$@" "$<" $(ORDERED_OBJS)
	@echo 'Finished building: $<'
	@echo ' '


