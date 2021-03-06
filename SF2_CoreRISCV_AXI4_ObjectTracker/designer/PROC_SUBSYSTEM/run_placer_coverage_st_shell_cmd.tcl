read_sdc -scenario "place_and_route" -netlist "user" -pin_separator "/" -ignore_errors {C:/Users/REN/Documents/GitHub/Microsemi_SmartFusion2_RISCV_ObjectTracker/SF2_CoreRISCV_AXI4_ObjectTracker/designer/PROC_SUBSYSTEM/place_route.sdc}
set_options -tdpr_scenario "place_and_route" 
save
set_options -analysis_scenario "place_and_route"
set coverage [report \
    -type     constraints_coverage \
    -format   xml \
    -slacks   no \
    {C:\Users\REN\Documents\GitHub\Microsemi_SmartFusion2_RISCV_ObjectTracker\SF2_CoreRISCV_AXI4_ObjectTracker\designer\PROC_SUBSYSTEM\PROC_SUBSYSTEM_place_and_route_constraint_coverage.xml}]
set reportfile {C:\Users\REN\Documents\GitHub\Microsemi_SmartFusion2_RISCV_ObjectTracker\SF2_CoreRISCV_AXI4_ObjectTracker\designer\PROC_SUBSYSTEM\coverage_placeandroute}
set fp [open $reportfile w]
puts $fp $coverage
close $fp
