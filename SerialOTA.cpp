#include "SerialOTA.h"


SerialOTA serialOTA;

WiFiServer SerialOTA::server(SERIAL_OTA_PORT);
WiFiClient SerialOTA::clients[SERIAL_OTA_N_CLIENTS_MAX];
uint8_t  SerialOTA::buffer[BUFFER_SIZE];

void SerialOTA::begin()
{
  server.begin();
  server.setNoDelay(true);

};

void SerialOTA::loop()
{

  uint8_t i;
  if (server.hasClient())
  {
    for(i = 0; i < SERIAL_OTA_N_CLIENTS_MAX; i++)
    {
      //find free/disconnected spot
      if (!clients[i] || !clients[i].connected())
      {
        if(clients[i]) clients[i].stop();
        clients[i] = server.available();
        continue;
      }
    }
    //no free/disconnected spot so reject
    WiFiClient serverClient = server.available();
    serverClient.stop();
  }



  //check clients for data and copy to buffer
  for(i = 0; i < SERIAL_OTA_N_CLIENTS_MAX; i++){
    if (clients[i] && clients[i].connected()){
      if(clients[i].available()){
        //get data from the telnet client and push it to the UART
        while(clients[i].available()) clients[i].read(buffer,BUFFER_SIZE);
      }
    }
  }

};


void SerialOTA::println(const char* str)
{

  for(uint8_t i = 0; i < SERIAL_OTA_N_CLIENTS_MAX; i++)
  {
      if (clients[i] && clients[i].connected())
      {
        clients[i].write(str);
      }
  }   
      
  
}

