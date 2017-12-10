set_device \
    -fam SmartFusion2 \
    -die PA4M2500_N \
    -pkg vf256
set_input_cfg \
	-path {C:/Users/REN/Desktop/199/workplace2/M2S025-Creative-Board/Modify_The_FPGA_Design/SF2_CoreRISCV_AXI4_TickTackToe/component/work/MSS_SUBSYSTEM_sb_MSS/ENVM.cfg}
set_output_efc \
    -path {C:\Users\REN\Desktop\199\workplace2\M2S025-Creative-Board\Modify_The_FPGA_Design\SF2_CoreRISCV_AXI4_TickTackToe\designer\PROC_SUBSYSTEM\PROC_SUBSYSTEM.efc}
set_proj_dir \
    -path {C:\Users\REN\Desktop\199\workplace2\M2S025-Creative-Board\Modify_The_FPGA_Design\SF2_CoreRISCV_AXI4_TickTackToe}
gen_prg -use_init false
