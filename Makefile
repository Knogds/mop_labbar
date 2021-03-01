.PHONY: clean All

All:
	@echo "----------Building project:[ mop_4-3 - Debug ]----------"
	@cd "mop_4-3" && "$(MAKE)" -f  "mop_4-3.mk" && "$(MAKE)" -f  "mop_4-3.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ mop_4-3 - Debug ]----------"
	@cd "mop_4-3" && "$(MAKE)" -f  "mop_4-3.mk" clean
