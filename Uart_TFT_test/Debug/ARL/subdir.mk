################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ARL/cmd_process.c \
../ARL/cmd_queue.c \
../ARL/hmi_driver.c \
../ARL/hmi_user_uart.c 

OBJS += \
./ARL/cmd_process.obj \
./ARL/cmd_queue.obj \
./ARL/hmi_driver.obj \
./ARL/hmi_user_uart.obj 

C_DEPS += \
./ARL/cmd_process.pp \
./ARL/cmd_queue.pp \
./ARL/hmi_driver.pp \
./ARL/hmi_user_uart.pp 

OBJS__QTD += \
".\ARL\cmd_process.obj" \
".\ARL\cmd_queue.obj" \
".\ARL\hmi_driver.obj" \
".\ARL\hmi_user_uart.obj" 

C_DEPS__QTD += \
".\ARL\cmd_process.pp" \
".\ARL\cmd_queue.pp" \
".\ARL\hmi_driver.pp" \
".\ARL\hmi_user_uart.pp" 

C_SRCS_QUOTED += \
"../ARL/cmd_process.c" \
"../ARL/cmd_queue.c" \
"../ARL/hmi_driver.c" \
"../ARL/hmi_user_uart.c" 


# Each subdirectory must supply rules for building sources it contributes
ARL/cmd_process.obj: ../ARL/cmd_process.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/Uart_TFT_test/ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/Uart_TFT_test/INCLUDE" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/cmd_process.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

ARL/cmd_queue.obj: ../ARL/cmd_queue.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/Uart_TFT_test/ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/Uart_TFT_test/INCLUDE" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/cmd_queue.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

ARL/hmi_driver.obj: ../ARL/hmi_driver.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/Uart_TFT_test/ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/Uart_TFT_test/INCLUDE" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/hmi_driver.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

ARL/hmi_user_uart.obj: ../ARL/hmi_user_uart.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/Uart_TFT_test/ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/Uart_TFT_test/INCLUDE" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/hmi_user_uart.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


