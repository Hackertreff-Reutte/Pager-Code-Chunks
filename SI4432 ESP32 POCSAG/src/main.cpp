#include <Arduino.h>
#include <DMASPI.h>
#include <stdbool.h>
#include <math.h>


#define HSPI_MISO   12
#define HSPI_MOSI   13
#define HSPI_SCLK   14
#define HSPI_SS     15

#define SDN 16


#define BUFFER_SIZE 1000
uint8_t* tx_buf;
uint8_t* rx_buf;


DMASPI::DMASPI spi;
static const int spiClk = 100000; // 100 kHz


uint8_t read(uint8_t address){
  //hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  spi.beginTransaction(HSPI, SPI_MODE0, spiClk);
  digitalWrite(HSPI_SS, LOW);
  address &= 0b01111111;
  //hspi->transfer(address);
  tx_buf[0] = address;
  tx_buf[1] = 0;
  spi.transfer(16, tx_buf, rx_buf);
  //uint8_t result = hspi->transfer(0);
  digitalWrite(HSPI_SS, HIGH);
  spi.endTransaction();
  //hspi->endTransaction();

  return rx_buf[1];
} 

void write(uint8_t address, uint8_t data){
  //hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  spi.beginTransaction(HSPI, SPI_MODE0, spiClk);
  digitalWrite(HSPI_SS, LOW);
  address |= 0b10000000;
  tx_buf[0] = address;
  tx_buf[1] = data;
  spi.transfer(16, tx_buf, rx_buf);
  //hspi->transfer(address);
  //hspi->transfer(data);
  digitalWrite(HSPI_SS, HIGH);
  //hspi->endTransaction();
  spi.endTransaction();
} 

void setup() {

  delay(5000);

  Serial.begin(115200);


  Serial.println("Setting up SPI");

  rx_buf = (uint8_t*)heap_caps_malloc(BUFFER_SIZE, MALLOC_CAP_DMA);
  tx_buf = (uint8_t*)heap_caps_malloc(BUFFER_SIZE, MALLOC_CAP_DMA);

  spi.begin(HSPI, 14, 12, 13, 1);
  //hspi = new SPIClass(HSPI);
  //hspi->begin();
  pinMode(HSPI_SS, OUTPUT);
  digitalWrite(HSPI_SS, HIGH);


  Serial.println("booting SI4432");
  
  //this reset is important because otherwise spi might not be working on the
  //si4432
  pinMode(SDN, OUTPUT);
  digitalWrite(SDN, HIGH);
  delay(500);
  digitalWrite(SDN, LOW);

  Serial.println("Now in IDLE");


}


//spi functions


void printDeviceStatusRegister(){
  Serial.print(read(0x02), BIN);
  Serial.println("");
}

void printOperatingModeandFunctionControl1(){
  Serial.print(read(0x07), BIN);
  Serial.println("");
}

void setIdleStandby(){
  write(0x07, 0x0);
}

void setTXMode(){
  write(0x07, (read(0x07) & 0b11110111) | 1 << 3);
}

void setRXMode(){
  write(0x07, (read(0x07) & 0b11111011) | 1 << 2);
}

void reset(){
  write(0x07, 0b10000000);
}


//freq in Mhz (5Mhz = 5.0)
void setFrequency(double freq){
  
  uint8_t hbsel;
  double fb_f;
  uint8_t fb;
  uint16_t fc;

  if(freq < 240 or freq > 930){
    Serial.println("Freq out of bounds");
    return;
  }

  if (freq < 480){
    hbsel = 0;
  }else{
    hbsel = 1;
  }

  //calculate the value for the fb register with float
  fb_f = (freq / (10 * (hbsel + 1))) - 24;


  //just the value for the fb register (remove the fractional part)
  fb = ((uint8_t) fb_f) & 0b11111;

  //calculat the fractional component
  fc = (uint16_t) ((fb_f - fb) * 64000);

  //write to the register 0x75 frequency band select 
  //(bit 5 = hbsel (highband select) and the lower are the fb (frequency band))
  //bit 6 is the siteband select and the recommended value is 1 so that the rx
  //frequency is below (low-side injection)
  write(0x75, 0b1 << 6 | hbsel << 5 | fb);


  //write the upper 8 bit for the fc to the "Nominal Carrier Frequency 1"
  //register
  write(0x76, fc >> 8);

  //write the lower 8 bit for the fc  to the "Nominal Carrier Frequency 0"
  write(0x77, fc & 0xFF);

  printf("send: fb: %d\n", fb);
  printf("send: fc: %d\n", fc);
  printf("send: hsb: %d\n", hbsel);

}

#define UnmodulatedCarrier 0b00
#define OOK 0b01
#define FSK 0b10
#define GFSK 0b11

void setModulationType(uint8_t typ){

  if(typ > 3){
    Serial.println("Invalid Mod Type");
    return;
  }

  //update the first 2 fields / bits (modtyp)
  write(0x71, (read(0x71) & 0b11111100) | typ);
}

void printFrequency(){

  uint8_t fbsr = read(0x75);

  uint8_t hbsel = (fbsr >> 5) & 0b1;
  uint8_t fb = fbsr & 0b11111;

  uint8_t fc_higher = read(0x76);
  uint8_t fc_lower = read(0x77);

  uint16_t fc = (fc_higher << 8) | fc_lower;

  double freq = 10.0 * (hbsel + 1) * (fb + 24 + fc / 64000.0);

  Serial.print("Stored Frequency: ");
  Serial.println(freq, DEC);

  printf("rec: fb: %d\n", fb);
  printf("rec: fc: %d\n", fc);
  printf("rec: hsb: %d\n", hbsel);
}

//deviation in khz  (50kHz = 50)
void setDeviation(double deviation){

  if(deviation < 1 || deviation >= 320){
    Serial.println("Deviation out of bounds");
  }

  uint8_t fd = round(deviation / 0.625);

  write(0x72, fd);
}

//datarate in kbps (3kbps = 3)
void setDataRate(double datarate){

  uint8_t txdtrtscale;
  double scale;
  uint16_t txdr;

  if(datarate < 0.123 || datarate > 256){
    Serial.print("Datarate out of bounds");
    return;
  }

  if (datarate < 30){
    txdtrtscale = 1;
    scale = 2097152.0;
  }else{
    txdtrtscale = 0;
    scale = 65536.0;
  }
  
  txdr = round(datarate * scale / 1000.0);

  //write the new datarate
  write(0x6E, txdr >> 8);
  write(0x6F, txdr & 0xFF);

  //update the txdtrtscale bit in the register 70h
  write(0x70, (read(0x70) & 0b11011111) ^ (txdtrtscale << 5));
}

#define SOURCE_DIRECT_GPIO 0b00
#define SOURCE_DIRECt_SPI 0b01
#define SOURCE_FIFO 0b10
#define SOURCE_PN9 0b11
void setModulationDataSource(uint8_t source){

  if(source > 3){
    Serial.println("Invalid Data Source");
    return;
  }

  //update the value
  write(0x71, (read(0x71) & 0b11001111) | (source << 4));

}

#define NO_TX_DATA_CLK 0b00
#define TX_CLK_GPIO 0b01
#define TX_CLK_SDO 0b10
#define TX_CLK_nIRQ 0b11
void setDirectClockSource(uint8_t source){

  if(source > 3){
    Serial.println("Invalid Clock Source");
  }

  write(0x71, (read(0x71) & 0b00111111) | (source << 6));  
}


#define POWER_11dB 0b00
#define POWER_14dB 0b01
#define POWER_17dB 0b10
#define POWER_20dB 0b11
void setPowerLevel(uint8_t level){

  if(level > 3){
    Serial.println("Power level too big");
    return;
  }

  write(0x6D, (read(0x6D) & 0b11111100) | level);
}

//pocsag frame sync word
void addFSC(uint8_t * tx){
    tx[0] = 0b01111100;
    tx[1] = 0b11010010;
    tx[2] = 0b00010101;
    tx[3] = 0b11011000;
}

uint8_t * add32Bit(uint8_t* tx, uint32_t data){
    tx[0] = (data >> 24) & 0xFF;
    tx[1] = (data >> 16) & 0xFF;
    tx[2] = (data >> 8) & 0xFF;
    tx[3] = (data >> 0) & 0xFF;
    return tx + 4;
}


//offset in khz
void setOffset(double offset){

  uint8_t fbsr = read(0x75);
  uint8_t hbsel = (fbsr >> 5) & 0b1;

  uint16_t fo = offset / (0.15625 * (hbsel + 1));

  write(0x73, fo & 0xFF);
  write(0x72, (fo >> 8) & 0b11);
}


void disablePacketHandler(){
  write(0x30, 0);
}

//length in bytes + threashld in bytes
void setPreamble(uint16_t length, uint16_t threashold){

  // byte = 8 bit
  // x = byte * 8 / 4 = byte * 2

  //bounds check
  if(length > 512 || threashold > 128){
    Serial.println("length or threashold out of bounds");
    return;
  }

  uint16_t lenNibbles = length * 2;
  uint8_t threasholdNibbles = threashold * 2;

  //writing the preamble length
  write(0x34, lenNibbles & 0xFF);
  write(0x33, (read(0x32) & 0b11111110) | ((lenNibbles >> 8) & 1));

  //writing the detection threashold
  write(0x35, (threasholdNibbles & 0b11111) << 3);
}

void printPreambleAndSyncStatus(){
  uint8_t status = read(0x04);

  Serial.print("Valid Preamble: ");
  Serial.println((status >> 6) & 1);
  Serial.print("Invalid Preamble: ");
  Serial.println((status >> 5) & 1);
  Serial.print("SYNC Word detected: ");
  Serial.println((status >> 7) & 1);
}


#define NO_SYNC_WORD 0
#define SYNC_WORD_1Byte 1
#define SYNC_WORD_2Byte 2
#define SYNC_WORD_3Byte 3
#define SYNC_WORD_4Byte 4

//length in byte
void setSYNC_Word(uint8_t length, uint32_t sync_word){
    
    if(length > 4){
      Serial.println("Sync Word is too big");
      return;
    }


    //set the SYNC word length in the header control register
    write(0x33, (read(0x33) & 0b11111001) | (length << 1));

    //fill the register
    if(length >= 1){
      //word 0
      write(0x36, (sync_word >> (8 * (length - 1))) & 0xFF);
    }

    if(length >= 2){
      //word 1
      write(0x37, (sync_word >> (8 * (length - 2))) & 0xFF);
    }

    if(length >= 3){
      //word 2
      write(0x38, (sync_word >> (8 * (length - 3))) & 0xFF);
    }

    if(length >= 4){
      //word 3
      write(0x39, sync_word & 0xFF);
    }
}

void sendData(){
    Serial.println("Setting Frequency");
    setFrequency(433);
    delay(100);
    Serial.println("Setting Deviation");
    setDeviation(4.5);
    delay(100);
    Serial.println("Setting Datarate");
    setDataRate(1.2);
    delay(100);
    Serial.println("Setting Modulation");
    setModulationType(FSK);
    delay(100);
    Serial.println("Setting Modulation Source");
    setModulationDataSource(SOURCE_DIRECt_SPI);
    delay(100);
    Serial.println("Setting Modulation CLK Source");
    setDirectClockSource(NO_TX_DATA_CLK);
    delay(100);
    Serial.println("Enable TX MODE");
    setTXMode();

    uint8_t * tx_temp = tx_buf;
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b01010101010101010101010101010101);
    tx_temp = add32Bit(tx_temp, 0b10000011001011011110101000100111);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b11111111111010110000001100001100);
    tx_temp = add32Bit(tx_temp, 0b01101010010110000110011111101011);
    tx_temp = add32Bit(tx_temp, 0b00110100011111011111011010011000);
    tx_temp = add32Bit(tx_temp, 0b01000001100011110001111010011000);
    tx_temp = add32Bit(tx_temp, 0b00100111110000111011101110000010);
    tx_temp = add32Bit(tx_temp, 0b01101011100110110010011000101001);
    tx_temp = add32Bit(tx_temp, 0b01100111111111111111110011010000);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b10000011001011011110101000100111);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b11111111111010110000001100001100);
    tx_temp = add32Bit(tx_temp, 0b01101010010110000110011111101011);
    tx_temp = add32Bit(tx_temp, 0b00110100011111011111011010011000);
    tx_temp = add32Bit(tx_temp, 0b01000001100011110001111010011000);
    tx_temp = add32Bit(tx_temp, 0b00100111110000111011101110000010);
    tx_temp = add32Bit(tx_temp, 0b01101011100110110010011000101001);
    tx_temp = add32Bit(tx_temp, 0b01100111111111111111110011010000);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
    tx_temp = add32Bit(tx_temp, 0b10000101011101100011111001101000);
  

    //DMA SPI (could change in the final release, but is not that hard to implement)
    spi.beginTransaction(HSPI, SPI_MODE0, 1200);
    spi.transfer(3000, tx_buf, rx_buf); 
    spi.endTransaction();

    delay(100);

    //Serial.println("Reset");
   // reset();
}

//datarate in kbps / deviation in khz / manchester = 1 (true) or 0 (false)
void setupModem(double datarate, double deviation, uint8_t manchester){

  //TODO bounds checks

  //calculate the mod index (h)
  double modindex = (2 * deviation / (datarate * (1 + manchester)));

  double bandwidth;

  //calculate the bandwidth
  if(modindex > 1){
      bandwidth = (datarate / 2 * (1 + manchester) + 2 * deviation);
  }else{
      bandwidth = (datarate * (1 + manchester) + deviation);
  }

  uint8_t ndec_exp;
  uint8_t dwm3_bypass;
  uint8_t fileset;

  if(bandwidth <= 142.8){
      dwm3_bypass = 0;
  }else{
      dwm3_bypass = 1;
  }

  //this is the digitized version of a table located in the datasheet
  //it is not nice but i count find any consistency in the table that could 
  //have been used to calculate those values
  if(bandwidth <= 2.6){
      ndec_exp = 5;
      fileset = 1;
  }else if(bandwidth <= 2.8){
      ndec_exp = 5;
      fileset = 2;
  }else if(bandwidth <= 3.1){
      ndec_exp = 5;
      fileset = 3;
  }else if(bandwidth <= 3.2){
      ndec_exp = 5;
      fileset = 4;
  }else if(bandwidth <= 3.7){
      ndec_exp = 5;
      fileset = 5;
  }else if(bandwidth <= 4.2){
      ndec_exp = 5;
      fileset = 6;
  }else if(bandwidth <= 4.5){
      ndec_exp = 5;
      fileset = 6;
  }else if(bandwidth <= 4.9){
      ndec_exp = 4;
      fileset = 1;
  }else if(bandwidth <= 5.4){
      ndec_exp = 4;
      fileset = 2;
  }else if(bandwidth <= 5.9){
      ndec_exp = 4;
      fileset = 3;
  }else if(bandwidth <= 6.1){
      ndec_exp = 4;
      fileset = 4;
  }else if(bandwidth <= 7.2){
      ndec_exp = 4;
      fileset = 5;
  }else if(bandwidth <= 8.2){
      ndec_exp = 4;
      fileset = 6;
  }else if(bandwidth <= 8.8){
      ndec_exp = 4;
      fileset = 7;
  }else if(bandwidth <= 9.5){
      ndec_exp = 3;
      fileset = 1;
  }else if(bandwidth <= 10.6){
      ndec_exp = 3;
      fileset = 2;
  }else if(bandwidth <= 11.5){
      ndec_exp = 3;
      fileset = 3;
  }else if(bandwidth <= 12.1){
      ndec_exp = 3;
      fileset = 4;
  }else if(bandwidth <= 14.2){
      ndec_exp = 3;
      fileset = 5;
  }else if(bandwidth <= 16.2){
      ndec_exp = 3;
      fileset = 6;
  }else if(bandwidth <= 17.5){
      ndec_exp = 3;
      fileset = 7;
  }else if(bandwidth <= 18.9){
      ndec_exp = 2;
      fileset = 1;
  }else if(bandwidth <= 21.0){
      ndec_exp = 2;
      fileset = 2;
  }else if(bandwidth <= 22.7){
      ndec_exp = 2;
      fileset = 3;
  }else if(bandwidth <= 24.0){
      ndec_exp = 2;
      fileset = 4;
  }else if(bandwidth <= 28.2){
      ndec_exp = 2;
      fileset = 5;
  }else if(bandwidth <= 32.2){
      ndec_exp = 2;
      fileset = 6;
  }else if(bandwidth <= 34.7){
      ndec_exp = 2;
      fileset = 7;
  }else if(bandwidth <= 37.7){
      ndec_exp = 1;
      fileset = 1;
  }else if(bandwidth <= 41.7){
      ndec_exp = 1;
      fileset = 2;
  }else if(bandwidth <= 45.2){
      ndec_exp = 1;
      fileset = 3;
  }else if(bandwidth <= 47.9){
      ndec_exp = 1;
      fileset = 4;
  }else if(bandwidth <= 56.2){
      ndec_exp = 1;
      fileset = 5;
  }else if(bandwidth <= 64.1){
      ndec_exp = 1;
      fileset = 6;
  }else if(bandwidth <= 69.2){
      ndec_exp = 1;
      fileset = 7;
  }else if(bandwidth <= 75.2){
      ndec_exp = 0;
      fileset = 1;
  }else if(bandwidth <= 83.2){
      ndec_exp = 0;
      fileset = 2;
  }else if(bandwidth <= 90.0){
      ndec_exp = 0;
      fileset = 3;
  }else if(bandwidth <= 95.3){
      ndec_exp = 0;
      fileset = 4;
  }else if(bandwidth <= 112.1){
      ndec_exp = 0;
      fileset = 5;
  }else if(bandwidth <= 127.9){
      ndec_exp = 0;
      fileset = 6;
  }else if(bandwidth <= 137.9){
      ndec_exp = 0;
      fileset = 7;
  }else if(bandwidth <= 142.8){
      ndec_exp = 1;
      fileset = 4;
  }else if(bandwidth <= 167.8){
      ndec_exp = 1;
      fileset = 5;
  }else if(bandwidth <= 181.1){
      ndec_exp = 1;
      fileset = 9;
  }else if(bandwidth <= 191.5){
      ndec_exp = 0;
      fileset = 15;
  }else if(bandwidth <= 225.1){
      ndec_exp = 0;
      fileset = 1;
  }else if(bandwidth <= 248.8){
      ndec_exp = 0;
      fileset = 2;
  }else if(bandwidth <= 269.3){
      ndec_exp = 0;
      fileset = 3;
  }else if(bandwidth <= 284.9){
      ndec_exp = 0;
      fileset = 4;
  }else if(bandwidth <= 335.5){
      ndec_exp = 0;
      fileset = 8;
  }else if(bandwidth <= 361.8){
      ndec_exp = 0;
      fileset = 9;
  }else if(bandwidth <= 420.2){
      ndec_exp = 0;
      fileset = 10;
  }else if(bandwidth <= 468.4){
      ndec_exp = 0;
      fileset = 11;
  }else if(bandwidth <= 518.8){
      ndec_exp = 0;
      fileset = 12;
  }else if(bandwidth <= 577.0){
      ndec_exp = 0;
      fileset = 13;
  }else if(bandwidth <= 620.7){
      ndec_exp = 0;
      fileset = 14;
  }



  double rxosr_f = (500 * (1 + 2 * dwm3_bypass)) / (pow(2,ndec_exp - 3) * datarate * (1 + manchester));
  uint32_t rxosr = (uint32_t) rxosr_f;

  uint32_t ncoff = (uint32_t) ((datarate * (1 + manchester) * pow(2, 20 + ndec_exp)) / (500 * (1 + 2*dwm3_bypass)));

  //the formula that was mentioned in the datasheet does not really work for the crgain
  uint32_t crgain = (uint32_t) (2 + ((65535 * ((uint32_t) datarate)) / (uint32_t) (rxosr_f * deviation)));


  //write the values to the registers 

  //set the dwn3_bypass, ndec_exp and fileset in the register 1Ch
  write(0x1C, (((dwm3_bypass & 1) << 7) | ((ndec_exp & 0b111) << 4)) | (fileset & 0b1111));

  //set the rxosr in the register 20h and 21h
  write(0x20, rxosr & 0xFF);
  write(0x21, (read(0x21) & 0b00011111) | (((rxosr >> 8) & 0b111) << 5));

  //set the ncoff in the register 21h 22h 23h 
  write(0x23, ncoff & 0xFF);
  write(0x22, (ncoff >> 8) & 0xFF);
  write(0x21, (read(0x21) & 0b11110000) | ((ncoff >> 16) & 0b1111));

  //set the crgain in the register 24h 25h
  write(0x25, crgain & 0xFF);
  write(0x24, (crgain >> 8) & 0b111);
}

void printModem(){

  uint8_t reg1C = read(0x1C);

  Serial.print("DW3: ");
  Serial.println(reg1C >> 7, HEX);
  Serial.print("ndec_exp: ");
  Serial.println((reg1C >> 4) & 0b111, HEX);
  Serial.print("fileset: ");
  Serial.println(reg1C & 0b1111, HEX);

  uint32_t rxosr = read(0x20);
  rxosr |= ((read(0x21) >> 5) & 0b111) << 8;
  Serial.print("rxosr: ");
  Serial.println(rxosr, HEX);

  uint32_t ncoff = read(0x23);
  ncoff |= read(0x22) << 8;
  ncoff |= (read(0x21) & 0b1111) << 16;
  Serial.print("ncoff: ");
  Serial.println(ncoff, HEX);

  uint32_t crgain = read(0x25);
  crgain |= (read(0x24) & 0b111) << 8;
  Serial.print("crgain: ");
  Serial.println(crgain, HEX);
}

void receive(){
  Serial.println("Setting Frequency");
  setFrequency(433);
  delay(100);
  Serial.println("Setting Deviation");
  setDeviation(4.5);
  delay(100);
  Serial.println("Setting Datarate");
  setDataRate(1.2);
  delay(100);
  Serial.println("Setting Modulation");
  setModulationType(FSK);
  delay(100);
  Serial.println("Disable Packet Handler");
  disablePacketHandler();
  delay(100);
  Serial.println("Setting Peramble");
  setPreamble(72,20);
  delay(100);
  Serial.println("Setting SYNC Words");
  setSYNC_Word(SYNC_WORD_4Byte, 0b10000011001011011110101000100111);  
  delay(100);
  Serial.println("Setting Modem");
  setupModem(1.2,4.5,0);
  delay(100);
  setRXMode();
}


void enableRXOutputPins(){
  write(0x0B, 0b10100); //RX Data on GPIO 0
  write(0x0C, 0b01111); //RX Clock on GPIO 1
}

//load 0 - 0b01111111 (127)
void setCrystalLoadCap(uint8_t load){
  write(0x09, (read(0x09) & 0b10000000) | (load & 0b01111111));
}

void loop() {
  
  if(Serial.available()){

    //--------do spi stuff here-------
    
    //receive();
    //enableRXOutputPins();
    
    
    setOffset(0);
    setCrystalLoadCap(127);
    sendData();
    reset();
      
    

    //sendData(); 
    //---------------------------------

    delay(1500);
    while(Serial.available()){
      Serial.read();
    }
  }
  //printPreambleAndSyncStatus();
  delay(100);
}