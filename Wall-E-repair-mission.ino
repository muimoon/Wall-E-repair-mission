#include <IRremote.h>
const int RECV_PIN = 7;
int Button_Pin = A0;
int Go_motor = 11;
int Back_motor = 10;
int head_motor = 13;
int headwithhands_motor = 12;
int Left_eye_LED = 5;
int Right_eye_LED = 6;
// boolean flag = false;
// boolean motor_status = false;
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
  pinMode(Button_Pin, INPUT_PULLUP);
  pinMode(Go_motor, OUTPUT);
  pinMode(Back_motor, OUTPUT);
  pinMode(head_motor, OUTPUT);
  pinMode(headwithhands_motor, OUTPUT);
  pinMode(Left_eye_LED, OUTPUT);
  pinMode(Right_eye_LED, OUTPUT);
  digitalWrite(head_motor, HIGH);
  digitalWrite(headwithhands_motor, HIGH);
  digitalWrite(Back_motor, HIGH);
  digitalWrite(Go_motor, HIGH);
  digitalWrite(Left_eye_LED, LOW);
  digitalWrite(Right_eye_LED, LOW);
  irrecv.enableIRIn();
}

void Stop()
{
  digitalWrite(head_motor, HIGH);
  digitalWrite(headwithhands_motor, HIGH);
  digitalWrite(Back_motor, HIGH);
  digitalWrite(Go_motor, HIGH);
  digitalWrite(Left_eye_LED, LOW);
  digitalWrite(Right_eye_LED, LOW);
}

void Blink()
{
  digitalWrite(Left_eye_LED, LOW);
  digitalWrite(Right_eye_LED, LOW);
  delay(500);
  digitalWrite(Left_eye_LED, HIGH);
  digitalWrite(Right_eye_LED, HIGH);
}

void loop()
{
   if (analogRead(Button_Pin) < 50)
   {
    Stop();
    delay(300);
   }

  digitalWrite(Left_eye_LED, HIGH);
  digitalWrite(Right_eye_LED, HIGH);
  if (irrecv.decode(& results))
  {
    switch (results.value)
    {
      //case 0x42071B37://stop
      //Stop();
      case 0x42071B37://go
      digitalWrite(Go_motor, LOW);
      digitalWrite(Back_motor, HIGH);
      break;
      case 0x5321CE3F://back
      digitalWrite(Go_motor, HIGH);
      digitalWrite(Back_motor, LOW);
      break;
      case 0xF034E147://go
      digitalWrite(Go_motor, LOW);
      digitalWrite(Back_motor, HIGH);
      break;
      case 0x14F944F://back
      digitalWrite(Go_motor, HIGH);
      digitalWrite(Back_motor, LOW);
      break;
      case 0xFABE8FFF://headwithhands move
      digitalWrite(headwithhands_motor, LOW);
      digitalWrite(head_motor, HIGH);
      break;
      case 0xA01B3B9F://head move
      digitalWrite(headwithhands_motor, HIGH);
      digitalWrite(head_motor, LOW);
      break;
      case 0x667C9767://BLINK
      Blink();
      case 0xE60A533F://BLINK
      Stop();
      break;
      case 0xBD94307://TESTING CODE

      break;
    }
    irrecv.resume();
    delay(200);
  }
}
