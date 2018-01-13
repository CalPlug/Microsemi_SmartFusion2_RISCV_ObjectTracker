set_device \
    -fam SmartFusion2 \
    -die PA4M2500_N \
    -pkg vf256
set_input_cfg \
	-path {C:/Users/REN/Documents/GitHub/Microsemi_SmartFusion2_RISCV_ObjectTracker/SF2_CoreRISCV_AXI4_ObjectTracker/component/work/MSS_SUBSYSTEM_sb_MSS/ENVM.cfg}
set_output_efc \
    -path {C:\Users\REN\Documents\GitHub\Microsemi_SmartFusion2_RISCV_ObjectTracker\SF2_CoreRISCV_AXI4_ObjectTracker\designer\PROC_SUBSYSTEM\PROC_SUBSYSTEM.efc}
set_proj_dir \
    -path {C:\Users\REN\Documents\GitHub\Microsemi_SmartFusion2_RISCV_ObjectTracker\SF2_CoreRISCV_AXI4_ObjectTracker}
gen_prg -use_init false
