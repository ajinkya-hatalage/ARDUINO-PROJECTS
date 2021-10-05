#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(10, 11);
#include <String.h>
int flag = 0;
void setup()
{
  pinMode(9, OUTPUT);
  pinMode(12, INPUT);
  gprsSerial.begin(9600);               // the GPRS baud rate
  Serial.begin(9600);    // the GPRS baud rate
  Module_Init();
}
void loop()
{
  if (gprsSerial.available())
    Serial.write(gprsSerial.read());
  int fire = digitalRead(12);
  if (fire == 0)
  {
    digitalWrite(9, HIGH);
    gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
    delay(6000);
    ShowSerialData();
    gprsSerial.println("AT+CIPSEND");//begin send data to remote server
    delay(4000);
    ShowSerialData();
    String str = "GET https://api.thingspeak.com/update?api_key=ER43PXXXXXHQF0I&field1=" + String(1);
    Serial.println(str);
    gprsSerial.println(str);//begin send data to remote server
    delay(4000);
    ShowSerialData();
    digitalWrite(9, LOW);
    gprsSerial.println((char)26);//sending
    delay(5000);//waitting for reply, important! the time is base on the condition of internet
    gprsSerial.println();
    ShowSerialData();
    gprsSerial.println("AT+CIPSHUT");//close the connection
    delay(100);
    ShowSerialData();
    flag = 0;
  }
else
  {
    digitalWrite(9, LOW);
    if (flag == 0)
    {
      flag = 1;
      gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
      delay(6000);
      ShowSerialData();
      gprsSerial.println("AT+CIPSEND");//begin send data to remote server
      delay(4000);
      ShowSerialData();
      String str = "GET https://api.thingspeak.com/update?api_key=ER43PWT91CGHQF0I&field1=" + String(0);
      Serial.println(str);
      gprsSerial.println(str);//begin send data to remote server
      delay(4000);
      ShowSerialData();
      digitalWrite(9, LOW);
      gprsSerial.println((char)26);//sending
      delay(5000);//waitting for reply, important! the time is base on the condition of internet
      gprsSerial.println();
      ShowSerialData();
      gprsSerial.println("AT+CIPSHUT");//close the connection
      delay(100);
      ShowSerialData();
    }
  }
}
void ShowSerialData()
{
  while (gprsSerial.available() != 0)
    Serial.write(gprsSerial.read());
  delay(5000);
}
void Module_Init()
{
  gprsSerial.println("AT");
  delay(1000);
  gprsSerial.println("AT+CPIN?");
  delay(1000);
  gprsSerial.println("AT+CREG?");
  delay(1000);
  gprsSerial.println("AT+CGATT?");
  delay(1000);
  gprsSerial.println("AT+CIPSHUT");
  delay(1000);
  gprsSerial.println("AT+CIPSTATUS");
  delay(2000);
  gprsSerial.println("AT+CIPMUX=0");
  delay(2000);
  ShowSerialData();
  gprsSerial.println("AT+CSTT=\"www\"");
  delay(1000);
  ShowSerialData();
  gprsSerial.println("AT+CIICR");
  delay(3000);
  ShowSerialData();
  gprsSerial.println("AT+CIFSR");
  delay(2000);
  ShowSerialData();
  gprsSerial.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();
}