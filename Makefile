.PHONY: clean All

All:
	@echo "----------Building project:[ Week5 -  ]----------"
	@cd "Week5" && "$(MAKE)" -f  "Week5.mk"
clean:
	@echo "----------Cleaning project:[ Week5 -  ]----------"
	@cd "Week5" && "$(MAKE)" -f  "Week5.mk" clean
