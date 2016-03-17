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
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/INCLUDE" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/ARL" --include_path="C:/workspace/AD9833_test/INCLUDE" --include_path="C:/workspace/AD9833_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_ADC_cal.pp" --obj_directory="SRC" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_Adc.obj: ../SRC/DSP2833x_Adc.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/INCLUDE" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/ARL" --include_path="C:/workspace/AD9833_test/INCLUDE" --include_path="C:/workspace/AD9833_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_Adc.pp" --obj_directory="SRC" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_CodeStartBranch.obj: ../SRC/DSP2833x_CodeStartBranch.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/INCLUDE" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/ARL" --include_path="C:/workspace/AD9833_test/INCLUDE" --include_path="C:/workspace/AD9833_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_CodeStartBranch.pp" --obj_directory="SRC" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_CpuTimers.obj: ../SRC/DSP2833x_CpuTimers.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/INCLUDE" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/ARL" --include_path="C:/workspace/AD9833_test/INCLUDE" --include_path="C:/workspace/AD9833_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_CpuTimers.pp" --obj_directory="SRC" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_DefaultIsr.obj: ../SRC/DSP2833x_DefaultIsr.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/INCLUDE" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/ARL" --include_path="C:/workspace/AD9833_test/INCLUDE" --include_path="C:/workspace/AD9833_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_DefaultIsr.pp" --obj_directory="SRC" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_GlobalVariableDefs.obj: ../SRC/DSP2833x_GlobalVariableDefs.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/INCLUDE" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/ARL" --include_path="C:/workspace/AD9833_test/INCLUDE" --include_path="C:/workspace/AD9833_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_GlobalVariableDefs.pp" --obj_directory="SRC" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_PieCtrl.obj: ../SRC/DSP2833x_PieCtrl.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/INCLUDE" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/ARL" --include_path="C:/workspace/AD9833_test/INCLUDE" --include_path="C:/workspace/AD9833_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_PieCtrl.pp" --obj_directory="SRC" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_PieVect.obj: ../SRC/DSP2833x_PieVect.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/INCLUDE" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/ARL" --include_path="C:/workspace/AD9833_test/INCLUDE" --include_path="C:/workspace/AD9833_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_PieVect.pp" --obj_directory="SRC" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_Sci.obj: ../SRC/DSP2833x_Sci.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/INCLUDE" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/ARL" --include_path="C:/workspace/AD9833_test/INCLUDE" --include_path="C:/workspace/AD9833_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_Sci.pp" --obj_directory="SRC" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_SysCtrl.obj: ../SRC/DSP2833x_SysCtrl.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/INCLUDE" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/ARL" --include_path="C:/workspace/AD9833_test/INCLUDE" --include_path="C:/workspace/AD9833_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_SysCtrl.pp" --obj_directory="SRC" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_Xintf.obj: ../SRC/DSP2833x_Xintf.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/INCLUDE" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/ARL" --include_path="C:/workspace/AD9833_test/INCLUDE" --include_path="C:/workspace/AD9833_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_Xintf.pp" --obj_directory="SRC" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

SRC/DSP2833x_usDelay.obj: ../SRC/DSP2833x_usDelay.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/INCLUDE" --include_path="E:/01_Master_project/Water_Detection_Project/04_Software_Design/AD9833_test/ARL" --include_path="C:/workspace/AD9833_test/INCLUDE" --include_path="C:/workspace/AD9833_test/ARL" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_usDelay.pp" --obj_directory="SRC" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


