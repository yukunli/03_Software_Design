################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
E:/01_Master_project/Water_Detection_Project/04_Software_Design/28335_AD7656/28335_AD7656/CMD/28335_RAM_lnk.cmd \
E:/01_Master_project/Water_Detection_Project/04_Software_Design/28335_AD7656/28335_AD7656/CMD/DSP2833x_Headers_nonBIOS.cmd 


# Each subdirectory must supply rules for building sources it contributes
CMD/28335_RAM_lnk.out: E:/01_Master_project/Water_Detection_Project/04_Software_Design/28335_AD7656/28335_AD7656/CMD/28335_RAM_lnk.cmd $(OBJS)
	@echo 'Building file: $<'
	@echo 'Invoking: Linker'
	$(shell echo --silicon_version=28 > ccsLinker.opt)
	$(shell echo -g >> ccsLinker.opt)
	$(shell echo --define="_DEBUG" --define="LARGE_MODEL" >> ccsLinker.opt)
	$(shell echo --diag_warning=225 >> ccsLinker.opt)
	$(shell echo --large_memory_model >> ccsLinker.opt)
	$(shell echo --float_support=fpu32 >> ccsLinker.opt)
	$(shell echo --obj_directory="E:/01_Master_project/Water_Detection_Project/04_Software_Design/28335_AD7656/28335_AD7656/Debug" >> ccsLinker.opt)
	$(shell echo -z >> ccsLinker.opt)
	$(shell echo -m"E:/01_Master_project/Water_Detection_Project/04_Software_Design/28335_AD7656/28335_AD7656/CMD/Debug/28335_AD7656.map" >> ccsLinker.opt)
	$(shell echo --stack_size=1000 >> ccsLinker.opt)
	$(shell echo --heap_size=1000 >> ccsLinker.opt)
	$(shell echo --warn_sections >> ccsLinker.opt)
	$(shell echo -i"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/lib" -i"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" -i"E:/01_Master_project/Water_Detection_Project/04_Software_Design/28335_AD7656/28335_AD7656/28335_AD7656" -i"E:/01_Master_project/Water_Detection_Project/04_Software_Design/28335_AD7656/28335_AD7656" >> ccsLinker.opt)
	$(shell echo --reread_libs >> ccsLinker.opt)
	$(shell echo --entry_point=code_start >> ccsLinker.opt)
	$(shell echo --rom_model >> ccsLinker.opt)
	$(shell echo $< >> ccsLinker.opt)
	$(shell type ccsObjs.opt >> ccsLinker.opt)
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsLinker.opt -o "$@"
	@echo 'Finished building: $<'
	@echo ' '

CMD/DSP2833x_Headers_nonBIOS.out: E:/01_Master_project/Water_Detection_Project/04_Software_Design/28335_AD7656/28335_AD7656/CMD/DSP2833x_Headers_nonBIOS.cmd $(OBJS)
	@echo 'Building file: $<'
	@echo 'Invoking: Linker'
	$(shell echo --silicon_version=28 > ccsLinker.opt)
	$(shell echo -g >> ccsLinker.opt)
	$(shell echo --define="_DEBUG" --define="LARGE_MODEL" >> ccsLinker.opt)
	$(shell echo --diag_warning=225 >> ccsLinker.opt)
	$(shell echo --large_memory_model >> ccsLinker.opt)
	$(shell echo --float_support=fpu32 >> ccsLinker.opt)
	$(shell echo --obj_directory="E:/01_Master_project/Water_Detection_Project/04_Software_Design/28335_AD7656/28335_AD7656/Debug" >> ccsLinker.opt)
	$(shell echo -z >> ccsLinker.opt)
	$(shell echo -m"E:/01_Master_project/Water_Detection_Project/04_Software_Design/28335_AD7656/28335_AD7656/CMD/Debug/28335_AD7656.map" >> ccsLinker.opt)
	$(shell echo --stack_size=1000 >> ccsLinker.opt)
	$(shell echo --heap_size=1000 >> ccsLinker.opt)
	$(shell echo --warn_sections >> ccsLinker.opt)
	$(shell echo -i"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/lib" -i"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" -i"E:/01_Master_project/Water_Detection_Project/04_Software_Design/28335_AD7656/28335_AD7656/28335_AD7656" -i"E:/01_Master_project/Water_Detection_Project/04_Software_Design/28335_AD7656/28335_AD7656" >> ccsLinker.opt)
	$(shell echo --reread_libs >> ccsLinker.opt)
	$(shell echo --entry_point=code_start >> ccsLinker.opt)
	$(shell echo --rom_model >> ccsLinker.opt)
	$(shell echo $< >> ccsLinker.opt)
	$(shell type ccsObjs.opt >> ccsLinker.opt)
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsLinker.opt -o "$@"
	@echo 'Finished building: $<'
	@echo ' '


