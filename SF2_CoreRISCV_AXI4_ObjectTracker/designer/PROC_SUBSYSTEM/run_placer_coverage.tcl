set_family {SmartFusion2}
read_adl {C:\Users\REN\Desktop\199\workplace2\M2S025-Creative-Board\Modify_The_FPGA_Design\SF2_CoreRISCV_AXI4_TickTackToe\designer\PROC_SUBSYSTEM\PROC_SUBSYSTEM.adl}
map_netlist
read_sdc {C:\Users\REN\Desktop\199\workplace2\M2S025-Creative-Board\Modify_The_FPGA_Design\SF2_CoreRISCV_AXI4_TickTackToe\constraint\PROC_SUBSYSTEM_derived_constraints.sdc}
read_sdc {C:\Users\REN\Desktop\199\workplace2\M2S025-Creative-Board\Modify_The_FPGA_Design\SF2_CoreRISCV_AXI4_TickTackToe\constraint\user.sdc}
check_constraints {C:\Users\REN\Desktop\199\workplace2\M2S025-Creative-Board\Modify_The_FPGA_Design\SF2_CoreRISCV_AXI4_TickTackToe\designer\PROC_SUBSYSTEM\placer_coverage.log}
write_sdc -strict {C:\Users\REN\Desktop\199\workplace2\M2S025-Creative-Board\Modify_The_FPGA_Design\SF2_CoreRISCV_AXI4_TickTackToe\designer\PROC_SUBSYSTEM\place_route.sdc}
