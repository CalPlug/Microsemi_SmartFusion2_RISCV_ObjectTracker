set_component MSS_SUBSYSTEM_sb_CCC_0_FCCC
# Microsemi Corp.
# Date: 2017-Jun-15 10:02:25
#

create_clock -period 20 [ get_pins { CCC_INST/CLK0_PAD } ]
create_generated_clock -multiply_by 33 -divide_by 25 -source [ get_pins { CCC_INST/CLK0_PAD } ] -phase 0 [ get_pins { CCC_INST/GL0 } ]
create_generated_clock -multiply_by 33 -divide_by 25 -source [ get_pins { CCC_INST/CLK0_PAD } ] -phase 0 [ get_pins { CCC_INST/GL2 } ]
