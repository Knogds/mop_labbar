.PHONY: clean All

All:
	@echo "----------Building project:[ mop_3-1 - Debug ]----------"
	@cd "mop_3-1" && "$(MAKE)" -f  "mop_3-1.mk" && "$(MAKE)" -f  "mop_3-1.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ mop_3-1 - Debug ]----------"
	@cd "mop_3-1" && "$(MAKE)" -f  "mop_3-1.mk" clean
