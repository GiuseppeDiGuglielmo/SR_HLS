help:
	@echo "INFO: make <tab> to show targets"
.PHONY: help

hls:
	vivado_hls build_prj.tcl
.PHONY: hls

#hls-gui:
#	vivado_hls build_prj.tcl -gui
#.PHONY: hls-gui

gui:
	vivado_hls -p myproject_prj
.PHONY: gui

verification:
	python py/csv_compare.py \
		--csim_file myproject_prj/solution1/csim/build/output.dat \
		--cosim_file myproject_prj/solution1/sim/wrapc/output.dat
.PHONY: verification

fifo-opt:
	python py/fifo_depth_optimization.py
.PHONY: fifo-opt

clean:
	@rm -rf myproject_prj
	@rm -f vivado.jou vivado.log vivado_hls.log
.PHONY: clean
