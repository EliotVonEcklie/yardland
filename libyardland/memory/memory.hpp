/**
 * @file memory.hpp
 * @author Joseph Hans Diaz Gonzalez <eliotvonecklie@gmail.com>
 * @date 2021-03-27
 */

#pragma once

#include <cstdint>
#include <cstdlib>
#include <vector>

/**
 * @brief Memory Bank Class.
 * @version v0.1.0
 */
class Memory
{
public:
    /**
     * @brief Construct a new `Memory` object.
     *
     * @param size
     */
    Memory(std::uint32_t size);

    /**
     * @brief Get an element from this memory bank.
     *
     * @param address The address of the element.
     * @return The element.
     */
	std::uint8_t get(std::uint32_t address);

    /**
     * @brief Puts an element onto this memory bank.
     *
     * @param address The destination address of the element.
     * @param data The element.
     */
	void put(std::uint32_t address, std::uint8_t data);

    /**
     * @brief Provides access to both 'get' and 'put' functions of this memory bank (used to chain memory banks).
     *
     * @param address The destination/source address of the element.
     * @param data The element.
     * @param get Calls `Memory::get()` if True, if False calls `Memory::put()`
     */
    void access(std::uint32_t address, std::uint8_t* data, bool get);

    /**
     * @brief Adds a Memory Mapped IO Device to this memory bank.
     *
     * @param start_address Start address for the Memory of the device.
     * @param end_address End address for the Memory of the device.
     * @param access_func Access funtion of the MMIOD.
     * @return An integer used to identify the MMIOD.
     */
	int AddMMIOD(std::uint32_t start_address, std::uint32_t end_address, void ( *access_func ) (std::uint32_t, std::uint8_t*, bool));

    /**
     * @brief Removes a Memory Mapped IO Device from this memory bank.
     *
     * @param id The integer returned from `Memory::AddMMIOD()`
     */
    void RemoveMMIOD(int id);

private:
    /**
     * @brief Memory Buffer.
     *
     */
	std::uint8_t* memory_buffer;

    /**
     * @brief An MMIODevice.
     *
     */
    struct MMIODevice
    {
        std::uint32_t start_address;
        std::uint32_t end_address;
        void ( *access_func ) (std::uint32_t, std::uint8_t*, bool);
    };

    /**
     * @brief MMIODevices.
     *
     */
    std::vector<MMIODevice> MMIODevices;
};
