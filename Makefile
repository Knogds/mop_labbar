.PHONY: clean All

All:
	@echo "----------Building project:[ mop_4-1 - Debug ]----------"
	@cd "mop_4-1" && "$(MAKE)" -f  "mop_4-1.mk" && "$(MAKE)" -f  "mop_4-1.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ mop_4-1 - Debug ]----------"
	@cd "mop_4-1" && "$(MAKE)" -f  "mop_4-1.mk" clean
