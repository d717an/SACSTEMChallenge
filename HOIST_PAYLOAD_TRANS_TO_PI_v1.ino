

#include<SPI.h>
#include<Wire.h>
#include<RF24.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
// configuration:
//NRF24L01+ <> ARDUINO PRO MINI <> MPU6050
//GND          GND                 GND
//3V3          3V3                 VCC
//CE           D9
//CSN          D10
//SCK          D13(sck)
//MOSI         D11(mosi)
//MISO         D12 (miso)
//IRQ (n/s)
//             A4 (SDA)           SDA
//             A5 (SCL)           SCL
//

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data

char tmp_str[7]; // temporary variable used in convert function


struct dataStruct{
  char _parameter;
  float value;
} myData[7];


char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

RF24 radio(9,10);
Adafruit_MPU6050 mpu;

void setup(void){
  Serial.begin(115200);
  Wire.begin();
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.enableAckPayload();
  radio.setChannel(76);
  radio.openWritingPipe(0xf0f0f0f0e1LL);
  radio.enableDynamicPayloads();
  radio.powerUp();

//MPU6050 SETUP//
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

} 
void loop(void){
    /* Take a new reading */
  mpu.read();
    
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  myData[0]._parameter = 'x';
  myData[0].value = a.acceleration.x;
  myData[1]._parameter = 'y';
  myData[1].value = a.acceleration.y;
  myData[2]._parameter = 'z';
  myData[2].value = a.acceleration.z;
  myData[3]._parameter = 'p';
  myData[3].value = g.gyro.x;
  myData[4]._parameter = 'q';
  myData[4].value = g.gyro.y;
  myData[5]._parameter = 'r';
  myData[5].value = g.gyro.z;  
//  buff[1] = a.acceleration.y;
//  buff[2] = a.acceleration.z;
//  buff[3] = temp.temperature;
//  buff[4] = g.gyro.x;
//  buff[5] = g.gyro.y;
//  buff[6] = g.gyro.z;
//  Serial.println(sizeof(buff[2]));
//  delay(100);
//  Wire.requestFrom(MPU_ADDR,2);
//  buff[0] = (Wire.read()<<8 | Wire.read()); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
//  buff[1] = (Wire.read()<<8 | Wire.read()); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
//  buff[2] = (Wire.read()<<8 | Wire.read()); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
//  buff[3] = (Wire.read()<<8 | Wire.read()); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
//  buff[4] = (Wire.read()<<8 | Wire.read()); // reading registers: 0recv_x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
//  buff[5] = (Wire.read()<<8 | Wire.read()); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
//  buff[6] = (Wire.read()<<8 | Wire.read()); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
//  buff[0] = (Wire.read()<<8 | a.acceleration.x); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
//  buff[1] = (Wire.read()<<8 | a.acceleration.y); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
//  buff[2] = (Wire.read()<<8 | a.acceleration.z); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
//  buff[3] = (Wire.read()<<8 | g.gyro.x); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
//  buff[4] = (Wire.read()<<8 | g.gyro.y); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
//  buff[5] = (Wire.read()<<8 | g.gyro.z); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
//  buff[6] = (Wire.read()<<8 | temp.temperature); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
  radio.stopListening(); 
  radio.write(&myData,sizeof(myData));
//  for(int i=0; i<1;i++){
//    radio.write(&myData[0], sizeof(myData));
//  }
  radio.startListening();
}
