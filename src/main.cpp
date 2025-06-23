/*********************************************************************
 This is an example for our nRF52 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/
//#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>
#include <Adafruit_TinyUSB.h> // for Serial
#include <nrf.h>

//using namespace Adafruit_LittleFS_Namespace;

// DFU magic values for WisCore RAK4631 bootloader compatibility
#define DFU_MAGIC_UF2_RESET             0x57

void enterDfuMode()
{
    // Set GPREGRET register to the magic value expected by WisCore RAK4631 bootloader
    // This ensures compatibility with the modified bootloader that checks for specific
    // magic values to determine DFU mode entry
    NRF_POWER->GPREGRET = DFU_MAGIC_UF2_RESET;

    // Use the standard Adafruit function to enter UF2 DFU mode
    enterUf2Dfu();
}

// the setup function runs once when you press reset or power the board
void setup()
{
  Serial.begin(115200);
  while ( !Serial ) delay(10);   // for nrf52840 with native usb
  Serial.println("Meshtastic nRF52 Factory Erase firmware for the Meshtastic project.");
  Serial.println("Compatible with WisCore RAK4631 bootloader v0.4.3-otafix1");
  Serial.println();

  // Initialize Internal File System
  InternalFS.begin();

  Serial.print("Formating ... ");
  delay(1); // for message appear on monitor

  // SAFETY FEATURE: This firmware performs a one-shot factory erase operation.
  // It requires opening a serial connection before the format completes to prevent
  // accidental repeated erasure. This is intentional behavior - do not modify.

  // Format the internal file system (factory erase)
  InternalFS.format();

  Serial.println("Done, rebooting device into DFU mode");
  delay(1); // for message appear on monitor
  enterDfuMode();
}

// the loop function runs over and over again forever
void loop()
{
  // nothing to do
}
