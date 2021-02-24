EESchema Schematic File Version 4
LIBS:Pager-Interface (KiCAD)-cache
EELAYER 26 0
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
$EndDescr
$Comp
L Connector:USB_B_Micro J1
U 1 1 603652A3
P 1450 2850
F 0 "J1" H 1505 3317 50  0000 C CNN
F 1 "USB_B_Micro" H 1505 3226 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_GCT_USB3076-30-A" H 1600 2800 50  0001 C CNN
F 3 "~" H 1600 2800 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/USB-Connectors_Shenzhen-Kinghelm-Elec-KH-MICRO5P-JZH_C962224.html" H 1450 2850 50  0001 C CNN "JCLC"
	1    1450 2850
	1    0    0    -1  
$EndComp
$Comp
L Interface_USB:CP2102N-A01-GQFN24 U2
U 1 1 60365580
P 3300 2450
F 0 "U2" H 3400 3400 50  0000 C CNN
F 1 "CP2102N-A01-GQFN24" H 3800 3300 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-24-1EP_4x4mm_P0.5mm_EP2.6x2.6mm" H 3750 1650 50  0001 L CNN
F 3 "http://www.silabs.com/support%20documents/technicaldocs/cp2102n-datasheet.pdf" H 3350 1400 50  0001 C CNN
	1    3300 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 2650 1950 2650
Wire Wire Line
	1350 3250 1350 3550
Wire Wire Line
	1350 3550 1450 3550
Wire Wire Line
	1450 3550 1450 3250
Wire Wire Line
	1450 3550 1450 3650
Connection ~ 1450 3550
$Comp
L power:GND #PWR0101
U 1 1 603658FD
P 1450 3650
F 0 "#PWR0101" H 1450 3400 50  0001 C CNN
F 1 "GND" H 1455 3477 50  0000 C CNN
F 2 "" H 1450 3650 50  0001 C CNN
F 3 "" H 1450 3650 50  0001 C CNN
	1    1450 3650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 60365973
P 1950 950
F 0 "#PWR0102" H 1950 800 50  0001 C CNN
F 1 "+5V" H 1965 1123 50  0000 C CNN
F 2 "" H 1950 950 50  0001 C CNN
F 3 "" H 1950 950 50  0001 C CNN
	1    1950 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 2450 1950 2450
Wire Wire Line
	3300 3350 3300 3600
Wire Wire Line
	3300 3600 3400 3600
Wire Wire Line
	3400 3600 3400 3350
Wire Wire Line
	3400 3600 3400 3750
Connection ~ 3400 3600
$Comp
L power:GND #PWR0103
U 1 1 60365D36
P 3400 3750
F 0 "#PWR0103" H 3400 3500 50  0001 C CNN
F 1 "GND" H 3405 3577 50  0000 C CNN
F 2 "" H 3400 3750 50  0001 C CNN
F 3 "" H 3400 3750 50  0001 C CNN
	1    3400 3750
	1    0    0    -1  
$EndComp
Text Label 9600 2850 0    50   ~ 0
RX0
Text Label 9600 2750 0    50   ~ 0
TX0
Wire Wire Line
	3200 1550 3200 900 
Wire Wire Line
	3200 900  2450 900 
$Comp
L Device:C C4
U 1 1 60366ACE
P 2450 1250
F 0 "C4" H 2565 1296 50  0000 L CNN
F 1 "100nF" H 2565 1205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2488 1100 50  0001 C CNN
F 3 "~" H 2450 1250 50  0001 C CNN
	1    2450 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 900  2450 1100
Wire Wire Line
	2450 1400 2450 1550
$Comp
L power:GND #PWR0104
U 1 1 60366EE5
P 2450 1550
F 0 "#PWR0104" H 2450 1300 50  0001 C CNN
F 1 "GND" H 2455 1377 50  0000 C CNN
F 2 "" H 2450 1550 50  0001 C CNN
F 3 "" H 2450 1550 50  0001 C CNN
	1    2450 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  1250 950  1400
$Comp
L Device:C C1
U 1 1 60367798
P 950 1550
F 0 "C1" H 1065 1596 50  0000 L CNN
F 1 "100nF" H 1065 1505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 988 1400 50  0001 C CNN
F 3 "~" H 950 1550 50  0001 C CNN
	1    950  1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  1250 1500 1250
Wire Wire Line
	1500 1400 1500 1250
Connection ~ 1500 1250
Wire Wire Line
	1500 1250 1950 1250
Wire Wire Line
	950  1700 950  1850
Wire Wire Line
	1500 1700 1500 1850
$Comp
L power:GND #PWR0105
U 1 1 6036842B
P 950 1850
F 0 "#PWR0105" H 950 1600 50  0001 C CNN
F 1 "GND" H 955 1677 50  0000 C CNN
F 2 "" H 950 1850 50  0001 C CNN
F 3 "" H 950 1850 50  0001 C CNN
	1    950  1850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 60368447
P 1500 1850
F 0 "#PWR0106" H 1500 1600 50  0001 C CNN
F 1 "GND" H 1505 1677 50  0000 C CNN
F 2 "" H 1500 1850 50  0001 C CNN
F 3 "" H 1500 1850 50  0001 C CNN
	1    1500 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 950  1950 1250
Connection ~ 1950 1250
Wire Wire Line
	1950 1250 1950 2450
Connection ~ 1950 2450
Wire Wire Line
	1950 2450 1950 2650
Wire Wire Line
	2700 2750 1950 2750
Wire Wire Line
	1950 2750 1950 2650
Connection ~ 1950 2650
Wire Wire Line
	2700 2850 1750 2850
Wire Wire Line
	1750 2950 2700 2950
$Comp
L Transistor_BJT:BC817 Q1
U 1 1 6036C595
P 5050 2050
F 0 "Q1" H 5241 2096 50  0000 L CNN
F 1 "BC817" H 5241 2005 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5250 1975 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC817.pdf" H 5050 2050 50  0001 L CNN
	1    5050 2050
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC817 Q2
U 1 1 6036C5CD
P 5050 2750
F 0 "Q2" H 5241 2704 50  0000 L CNN
F 1 "BC817" H 5241 2795 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5250 2675 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC817.pdf" H 5050 2750 50  0001 L CNN
	1    5050 2750
	1    0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 6036D59F
P 4650 2050
F 0 "R1" V 4443 2050 50  0000 C CNN
F 1 "10k" V 4534 2050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4580 2050 50  0001 C CNN
F 3 "~" H 4650 2050 50  0001 C CNN
	1    4650 2050
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 6036D606
P 4650 2750
F 0 "R2" V 4443 2750 50  0000 C CNN
F 1 "10k" V 4534 2750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4580 2750 50  0001 C CNN
F 3 "~" H 4650 2750 50  0001 C CNN
	1    4650 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	4800 2050 4850 2050
Wire Wire Line
	4800 2750 4850 2750
Wire Wire Line
	3900 2450 4400 2450
Wire Wire Line
	4400 2450 4400 2050
Wire Wire Line
	4400 2050 4500 2050
Wire Wire Line
	4500 2750 4350 2750
Wire Wire Line
	4350 2750 4350 2350
Wire Wire Line
	4350 2050 3900 2050
Wire Wire Line
	3900 2150 4000 2150
Wire Wire Line
	3900 2250 4000 2250
Wire Wire Line
	4400 2450 5150 2450
Wire Wire Line
	5150 2450 5150 2550
Connection ~ 4400 2450
Wire Wire Line
	4350 2350 5150 2350
Wire Wire Line
	5150 2350 5150 2250
Connection ~ 4350 2350
Wire Wire Line
	4350 2350 4350 2050
Wire Wire Line
	5150 2950 5150 3050
Wire Wire Line
	5150 1850 5150 1700
Text Label 5150 1700 0    50   ~ 0
EN
Text Label 5150 3050 3    50   ~ 0
IO0
$Comp
L ESP32:ESP32-WROOM U4
U 1 1 603711F2
P 8600 3300
F 0 "U4" H 8575 4687 60  0000 C CNN
F 1 "ESP32-WROOM" H 8575 4581 60  0000 C CNN
F 2 "ESP32:ESP32-WROOM" H 8950 4650 60  0001 C CNN
F 3 "" H 8150 3750 60  0001 C CNN
	1    8600 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 2800 7300 2800
Text Label 7300 2700 1    50   ~ 0
EN
Wire Wire Line
	9500 3750 9750 3750
Text Label 9750 3750 0    50   ~ 0
IO0
Wire Wire Line
	9600 2750 9500 2750
Wire Wire Line
	9600 2850 9500 2850
Text Label 4000 2250 0    50   ~ 0
TX0
Text Label 4000 2150 0    50   ~ 0
RX0
$Comp
L power:GND #PWR0107
U 1 1 60374DEC
P 6150 2800
F 0 "#PWR0107" H 6150 2550 50  0001 C CNN
F 1 "GND" V 6155 2672 50  0000 R CNN
F 2 "" H 6150 2800 50  0001 C CNN
F 3 "" H 6150 2800 50  0001 C CNN
	1    6150 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	6150 2800 6300 2800
$Comp
L Device:R R3
U 1 1 6037582E
P 6700 2350
F 0 "R3" H 6770 2396 50  0000 L CNN
F 1 "10k" H 6770 2305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6630 2350 50  0001 C CNN
F 3 "~" H 6700 2350 50  0001 C CNN
	1    6700 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 2500 6700 2800
Wire Wire Line
	6700 2800 6600 2800
Wire Wire Line
	6700 2200 6700 2000
$Comp
L power:+3.3V #PWR0108
U 1 1 60377560
P 6700 2000
F 0 "#PWR0108" H 6700 1850 50  0001 C CNN
F 1 "+3.3V" H 6715 2173 50  0000 C CNN
F 2 "" H 6700 2000 50  0001 C CNN
F 3 "" H 6700 2000 50  0001 C CNN
	1    6700 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 2700 7400 2700
Wire Wire Line
	7400 2700 7400 1850
$Comp
L power:+3.3V #PWR0109
U 1 1 60377F7F
P 7400 1300
F 0 "#PWR0109" H 7400 1150 50  0001 C CNN
F 1 "+3.3V" H 7415 1473 50  0000 C CNN
F 2 "" H 7400 1300 50  0001 C CNN
F 3 "" H 7400 1300 50  0001 C CNN
	1    7400 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 6037A0D0
P 7850 1850
F 0 "C8" V 7598 1850 50  0000 C CNN
F 1 "100nF" V 7689 1850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7888 1700 50  0001 C CNN
F 3 "~" H 7850 1850 50  0001 C CNN
	1    7850 1850
	0    1    1    0   
$EndComp
Wire Wire Line
	7700 1450 7400 1450
Connection ~ 7400 1450
Wire Wire Line
	7400 1450 7400 1300
Wire Wire Line
	7700 1850 7400 1850
Connection ~ 7400 1850
Wire Wire Line
	7400 1850 7400 1450
Wire Wire Line
	8000 1850 8150 1850
Wire Wire Line
	8150 1850 8150 1650
Wire Wire Line
	8150 1450 8000 1450
Wire Wire Line
	8150 1650 8400 1650
Connection ~ 8150 1650
Wire Wire Line
	8150 1650 8150 1450
$Comp
L power:GND #PWR0110
U 1 1 6037E32B
P 8400 1650
F 0 "#PWR0110" H 8400 1400 50  0001 C CNN
F 1 "GND" V 8405 1522 50  0000 R CNN
F 2 "" H 8400 1650 50  0001 C CNN
F 3 "" H 8400 1650 50  0001 C CNN
	1    8400 1650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7650 4000 7350 4000
Wire Wire Line
	7350 4000 7350 4200
$Comp
L power:GND #PWR0111
U 1 1 6037F255
P 7350 4200
F 0 "#PWR0111" H 7350 3950 50  0001 C CNN
F 1 "GND" H 7355 4027 50  0000 C CNN
F 2 "" H 7350 4200 50  0001 C CNN
F 3 "" H 7350 4200 50  0001 C CNN
	1    7350 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 6037F357
P 8000 4500
F 0 "#PWR0112" H 8000 4250 50  0001 C CNN
F 1 "GND" H 8005 4327 50  0000 C CNN
F 2 "" H 8000 4500 50  0001 C CNN
F 3 "" H 8000 4500 50  0001 C CNN
	1    8000 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 3850 9700 3850
Wire Wire Line
	9700 3850 9700 3950
Wire Wire Line
	9700 3950 9500 3950
Wire Wire Line
	9700 3950 9700 4100
Connection ~ 9700 3950
$Comp
L power:GND #PWR0113
U 1 1 60382300
P 9700 4100
F 0 "#PWR0113" H 9700 3850 50  0001 C CNN
F 1 "GND" H 9705 3927 50  0000 C CNN
F 2 "" H 9700 4100 50  0001 C CNN
F 3 "" H 9700 4100 50  0001 C CNN
	1    9700 4100
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 603826C5
P 6950 2800
F 0 "JP1" H 6950 2600 50  0000 C CNN
F 1 "EN Supply" H 6950 2700 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 6950 2800 50  0001 C CNN
F 3 "~" H 6950 2800 50  0001 C CNN
	1    6950 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 2700 7300 2800
Connection ~ 7300 2800
Wire Wire Line
	7100 2800 7300 2800
Wire Wire Line
	6800 2800 6700 2800
Connection ~ 6700 2800
$Comp
L Regulator_Linear:AMS1117-3.3 U1
U 1 1 60389149
P 1950 4700
F 0 "U1" H 1950 4942 50  0000 C CNN
F 1 "AMS1117-3.3" H 1950 4851 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 1950 4900 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 2050 4450 50  0001 C CNN
	1    1950 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 4750 1300 4700
Wire Wire Line
	1300 4700 1650 4700
Wire Wire Line
	2250 4700 2550 4700
Wire Wire Line
	2550 4700 2550 4750
Wire Wire Line
	1950 5000 1950 5150
Wire Wire Line
	1300 5050 1300 5150
Wire Wire Line
	2550 5050 2550 5150
$Comp
L power:GND #PWR0114
U 1 1 60394963
P 1300 5150
F 0 "#PWR0114" H 1300 4900 50  0001 C CNN
F 1 "GND" H 1305 4977 50  0000 C CNN
F 2 "" H 1300 5150 50  0001 C CNN
F 3 "" H 1300 5150 50  0001 C CNN
	1    1300 5150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 603949BB
P 1950 5150
F 0 "#PWR0115" H 1950 4900 50  0001 C CNN
F 1 "GND" H 1955 4977 50  0000 C CNN
F 2 "" H 1950 5150 50  0001 C CNN
F 3 "" H 1950 5150 50  0001 C CNN
	1    1950 5150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 60394A13
P 2550 5150
F 0 "#PWR0116" H 2550 4900 50  0001 C CNN
F 1 "GND" H 2555 4977 50  0000 C CNN
F 2 "" H 2550 5150 50  0001 C CNN
F 3 "" H 2550 5150 50  0001 C CNN
	1    2550 5150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0117
U 1 1 60394BB1
P 1300 4450
F 0 "#PWR0117" H 1300 4300 50  0001 C CNN
F 1 "+5V" H 1315 4623 50  0000 C CNN
F 2 "" H 1300 4450 50  0001 C CNN
F 3 "" H 1300 4450 50  0001 C CNN
	1    1300 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 4700 1300 4450
Connection ~ 1300 4700
$Comp
L power:+3.3V #PWR0118
U 1 1 603965C3
P 2550 4450
F 0 "#PWR0118" H 2550 4300 50  0001 C CNN
F 1 "+3.3V" H 2565 4623 50  0000 C CNN
F 2 "" H 2550 4450 50  0001 C CNN
F 3 "" H 2550 4450 50  0001 C CNN
	1    2550 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 4450 2550 4700
Connection ~ 2550 4700
$Comp
L si4432:SI4432-Module U3
U 1 1 6039ABF6
P 4750 5900
F 0 "U3" H 4750 6665 50  0000 C CNN
F 1 "SI4432-Module" H 4750 6574 50  0000 C CNN
F 2 "SI4432 Module:SI4432-Module" H 5400 6450 50  0001 C CNN
F 3 "" H 5400 6450 50  0001 C CNN
	1    4750 5900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_Coaxial J2
U 1 1 6039ADF5
P 5900 5400
F 0 "J2" H 6000 5376 50  0000 L CNN
F 1 "SMA ANT" H 6000 5285 50  0000 L CNN
F 2 "Connector_Coaxial:SMA_Amphenol_132289_EdgeMount" H 5900 5400 50  0001 C CNN
F 3 " ~" H 5900 5400 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/RF-Connectors-Coaxial-Connectors_ZHONGCHI-ELECTRONIC-ZC8-841KK_C976230.html" H 5900 5400 50  0001 C CNN "JCLC"
	1    5900 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 5400 5700 5400
Wire Wire Line
	5900 5600 5250 5600
Wire Wire Line
	5250 5600 5250 5500
Wire Wire Line
	4250 5400 4150 5400
Wire Wire Line
	4150 5400 4150 5250
Wire Wire Line
	4250 6500 4100 6500
Wire Wire Line
	4100 6500 4100 6650
$Comp
L power:GND #PWR0119
U 1 1 603A1EF6
P 5250 5700
F 0 "#PWR0119" H 5250 5450 50  0001 C CNN
F 1 "GND" H 5255 5527 50  0000 C CNN
F 2 "" H 5250 5700 50  0001 C CNN
F 3 "" H 5250 5700 50  0001 C CNN
	1    5250 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 5600 5250 5700
Connection ~ 5250 5600
$Comp
L power:GND #PWR0120
U 1 1 603A3E00
P 4150 5250
F 0 "#PWR0120" H 4150 5000 50  0001 C CNN
F 1 "GND" H 4155 5077 50  0000 C CNN
F 2 "" H 4150 5250 50  0001 C CNN
F 3 "" H 4150 5250 50  0001 C CNN
	1    4150 5250
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0121
U 1 1 603A3EA1
P 4100 6650
F 0 "#PWR0121" H 4100 6400 50  0001 C CNN
F 1 "GND" H 4105 6477 50  0000 C CNN
F 2 "" H 4100 6650 50  0001 C CNN
F 3 "" H 4100 6650 50  0001 C CNN
	1    4100 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 5800 3900 5800
Wire Wire Line
	3900 5800 3900 5250
$Comp
L power:+3.3V #PWR0122
U 1 1 603A5FDC
P 3900 5250
F 0 "#PWR0122" H 3900 5100 50  0001 C CNN
F 1 "+3.3V" H 3915 5423 50  0000 C CNN
F 2 "" H 3900 5250 50  0001 C CNN
F 3 "" H 3900 5250 50  0001 C CNN
	1    3900 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 5500 3650 5500
Wire Wire Line
	4250 5600 3650 5600
Wire Wire Line
	4250 5700 3650 5700
Text Label 3650 5500 2    50   ~ 0
RX_Data
Text Label 3650 5600 2    50   ~ 0
RX_Clock
Text Label 3650 5700 2    50   ~ 0
RSSI
Wire Wire Line
	4250 5900 3650 5900
Wire Wire Line
	4250 6000 3650 6000
Wire Wire Line
	4250 6100 3650 6100
Wire Wire Line
	4250 6200 3650 6200
Text Label 3650 5900 2    50   ~ 0
MISO
Text Label 3650 6000 2    50   ~ 0
MOSI
Text Label 3650 6100 2    50   ~ 0
CLK
Text Label 3650 6200 2    50   ~ 0
CS
Wire Wire Line
	4250 6300 3650 6300
Wire Wire Line
	4250 6400 3650 6400
Text Label 3650 6300 2    50   ~ 0
nIRQ
Text Label 3650 6400 2    50   ~ 0
SDN
Text Label 9600 3250 0    50   ~ 0
RX_Clock
Wire Wire Line
	9500 3250 9600 3250
Text Label 9600 3150 0    50   ~ 0
RX_Data
Wire Wire Line
	9500 3150 9600 3150
Text Label 9600 2950 0    50   ~ 0
RSSI
Wire Wire Line
	9500 2950 9600 2950
Text Label 9600 3350 0    50   ~ 0
nIRQ
Wire Wire Line
	9600 3350 9500 3350
Text Label 9600 3550 0    50   ~ 0
SDN
Wire Wire Line
	9500 3550 9600 3550
Text Label 7500 3900 2    50   ~ 0
MISO
Wire Wire Line
	7650 3900 7500 3900
Text Label 8250 4450 3    50   ~ 0
MOSI
Wire Wire Line
	8150 4350 8150 4450
Wire Wire Line
	8150 4450 8000 4450
Wire Wire Line
	8000 4450 8000 4500
Wire Wire Line
	8250 4350 8250 4450
Text Label 7500 3800 2    50   ~ 0
CLK
Wire Wire Line
	7650 3800 7500 3800
Text Label 8950 4450 3    50   ~ 0
CS
Wire Wire Line
	8950 4350 8950 4450
$Comp
L Device:C C6
U 1 1 603E1A86
P 6450 2800
F 0 "C6" V 6198 2800 50  0000 C CNN
F 1 "1uF" V 6289 2800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6488 2650 50  0001 C CNN
F 3 "~" H 6450 2800 50  0001 C CNN
	1    6450 2800
	0    1    1    0   
$EndComp
$Comp
L Device:C C7
U 1 1 603E1C23
P 7850 1450
F 0 "C7" V 7598 1450 50  0000 C CNN
F 1 "10uF" V 7689 1450 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7888 1300 50  0001 C CNN
F 3 "~" H 7850 1450 50  0001 C CNN
	1    7850 1450
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 603E1E7F
P 1300 4900
F 0 "C2" V 1048 4900 50  0000 C CNN
F 1 "10uF" V 1139 4900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1338 4750 50  0001 C CNN
F 3 "~" H 1300 4900 50  0001 C CNN
	1    1300 4900
	-1   0    0    1   
$EndComp
$Comp
L Device:C C5
U 1 1 603E20BD
P 2550 4900
F 0 "C5" V 2298 4900 50  0000 C CNN
F 1 "10uF" V 2389 4900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2588 4750 50  0001 C CNN
F 3 "~" H 2550 4900 50  0001 C CNN
	1    2550 4900
	-1   0    0    1   
$EndComp
$Comp
L Device:C C3
U 1 1 603E22DF
P 1500 1550
F 0 "C3" H 1385 1504 50  0000 R CNN
F 1 "4.7uF" H 1385 1595 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1538 1400 50  0001 C CNN
F 3 "~" H 1500 1550 50  0001 C CNN
	1    1500 1550
	-1   0    0    1   
$EndComp
$EndSCHEMATC
