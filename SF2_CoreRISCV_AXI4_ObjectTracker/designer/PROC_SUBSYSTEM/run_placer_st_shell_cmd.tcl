read_sdc -scenario "place_and_route" -netlist "user" -pin_separator "/" -ignore_errors {C:/Users/REN/Documents/GitHub/Microsemi_SmartFusion2_RISCV_ObjectTracker/SF2_CoreRISCV_AXI4_ObjectTracker/designer/PROC_SUBSYSTEM/place_route.sdc}
set_options -tdpr_scenario "place_and_route" 
save
set_options -analysis_scenario "place_and_route"
report -type combinational_loops -format xml {C:\Users\REN\Documents\GitHub\Microsemi_SmartFusion2_RISCV_ObjectTracker\SF2_CoreRISCV_AXI4_ObjectTracker\designer\PROC_SUBSYSTEM\PROC_SUBSYSTEM_layout_combinational_loops.xml}
report -type slack {C:\Users\REN\Documents\GitHub\Microsemi_SmartFusion2_RISCV_ObjectTracker\SF2_CoreRISCV_AXI4_ObjectTracker\designer\PROC_SUBSYSTEM\pinslacks.txt}
