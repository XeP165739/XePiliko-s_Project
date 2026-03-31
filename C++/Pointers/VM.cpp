// what i want to implemet: addition, subraction, multiplication, division (floor val).
// constrainst: input--- min = -32 768 | max = 32 767, output--- min = -2,147,483,648 || max = 2,147,483,647, non-float
// memory: 1kb (256 machine memory; 256 variable memory; 512 stack memory)

#include <iostream>
#include <cstdint>
#include <iterator>
#include <string>

const int CodeSize = 1;

uint8_t* vm = new uint8_t[1024](); // VM memory

uint8_t* machine_pt     = &vm[0];
int machine_index       = 0;
uint8_t* machine_pt_max = &vm[255];

uint8_t* value_pt       = &vm[256];
int value_index         = 0;
uint8_t* value_pt_max   = &vm[511];

uint8_t* stack_pt       = &vm[512];
int stack_index         = 0;
uint8_t* stack_pt_max   = &vm[1023];

// 0x01 = Load Val to constant
// 0x02 = Get Val adrss inside variable_pt
// 0x03 = Add val1 and val2
// 0x04 = Invert
// 0x09 = Out

void cleanup() {
    delete[] vm;
    vm = nullptr;

    machine_pt = nullptr; machine_pt_max = nullptr;
    value_pt = nullptr; value_pt_max = nullptr;
    stack_pt = nullptr; stack_pt_max = nullptr;
}

void LoadStatic(int val){
    if (INT16_MIN > val || val > INT16_MAX) throw std::runtime_error("Integer input is too big || -32 768 -- 32 767");

    uint8_t* target = machine_pt + machine_index + CodeSize;

    if(target + sizeof(int16_t) - 1 > machine_pt_max || machine_pt + machine_index + sizeof(int16_t) + CodeSize > machine_pt_max){
        throw std::runtime_error("VM Memory Overflow: Machine stack is full.");
    }

    vm[machine_index++] = 0x01;
    *(reinterpret_cast<int16_t*>(target)) = val;
    machine_index += sizeof(int16_t);
}

void StoreVal(int val){
    if (INT16_MIN > val || val > INT16_MAX) throw std::runtime_error("Integer input is too big || -32 768 -- 32 767");

    uint8_t* target = value_pt + value_index;

    if(target + sizeof(int16_t) - 1 > value_pt_max){
        throw std::runtime_error("VM Memory Overflow: Variable stack is full.");
    }

    if(machine_pt + machine_index + CodeSize > machine_pt_max){
        throw std::runtime_error("VM Memory Overflow: Machine stack is full.");
    }

    // add the index and adress of val to machine mem
    vm[machine_index++] = 0x02;
    vm[machine_index++] = static_cast<uint8_t>(value_index);

    // add the val in value mem
    *(reinterpret_cast<uint16_t*>(target)) = val;
    value_index += sizeof(int16_t);
}

void testMem() {
    if(vm == nullptr) throw std::runtime_error("VM Memory Clear");

    std::cout << "--- Machine Mem (Bytecode) ---" << std::endl;
    for (int i = 0; i < 32; i++) { // Just printing the first 32 bytes for brevity
        printf("%02X ", vm[i]);
        if ((i + 1) % 8 == 0) std::cout << std::endl;
    }

    std::cout << "\n--- Value Mem (Data) ---" << std::endl;
    for (int i = 0; i < 32; i++) {
        printf("%02X ", vm[i + 256]);
        if ((i + 1) % 8 == 0) std::cout << std::endl;
    }

    // std::cout << "\n--- Stack Mem (Data) ---" << std::endl;
    // for (int i = 0; i < 64; i++) {
    //     printf("%02X ", vm[i + 512]);
    //     if ((i + 1) % 8 == 0) std::cout << std::endl;
    // }

    std::cout << std::endl;
}

int main(){
    LoadStatic(7002);
    StoreVal(169);
    StoreVal(32007);

    testMem();

    cleanup();

    return 0;
}
