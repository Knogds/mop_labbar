.PHONY: clean All

All:
	@echo "----------Building project:[ mop_3-5_spindeljakt - Debug ]----------"
	@cd "mop_3-5_spindeljakt" && "$(MAKE)" -f  "mop_3-5_spindeljakt.mk" && "$(MAKE)" -f  "mop_3-5_spindeljakt.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ mop_3-5_spindeljakt - Debug ]----------"
	@cd "mop_3-5_spindeljakt" && "$(MAKE)" -f  "mop_3-5_spindeljakt.mk" clean
