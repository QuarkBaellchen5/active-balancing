<Qucs Schematic 1.0.1>
<Properties>
  <View=0,6,1910,1035,1,0,0>
  <Grid=10,10,1>
  <DataSet=J201_IV_Sweep.dat>
  <DataDisplay=J201_IV_Sweep.dpl>
  <OpenDisplay=0>
  <Script=J201_IV_Sweep.m>
  <RunScript=0>
  <showFrame=0>
  <FrameText0=Titel>
  <FrameText1=Gezeichnet von:>
  <FrameText2=Datum:>
  <FrameText3=Revision:>
</Properties>
<Symbol>
</Symbol>
<Components>
  <.DC DC1 1 50 280 0 40 0 0 "26.85" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "no" 0 "150" 0 "no" 0 "none" 0 "CroutLU" 0>
  <Vdc V2 1 100 170 -55 -19 0 1 "1" 1>
  <GND * 1 100 220 0 0 0 0>
  <IProbe Pr1 1 250 60 -10 18 1 2>
  <Vdc V1 1 320 110 28 -16 0 1 "1" 1>
  <GND * 1 320 160 0 0 0 0>
  <GND * 1 180 180 0 0 0 0>
  <NJF_SPICE J1 1 180 130 15 -18 0 0 "J201" 1 "" 0 "" 0 "" 0 "" 0>
  <SpiceModel SpiceModel1 0 70 550 -27 16 0 0 ".MODEL J201 NJF(Beta=1.621m Betatce=-500m Rd=1 Rs=1 Lambda=2.236m Vto=-600m Vtotc=-2.5m Is=114.5f Isr=1.091p N=1 Nr=2 Xti=3 Alpha=506.8u Vk=251.7 Cgd=4.667p M=227.1m Pb=500m Fc=500m Cgs=2.992p Kf=0.6042f Af=1)" 1 "" 0 "" 0 "" 0 "Line_5=" 0>
  <.SW SW1 1 240 280 0 65 0 0 "DC1" 1 "lin" 1 "V1" 1 "0" 1 "5" 1 "51" 1 "false" 0>
  <SpiceModel SpiceModel2 1 70 650 -27 16 0 0 ".MODEL J201 NJF(Beta=1.621m Betatce=-500m Rd=1 Rs=1 Lambda=2.236m Vto=-600m Vtotc=-2.5m Is=114.5f Isr=1.091p N=1 Nr=2 Xti=3 Alpha=506.8u Vk=251.7 Cgd=4.667p M=227.1m Pb=500m Fc=500m Cgs=2.992p Kf=0.6042f Af=1)" 1 "" 0 "" 0 "" 0 "Line_5=" 0>
  <.SW SW2 1 390 280 0 65 0 0 "SW1" 1 "lin" 1 "V2" 1 "-1" 1 "0" 1 "11" 1 "false" 0>
</Components>
<Wires>
  <100 130 100 140 "" 0 0 0 "">
  <100 130 150 130 "" 0 0 0 "">
  <100 200 100 220 "" 0 0 0 "">
  <180 60 180 100 "" 0 0 0 "">
  <180 60 220 60 "" 0 0 0 "">
  <280 60 320 60 "" 0 0 0 "">
  <320 60 320 80 "" 0 0 0 "">
  <320 140 320 160 "" 0 0 0 "">
  <180 160 180 180 "" 0 0 0 "">
</Wires>
<Diagrams>
  <Rect 600 421 440 361 3 #c0c0c0 1 00 1 0 0.2 1 1 -0.1 0.5 1.1 1 -0.1 0.5 1.1 315 0 225 0 0 0 "" "" "">
	<"ngspice/i(pr1)" #0000ff 0 3 0 0 0>
  </Rect>
</Diagrams>
<Paintings>
</Paintings>
