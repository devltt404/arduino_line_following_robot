
#define in1 5
#define in2 8
#define in3 7
#define in4 6
#define enA 10
#define enB 9

bool isFirstLoop = false;
int forwardSpeed = 180;
int turnSpeed = 255;
int M1_Speed = forwardSpeed;// speed of motor 1
int M2_Speed = forwardSpeed;// speed of motor 2
int LeftRotationSpeed = turnSpeed;  // Left Rotation Speed
int RightRotationSpeed = turnSpeed; // Right Rotation Speed
int turnDelay = 30;

void Stop()
{
  Serial.println("STOP");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}


void forward()
{
  Serial.println("FORWARD");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}


void right()
{
  Serial.println("TURN RIGHT");
  Stop(); // First, stop the motors
  delay(10);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
  delay(turnDelay);
}

void left()
{
  Serial.println("TURN LEFT");
  Stop(); // First, stop the motors
  delay(10);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
  delay(turnDelay);

}


void setup()
{

  Serial.begin(9600);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(A0, INPUT); // initialize Left sensor as an input
  pinMode(A1, INPUT); // initialize Right sensor as an input
  TCCR0B = TCCR0B & B11111000 | B00000001;
  TCCR1B = TCCR1B & B11111000 | B00000001;
  TCCR1B = TCCR1B & 0b11111000 | 0x01;
}

void loop()
{
  int LEFT_SENSOR = digitalRead(A0);
  int RIGHT_SENSOR = digitalRead(A1);
  if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 0)
  {
    Stop(); // FORWARD
  }

  else if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 1)
  {

    right(); // Move Right
  }

  else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 0)
  {
    left(); // Move Left
  }

  else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 1)
  {
    forward(); // STOP
  }
}
