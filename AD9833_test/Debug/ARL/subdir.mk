################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ARL/AD9833.c 

OBJS += \
./ARL/AD9833.obj 

C_DEPS += \
./ARL/AD9833.pp 

OBJS__QTD += \
".\ARL\AD9833.obj" 

C_DEPS__QTD += \
".\ARL\AD9833.pp" 

C_SRCS_QUOTED += \
"../ARL/AD9833.c" 


# Each subdirectory must supply rules for building sources it contributes
ARL/AD9833.obj: ../ARL/AD9833.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/workspace/AD9833_test/INCLUDE" --include_path="C:/workspace/AD9833_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/AD9833.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


