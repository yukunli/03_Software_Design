################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SRC/DSP2833x_Adc.c \
../SRC/DSP2833x_CpuTimers.c \
../SRC/DSP2833x_DefaultIsr.c \
../SRC/DSP2833x_GlobalVariableDefs.c \
../SRC/DSP2833x_PieCtrl.c \
../SRC/DSP2833x_PieVect.c \
../SRC/DSP2833x_Sci.c \
../SRC/DSP2833x_SysCtrl.c \
../SRC/DSP2833x_Xintf.c 

ASM_SRCS += \
../SRC/DSP2833x_ADC_cal.asm \
../SRC/DSP2833x_CodeStartBranch.asm \
../SRC/DSP2833x_usDelay.asm 

ASM_DEPS += \
./SRC/DSP2833x_ADC_cal.pp \
./SRC/DSP2833x_CodeStartBranch.pp \
./SRC/DSP2833x_usDelay.pp 

OBJS += \
./SRC/DSP2833x_ADC_cal.obj \
./SRC/DSP2833x_Adc.obj \
./SRC/DSP2833x_CodeStartBranch.obj \
./SRC/DSP2833x_CpuTimers.obj \
./SRC/DSP2833x_DefaultIsr.obj \
./SRC/DSP2833x_GlobalVariableDefs.obj \
./SRC/DSP2833x_PieCtrl.obj \
./SRC/DSP2833x_PieVect.obj \
./SRC/DSP2833x_Sci.obj \
./SRC/DSP2833x_SysCtrl.obj \
./SRC/DSP2833x_Xintf.obj \
./SRC/DSP2833x_usDelay.obj 

C_DEPS += \
./SRC/DSP2833x_Adc.pp \
./SRC/DSP2833x_CpuTimers.pp \
./SRC/DSP2833x_DefaultIsr.pp \
./SRC/DSP2833x_GlobalVariableDefs.pp \
./SRC/DSP2833x_PieCtrl.pp \
./SRC/DSP2833x_PieVect.pp \
./SRC/DSP2833x_Sci.pp \
./SRC/DSP2833x_SysCtrl.pp \
./SRC/DSP2833x_Xintf.pp 

OBJS__QTD += \
".\SRC\DSP2833x_ADC_cal.obj" \
".\SRC\DSP2833x_Adc.obj" \
".\SRC\DSP2833x_CodeStartBranch.obj" \
".\SRC\DSP2833x_CpuTimers.obj" \
".\SRC\DSP2833x_DefaultIsr.obj" \
".\SRC\DSP2833x_GlobalVariableDefs.obj" \
".\SRC\DSP2833x_PieCtrl.obj" \
".\SRC\DSP2833x_PieVect.obj" \
".\SRC\DSP2833x_Sci.obj" \
".\SRC\DSP2833x_SysCtrl.obj" \
".\SRC\DSP2833x_Xintf.obj" \
".\SRC\DSP2833x_usDelay.obj" 

ASM_DEPS__QTD += \
".\SRC\DSP2833x_ADC_cal.pp" \
".\SRC\DSP2833x_CodeStartBranch.pp" \
".\SRC\DSP2833x_usDelay.pp" 

C_DEPS__QTD += \
".\SRC\DSP2833x_Adc.pp" \
".\SRC\DSP2833x_CpuTimers.pp" \
".\SRC\DSP2833x_DefaultIsr.pp" \
".\SRC\DSP2833x_GlobalVariableDefs.pp" \
".\SRC\DSP2833x_PieCtrl.pp" \
".\SRC\DSP2833x_PieVect.pp" \
".\SRC\DSP2833x_Sci.pp" \
".\SRC\DSP2833x_SysCtrl.pp" \
".\SRC\DSP2833x_Xintf.pp" 

ASM_SRCS_QUOTED += \
"../SRC/DSP2833x_ADC_cal.asm" \
"../SRC/DSP2833x_CodeStartBranch.asm" \
"../SRC/DSP2833x_usDelay.asm" 

C_SRCS_QUOTED += \
"../SRC/DSP2833x_Adc.c" \
"../SRC/DSP2833x_CpuTimers.c" \
"../SRC/DSP2833x_DefaultIsr.c" \
"../SRC/DSP2833x_GlobalVariableDefs.c" \
"../SRC/DSP2833x_PieCtrl.c" \
"../SRC/DSP2833x_PieVect.c" \
"../SRC/DSP2833x_Sci.c" \
"../SRC/DSP2833x_SysCtrl.c" \
"../SRC/DSP2833x_Xintf.c" 


# Each subdirectory must supply rules for building sources it contributes
SRC/DSP2833x_ADC_cal.obj: ../SRC/DSP2833x_ADC_cal.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(shell echo --silicon_version=28 > ccsCompiler.opt)
	$(shell echo -g >> ccsCompiler.opt)
	$(shell echo --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/1_AD7656_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/2_AD9833_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/3_SCI_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/4_DataPro_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/5_LED_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/6_TempCtrl_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/7_FTF_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/A_MAIN" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/INCLUDE" >> ccsCompiler.opt)
	$(shell echo --diag_warning=225 >> ccsCompiler.opt)
	$(shell echo --large_memory_model >> ccsCompiler.opt)
	$(shell echo --float_support=fpu32 >> ccsCompiler.opt)
	$(shell echo --preproc_with_compile >> ccsCompiler.opt)
	$(shell echo --preproc_dependency="SRC/DSP2833x_ADC_cal.pp" >> ccsCompiler.opt)
	$(shell echo --obj_directory="SRC" >> ccsCompiler.opt)
	$(if $(strip $(GEN_OPTS_QUOTED)), $(shell echo $(GEN_OPTS_QUOTED) >> ccsCompiler.opt))
	$(if $(strip $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")), $(shell echo $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#") >> ccsCompiler.opt))
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsCompiler.opt
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_Adc.obj: ../SRC/DSP2833x_Adc.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(shell echo --silicon_version=28 > ccsCompiler.opt)
	$(shell echo -g >> ccsCompiler.opt)
	$(shell echo --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/1_AD7656_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/2_AD9833_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/3_SCI_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/4_DataPro_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/5_LED_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/6_TempCtrl_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/7_FTF_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/A_MAIN" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/INCLUDE" >> ccsCompiler.opt)
	$(shell echo --diag_warning=225 >> ccsCompiler.opt)
	$(shell echo --large_memory_model >> ccsCompiler.opt)
	$(shell echo --float_support=fpu32 >> ccsCompiler.opt)
	$(shell echo --preproc_with_compile >> ccsCompiler.opt)
	$(shell echo --preproc_dependency="SRC/DSP2833x_Adc.pp" >> ccsCompiler.opt)
	$(shell echo --obj_directory="SRC" >> ccsCompiler.opt)
	$(if $(strip $(GEN_OPTS_QUOTED)), $(shell echo $(GEN_OPTS_QUOTED) >> ccsCompiler.opt))
	$(if $(strip $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")), $(shell echo $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#") >> ccsCompiler.opt))
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsCompiler.opt
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_CodeStartBranch.obj: ../SRC/DSP2833x_CodeStartBranch.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(shell echo --silicon_version=28 > ccsCompiler.opt)
	$(shell echo -g >> ccsCompiler.opt)
	$(shell echo --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/1_AD7656_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/2_AD9833_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/3_SCI_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/4_DataPro_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/5_LED_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/6_TempCtrl_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/7_FTF_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/A_MAIN" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/INCLUDE" >> ccsCompiler.opt)
	$(shell echo --diag_warning=225 >> ccsCompiler.opt)
	$(shell echo --large_memory_model >> ccsCompiler.opt)
	$(shell echo --float_support=fpu32 >> ccsCompiler.opt)
	$(shell echo --preproc_with_compile >> ccsCompiler.opt)
	$(shell echo --preproc_dependency="SRC/DSP2833x_CodeStartBranch.pp" >> ccsCompiler.opt)
	$(shell echo --obj_directory="SRC" >> ccsCompiler.opt)
	$(if $(strip $(GEN_OPTS_QUOTED)), $(shell echo $(GEN_OPTS_QUOTED) >> ccsCompiler.opt))
	$(if $(strip $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")), $(shell echo $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#") >> ccsCompiler.opt))
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsCompiler.opt
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_CpuTimers.obj: ../SRC/DSP2833x_CpuTimers.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(shell echo --silicon_version=28 > ccsCompiler.opt)
	$(shell echo -g >> ccsCompiler.opt)
	$(shell echo --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/1_AD7656_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/2_AD9833_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/3_SCI_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/4_DataPro_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/5_LED_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/6_TempCtrl_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/7_FTF_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/A_MAIN" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/INCLUDE" >> ccsCompiler.opt)
	$(shell echo --diag_warning=225 >> ccsCompiler.opt)
	$(shell echo --large_memory_model >> ccsCompiler.opt)
	$(shell echo --float_support=fpu32 >> ccsCompiler.opt)
	$(shell echo --preproc_with_compile >> ccsCompiler.opt)
	$(shell echo --preproc_dependency="SRC/DSP2833x_CpuTimers.pp" >> ccsCompiler.opt)
	$(shell echo --obj_directory="SRC" >> ccsCompiler.opt)
	$(if $(strip $(GEN_OPTS_QUOTED)), $(shell echo $(GEN_OPTS_QUOTED) >> ccsCompiler.opt))
	$(if $(strip $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")), $(shell echo $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#") >> ccsCompiler.opt))
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsCompiler.opt
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_DefaultIsr.obj: ../SRC/DSP2833x_DefaultIsr.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(shell echo --silicon_version=28 > ccsCompiler.opt)
	$(shell echo -g >> ccsCompiler.opt)
	$(shell echo --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/1_AD7656_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/2_AD9833_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/3_SCI_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/4_DataPro_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/5_LED_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/6_TempCtrl_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/7_FTF_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/A_MAIN" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/INCLUDE" >> ccsCompiler.opt)
	$(shell echo --diag_warning=225 >> ccsCompiler.opt)
	$(shell echo --large_memory_model >> ccsCompiler.opt)
	$(shell echo --float_support=fpu32 >> ccsCompiler.opt)
	$(shell echo --preproc_with_compile >> ccsCompiler.opt)
	$(shell echo --preproc_dependency="SRC/DSP2833x_DefaultIsr.pp" >> ccsCompiler.opt)
	$(shell echo --obj_directory="SRC" >> ccsCompiler.opt)
	$(if $(strip $(GEN_OPTS_QUOTED)), $(shell echo $(GEN_OPTS_QUOTED) >> ccsCompiler.opt))
	$(if $(strip $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")), $(shell echo $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#") >> ccsCompiler.opt))
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsCompiler.opt
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_GlobalVariableDefs.obj: ../SRC/DSP2833x_GlobalVariableDefs.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(shell echo --silicon_version=28 > ccsCompiler.opt)
	$(shell echo -g >> ccsCompiler.opt)
	$(shell echo --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/1_AD7656_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/2_AD9833_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/3_SCI_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/4_DataPro_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/5_LED_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/6_TempCtrl_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/7_FTF_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/A_MAIN" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/INCLUDE" >> ccsCompiler.opt)
	$(shell echo --diag_warning=225 >> ccsCompiler.opt)
	$(shell echo --large_memory_model >> ccsCompiler.opt)
	$(shell echo --float_support=fpu32 >> ccsCompiler.opt)
	$(shell echo --preproc_with_compile >> ccsCompiler.opt)
	$(shell echo --preproc_dependency="SRC/DSP2833x_GlobalVariableDefs.pp" >> ccsCompiler.opt)
	$(shell echo --obj_directory="SRC" >> ccsCompiler.opt)
	$(if $(strip $(GEN_OPTS_QUOTED)), $(shell echo $(GEN_OPTS_QUOTED) >> ccsCompiler.opt))
	$(if $(strip $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")), $(shell echo $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#") >> ccsCompiler.opt))
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsCompiler.opt
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_PieCtrl.obj: ../SRC/DSP2833x_PieCtrl.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(shell echo --silicon_version=28 > ccsCompiler.opt)
	$(shell echo -g >> ccsCompiler.opt)
	$(shell echo --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/1_AD7656_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/2_AD9833_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/3_SCI_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/4_DataPro_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/5_LED_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/6_TempCtrl_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/7_FTF_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/A_MAIN" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/INCLUDE" >> ccsCompiler.opt)
	$(shell echo --diag_warning=225 >> ccsCompiler.opt)
	$(shell echo --large_memory_model >> ccsCompiler.opt)
	$(shell echo --float_support=fpu32 >> ccsCompiler.opt)
	$(shell echo --preproc_with_compile >> ccsCompiler.opt)
	$(shell echo --preproc_dependency="SRC/DSP2833x_PieCtrl.pp" >> ccsCompiler.opt)
	$(shell echo --obj_directory="SRC" >> ccsCompiler.opt)
	$(if $(strip $(GEN_OPTS_QUOTED)), $(shell echo $(GEN_OPTS_QUOTED) >> ccsCompiler.opt))
	$(if $(strip $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")), $(shell echo $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#") >> ccsCompiler.opt))
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsCompiler.opt
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_PieVect.obj: ../SRC/DSP2833x_PieVect.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(shell echo --silicon_version=28 > ccsCompiler.opt)
	$(shell echo -g >> ccsCompiler.opt)
	$(shell echo --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/1_AD7656_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/2_AD9833_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/3_SCI_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/4_DataPro_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/5_LED_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/6_TempCtrl_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/7_FTF_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/A_MAIN" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/INCLUDE" >> ccsCompiler.opt)
	$(shell echo --diag_warning=225 >> ccsCompiler.opt)
	$(shell echo --large_memory_model >> ccsCompiler.opt)
	$(shell echo --float_support=fpu32 >> ccsCompiler.opt)
	$(shell echo --preproc_with_compile >> ccsCompiler.opt)
	$(shell echo --preproc_dependency="SRC/DSP2833x_PieVect.pp" >> ccsCompiler.opt)
	$(shell echo --obj_directory="SRC" >> ccsCompiler.opt)
	$(if $(strip $(GEN_OPTS_QUOTED)), $(shell echo $(GEN_OPTS_QUOTED) >> ccsCompiler.opt))
	$(if $(strip $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")), $(shell echo $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#") >> ccsCompiler.opt))
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsCompiler.opt
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_Sci.obj: ../SRC/DSP2833x_Sci.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(shell echo --silicon_version=28 > ccsCompiler.opt)
	$(shell echo -g >> ccsCompiler.opt)
	$(shell echo --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/1_AD7656_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/2_AD9833_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/3_SCI_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/4_DataPro_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/5_LED_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/6_TempCtrl_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/7_FTF_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/A_MAIN" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/INCLUDE" >> ccsCompiler.opt)
	$(shell echo --diag_warning=225 >> ccsCompiler.opt)
	$(shell echo --large_memory_model >> ccsCompiler.opt)
	$(shell echo --float_support=fpu32 >> ccsCompiler.opt)
	$(shell echo --preproc_with_compile >> ccsCompiler.opt)
	$(shell echo --preproc_dependency="SRC/DSP2833x_Sci.pp" >> ccsCompiler.opt)
	$(shell echo --obj_directory="SRC" >> ccsCompiler.opt)
	$(if $(strip $(GEN_OPTS_QUOTED)), $(shell echo $(GEN_OPTS_QUOTED) >> ccsCompiler.opt))
	$(if $(strip $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")), $(shell echo $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#") >> ccsCompiler.opt))
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsCompiler.opt
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_SysCtrl.obj: ../SRC/DSP2833x_SysCtrl.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(shell echo --silicon_version=28 > ccsCompiler.opt)
	$(shell echo -g >> ccsCompiler.opt)
	$(shell echo --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/1_AD7656_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/2_AD9833_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/3_SCI_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/4_DataPro_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/5_LED_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/6_TempCtrl_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/7_FTF_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/A_MAIN" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/INCLUDE" >> ccsCompiler.opt)
	$(shell echo --diag_warning=225 >> ccsCompiler.opt)
	$(shell echo --large_memory_model >> ccsCompiler.opt)
	$(shell echo --float_support=fpu32 >> ccsCompiler.opt)
	$(shell echo --preproc_with_compile >> ccsCompiler.opt)
	$(shell echo --preproc_dependency="SRC/DSP2833x_SysCtrl.pp" >> ccsCompiler.opt)
	$(shell echo --obj_directory="SRC" >> ccsCompiler.opt)
	$(if $(strip $(GEN_OPTS_QUOTED)), $(shell echo $(GEN_OPTS_QUOTED) >> ccsCompiler.opt))
	$(if $(strip $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")), $(shell echo $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#") >> ccsCompiler.opt))
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsCompiler.opt
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_Xintf.obj: ../SRC/DSP2833x_Xintf.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(shell echo --silicon_version=28 > ccsCompiler.opt)
	$(shell echo -g >> ccsCompiler.opt)
	$(shell echo --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/1_AD7656_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/2_AD9833_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/3_SCI_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/4_DataPro_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/5_LED_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/6_TempCtrl_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/7_FTF_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/A_MAIN" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/INCLUDE" >> ccsCompiler.opt)
	$(shell echo --diag_warning=225 >> ccsCompiler.opt)
	$(shell echo --large_memory_model >> ccsCompiler.opt)
	$(shell echo --float_support=fpu32 >> ccsCompiler.opt)
	$(shell echo --preproc_with_compile >> ccsCompiler.opt)
	$(shell echo --preproc_dependency="SRC/DSP2833x_Xintf.pp" >> ccsCompiler.opt)
	$(shell echo --obj_directory="SRC" >> ccsCompiler.opt)
	$(if $(strip $(GEN_OPTS_QUOTED)), $(shell echo $(GEN_OPTS_QUOTED) >> ccsCompiler.opt))
	$(if $(strip $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")), $(shell echo $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#") >> ccsCompiler.opt))
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsCompiler.opt
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_usDelay.obj: ../SRC/DSP2833x_usDelay.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(shell echo --silicon_version=28 > ccsCompiler.opt)
	$(shell echo -g >> ccsCompiler.opt)
	$(shell echo --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/1_AD7656_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/2_AD9833_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/3_SCI_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/4_DataPro_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/5_LED_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/6_TempCtrl_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/7_FTF_ARL" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/A_MAIN" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/4_NEW_Data_Process/INCLUDE" >> ccsCompiler.opt)
	$(shell echo --diag_warning=225 >> ccsCompiler.opt)
	$(shell echo --large_memory_model >> ccsCompiler.opt)
	$(shell echo --float_support=fpu32 >> ccsCompiler.opt)
	$(shell echo --preproc_with_compile >> ccsCompiler.opt)
	$(shell echo --preproc_dependency="SRC/DSP2833x_usDelay.pp" >> ccsCompiler.opt)
	$(shell echo --obj_directory="SRC" >> ccsCompiler.opt)
	$(if $(strip $(GEN_OPTS_QUOTED)), $(shell echo $(GEN_OPTS_QUOTED) >> ccsCompiler.opt))
	$(if $(strip $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")), $(shell echo $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#") >> ccsCompiler.opt))
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsCompiler.opt
	@echo 'Finished building: $<'
	@echo ' '


