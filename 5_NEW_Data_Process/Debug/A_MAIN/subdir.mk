################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../A_MAIN/main.c 

OBJS += \
./A_MAIN/main.obj 

C_DEPS += \
./A_MAIN/main.pp 

OBJS__QTD += \
".\A_MAIN\main.obj" 

C_DEPS__QTD += \
".\A_MAIN\main.pp" 

C_SRCS_QUOTED += \
"../A_MAIN/main.c" 


# Each subdirectory must supply rules for building sources it contributes
A_MAIN/main.obj: ../A_MAIN/main.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(shell echo --silicon_version=28 > ccsCompiler.opt)
	$(shell echo -g >> ccsCompiler.opt)
	$(shell echo --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/5_NEW_Data_Process/1_AD7656_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/5_NEW_Data_Process/2_AD9833_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/5_NEW_Data_Process/3_SCI_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/5_NEW_Data_Process/4_DataPro_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/5_NEW_Data_Process/5_LED_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/5_NEW_Data_Process/6_TempCtrl_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/5_NEW_Data_Process/7_FTF_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/5_NEW_Data_Process/A_MAIN" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/5_NEW_Data_Process/INCLUDE" >> ccsCompiler.opt)
	$(shell echo --diag_warning=225 >> ccsCompiler.opt)
	$(shell echo --large_memory_model >> ccsCompiler.opt)
	$(shell echo --float_support=fpu32 >> ccsCompiler.opt)
	$(shell echo --preproc_with_compile >> ccsCompiler.opt)
	$(shell echo --preproc_dependency="A_MAIN/main.pp" >> ccsCompiler.opt)
	$(shell echo --obj_directory="A_MAIN" >> ccsCompiler.opt)
	$(if $(strip $(GEN_OPTS_QUOTED)), $(shell echo $(GEN_OPTS_QUOTED) >> ccsCompiler.opt))
	$(if $(strip $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")), $(shell echo $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#") >> ccsCompiler.opt))
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsCompiler.opt
	@echo 'Finished building: $<'
	@echo ' '


