#pragma once
#ifndef DMASPI_h
#define DMASPI_h


#include <Arduino.h>
#include <SPI.h>
#include <driver/spi_master.h>
#include <stdbool.h>

#ifndef DMA_SPI_NAMESPACE_START
#define DMA_SPI_NAMESPACE_START namespace arduino { namespace esp32 { namespace spi { namespace dma {
#endif

#ifndef DMA_SPI_NAMESPACE_END
#define DMA_SPI_NAMESPACE_END   }}}}
#endif

DMA_SPI_NAMESPACE_START

//------------------------------------------------------------------------------
class DMASPI {

    spi_device_handle_t handle;

    public:
        bool begin(uint8_t spi_bus = HSPI, int8_t sck = -1, int8_t miso = -1, int8_t mosi = -1, int8_t dma = 0);
        bool beginTransaction(uint8_t spi_bus, uint8_t mode, int clk);
        uint8_t * transfer(size_t length, uint8_t *txbuffer, uint8_t *rxbuffer);
        bool endTransaction();

        //TODO add spi end
    private:

};


//------------------------------------------------------------------------------

DMA_SPI_NAMESPACE_END

namespace DMASPI = arduino::esp32::spi::dma;

#endif

