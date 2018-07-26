#include <SoftwareSerial.h>
SoftwareSerial akpalgps(3, 4); // RX, TX
SoftwareSerial akpalbts(12, 13);
int buzzer = 2, motbase = 0, moty = 0, motbasein1 = 8, motbasein2 = 9, motyin3 = 10, motyin4 = 11, pir = 0, batsense = 0;
float  sound_pulse_duration = 0, practical_speed_of_sound = 0, distance = 0;
char a;
void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  pinMode(buzzer, OUTPUT);
  pinMode(motbasein1, OUTPUT);
  pinMode(motbasein2, OUTPUT);
  pinMode(motyin3, OUTPUT);
  pinMode(motyin4, OUTPUT);
  pinMode(5, OUTPUT);
  //TRIG
  pinMode(6, INPUT);
  //ECHO
  pinMode(7, INPUT);
  digitalWrite(buzzer, HIGH);
  delay(300);
  digitalWrite(buzzer, LOW);
  delay(1000);
  digitalWrite(buzzer, HIGH);
  delay(600);
  digitalWrite(buzzer, LOW);
  delay(1000);
  digitalWrite(buzzer, HIGH);
  delay(950);
  digitalWrite(buzzer, LOW);
}
void loop()
{
  akpalbts.begin(9600);
  if (akpalbts.available())
  {
    a = akpalbts.read();
    Serial.write(a);
    motbase = analogRead(A0);
    moty = analogRead(A1);
    batsense = analogRead(A2);
    Serial.println("base value");
    Serial.println(motbase);
    Serial.println("y value");
    Serial.println(moty);
    Serial.print("battery sense=");
    Serial.println(batsense);
    if (a == 'u')
    {
      digitalWrite(motyin4, HIGH);
      digitalWrite(motyin3, LOW);
      delay(70);
      digitalWrite(motyin3, LOW);
      digitalWrite(motyin4, LOW);
      Serial.println("u loop entered");
    }
    if (a == 'd')
    {
      digitalWrite(motyin3, HIGH);
      digitalWrite(motyin4, LOW);
      delay(70);
      digitalWrite(motyin3, LOW);
      digitalWrite(motyin4, LOW);
      Serial.println("d loop entered");
    }
    if (a == 'l')
    {
      digitalWrite(motbasein2, HIGH);
      digitalWrite(motbasein1, LOW);
      delay(70);
      digitalWrite(motbasein2, LOW);
      digitalWrite(motbasein1, LOW);
      Serial.println("l loop entered");
    }
    if (a == 'r')
    {
      digitalWrite(motbasein1, HIGH);
      digitalWrite(motbasein2, LOW);
      delay(70);
      digitalWrite(motbasein1, LOW);
      digitalWrite(motbasein2, LOW);
      Serial.println("l loop entered");
    }
    else if (a == '1')
    {
      akpalgps.begin(9600);
      delay(500);
      for (int i = 0; i < 200; i++)
      {
        if (akpalgps.available())
          Serial.write(akpalgps.read());
      }
      Serial.println("1 loop entered");
    }
    else if (a == '2')
    {
      //initiating ultra-sonic  sensor
      digitalWrite(5, HIGH);
      delay(0.00001);
      digitalWrite(5, LOW);
      sound_pulse_duration = pulseIn(6, HIGH);
      delay(0.00001);
      sound_pulse_duration = sound_pulse_duration * 0.0000005;
      practical_speed_of_sound = (331.5);
      distance = practical_speed_of_sound * sound_pulse_duration * 100;
      Serial.print(distance);
      Serial.println("2 loop entered");
      delay(2000);
    }
    else if (a == '3')
    {
      pir = digitalRead(7);
      Serial.print("pir action=");
      Serial.println(pir);
      pir = 0;
    }
  }
}


