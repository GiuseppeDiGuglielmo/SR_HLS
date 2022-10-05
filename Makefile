help:
	@echo "INFO: make <tab> to show targets"
.PHONY: help

clean:
	@rm -rf myproject_prj
	@rm -rf tb_data
	@rm -f vivado.jou vivado.log vivado_hls.log
.PHONY: clean
