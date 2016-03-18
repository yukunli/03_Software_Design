################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_UPPER_SRCS += \
../ARL/LED.C \
../ARL/PWM_LED.C 

OBJS += \
./ARL/LED.obj \
./ARL/PWM_LED.obj 

C_UPPER_DEPS += \
./ARL/LED.pp \
./ARL/PWM_LED.pp 

OBJS__QTD += \
".\ARL\LED.obj" \
".\ARL\PWM_LED.obj" 

C_UPPER_DEPS__QTD += \
".\ARL\LED.pp" \
".\ARL\PWM_LED.pp" 

C_UPPER_SRCS_QUOTED += \
"../ARL/LED.C" \
"../ARL/PWM_LED.C" 


# Each subdirectory must supply rules for building sources it contributes
ARL/LED.obj: ../ARL/LED.C $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/workspace/LED_test/ARL" --include_path="C:/workspace/LED_test/INCLUDE" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/LED.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

ARL/PWM_LED.obj: ../ARL/PWM_LED.C $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/workspace/LED_test/ARL" --include_path="C:/workspace/LED_test/INCLUDE" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ARL/PWM_LED.pp" --obj_directory="ARL" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


