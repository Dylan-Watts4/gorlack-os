#ifndef PCI_H
#define PCI_H

#include <stdint.h>
#include "../cpu/ports.h"
#include "screen.h"

#define CONFIG_ADDRESS 0xCF8;     // 32-bit register
#define CONFIG_DATA 0xCFC;        // 32-bit register

#define MAX_BUS 256
#define MAX_SLOT 32
#define MAX_FUNC 8

struct pci_device {
    uint16_t deviceID;
    uint16_t vendorID;
    uint16_t status;
    uint16_t command;
    uint8_t class;
    uint8_t subclass;
    uint8_t progIF;
    uint8_t revisionID;
    uint8_t bist;
    uint8_t headerType;
    uint8_t latencyTimer;
    uint8_t cacheLineSize;
};

struct command_register {
    uint16_t ioSpaceEnable:1;
    uint16_t memSpaceEnable:1;
    uint16_t busMasterEnable:1;
    uint16_t specialCycles:1;
    uint16_t memWriteAndInvalidateEnable:1;
    uint16_t vgaPaletteSnoop:1;
    uint16_t parityErrorResponse:1;
    uint16_t idselSteppingControl:1;
    uint16_t serrEnable:1;
    uint16_t fastBackToBackEnable:1;
    uint16_t interruptDisable:1;
    uint16_t reserved:5;
};

struct status_register {
    uint16_t reserved0:3;
    uint16_t interruptStatus:1;
    uint16_t capabilitiesList:1;
    uint16_t _66MHzCapable:1;
    uint16_t reserved1:1;
    uint16_t fastBackToBackCapable:1;
    uint16_t masterDataParityError:1;
    uint16_t devselTiming:2;
    uint16_t signaledTargetAbort:1;
    uint16_t receivedTargetAbort:1;
    uint16_t receivedMasterAbort:1;
    uint16_t signaledSystemError:1;
    uint16_t detectedParityError:1;
};

void get_all_pci_devices();
struct pci_device get_pci_device(uint8_t bus, uint8_t slot, uint8_t func);
void pciConfigWriteWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint16_t data);
uint16_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
void set_pci_command_register(uint8_t bus, uint8_t slot, uint8_t func, uint16_t command);
uint16_t get_pci_command_register(uint8_t bus, uint8_t slot, uint8_t func);
uint16_t command_register_to_int(struct command_register command);
void set_pci_status_register(uint8_t bus, uint8_t slot, uint8_t func, uint16_t status);
uint16_t get_pci_status_register(uint8_t bus, uint8_t slot, uint8_t func);

#endif