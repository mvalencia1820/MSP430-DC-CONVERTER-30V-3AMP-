################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'GNU Compiler: $<'
	"" -c -mmcu=msp430g2553 -DF_CPU=16000000L -DARDUINO=101 -DENERGIA=12 -I"E:/Martin/TEXAS INSTRUMENT/energia-0101E0012/hardware/msp430/cores/msp430" -I"E:/Martin/TEXAS INSTRUMENT/energia-0101E0012/hardware/msp430/variants/launchpad" -I -Os -ffunction-sections -fdata-sections -g -gstrict-dwarf -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" --super_quiet -o"$@" $(GEN_OPTS__FLAG) "$<"
	@echo ' '


