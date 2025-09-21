// === Motor Pin Definitions (from your setup) ===
const int IN1 = 4;    // Right motor IN1
const int IN2 = 5;    // Right motor IN2
const int IN3 = 6;    // Left motor IN3
const int IN4 = 7;    // Left motor IN4
const int ENA = 9;    // Right motor speed (PWM)
const int ENB = 10;   // Left motor speed (PWM)

// === IR Sensors ===
const int IR_LEFT  = 2;  // Left line sensor
const int IR_RIGHT = 3;  // Right line sensor

// === Motor speed settings ===
#define SPEED 120     // Forward speed
#define TURN 150      // Turning speed

void setup() {
  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Sensors
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  Serial.begin(9600);
}

void loop() {
  bool leftSensor  = digitalRead(IR_LEFT);
  bool rightSensor = digitalRead(IR_RIGHT);

  // Print sensor readings for debugging
  Serial.print("L:");
  Serial.print(leftSensor);
  Serial.print(" | R:");
  Serial.println(rightSensor);

  // === Line-following logic ===
  if (leftSensor == LOW && rightSensor == LOW) {
    moveForward();        // Both sensors detect line → go forward
  }
  else if (leftSensor == LOW && rightSensor == HIGH) {
    turnRight();          // Left detects line, right off → turn right
  }
  else if (leftSensor == HIGH && rightSensor == LOW) {
    turnLeft();           // Right detects line, left off → turn left
  }
  else {
    stopMotors();         // Both sensors off line → stop
  }

  delay(100); // Small delay for stability
}

// === Motor control functions ===
void moveForward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);  // Right motor backward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);  // Left motor forward
  analogWrite(ENA, TURN);
  analogWrite(ENB, TURN);
}

void turnLeft() {
  digitalWrite(IN1, LOW);  // Right motor forward
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  // Left motor backward
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, TURN);
  analogWrite(ENB, TURN);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
