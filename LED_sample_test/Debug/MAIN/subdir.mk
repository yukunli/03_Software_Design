################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MAIN/mian.c 

OBJS += \
./MAIN/mian.obj 

C_DEPS += \
./MAIN/mian.pp 

OBJS__QTD += \
".\MAIN\mian.obj" 

C_DEPS__QTD += \
".\MAIN\mian.pp" 

C_SRCS_QUOTED += \
"../MAIN/mian.c" 


# Each subdirectory must supply rules for building sources it contributes
MAIN/mian.obj: ../MAIN/mian.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/LED_sample_test/ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/LED_sample_test/INCLUDE" --include_path="C:/workspace/LED_test/INCLUDE" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="MAIN/mian.pp" --obj_directory="MAIN" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


