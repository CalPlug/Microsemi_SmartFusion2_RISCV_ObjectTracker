open_project -project {C:\Users\REN\Documents\GitHub\Microsemi_SmartFusion2_RISCV_ObjectTracker\SF2_CoreRISCV_AXI4_ObjectTracker\designer\PROC_SUBSYSTEM\PROC_SUBSYSTEM_fp\PROC_SUBSYSTEM.pro}
set_programming_file -name {M2S025} -file {C:\Users\REN\Documents\GitHub\Microsemi_SmartFusion2_RISCV_ObjectTracker\SF2_CoreRISCV_AXI4_ObjectTracker\designer\PROC_SUBSYSTEM\PROC_SUBSYSTEM.ipd}
enable_device -name {M2S025} -enable 1
set_programming_action -action {PROGRAM} -name {M2S025} 
run_selected_actions
set_programming_file -name {M2S025} -no_file
save_project
close_project
