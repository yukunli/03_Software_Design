################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DSP2833x_MemCopy.c 

OBJS += \
./DSP2833x_MemCopy.obj 

C_DEPS += \
./DSP2833x_MemCopy.pp 

OBJS__QTD += \
".\DSP2833x_MemCopy.obj" 

C_DEPS__QTD += \
".\DSP2833x_MemCopy.pp" 

C_SRCS_QUOTED += \
"../DSP2833x_MemCopy.c" 


# Each subdirectory must supply rules for building sources it contributes
DSP2833x_MemCopy.obj: ../DSP2833x_MemCopy.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/INCLUDE" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/ARL" --include_path="C:/workspace/AD9833_test/INCLUDE" --include_path="C:/workspace/AD9833_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_MemCopy.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


