set_device \
    -family  SmartFusion2 \
    -die     PA4M2500_N \
    -package vf256 \
    -speed   STD \
    -tempr   {COM} \
    -voltr   {COM}
set_def {VOLTAGE} {1.2}
set_def {VCCI_1.2_VOLTR} {COM}
set_def {VCCI_1.5_VOLTR} {COM}
set_def {VCCI_1.8_VOLTR} {COM}
set_def {VCCI_2.5_VOLTR} {COM}
set_def {VCCI_3.3_VOLTR} {COM}
set_def {RTG4_MITIGATION_ON} {0}
set_def USE_CONSTRAINTS_FLOW 1
set_def NETLIST_TYPE EDIF
set_name PROC_SUBSYSTEM
set_workdir {C:\Users\REN\Desktop\199\workplace2\M2S025-Creative-Board\Modify_The_FPGA_Design\SF2_CoreRISCV_AXI4_TickTackToe\designer\PROC_SUBSYSTEM}
set_log     {C:\Users\REN\Desktop\199\workplace2\M2S025-Creative-Board\Modify_The_FPGA_Design\SF2_CoreRISCV_AXI4_TickTackToe\designer\PROC_SUBSYSTEM\PROC_SUBSYSTEM_coverage_pr.log}
set_design_state pre_layout