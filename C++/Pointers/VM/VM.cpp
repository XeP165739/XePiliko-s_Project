// what i want to implemet: addition, subraction, multiplication, division (floor val).
// constrainst: input--- min = -32 768 | max = 32 767
// memory: 1kb (256 machine memory; 256 variable memory; 512 stack memory)

#include <iostream>
#include <cstdint>
#include <iterator>
#include <string>
#include <cstring>

// Instruction = Code
const uint8_t PUSH  = 0x01;
const uint8_t SAVE  = 0x02;
const uint8_t LOAD  = 0x03;
const uint8_t STORE = 0x04;
const uint8_t ADD   = 0x05;
const uint8_t SUB   = 0x06;
const uint8_t MULT  = 0x07;
const uint8_t DIV   = 0x08;
const uint8_t IoOUT = 0x09;

const int CodeSize = 1;
const int ASCIISize = 1;

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

void cleanup() {
    delete[] vm;
    vm = nullptr;

    machine_pt = nullptr; machine_pt_max = nullptr;
    value_pt = nullptr; value_pt_max = nullptr;
    stack_pt = nullptr; stack_pt_max = nullptr;
}

bool varInUse(uint8_t ascii){
    uint8_t* target = value_pt;

    while(*(target) != 0x00){
        if(*(target) == ascii) return true;
        target += 3;
    }

    return false;
}

void Push(int val){ // 0x01
    if (INT16_MIN > val || val > INT16_MAX) throw std::runtime_error("Integer invalid || -32 768 -- 32 767");

    uint8_t* target = machine_pt + machine_index + CodeSize;

    if(target + sizeof(int16_t) - 1 > machine_pt_max || machine_pt + machine_index + sizeof(int16_t) + CodeSize > machine_pt_max){
        throw std::runtime_error("VM Memory Overflow: Machine stack is full.");
    }

    vm[machine_index++] = PUSH;
    *(reinterpret_cast<int16_t*>(target)) = val;
    machine_index += sizeof(int16_t);
}

void Save(char var ,int val){ // 0x02
    uint8_t varchar = static_cast<uint8_t>(var);

    if(varInUse(varchar)) throw std::runtime_error(std::string("Variable input is invalid || ") + var);

    if (INT16_MIN > val || val > INT16_MAX) throw std::runtime_error("Integer input is invalid || -32 768 -- 32 767");

    uint8_t* target = value_pt + value_index;

    if(target + sizeof(int16_t) - 1 > value_pt_max) throw std::runtime_error("VM Memory Overflow: Variable stack is full.");

    if(machine_pt + machine_index + CodeSize > machine_pt_max) throw std::runtime_error("VM Memory Overflow: Machine stack is full.");

    // addition the index and adress of val to machine mem
    vm[machine_index++] = SAVE;
    vm[machine_index++] = varchar;

    // addition the val in value mem
    *(target++) = varchar;
    *(reinterpret_cast<int16_t*>(target)) = val;
    value_index += sizeof(varchar) + sizeof(int16_t);
}

void Load(char var){ // 0x03
    uint8_t varchar = static_cast<uint8_t>(var);

    if(!varInUse(varchar)) throw std::runtime_error(std::string("Variable is not in use || ") + var);

    if(machine_pt + machine_index + CodeSize > machine_pt_max) throw std::runtime_error("VM Memory Overflow: Machine stack is full.");
    
    vm[machine_index++] = LOAD;
    vm[machine_index++] = varchar;
}

void Store(char var){ // 0x04
    uint8_t varchar = static_cast<uint8_t>(var);

    if(!varInUse(varchar)) throw std::runtime_error(std::string("Variable is not in use || ") + var);

    if(machine_pt + machine_index + CodeSize > machine_pt_max) throw std::runtime_error("VM Memory Overflow: Machine stack is full.");
    
    vm[machine_index++] = STORE;
    vm[machine_index++] = varchar;
}

void Add(){ // 0x05
    if(machine_pt + machine_index + CodeSize > machine_pt_max) throw std::runtime_error("VM Memory Overflow: Machine stack is full.");
    
    vm[machine_index++] = ADD;
}

void Sub(){ // 0x06
    if(machine_pt + machine_index + CodeSize > machine_pt_max) throw std::runtime_error("VM Memory Overflow: Machine stack is full.");
    
    vm[machine_index++] = SUB;
}

void Mult(){ // 0x07
    if(machine_pt + machine_index + CodeSize > machine_pt_max) throw std::runtime_error("VM Memory Overflow: Machine stack is full.");
    
    vm[machine_index++] = MULT;
}

void Div(){
    if(machine_pt + machine_index + CodeSize > machine_pt_max) throw std::runtime_error("VM Memory Overflow: Machine stack is full.");
    
    vm[machine_index++] = DIV;
}

void IoOut(char var){ // 0x09
    uint8_t varchar = static_cast<uint8_t>(var);

    if(!varInUse(varchar)) throw std::runtime_error(std::string("Variable is not in use || ") + var);

    if(machine_pt + machine_index + CodeSize > machine_pt_max) throw std::runtime_error("VM Memory Overflow: Machine stack is full.");
    
    vm[machine_index++] = IoOUT;
    vm[machine_index++] = varchar;
}

uint8_t* getTarget(uint8_t ascii){
    uint8_t* target = value_pt;

    while(*(target) != 0x00){
        if(*(target) == ascii) break;
        target += 3;
    }

    return target;
}

int16_t addition(int16_t a, int16_t b){
    return a + b;
}

int16_t subtraction(int16_t a, int16_t b){
    return a + (~b + 1);
}

int16_t multiply(int16_t a, int16_t b){
    if(b <= 0) return 0;

    return a + multiply(a, b + (~1 + 1));
}

int16_t division(int16_t a, int16_t b, int16_t c){
    if (subtraction(a, b) >= 0) return division(subtraction(a, b), b, c + 1);

    return c;
}

void Interpret(){
    if(vm == nullptr) throw std::runtime_error("VM Memory Clear");

    uint8_t* temp_machine_pt = machine_pt;
    uint8_t* temp_stack_pt = stack_pt;

    while(*(temp_machine_pt) != 0x00 && temp_machine_pt <= machine_pt_max){
        switch (*(temp_machine_pt)) {
            case PUSH:
            {
                temp_machine_pt += CodeSize;

                std::cout << "Push : " <<std::to_string(*(reinterpret_cast<int16_t*>(temp_machine_pt))) << std::endl;

                std::memcpy(temp_stack_pt, temp_machine_pt, sizeof(int16_t));
                temp_stack_pt += sizeof(int16_t);
                temp_machine_pt += sizeof(int16_t);

                break;
            }

            case SAVE:
            {
                std::cout << "Save" << std::endl;

                temp_machine_pt += CodeSize;
                temp_machine_pt += ASCIISize;
                break;
            }

            case LOAD: 
            {
                temp_machine_pt += CodeSize;

                uint8_t* target = getTarget(*(temp_machine_pt)) + ASCIISize;

                std::cout << "Load : " <<std::to_string(*(reinterpret_cast<int16_t*>(target))) << std::endl;

                std::memcpy(temp_stack_pt, target, sizeof(int16_t));
                temp_machine_pt += ASCIISize;
                temp_stack_pt += sizeof(int16_t);

                break;
            }

            case STORE:
            {
                temp_machine_pt += CodeSize;

                uint8_t* target = getTarget(*(temp_machine_pt)) + ASCIISize;

                std::cout << "Store : (current) " <<std::to_string(*(reinterpret_cast<int16_t*>(target)));

                temp_stack_pt -= sizeof(int16_t);
                std::memcpy(target, temp_stack_pt, sizeof(int16_t));
                *(reinterpret_cast<int16_t*>(temp_stack_pt)) = 0;

                std::cout << " || (now) " <<std::to_string(*(reinterpret_cast<int16_t*>(target))) << std::endl;

                temp_machine_pt += ASCIISize;

                break;
            }

            case ADD: 
            {
                temp_machine_pt += CodeSize;

                if (temp_stack_pt - sizeof(int16_t) * 2 < stack_pt) throw std::runtime_error("Add Cannot be Performed");

                int16_t b;
                temp_stack_pt -= sizeof(int16_t); // since the temp_stack_pt is pointing to 0x00;
                std::memcpy(&b, temp_stack_pt, sizeof(int16_t));
                *(reinterpret_cast<int16_t*>(temp_stack_pt)) = 0;


                int16_t a;
                temp_stack_pt -= sizeof(int16_t); 
                std::memcpy(&a, temp_stack_pt, sizeof(int16_t));

                int16_t result = addition(a, b);
                std::memcpy(temp_stack_pt, &result, sizeof(int16_t));

                std::cout << "Add : " << std::to_string(a) << " + " << std::to_string(b) << " = " << std::to_string(result) << std::endl;

                temp_stack_pt += sizeof(int16_t); // will point to the next;
                
                break;
            }

            case SUB:
            {
                temp_machine_pt += CodeSize;

                if (temp_stack_pt - sizeof(int16_t) * 2 < stack_pt) throw std::runtime_error("Sub Cannot be Performed");

                int16_t b;
                temp_stack_pt -= sizeof(int16_t); // since the temp_stack_pt is pointing to 0x00;
                std::memcpy(&b, temp_stack_pt, sizeof(int16_t));
                *(reinterpret_cast<int16_t*>(temp_stack_pt)) = 0;


                int16_t a;
                temp_stack_pt -= sizeof(int16_t); 
                std::memcpy(&a, temp_stack_pt, sizeof(int16_t));

                int16_t result = subtraction(a, b);
                std::memcpy(temp_stack_pt, &result, sizeof(int16_t));

                std::cout << "Sub : " << std::to_string(a) << " - " << std::to_string(b) << " = " << std::to_string(result) << std::endl;

                temp_stack_pt += sizeof(int16_t); // will point to the next;
                
                break;
            }

            case MULT:
            {
                temp_machine_pt += CodeSize;

                if (temp_stack_pt - sizeof(int16_t) * 2 < stack_pt) throw std::runtime_error("Sub Cannot be Performed");

                int16_t b;
                temp_stack_pt -= sizeof(int16_t); // since the temp_stack_pt is pointing to 0x00;
                std::memcpy(&b, temp_stack_pt, sizeof(int16_t));
                *(reinterpret_cast<int16_t*>(temp_stack_pt)) = 0;

                int16_t a;
                temp_stack_pt -= sizeof(int16_t); 
                std::memcpy(&a, temp_stack_pt, sizeof(int16_t));

                int16_t result = multiply(a, b);
                std::memcpy(temp_stack_pt, &result, sizeof(int16_t));

                std::cout << "Mult : " << std::to_string(a) << " * " << std::to_string(b) << " = " << std::to_string(result) << std::endl;

                temp_stack_pt += sizeof(int16_t); // will point to the next;
                
                break;
            }

            case DIV:
            {
                temp_machine_pt += CodeSize;

                if (temp_stack_pt - sizeof(int16_t) * 2 < stack_pt) throw std::runtime_error("Sub Cannot be Performed");

                int16_t b;
                temp_stack_pt -= sizeof(int16_t); // since the temp_stack_pt is pointing to 0x00;
                std::memcpy(&b, temp_stack_pt, sizeof(int16_t));
                if(b == 0) throw std::runtime_error("value of b is 0");
                *(reinterpret_cast<int16_t*>(temp_stack_pt)) = 0;

                int16_t a;
                temp_stack_pt -= sizeof(int16_t); 
                std::memcpy(&a, temp_stack_pt, sizeof(int16_t));

                int16_t result = division(a, b, 0);
                std::memcpy(temp_stack_pt, &result, sizeof(int16_t));

                std::cout << "Div : " << std::to_string(a) << " / " << std::to_string(b) << " = " << std::to_string(result) << std::endl;

                temp_stack_pt += sizeof(int16_t); // will point to the next;
                
                break;
            }

            case IoOUT:
            {
                temp_machine_pt += CodeSize;

                uint8_t* target = getTarget(*(temp_machine_pt)) + ASCIISize;

                int16_t val;
                std::memcpy(&val, target, sizeof(int16_t));

                std::cout << "IoOut : " <<std::to_string(val) << std::endl;

                temp_machine_pt += ASCIISize;

                break;
            }

            default: {
                std::cout << "Instrcution Null" << std::endl;
                temp_machine_pt = machine_pt_max + 1;
                break;
            }
        }
    }  
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

    std::cout << "\n--- Stack Mem (Data) ---" << std::endl;
    for (int i = 0; i < 64; i++) {
        printf("%02X ", vm[i + 512]);
        if ((i + 1) % 8 == 0) std::cout << std::endl;
    }

    std::cout << std::endl;
}

void testInstruction(){
    if(vm == nullptr) throw std::runtime_error("VM Memory Clear");

    uint8_t* temp_machine_pt = &vm[0];

    std::cout << "--- Machine Instructions (Bytecode) ---" << std::endl;

    while(*(temp_machine_pt) != 0x00 && temp_machine_pt <= machine_pt_max){
        switch (*(temp_machine_pt)) {
            case PUSH:
            {
                printf("%02X ", *(temp_machine_pt++));
                printf("%02X ", *(temp_machine_pt++));
                printf("%02X\n", *(temp_machine_pt++));
                break;
            }

            case SAVE:
            case LOAD:
            case STORE:
            case IoOUT:
            {
                printf("%02X ", *(temp_machine_pt++));
                printf("%02X\n", *(temp_machine_pt++));
                break;
            }

            case ADD: 
            case SUB:
            case MULT:
            case DIV:
            {
                printf("%02X\n", *(temp_machine_pt++));
                break;
            }

            default: {
                std::cout << "Instrcution Null" << std::endl;
                temp_machine_pt = machine_pt_max + 1;
                break;
            }
        }
    }
}

void testAddSub(){
    /*
    int16_t a = 100, b = 69, c = 0;

    c = (a - b) + 420;

    printf(c);
    */

    Save('a', 100);
    Save('b', 69);
    Save('c', 0);

    Load('a');
    Load('b');

    Sub();

    Push(420);

    Add();

    Store('c');

    IoOut('a');
    IoOut('b');
    IoOut('c');
}

void testMult(){
    /*
    int16_t a = 10;

    a = a * 6;

    printf(a)
    */

    Save('a', 10);

    Load('a');
    Push(6);

    Mult();

    Store('a');

    IoOut('a');
}

void testDiv(){
    /*
    int16_t a = 66;

    a = a / 6;

    printf(a)
    */

    Save('a', 66);

    Load('a');
    Push(6);

    Div();

    Store('a');

    IoOut('a');
}

int main(){
    // testAddSub();
    // testMult();
    // testDiv();

    Interpret();

    // testMem();
    // testInstruction();

    cleanup();

    return 0;
}
