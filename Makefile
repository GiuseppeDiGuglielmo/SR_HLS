help:
	@echo "INFO: make <tab> to show targets"
.PHONY: help

run-vivado-hls:
	vivado_hls build_prj.tcl
.PHONY: run-vivado-hls

run-verification:
	python py/csv_compare.py \
		--csim_file myproject_prj/solution1/csim/build/output.dat \
		--cosim_file myproject_prj/solution1/sim/wrapc/output.dat
.PHONY: run-verification

clean:
	@rm -rf myproject_prj
	@rm -f vivado.jou vivado.log vivado_hls.log
.PHONY: clean
