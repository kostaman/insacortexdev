#add the 'hex' rule for avr
hex: $(EXEC)
	avr-objcopy -j .text -j .data -O ihex $(EXEC) $(EXEC).hex

EXTRA_FILES_CLEAN += $(EXEC).hex
