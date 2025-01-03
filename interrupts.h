#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H
#include "types.h"
#include "port.h"
#include "gdt.h"


    class InterruptManager{
        protected:
            struct GateDescriptor
            {
                uint16_t handlerAddressLowBits;
                uint16_t gdt_codeSegmentSelector;
                uint8_t reserved;
                uint8_t access;
                uint8_t handlerAddressHighBits;

            }__attribute__((packed));

            static GateDescriptor interruptDescriptorTable[256];

            struct InterruptDescriptorTablePointer
            {
                uint16_t size;
                uint32_t base;
            }__attribute__((packed));
            

            static void SetInterruptDescriptorTableEntry(
                uint8_t interruptnumber,
                uint16_t codeSegmentSelectorOffset,
                void (*handler)(),
                uint8_t DescriptorPrivelegeLevel,
                uint8_t DescriptorType
            );

            Port8BitSlow picMasterCommand;
            Port8BitSlow picMasterData;
            Port8BitSlow picSlaveCommand;
            Port8BitSlow picSlaveData;

            
        public:
            InterruptManager(GlobalDescriptorTable* gdt);
            ~InterruptManager();

            void Activate();


            static uint32_t handleInterrupt(uint8_t interruptnumber, uint32_t esp);

            static void IgnoreInterruptRequest();
            static void HandleInterruptRequest0x00();
            static void HandleInterruptRequest0x01();
    };


#endif