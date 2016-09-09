################################################################################
# Automatically-generated file. Do not edit!
################################################################################

EMPTY := 
SPACE := $(EMPTY) $(EMPTY)

ORDERED_OBJS += \
$(GEN_CMDS_QUOTED) \
"./1_AD7656_ARL/AD7656.obj" \
"./2_AD9833_ARL/AD9833.obj" \
"./3_SCI_ARL/hmi_user_uart.obj" \
"./4_DataPro_ARL/DATA_Process.obj" \
"./4_DataPro_ARL/ConstData_Table.obj" \
"./5_LED_ARL/LED.obj" \
"./6_TempCtrl_ARL/tem_control.obj" \
"./6_TempCtrl_ARL/PWM_tem.obj" \
"./6_TempCtrl_ARL/DS18B20.obj" \
"./7_FTF_ARL/hmi_driver.obj" \
"./7_FTF_ARL/cmd_queue.obj" \
"./7_FTF_ARL/cmd_process.obj" \
"./A_MAIN/main.obj" \
"./DSP2833x_MemCopy.obj" \
"./SRC/DSP2833x_usDelay.obj" \
"./SRC/DSP2833x_Xintf.obj" \
"./SRC/DSP2833x_SysCtrl.obj" \
"./SRC/DSP2833x_Sci.obj" \
"./SRC/DSP2833x_PieVect.obj" \
"./SRC/DSP2833x_PieCtrl.obj" \
"./SRC/DSP2833x_GlobalVariableDefs.obj" \
"./SRC/DSP2833x_DefaultIsr.obj" \
"./SRC/DSP2833x_CpuTimers.obj" \
"./SRC/DSP2833x_CodeStartBranch.obj" \
"./SRC/DSP2833x_Adc.obj" \
"./SRC/DSP2833x_ADC_cal.obj" \
-l"libc.a" \
-l"E:\01_Master_project\Water_Detection_Project\04_Software_Design\4_NEW_Data_Process\IQmath_fpu32.lib" \
"../IQmath_fpu32.lib" \
"../CMD/DSP2833x_Headers_nonBIOS.cmd" \
"../CMD/F28335.cmd" \

-include ../makefile.init

RM := DEL /F

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include SRC/subdir.mk
-include CMD/subdir.mk
-include A_MAIN/subdir.mk
-include 7_FTF_ARL/subdir.mk
-include 6_TempCtrl_ARL/subdir.mk
-include 5_LED_ARL/subdir.mk
-include 4_DataPro_ARL/subdir.mk
-include 3_SCI_ARL/subdir.mk
-include 2_AD9833_ARL/subdir.mk
-include 1_AD7656_ARL/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: 4_NEW_Data_Process.out

dependents:
	-cd E:/01_Master_project/Water_Detection_Project/04_Software_Design/3_NEW_Data_Process && $(MAKE) all

# Tool invocations
4_NEW_Data_Process.out: $(GEN_CMDS) $(LIB_SRCS) $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	$(shell echo --silicon_version=28 > ccsLinker.opt)
	$(shell echo -g >> ccsLinker.opt)
	$(shell echo --diag_warning=225 >> ccsLinker.opt)
	$(shell echo --large_memory_model >> ccsLinker.opt)
	$(shell echo --float_support=fpu32 >> ccsLinker.opt)
	$(shell echo -z >> ccsLinker.opt)
	$(shell echo -m"4_NEW_Data_Process.map" >> ccsLinker.opt)
	$(shell echo --stack_size=1000 >> ccsLinker.opt)
	$(shell echo --heap_size=1000 >> ccsLinker.opt)
	$(shell echo --warn_sections >> ccsLinker.opt)
	$(shell echo -i"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/lib" -i"E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process" -i"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" >> ccsLinker.opt)
	$(shell echo --reread_libs >> ccsLinker.opt)
	$(shell echo --rom_model >> ccsLinker.opt)
	$(shell type ccsObjs.opt >> ccsLinker.opt)
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsLinker.opt -o "4_NEW_Data_Process.out"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C2000_EXECUTABLE_OUTPUTS__QTD) "4_NEW_Data_Process.out"
	-$(RM) ".\SRC\DSP2833x_ADC_cal.obj" ".\SRC\DSP2833x_Adc.obj" ".\SRC\DSP2833x_CodeStartBranch.obj" ".\SRC\DSP2833x_CpuTimers.obj" ".\SRC\DSP2833x_DefaultIsr.obj" ".\SRC\DSP2833x_GlobalVariableDefs.obj" ".\SRC\DSP2833x_PieCtrl.obj" ".\SRC\DSP2833x_PieVect.obj" ".\SRC\DSP2833x_Sci.obj" ".\SRC\DSP2833x_SysCtrl.obj" ".\SRC\DSP2833x_Xintf.obj" ".\SRC\DSP2833x_usDelay.obj" ".\DSP2833x_MemCopy.obj" ".\A_MAIN\main.obj" ".\7_FTF_ARL\cmd_process.obj" ".\7_FTF_ARL\cmd_queue.obj" ".\7_FTF_ARL\hmi_driver.obj" ".\6_TempCtrl_ARL\DS18B20.obj" ".\6_TempCtrl_ARL\PWM_tem.obj" ".\6_TempCtrl_ARL\tem_control.obj" ".\5_LED_ARL\LED.obj" ".\4_DataPro_ARL\ConstData_Table.obj" ".\4_DataPro_ARL\DATA_Process.obj" ".\3_SCI_ARL\hmi_user_uart.obj" ".\2_AD9833_ARL\AD9833.obj" ".\1_AD7656_ARL\AD7656.obj" 
	-$(RM) ".\SRC\DSP2833x_ADC_cal.pp" ".\SRC\DSP2833x_CodeStartBranch.pp" ".\SRC\DSP2833x_usDelay.pp" 
	-$(RM) ".\6_TempCtrl_ARL\DS18B20.pp" ".\6_TempCtrl_ARL\PWM_tem.pp" ".\5_LED_ARL\LED.pp" 
	-$(RM) ".\SRC\DSP2833x_Adc.pp" ".\SRC\DSP2833x_CpuTimers.pp" ".\SRC\DSP2833x_DefaultIsr.pp" ".\SRC\DSP2833x_GlobalVariableDefs.pp" ".\SRC\DSP2833x_PieCtrl.pp" ".\SRC\DSP2833x_PieVect.pp" ".\SRC\DSP2833x_Sci.pp" ".\SRC\DSP2833x_SysCtrl.pp" ".\SRC\DSP2833x_Xintf.pp" ".\DSP2833x_MemCopy.pp" ".\A_MAIN\main.pp" ".\7_FTF_ARL\cmd_process.pp" ".\7_FTF_ARL\cmd_queue.pp" ".\7_FTF_ARL\hmi_driver.pp" ".\6_TempCtrl_ARL\tem_control.pp" ".\4_DataPro_ARL\ConstData_Table.pp" ".\4_DataPro_ARL\DATA_Process.pp" ".\3_SCI_ARL\hmi_user_uart.pp" ".\2_AD9833_ARL\AD9833.pp" ".\1_AD7656_ARL\AD7656.pp" 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
