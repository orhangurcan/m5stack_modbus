#include <Arduino.h>
#include <esp32ModbusRTU.h>
#include <algorithm>  // for std::reverse
esp32ModbusRTU modbus(&Serial1, 16);  // use Serial1 and pin 16 as RTS


#define ENDIAN 1

//set pin 4 and 17 for Modbus RTU RS485
#define RXD1 17
#define TXD1 4

// set Slave Address 
#define SlaveAddress 0x01
#define Function 0x03

// set Starting Address of Registers

#define StateRegister 0x7000
#define VTRegister 0x7001
#define V_15Register   0x7003
#define WeightRegister 0x7005
#define SumVTRegister 0x7007
#define SumV15Register 0x7009
#define SumWghtRegister 0x700B         
#define BatchQuantityRegister 0x700D
#define AvgDensityXRegister 0x700F
#define AvgTemp1Register 0x7011
#define FlowRateRegister 0x7013
#define ProductNoRegister 0x7015
#define AdditivTypeRegister 0x7016
#define AddVTRegister 0x7017
#define SumAddVTRegister  0x7019
#define TargetAddRateRegister 0x701B
#define DateTimeRegister 0x701C

//set Quantity of Registers Low

#define StateRegNum 0x0001
#define VTRegNum 0x0002
#define V_15RegNum   0x0002
#define WeightRegNum 0x0002
#define SumVTRegNum 0x0002
#define SumV15RegNum 0x0002
#define SumWghtRegNum 0x0002         
#define BatchQuantityRegNum 0x0002
#define AvgDensityXRegNum 0x0002
#define AvgTemp1RegNum 0x0002
#define FlowRateRegNum 0x0002
#define ProductNoRegNum 0x0001
#define AdditivTypeRegNum 0x0001
#define AddVTRegNum 0x0002
#define SumAddVTRegNum  0x0002
#define TargetAddRateRegNum 0x0001
#define DateTimeRegNum 0x0008


//set variables for loop
#define State 1
#define VT  2
#define V_15  3
#define Weight  4
#define SumVT 5
#define SumV15  6
#define SumWght 7         
#define BatchQuantity 8
#define AvgDensityX 9
#define AvgTemp1  10
#define FlowRate  11
#define ProductNo 12
#define AdditivType 13
#define AddVT 14
#define SumAddVT  15
#define TargetAddRate 16
#define DateTime  17

//to converse hex data into float

uint32_t UI4Set(char byte_0, char byte_1, char byte_2, char byte_3) {
#if ENDIAN == 1
  return byte_0 | ((uint32_t)byte_1) << 8 | ((uint32_t)byte_2) << 16 |
         ((uint32_t)byte_3) << 24;
#else
  return byte_3 | ((uint32_t)byte_2) << 8 | ((uint32_t)byte_1) << 16 |
         ((uint32_t)byte_0) << 24;
#endif
}

float FLTSet(char byte_0, char byte_1, char byte_2, char byte_3) {
  uint32_t flt = UI4Set(byte_0, byte_1, byte_2, byte_3);
  return *reinterpret_cast<float*>(&flt);
}

uint32_t FLTSet(char byte_0, char byte_1, char byte_2, char byte_3,
                   float* destination) {
  uint32_t FloatValue = UI4Set (byte_0, byte_1, byte_2, byte_3);
  *reinterpret_cast<uint32_t*>(destination) = FloatValue;
  return FloatValue;
}

volatile int Register;
uint16_t StateValue;
uint16_t ProductNoValue;
uint16_t AdditivTypeValue;
float flt;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
  Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1);  // Modbus connection

  modbus.onData([](uint8_t serverAddress, esp32Modbus::FunctionCode fc, uint16_t address, uint8_t* data, size_t length) {

     String SendingData = "";
     switch (Register-1){
      case State:
        StateValue = (256*data[0]) + data[1];  //to converse hex data into integer
        SendingData = String(Register-1) + ':' + String(StateValue);
        Serial.print(SendingData);
        Serial.println("\n");
        break;
      case VT:
        flt = FLTSet (data[3], data[2], data[1], data[0]);
        SendingData = String(Register-1) + ':' + String(flt);
        Serial.print(SendingData);
        Serial.println("\n");
        break;
      case V_15:
        flt = FLTSet (data[3], data[2], data[1], data[0]);
        SendingData = String(Register-1) + ':' + String(flt);
        Serial.print(SendingData);
        Serial.println("\n");
        break;
      case Weight:
        flt = FLTSet (data[3], data[2], data[1], data[0]);
        SendingData = String(Register-1) + ':' + String(flt);
        Serial.print(SendingData);
        Serial.println("\n");
        break;
      case SumVT:
        flt = FLTSet (data[3], data[2], data[1], data[0]);
        SendingData = String(Register-1) + ':' + String(flt);
        Serial.print(SendingData);
        Serial.println("\n");
         break;
      case SumV15:
        flt = FLTSet (data[3], data[2], data[1], data[0]);
        SendingData = String(Register-1) + ':' + String(flt);
        Serial.print(SendingData);
        Serial.println("\n");
        break;
      case SumWght:
        flt = FLTSet (data[3], data[2], data[1], data[0]);
        SendingData = String(Register-1) + ':' + String(flt);
        Serial.print(SendingData);
        Serial.println("\n");
        break;
      case BatchQuantity:
        flt = FLTSet (data[3], data[2], data[1], data[0]);
        SendingData = String(Register-1) + ':' + String(flt);
        Serial.print(SendingData);
        Serial.println("\n");
        break;
      case AvgDensityX:
        flt = FLTSet (data[3], data[2], data[1], data[0]);
        SendingData = String(Register-1) + ':' + String(flt);
        Serial.print(SendingData);
        Serial.println("\n");
        break;
      case AvgTemp1:
        flt = FLTSet (data[3], data[2], data[1], data[0]);
        SendingData = String(Register-1) + ':' + String(flt);
        Serial.print(SendingData);
        Serial.println("\n");
        break;
      case FlowRate:
        flt = FLTSet (data[3], data[2], data[1], data[0]);
        SendingData = String(Register-1) + ':' + String(flt);
        Serial.print(SendingData);
        Serial.println("\n");
        break;
      case ProductNo:
        ProductNoValue = (256*data[0]) + data[1];
        SendingData = String(Register-1) + ':' + String(ProductNoValue);
        Serial.print(SendingData);
        break;
      case AdditivType:
        AdditivTypeValue = (256*data[0]) + data[1];
        SendingData = String(Register-1) + ':' + String(AdditivTypeValue);
        Serial.print(SendingData);
        break;
      case AddVT:
        flt = FLTSet (data[3], data[2], data[1], data[0]);
        SendingData = String(Register-1) + ':' + String(flt);
        Serial.print(SendingData);
        Serial.println("\n");
        break;
      case SumAddVT:
        flt = FLTSet (data[3], data[2], data[1], data[0]);
        SendingData = String(Register-1) + ':' + String(flt);
        Serial.print(SendingData);
        Serial.println("\n");
        break;
      case TargetAddRate:
        flt = FLTSet (data[3], data[2], data[1], data[0]);
        SendingData = String(Register-1) + ':' + String(flt);
        Serial.print(SendingData);
        Serial.println("\n");
        break;
      case DateTime:
        break;                                                                                                                
    }
  });

  modbus.onError([](esp32Modbus::Error error) {
    Serial.printf("error: 0x%02x\n\n", static_cast<uint8_t>(error));
  });
  
  modbus.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  static uint32_t lastMillis = 0;
  for (Register = State; Register <= DateTime; Register++ ){ 
    lastMillis = millis(); 
    while(millis() - lastMillis < 1000) {}
    switch (Register){
      case State:
        modbus.readHoldingRegisters(SlaveAddress,StateRegister,StateRegNum);
        break;
      case VT:
        modbus.readHoldingRegisters(SlaveAddress,VTRegister,VTRegNum);
        break;
      case V_15:
        modbus.readHoldingRegisters(SlaveAddress,V_15Register,V_15RegNum);
        break;
      case Weight:
        modbus.readHoldingRegisters(SlaveAddress,WeightRegister,WeightRegNum);
        break;
      case SumVT:
        modbus.readHoldingRegisters(SlaveAddress,SumVTRegister,SumVTRegNum);
        break;
      case SumV15:
        modbus.readHoldingRegisters(SlaveAddress,SumV15Register,SumV15RegNum);
        break;
      case SumWght:
        modbus.readHoldingRegisters(SlaveAddress,SumWghtRegister,SumWghtRegNum);
        break;
      case BatchQuantity:
        modbus.readHoldingRegisters(SlaveAddress,BatchQuantityRegister,BatchQuantityRegNum);
        break;
      case AvgDensityX:
        modbus.readHoldingRegisters(SlaveAddress,AvgDensityXRegister,AvgDensityXRegNum);
        break;
      case AvgTemp1:
        modbus.readHoldingRegisters(SlaveAddress,AvgTemp1Register,AvgTemp1RegNum);
        break;
      case FlowRate:
        modbus.readHoldingRegisters(SlaveAddress,FlowRateRegister,FlowRateRegNum);
        break;
      case ProductNo:
        modbus.readHoldingRegisters(SlaveAddress,ProductNoRegister,ProductNoRegNum);
        break;
      case AdditivType:
        modbus.readHoldingRegisters(SlaveAddress,AdditivTypeRegister,AdditivTypeRegNum);
        break;
      case AddVT:
        modbus.readHoldingRegisters(SlaveAddress,AddVTRegister,AddVTRegNum);
        break;
      case SumAddVT:
        modbus.readHoldingRegisters(SlaveAddress,SumAddVTRegister,SumAddVTRegNum);
        break;
      case TargetAddRate:
        modbus.readHoldingRegisters(SlaveAddress,TargetAddRateRegister,TargetAddRateRegNum);
        break;
      case DateTime:
        modbus.readHoldingRegisters(SlaveAddress,DateTimeRegister,DateTimeRegNum);
        break;                                                                                                                
    }
  }      
}
