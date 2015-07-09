#include "unity.h"
#include "ROM.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void test_initROM_should_initialize_the_ROM_properly()
{
    createROM();
    int i;

    TEST_ASSERT_NOT_NULL(rom);
    TEST_ASSERT_NOT_NULL(rom->address);

    destroyROM();
}


void test_resetROM_should_reset_all_the_ROM_data_to_0(void)
{
    int i;
    createROM();

    //write some value into the ROM
    for(i = 0; i < TWO_HUND_FIFTY_SIX_KB * 2; i ++ )
    {
        rom->address[i].data = 1234;
    }

    resetROM();

    for(i = 0 ; i < TWO_HUND_FIFTY_SIX_KB * 2 ; i ++ )
    {
        TEST_ASSERT_EQUAL(0, rom->address[i].data);
    }

    destroyROM();
}

void test_virtualMemToPhysicalMem_given_0x8000000_should_convert_the_mem_addr_into_virtual_mem_addr(void)
{
    int i;
    uint32_t virtMemAddr, phyMemAddr = 0x8000000;

    virtMemAddr = virtualMemToPhysicalMem(phyMemAddr);
    
    TEST_ASSERT_EQUAL(0x10204, virtMemAddr);
}

void test_virtualMemToPhysicalMem_given_0x8000001_should_convert_the_mem_addr_into_virtual_mem_addr(void)
{
    int i;
    uint32_t virtMemAddr, phyMemAddr = 0x800007f;

    virtMemAddr = virtualMemToPhysicalMem(phyMemAddr);
    
    TEST_ASSERT_EQUAL(0x102041, virtMemAddr);
}