#include "DMASPI.h"

DMA_SPI_NAMESPACE_START

bool DMASPI::begin(uint8_t spi_bus, int8_t sck, int8_t miso, int8_t mosi, int8_t dma){

    spi_bus_config_t spi_bus_config;

    //only VSPI and HSPI are allowed
    if(spi_bus != VSPI && spi_bus != HSPI){
        return false;
    }

    //SPI	  MOSI	    MISO	    CLK	       CS
    //VSPI	GPIO 23    GPIO 19	  GPIO 18	 GPIO 5
    //HSPI	GPIO 13	   GPIO 12	  GPIO 14	 GPIO 15

    if(sck == -1 && miso == -1 && mosi == -1){
        if(spi_bus == VSPI){
            spi_bus_config.mosi_io_num = 23;
            spi_bus_config.miso_io_num = 19;
            spi_bus_config.sclk_io_num = 18;
        }else if(spi_bus == HSPI){
            spi_bus_config.mosi_io_num = 13;
            spi_bus_config.miso_io_num = 12;
            spi_bus_config.sclk_io_num = 14;
        }else{
            return false;
        }
    }else{
        spi_bus_config.mosi_io_num = mosi;
        spi_bus_config.miso_io_num = miso;
        spi_bus_config.sclk_io_num = sck;
    }

    spi_bus_config.quadwp_io_num = -1;
    spi_bus_config.quadhd_io_num = -1;
    spi_bus_config.max_transfer_sz = 1000 * 10; //defaults to 4094

    //TODO what do they do?
    spi_bus_config.flags = 0;
    spi_bus_config.intr_flags = 0;


    spi_host_device_t spi_host_device = (spi_bus == VSPI ? VSPI_HOST : HSPI_HOST);
    esp_err_t initerr = spi_bus_initialize(spi_host_device, &spi_bus_config, dma);

    //TODO error handling

    return true;
  
}

bool DMASPI::beginTransaction(uint8_t spi_bus, uint8_t mode, int clk){
    spi_device_interface_config_t spi_device_interface_config;

    spi_device_interface_config.command_bits = 0;
    spi_device_interface_config.address_bits = 0;
    spi_device_interface_config.dummy_bits = 0;

    spi_device_interface_config.mode = mode;
    spi_device_interface_config.duty_cycle_pos = 0; // defaults to 128 (50%)
    spi_device_interface_config.cs_ena_pretrans = 0;
    spi_device_interface_config.cs_ena_posttrans = 0;
    spi_device_interface_config.clock_speed_hz = clk;
    spi_device_interface_config.input_delay_ns = 0;
    spi_device_interface_config.spics_io_num = -1;
    spi_device_interface_config.flags = 0;
    spi_device_interface_config.queue_size = 1;

    //callback?? TODO
    spi_device_interface_config.pre_cb = NULL;
    spi_device_interface_config.post_cb = NULL;


    spi_host_device_t spi_host_device = (spi_bus == VSPI ? VSPI_HOST : HSPI_HOST);

    esp_err_t adderr = spi_bus_add_device(spi_host_device, &spi_device_interface_config, &handle);

    return true;

}

uint8_t * DMASPI::transfer(size_t length, uint8_t *txbuffer, uint8_t *rxbuffer){
    spi_transaction_t transaction;

    transaction.flags = 0;
    transaction.addr = 0;
    transaction.cmd = 0;
    transaction.length = length;
    transaction.rxlength = 0; //defaults to length
    transaction.user = NULL;
    transaction.tx_buffer = txbuffer;
    transaction.rx_buffer = rxbuffer;


    esp_err_t transerr = spi_device_transmit(handle, &transaction);

    //TODO error handling

    return (uint8_t*) transaction.rx_buffer;

}


bool DMASPI::endTransaction(){
    esp_err_t removeerr = spi_bus_remove_device(handle);

    //TODO error handling
    return true;
}


DMA_SPI_NAMESPACE_END