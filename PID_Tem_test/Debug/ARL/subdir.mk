################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ARL/tem_control.c 

C_UPPER_SRCS += \
../ARL/PWM_tem.C 

OBJS += \
./ARL/PWM_tem.obj \
./ARL/tem_control.obj 

C_DEPS += \
./ARL/tem_control.pp 

C_UPPER_DEPS += \
./ARL/PWM_tem.pp 

OBJS__QTD += \
".\ARL\PWM_tem.obj" \
".\ARL\tem_control.obj" 

C_UPPER_DEPS__QTD += \
".\ARL\PWM_tem.pp" 

C_DEPS__QTD += \
".\ARL\tem_control.pp" 

C_UPPER_SRCS_QUOTED += \
"../ARL/PWM_tem.C" 

C_SRCS_QUOTED += \
"../ARL/tem_control.c" 


# Each subdirectory must supply rules for building sources it contributes
ARL/PWM_tem.obj: ../ARL/PWM_tem.C $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/workspace/PID_Tem_test/INCLUDE" --include_path="C:/workspace/PID_Tem_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/PWM_tem.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

ARL/tem_control.obj: ../ARL/tem_control.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/workspace/PID_Tem_test/INCLUDE" --include_path="C:/workspace/PID_Tem_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/tem_control.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


