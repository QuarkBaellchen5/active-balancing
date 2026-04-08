<Qucs Schematic 1.0.1>
<Properties>
  <View=0,0,1188,800,1,0,0>
  <Grid=10,10,1>
  <DataSet=ACPL-K30T_TRAN.dat>
  <DataDisplay=ACPL-K30T_TRAN.dpl>
  <OpenDisplay=0>
  <Script=ACPL-K30T_TRAN.m>
  <RunScript=0>
  <showFrame=0>
  <FrameText0=Title>
  <FrameText1=Drawn By:>
  <FrameText2=Date:>
  <FrameText3=Revision:>
</Properties>
<Symbol>
  <.ID -20 -16 SUB>
  <Line -20 20 40 0 #000080 2 1>
  <Line 20 20 0 -40 #000080 2 1>
  <Line -20 -20 40 0 #000080 2 1>
  <Line -20 20 0 -40 #000080 2 1>
</Symbol>
<Components>
  <GND * 1 180 280 0 0 0 0>
  <GND * 1 100 300 0 0 0 0>
  <.DC DC1 1 100 370 0 40 0 0 "26.85" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "no" 0 "150" 0 "no" 0 "none" 0 "CroutLU" 0>
  <.TR TR1 1 280 370 0 66 0 0 "lin" 1 "0" 1 "5 ms" 1 "101" 1 "Trapezoidal" 0 "2" 0 "1 ns" 0 "1e-16" 0 "150" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "26.85" 0 "1e-3" 0 "1e-6" 0 "1" 0 "CroutLU" 0 "no" 0 "yes" 0 "0" 0>
  <GND * 1 360 280 0 0 0 0>
  <GND * 1 420 300 0 0 0 0>
  <R R1 1 420 250 15 -26 0 1 "4.7MEG" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "US" 0>
  <Irect I1 1 100 250 -99 -26 1 1 "20 mA" 1 "1 ms" 1 "4 ms" 1 "100 ns" 1 "100 ns" 1 "1 ms" 1>
  <SPICEINIT SPICEINIT1 1 130 590 -30 16 0 0 "set ngbehavior=ltps" 1>
  <Sub SUB1 1 260 230 -40 -96 0 0 "ACPL-K30T.sch" 1>
</Components>
<Wires>
  <100 280 100 300 "" 0 0 0 "">
  <420 280 420 300 "" 0 0 0 "">
  <420 200 420 220 "" 0 0 0 "">
  <340 200 420 200 "Vout" 420 160 66 "">
  <360 260 360 280 "" 0 0 0 "">
  <340 260 360 260 "" 0 0 0 "">
  <180 260 180 280 "" 0 0 0 "">
  <180 260 200 260 "" 0 0 0 "">
  <100 200 100 220 "" 0 0 0 "">
  <100 200 200 200 "" 0 0 0 "">
</Wires>
<Diagrams>
  <Rect 550 574 461 414 3 #c0c0c0 1 00 1 0 0.005 0.05 1 -0.349336 0.5 3.82835 1 -1 0.2 1 315 0 225 1 0 0 "" "" "">
	<"ngspice/tran.v(vout)" #0000ff 0 3 0 0 0>
  </Rect>
</Diagrams>
<Paintings>
</Paintings>
