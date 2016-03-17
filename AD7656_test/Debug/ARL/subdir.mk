################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ARL/AD7656.c \
../ARL/Interrupt_Init.c 

OBJS += \
./ARL/AD7656.obj \
./ARL/Interrupt_Init.obj 

C_DEPS += \
./ARL/AD7656.pp \
./ARL/Interrupt_Init.pp 

OBJS__QTD += \
".\ARL\AD7656.obj" \
".\ARL\Interrupt_Init.obj" 

C_DEPS__QTD += \
".\ARL\AD7656.pp" \
".\ARL\Interrupt_Init.pp" 

C_SRCS_QUOTED += \
"../ARL/AD7656.c" \
"../ARL/Interrupt_Init.c" 


# Each subdirectory must supply rules for building sources it contributes
ARL/AD7656.obj: ../ARL/AD7656.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/workspace/AD7656_test/INCLUDE" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD7656_test/ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD7656_test/INCLUDE" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/AD7656.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

ARL/Interrupt_Init.obj: ../ARL/Interrupt_Init.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/workspace/AD7656_test/INCLUDE" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD7656_test/ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD7656_test/INCLUDE" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/Interrupt_Init.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


