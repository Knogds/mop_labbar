.PHONY: clean All

All:
	@echo "----------Building project:[ mop_3-5 - Debug ]----------"
	@cd "mop_3-5" && "$(MAKE)" -f  "mop_3-5.mk" && "$(MAKE)" -f  "mop_3-5.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ mop_3-5 - Debug ]----------"
	@cd "mop_3-5" && "$(MAKE)" -f  "mop_3-5.mk" clean
