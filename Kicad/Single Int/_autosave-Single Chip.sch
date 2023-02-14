EESchema Schematic File Version 5
EELAYER 43 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
Comment5 ""
Comment6 ""
Comment7 ""
Comment8 ""
Comment9 ""
$EndDescr
Text Notes 700  400  0    500  ~ 100
This does not match PCB
Text Label 1650 2600 2    50   ~ 0
AD15
Text Label 1650 2700 2    50   ~ 0
A16
Text Label 1650 2900 2    50   ~ 0
RESET
Text Label 1650 3000 2    50   ~ 0
AD11
Text Label 1650 3100 2    50   ~ 0
A17
Text Label 1650 3300 2    50   ~ 0
AD1
Text Label 1650 3400 2    50   ~ 0
INTR
Text Label 1650 3500 2    50   ~ 0
CLK
Text Label 1650 3700 2    50   ~ 0
AD9
Text Label 1650 3800 2    50   ~ 0
A18
Text Label 1650 3900 2    50   ~ 0
A19
Text Label 1650 4000 2    50   ~ 0
BHE
Text Label 1650 4100 2    50   ~ 0
AD0
Text Label 1650 4200 2    50   ~ 0
AD10
Text Label 2150 4800 3    50   ~ 0
GND
Text Label 2350 2200 1    50   ~ 0
5+
Text Label 2550 2200 1    50   ~ 0
3.3V
Text Label 2750 4800 3    50   ~ 0
GND
Text Label 3250 2600 0    50   ~ 0
AD5
Text Label 3250 2700 0    50   ~ 0
INTA
Text Label 3250 2900 0    50   ~ 0
AD14
Text Label 3250 3000 0    50   ~ 0
AD13
Text Label 3250 3200 0    50   ~ 0
AD12
Text Label 3250 3300 0    50   ~ 0
AD4
Text Label 3250 3400 0    50   ~ 0
AD3
Text Label 3250 3600 0    50   ~ 0
DTR
Text Label 3250 3700 0    50   ~ 0
IO_M
Text Label 3250 3800 0    50   ~ 0
AD6
Text Label 3250 3900 0    50   ~ 0
AD8
Text Label 3250 4000 0    50   ~ 0
AD7
Text Label 3250 4200 0    50   ~ 0
ALE
Text Label 3250 4300 0    50   ~ 0
AD2
Text Label 4850 2100 2    50   ~ 0
CLK
Text Label 4850 2300 2    50   ~ 0
3.3V
Text Label 4850 2500 2    50   ~ 0
RESET
Text Label 4850 2700 2    50   ~ 0
GND
Text Label 4850 2900 2    50   ~ 0
INTR
Text Label 4850 3100 2    50   ~ 0
INTA
Text Label 4850 3500 2    50   ~ 0
GND
Text Label 4850 3700 2    50   ~ 0
BHE
Text Label 4850 3900 2    50   ~ 0
GND
Text Label 4850 4100 2    50   ~ 0
3.3V
Text Label 5450 5400 3    50   ~ 0
GND
Text Label 5550 1800 0    50   ~ 0
3.3V
Text Label 5650 5400 3    50   ~ 0
GND
Text Label 6250 2100 0    50   ~ 0
DTR
Text Label 6250 2300 0    50   ~ 0
ALE
Text Label 6250 2500 0    50   ~ 0
AD0
Text Label 6250 2600 0    50   ~ 0
AD1
Text Label 6250 2700 0    50   ~ 0
AD2
Text Label 6250 2800 0    50   ~ 0
AD3
Text Label 6250 2900 0    50   ~ 0
AD4
Text Label 6250 3000 0    50   ~ 0
AD5
Text Label 6250 3100 0    50   ~ 0
AD6
Text Label 6250 3200 0    50   ~ 0
AD7
Text Label 6250 3400 0    50   ~ 0
AD8
Text Label 6250 3500 0    50   ~ 0
AD9
Text Label 6250 3600 0    50   ~ 0
AD10
Text Label 6250 3700 0    50   ~ 0
AD11
Text Label 6250 3800 0    50   ~ 0
AD12
Text Label 6250 3900 0    50   ~ 0
AD13
Text Label 6250 4000 0    50   ~ 0
AD14
Text Label 6250 4100 0    50   ~ 0
AD15
Text Label 6250 4300 0    50   ~ 0
A16
Text Label 6250 4400 0    50   ~ 0
A17
Text Label 6250 4500 0    50   ~ 0
A18
Text Label 6250 4600 0    50   ~ 0
A19
Text Label 6250 4800 0    50   ~ 0
IO_M
Text Label 8200 1750 0    50   ~ 0
5+
$Comp
L Connector:Raspberry_Pi_2_3 J1
U 1 1 5EF39620
P 2450 3500
F 0 "J1" H 2450 4981 50  0000 C CNN
F 1 "Raspberry_Pi_2_3" H 2450 4890 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x20_P2.54mm_Vertical" H 2450 3500 50  0001 C CNN
F 3 "https://www.raspberrypi.org/documentation/hardware/raspberrypi/schematics/rpi_SCH_3bplus_1p0_reduced.pdf" H 2450 3500 50  0001 C CNN
	1    2450 3500
	1    0    0    -1  
$EndComp
$Comp
L MCU_Intel:8088_Min_Mode U1
U 1 1 5EF37BD7
P 5550 3600
F 0 "U1" H 5550 5581 50  0000 C CNN
F 1 "8088_Min_Mode" H 5550 5490 50  0000 C CNN
F 2 "Package_DIP:DIP-40_W15.24mm_LongPads" H 5600 3700 50  0001 C CIN
F 3 "http://datasheets.chipdb.org/Intel/x86/808x/datashts/8088/231456-006.pdf" H 5550 3650 50  0001 C CNN
	1    5550 3600
	1    0    0    -1  
$EndComp
$EndSCHEMATC
