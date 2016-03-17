################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ARL/AD7656.c \
../ARL/ConstData_Table.c \
../ARL/DATA_Process.c \
../ARL/Interrupt_Init.c \
../ARL/SCI_Serial.c 

C_UPPER_SRCS += \
../ARL/LED.C 

OBJS += \
./ARL/AD7656.obj \
./ARL/ConstData_Table.obj \
./ARL/DATA_Process.obj \
./ARL/Interrupt_Init.obj \
./ARL/LED.obj \
./ARL/SCI_Serial.obj 

C_DEPS += \
./ARL/AD7656.pp \
./ARL/ConstData_Table.pp \
./ARL/DATA_Process.pp \
./ARL/Interrupt_Init.pp \
./ARL/SCI_Serial.pp 

C_UPPER_DEPS += \
./ARL/LED.pp 

OBJS__QTD += \
".\ARL\AD7656.obj" \
".\ARL\ConstData_Table.obj" \
".\ARL\DATA_Process.obj" \
".\ARL\Interrupt_Init.obj" \
".\ARL\LED.obj" \
".\ARL\SCI_Serial.obj" 

C_UPPER_DEPS__QTD += \
".\ARL\LED.pp" 

C_DEPS__QTD += \
".\ARL\AD7656.pp" \
".\ARL\ConstData_Table.pp" \
".\ARL\DATA_Process.pp" \
".\ARL\Interrupt_Init.pp" \
".\ARL\SCI_Serial.pp" 

C_SRCS_QUOTED += \
"../ARL/AD7656.c" \
"../ARL/ConstData_Table.c" \
"../ARL/DATA_Process.c" \
"../ARL/Interrupt_Init.c" \
"../ARL/SCI_Serial.c" 

C_UPPER_SRCS_QUOTED += \
"../ARL/LED.C" 


# Each subdirectory must supply rules for building sources it contributes
ARL/AD7656.obj: ../ARL/AD7656.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/DATA_Process_test/ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/DATA_Process_test/INCLUDE" --include_path="C:/workspace/DATA_Process_test/INCLUDE" --include_path="C:/workspace/DATA_Process_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/AD7656.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

ARL/ConstData_Table.obj: ../ARL/ConstData_Table.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/DATA_Process_test/ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/DATA_Process_test/INCLUDE" --include_path="C:/workspace/DATA_Process_test/INCLUDE" --include_path="C:/workspace/DATA_Process_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/ConstData_Table.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

ARL/DATA_Process.obj: ../ARL/DATA_Process.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/DATA_Process_test/ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/DATA_Process_test/INCLUDE" --include_path="C:/workspace/DATA_Process_test/INCLUDE" --include_path="C:/workspace/DATA_Process_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/DATA_Process.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

ARL/Interrupt_Init.obj: ../ARL/Interrupt_Init.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/DATA_Process_test/ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/DATA_Process_test/INCLUDE" --include_path="C:/workspace/DATA_Process_test/INCLUDE" --include_path="C:/workspace/DATA_Process_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/Interrupt_Init.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

ARL/LED.obj: ../ARL/LED.C $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/DATA_Process_test/ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/DATA_Process_test/INCLUDE" --include_path="C:/workspace/DATA_Process_test/INCLUDE" --include_path="C:/workspace/DATA_Process_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/LED.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

ARL/SCI_Serial.obj: ../ARL/SCI_Serial.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/DATA_Process_test/ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/DATA_Process_test/INCLUDE" --include_path="C:/workspace/DATA_Process_test/INCLUDE" --include_path="C:/workspace/DATA_Process_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/SCI_Serial.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


