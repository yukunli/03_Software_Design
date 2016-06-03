################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_UPPER_SRCS += \
../ARL/LED.C 

OBJS += \
./ARL/LED.obj 

C_UPPER_DEPS += \
./ARL/LED.pp 

OBJS__QTD += \
".\ARL\LED.obj" 

C_UPPER_DEPS__QTD += \
".\ARL\LED.pp" 

C_UPPER_SRCS_QUOTED += \
"../ARL/LED.C" 


# Each subdirectory must supply rules for building sources it contributes
ARL/LED.obj: ../ARL/LED.C $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/LED_sample_test/ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/LED_sample_test/INCLUDE" --include_path="C:/workspace/LED_test/INCLUDE" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/LED.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


