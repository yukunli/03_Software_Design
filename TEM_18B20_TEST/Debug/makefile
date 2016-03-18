################################################################################
# Automatically-generated file. Do not edit!
################################################################################

EMPTY := 
SPACE := $(EMPTY) $(EMPTY)

ORDERED_OBJS += \
$(GEN_CMDS_QUOTED) \
"./ARL/DS18B20.obj" \
"./MAIN/mian.obj" \
"./SRC/DSP2833x_usDelay.obj" \
"./SRC/DSP2833x_Xintf.obj" \
"./SRC/DSP2833x_SysCtrl.obj" \
"./SRC/DSP2833x_PieVect.obj" \
"./SRC/DSP2833x_PieCtrl.obj" \
"./SRC/DSP2833x_Mcbsp.obj" \
"./SRC/DSP2833x_GlobalVariableDefs.obj" \
"./SRC/DSP2833x_DefaultIsr.obj" \
"./SRC/DSP2833x_CpuTimers.obj" \
"./SRC/DSP2833x_CodeStartBranch.obj" \
"./SRC/DSP2833x_ADC_cal.obj" \
-l"libc.a" \
"../CMD/28335_RAM_lnk.cmd" \
"../CMD/DSP2833x_Headers_nonBIOS.cmd" \

-include ../makefile.init

RM := DEL /F

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include SRC/subdir.mk
-include MAIN/subdir.mk
-include CMD/subdir.mk
-include ARL/subdir.mk
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
all: TEM_18B20_TEST.out

# Tool invocations
TEM_18B20_TEST.out: $(GEN_CMDS) $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --diag_warning=225 --large_memory_model --float_support=fpu32 -z -m"TEM_18B20_TEST.map" --stack_size=1000 --heap_size=1000 --warn_sections -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/lib" -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --reread_libs --rom_model -o "TEM_18B20_TEST.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C2000_EXECUTABLE_OUTPUTS__QTD) "TEM_18B20_TEST.out"
	-$(RM) ".\SRC\DSP2833x_ADC_cal.obj" ".\SRC\DSP2833x_CodeStartBranch.obj" ".\SRC\DSP2833x_CpuTimers.obj" ".\SRC\DSP2833x_DefaultIsr.obj" ".\SRC\DSP2833x_GlobalVariableDefs.obj" ".\SRC\DSP2833x_Mcbsp.obj" ".\SRC\DSP2833x_PieCtrl.obj" ".\SRC\DSP2833x_PieVect.obj" ".\SRC\DSP2833x_SysCtrl.obj" ".\SRC\DSP2833x_Xintf.obj" ".\SRC\DSP2833x_usDelay.obj" ".\MAIN\mian.obj" ".\ARL\DS18B20.obj" 
	-$(RM) ".\SRC\DSP2833x_ADC_cal.pp" ".\SRC\DSP2833x_CodeStartBranch.pp" ".\SRC\DSP2833x_usDelay.pp" 
	-$(RM) ".\ARL\DS18B20.pp" 
	-$(RM) ".\SRC\DSP2833x_CpuTimers.pp" ".\SRC\DSP2833x_DefaultIsr.pp" ".\SRC\DSP2833x_GlobalVariableDefs.pp" ".\SRC\DSP2833x_Mcbsp.pp" ".\SRC\DSP2833x_PieCtrl.pp" ".\SRC\DSP2833x_PieVect.pp" ".\SRC\DSP2833x_SysCtrl.pp" ".\SRC\DSP2833x_Xintf.pp" ".\MAIN\mian.pp" 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
