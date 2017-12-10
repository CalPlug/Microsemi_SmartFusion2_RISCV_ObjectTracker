`timescale 1ns/100ps
// Actel Corporation Proprietary and Confidential
// Copyright 2008 Actel Corporation.  All rights reserved.
// ANY USE OR REDISTRIBUTION IN PART OR IN WHOLE MUST BE HANDLED IN 
// ACCORDANCE WITH THE ACTEL LICENSE AGREEMENT AND MUST BE APPROVED 
// IN ADVANCE IN WRITING.  
// Revision Information:
// SVN Revision Information:
// SVN $Revision: 6419 $
// SVN $Date: 2009-02-04 04:34:22 -0800 (Wed, 04 Feb 2009) $
module
PROC_SUBSYSTEM_CoreGPIO_1_BFMA1l1OII
(
HCLK
,
HRESETN
,
HSEL
,
HWRITE
,
HADDR
,
HWDATA
,
HRDATA
,
HREADYIN
,
HREADYOUT
,
HTRANS
,
HSIZE
,
HBURST
,
HMASTLOCK
,
HPROT
,
HRESP
,
PSEL
,
PADDR
,
PWRITE
,
PENABLE
,
PWDATA
,
PRDATA
,
PREADY
,
PSLVERR
)
;
parameter
TPD
=
1
;
input
HCLK
;
input
HRESETN
;
input
HSEL
;
input
HWRITE
;
input
[
31
:
0
]
HADDR
;
input
[
31
:
0
]
HWDATA
;
output
[
31
:
0
]
HRDATA
;
wire
[
31
:
0
]
HRDATA
;
input
HREADYIN
;
output
HREADYOUT
;
wire
HREADYOUT
;
input
[
1
:
0
]
HTRANS
;
input
[
2
:
0
]
HSIZE
;
input
[
2
:
0
]
HBURST
;
input
HMASTLOCK
;
input
[
3
:
0
]
HPROT
;
output
HRESP
;
wire
HRESP
;
output
[
15
:
0
]
PSEL
;
wire
[
15
:
0
]
PSEL
;
output
[
31
:
0
]
PADDR
;
wire
[
31
:
0
]
PADDR
;
output
PWRITE
;
wire
PWRITE
;
output
PENABLE
;
wire
PENABLE
;
output
[
31
:
0
]
PWDATA
;
wire
[
31
:
0
]
PWDATA
;
input
[
31
:
0
]
PRDATA
;
input
PREADY
;
input
PSLVERR
;
parameter
[
1
:
0
]
BFMA1OOIII
=
0
;
parameter
[
1
:
0
]
BFMA1IOIII
=
1
;
parameter
[
1
:
0
]
BFMA1lOIII
=
2
;
parameter
[
1
:
0
]
BFMA1OIIII
=
3
;
reg
[
1
:
0
]
BFMA1IIIII
;
reg
BFMA1lIIII
;
reg
BFMA1OlIII
;
reg
[
15
:
0
]
BFMA1IlIII
;
reg
[
31
:
0
]
BFMA1llIII
;
reg
BFMA1O0III
;
reg
BFMA1I0III
;
reg
[
31
:
0
]
BFMA1l0III
;
wire
[
31
:
0
]
BFMA1O1III
;
reg
BFMA1I1III
;
reg
BFMA1l1III
;
always
@
(
posedge
HCLK
or
negedge
HRESETN
)
begin
if
(
HRESETN
==
1
'b
0
)
begin
BFMA1IIIII
<=
BFMA1OOIII
;
BFMA1lIIII
<=
1
'b
1
;
BFMA1llIII
<=
{
32
{
1
'b
0
}
}
;
BFMA1l0III
<=
{
32
{
1
'b
0
}
}
;
BFMA1O0III
<=
1
'b
0
;
BFMA1I0III
<=
1
'b
0
;
BFMA1OlIII
<=
1
'b
0
;
BFMA1I1III
<=
1
'b
0
;
BFMA1l1III
<=
1
'b
0
;
end
else
begin
BFMA1OlIII
<=
1
'b
0
;
BFMA1lIIII
<=
1
'b
0
;
BFMA1I1III
<=
1
'b
0
;
case
(
BFMA1IIIII
)
BFMA1OOIII
:
begin
if
(
HSEL
==
1
'b
1
&
HREADYIN
==
1
'b
1
&
(
HTRANS
[
1
]
)
==
1
'b
1
)
begin
BFMA1IIIII
<=
BFMA1IOIII
;
BFMA1llIII
<=
HADDR
;
BFMA1O0III
<=
HWRITE
;
BFMA1l0III
<=
HWDATA
;
BFMA1I0III
<=
1
'b
0
;
BFMA1I1III
<=
HWRITE
;
BFMA1l1III
<=
1
'b
1
;
end
else
begin
BFMA1lIIII
<=
1
'b
1
;
end
end
BFMA1IOIII
:
begin
BFMA1I0III
<=
1
'b
1
;
BFMA1IIIII
<=
BFMA1lOIII
;
end
BFMA1lOIII
:
begin
if
(
PREADY
==
1
'b
1
)
begin
BFMA1I0III
<=
1
'b
0
;
BFMA1l1III
<=
1
'b
0
;
if
(
PSLVERR
==
1
'b
0
)
begin
BFMA1IIIII
<=
BFMA1OOIII
;
if
(
HSEL
==
1
'b
1
&
HREADYIN
==
1
'b
1
&
(
HTRANS
[
1
]
)
==
1
'b
1
)
begin
BFMA1IIIII
<=
BFMA1IOIII
;
BFMA1llIII
<=
HADDR
;
BFMA1O0III
<=
HWRITE
;
BFMA1I1III
<=
HWRITE
;
BFMA1l1III
<=
1
'b
1
;
end
end
else
begin
BFMA1OlIII
<=
1
'b
1
;
BFMA1IIIII
<=
BFMA1OIIII
;
end
end
end
BFMA1OIIII
:
begin
BFMA1OlIII
<=
1
'b
1
;
BFMA1lIIII
<=
1
'b
1
;
BFMA1IIIII
<=
BFMA1OOIII
;
end
endcase
if
(
BFMA1I1III
==
1
'b
1
)
begin
BFMA1l0III
<=
HWDATA
;
end
end
end
always
@
(
BFMA1llIII
or
BFMA1l1III
)
begin
BFMA1IlIII
<=
{
16
{
1
'b
0
}
}
;
if
(
BFMA1l1III
==
1
'b
1
)
begin
begin
:
BFMA1IO10
integer
BFMA1I0I0
;
for
(
BFMA1I0I0
=
0
;
BFMA1I0I0
<=
15
;
BFMA1I0I0
=
BFMA1I0I0
+
1
)
begin
BFMA1IlIII
[
BFMA1I0I0
]
<=
(
BFMA1llIII
[
27
:
24
]
==
BFMA1I0I0
)
;
end
end
end
end
assign
BFMA1O1III
=
(
BFMA1I1III
==
1
'b
1
)
?
HWDATA
:
BFMA1l0III
;
assign
#
TPD
HRDATA
=
PRDATA
;
assign
#
TPD
HREADYOUT
=
BFMA1lIIII
|
(
PREADY
&
BFMA1l1III
&
BFMA1I0III
&
~
PSLVERR
)
;
assign
#
TPD
HRESP
=
BFMA1OlIII
;
assign
#
TPD
PSEL
=
BFMA1IlIII
;
assign
#
TPD
PADDR
=
BFMA1llIII
;
assign
#
TPD
PWRITE
=
BFMA1O0III
;
assign
#
TPD
PENABLE
=
BFMA1I0III
;
assign
#
TPD
PWDATA
=
BFMA1O1III
;
endmodule
