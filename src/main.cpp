#include "OpenKNX.h"
#include "ShutterControllerModule.h"
#include "Logic.h"
 
#ifdef ARDUINO_ARCH_RP2040
    #include "FileTransferModule.h"
    #include "UsbExchangeModule.h"
#endif
#ifdef ARDUINO_ARCH_ESP32
    #include "FileTransferModule.h"
#endif
#include "FunctionBlocksModule.h"
#ifdef ARDUINO_ARCH_RP2040
    #pragma message "Pico Core Version: " ARDUINO_PICO_VERSION_STR
#endif

void setup()
{
    // change this also in library.json
    const uint8_t firmwareRevision = 1;
    openknx.init(firmwareRevision);
#if defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_ESP32)
#ifndef OPENKNX_FILE_TRANSFER_IGNORE
    openknx.addModule(9, openknxFileTransferModule);
#endif
#endif

 #ifdef ARDUINO_ARCH_RP2040
    openknx.addModule(8, openknxUsbExchangeModule);
#endif
    openknx.addModule(3, openknxShutterControllerModule);
    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxFunctionBlocksModule);
    openknx.setup();
}
  
void loop()
{
    openknx.loop();
}

#ifdef OPENKNX_DUALCORE
void setup1()
{
    openknx.setup1();
}

void loop1()
{
    openknx.loop1();
}
#endif
