<Qucs Schematic 1.0.1>
<Properties>
  <View=0,0,1188,800,1,0,0>
  <Grid=10,10,1>
  <DataSet=VOM1271T_DC.dat>
  <DataDisplay=VOM1271T_DC.dpl>
  <OpenDisplay=0>
  <Script=VOM1271T_DC.m>
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
  <Idc I1 1 100 250 -56 -21 1 1 "1A" 1>
  <.SW SW1 1 280 370 0 65 0 0 "DC1" 1 "lin" 1 "I1" 1 "0" 1 "20 mA" 1 "101" 1 "false" 0>
  <GND * 1 360 280 0 0 0 0>
  <GND * 1 420 300 0 0 0 0>
  <R R1 1 420 250 15 -26 0 1 "4.7MEG" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "US" 0>
  <SPICEINIT SPICEINIT1 1 130 610 -30 16 0 0 "set ngbehavior=ltps" 1>
  <Sub SUB1 1 260 230 -40 -96 0 0 "VOM1271.sch" 1>
</Components>
<Wires>
  <100 280 100 300 "" 0 0 0 "">
  <180 260 180 280 "" 0 0 0 "">
  <180 260 200 260 "" 0 0 0 "">
  <100 200 100 220 "" 0 0 0 "">
  <100 200 200 200 "" 0 0 0 "">
  <340 260 360 260 "" 0 0 0 "">
  <420 280 420 300 "" 0 0 0 "">
  <360 260 360 280 "" 0 0 0 "">
  <420 200 420 220 "" 0 0 0 "">
  <340 200 420 200 "Vout" 410 160 56 "">
</Wires>
<Diagrams>
  <Rect 550 574 461 414 3 #c0c0c0 1 00 1 -1 0.2 1 0 0 1 8 1 -1 0.2 1 315 0 225 1 0 0 "" "" "">
	<"ngspice/v(vout)" #0000ff 0 3 0 0 0>
  </Rect>
</Diagrams>
<Paintings>
</Paintings>
