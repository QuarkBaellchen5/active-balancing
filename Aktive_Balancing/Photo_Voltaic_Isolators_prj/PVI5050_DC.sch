<Qucs Schematic 1.0.1>
<Properties>
  <View=0,0,1188,800,1,0,0>
  <Grid=10,10,1>
  <DataSet=PVI5050_DC.dat>
  <DataDisplay=PVI5050_DC.dpl>
  <OpenDisplay=0>
  <Script=PVI5050_DC.m>
  <RunScript=0>
  <showFrame=0>
  <FrameText0=Title>
  <FrameText1=Drawn By:>
  <FrameText2=Date:>
  <FrameText3=Revision:>
</Properties>
<Symbol>
</Symbol>
<Components>
  <GND * 1 180 280 0 0 0 0>
  <GND * 1 100 300 0 0 0 0>
  <GND * 1 340 280 0 0 0 0>
  <.DC DC1 1 100 370 0 40 0 0 "26.85" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "no" 0 "150" 0 "no" 0 "none" 0 "CroutLU" 0>
  <GND * 1 400 300 0 0 0 0>
  <Sub SUB1 1 260 230 -57 -96 0 0 "PVI5050.sch" 1>
  <Idc I1 1 100 250 -53 -19 1 1 "1A" 1>
  <.SW SW1 1 280 370 0 65 0 0 "DC1" 1 "lin" 1 "I1" 1 "0" 1 "20 mA" 1 "101" 1 "false" 0>
  <R R1 1 400 250 15 -26 0 1 "4.7MEG" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "US" 0>
</Components>
<Wires>
  <100 280 100 300 "" 0 0 0 "">
  <100 200 100 220 "" 0 0 0 "">
  <100 200 200 200 "" 0 0 0 "">
  <180 260 200 260 "" 0 0 0 "">
  <180 260 180 280 "" 0 0 0 "">
  <320 260 340 260 "" 0 0 0 "">
  <340 260 340 280 "" 0 0 0 "">
  <320 200 400 200 "Vout" 390 160 56 "">
  <400 200 400 220 "" 0 0 0 "">
  <400 280 400 300 "" 0 0 0 "">
</Wires>
<Diagrams>
  <Rect 550 574 461 414 3 #c0c0c0 1 00 1 -1 0.2 1 0 0 1 8 1 -1 0.2 1 315 0 225 1 0 0 "" "" "">
	<"ngspice/v(vout)" #0000ff 0 3 0 0 0>
  </Rect>
</Diagrams>
<Paintings>
</Paintings>
