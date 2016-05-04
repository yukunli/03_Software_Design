################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_UPPER_SRCS += \
../ARL/DS18B20.C 

OBJS += \
./ARL/DS18B20.obj 

C_UPPER_DEPS += \
./ARL/DS18B20.pp 

OBJS__QTD += \
".\ARL\DS18B20.obj" 

C_UPPER_DEPS__QTD += \
".\ARL\DS18B20.pp" 

C_UPPER_SRCS_QUOTED += \
"../ARL/DS18B20.C" 


# Each subdirectory must supply rules for building sources it contributes
ARL/DS18B20.obj: ../ARL/DS18B20.C $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/TEM_18B20_TEST/ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/TEM_18B20_TEST/INCLUDE" --include_path="C:/workspace/TEM_18B20_TEST/INCLUDE" --include_path="C:/workspace/TEM_18B20_TEST/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/DS18B20.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


