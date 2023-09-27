

// INSTRUMENTATION CIRCUIT PROGRAMMING ESP8266  MAUHMMAD ARSLAN

/* Device Information from Blynk IOT APP*/
#define BLYNK_TEMPLATE_ID           "#####################"
#define BLYNK_TEMPLATE_NAME         "Instrumentation Circuit"
#define BLYNK_AUTH_TOKEN            "######################"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


  #include <ESP8266WiFi.h>
  #include <BlynkSimpleEsp8266.h>

// WiFi credentials.
// SSID = Netowrk Name and PASS is password.
char ssid[] = "############";
char pass[] = "##########";

BlynkTimer timer;

// This function sendss the uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  Blynk.virtualWrite(V2, millis() / 1000);
}
const int analogInPin= A0;

float Tempvalue = 0;
float voltageValue = 0;
int sensorValue = 0;


void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimerEvent); 
  
}
void myVoltageEvent()
{

  Blynk.virtualWrite(V4, voltageValue);  // Send the results to Gauge Widget
}
void myTempEvent()
{
  Blynk.virtualWrite(V5, Tempvalue);  // Send the results to Gauge Widget
}



void loop()
{
  sensorValue = analogRead(analogInPin);  // Read the analog in value:
  voltageValue = (sensorValue * (3.3/1023)-1.4);
  Tempvalue = ((voltageValue+0.4223)/0.0358);
  Serial.print("Voltage = ");  // Print the results...
  Serial.println(voltageValue);  // ...to the serial monitor:
  Blynk.virtualWrite(V4, voltageValue);  // Send the results to Gauge Widget
  Blynk.virtualWrite(V5, Tempvalue);
  
  Blynk.run();
  timer.run();

}