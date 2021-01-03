################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./TISource/DSP2833x_ADC_cal.obj" \
"./TISource/DSP2833x_Adc.obj" \
"./TISource/DSP2833x_CodeStartBranch.obj" \
"./TISource/DSP2833x_CpuTimers.obj" \
"./TISource/DSP2833x_DefaultIsr.obj" \
"./TISource/DSP2833x_EPwm.obj" \
"./TISource/DSP2833x_GlobalVariableDefs.obj" \
"./TISource/DSP2833x_MemCopy.obj" \
"./TISource/DSP2833x_PieCtrl.obj" \
"./TISource/DSP2833x_PieVect.obj" \
"./TISource/DSP2833x_SysCtrl.obj" \
"./TISource/DSP2833x_usDelay.obj" \
"./User_program/ADC_int.obj" \
"./User_program/Axis_transform.obj" \
"./User_program/EPWM_int.obj" \
"./User_program/GPIO_int.obj" \
"./User_program/KEY.obj" \
"./User_program/LCD12864.obj" \
"./User_program/Main_PMSM_QEncoder.obj" \
"./User_program/PI_Cale.obj" \
"./User_program/QEP_encoder.obj" \
"./User_program/SCI_RS232.obj" \
"./User_program/Spi.obj" \
"./User_program/Svpwm_dq.obj" \
"./User_program/Task_function.obj" \
"./User_program/Timer_function.obj" \
"../F28335.cmd" \
"../TISource/DSP2833x_Headers_nonBIOS.cmd" \
"../TI_lib/IQmath_fpu32.lib" \
"../TI_lib/rts2800_fpu32_fast_supplement.lib" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include TISource/subdir_vars.mk
-include TI_lib/subdir_vars.mk
-include User_program/subdir_vars.mk
-include subdir_rules.mk
-include TISource/subdir_rules.mk
-include TI_lib/subdir_rules.mk
-include User_program/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
PMSM_QEnconder_Joy_ADC_parallel.out \

EXE_OUTPUTS__QUOTED += \
"PMSM_QEnconder_Joy_ADC_parallel.out" \

BIN_OUTPUTS += \
PMSM_QEnconder_Joy_ADC_parallel.hex \

BIN_OUTPUTS__QUOTED += \
"PMSM_QEnconder_Joy_ADC_parallel.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "PMSM_QEnconder_Joy_ADC_parallel.out"

# Tool invocations
PMSM_QEnconder_Joy_ADC_parallel.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --diag_warning=225 --diag_wrap=off --display_error_number -z -m"PMSM_QEnconder_Joy_ADC_parallel.map" --stack_size=0x300 --warn_sections -i"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="PMSM_QEnconder_Joy_ADC_parallel_linkInfo.xml" --rom_model -o "PMSM_QEnconder_Joy_ADC_parallel.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

PMSM_QEnconder_Joy_ADC_parallel.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/hex2000"  -o "PMSM_QEnconder_Joy_ADC_parallel.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "TISource\DSP2833x_ADC_cal.obj" "TISource\DSP2833x_Adc.obj" "TISource\DSP2833x_CodeStartBranch.obj" "TISource\DSP2833x_CpuTimers.obj" "TISource\DSP2833x_DefaultIsr.obj" "TISource\DSP2833x_EPwm.obj" "TISource\DSP2833x_GlobalVariableDefs.obj" "TISource\DSP2833x_MemCopy.obj" "TISource\DSP2833x_PieCtrl.obj" "TISource\DSP2833x_PieVect.obj" "TISource\DSP2833x_SysCtrl.obj" "TISource\DSP2833x_usDelay.obj" "User_program\ADC_int.obj" "User_program\Axis_transform.obj" "User_program\EPWM_int.obj" "User_program\GPIO_int.obj" "User_program\KEY.obj" "User_program\LCD12864.obj" "User_program\Main_PMSM_QEncoder.obj" "User_program\PI_Cale.obj" "User_program\QEP_encoder.obj" "User_program\SCI_RS232.obj" "User_program\Spi.obj" "User_program\Svpwm_dq.obj" "User_program\Task_function.obj" "User_program\Timer_function.obj" 
	-$(RM) "TISource\DSP2833x_Adc.d" "TISource\DSP2833x_CpuTimers.d" "TISource\DSP2833x_DefaultIsr.d" "TISource\DSP2833x_EPwm.d" "TISource\DSP2833x_GlobalVariableDefs.d" "TISource\DSP2833x_MemCopy.d" "TISource\DSP2833x_PieCtrl.d" "TISource\DSP2833x_PieVect.d" "TISource\DSP2833x_SysCtrl.d" "User_program\ADC_int.d" "User_program\Axis_transform.d" "User_program\EPWM_int.d" "User_program\GPIO_int.d" "User_program\KEY.d" "User_program\LCD12864.d" "User_program\Main_PMSM_QEncoder.d" "User_program\PI_Cale.d" "User_program\QEP_encoder.d" "User_program\SCI_RS232.d" "User_program\Spi.d" "User_program\Svpwm_dq.d" "User_program\Task_function.d" "User_program\Timer_function.d" 
	-$(RM) "TISource\DSP2833x_ADC_cal.d" "TISource\DSP2833x_CodeStartBranch.d" "TISource\DSP2833x_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

