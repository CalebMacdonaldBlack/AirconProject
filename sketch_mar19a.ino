    int desired_state = 0;

    int A_PIN = 22;
    int B_PIN = 24;
    int C_PIN = 26;
    int D_PIN = 28;
    int E_PIN = 30;
    int F_PIN = 32;

    int MODE_1_PIN = 2;
    int MODE_2_PIN = 3;
    int MODE_3_PIN = 4;
    int MODE_4_PIN = 5;
    int MODE_5_PIN = 6;

    int MOTOR_FORWARD_PIN = 50;
    int MOTOR_BACKWARD_PIN = 52;

    int last_known_mode = 1;

    int desired_mode = 0;

    int motor_direction = 0;

    
void stop_motor() {
  digitalWrite(MOTOR_FORWARD_PIN, LOW);
  digitalWrite(MOTOR_BACKWARD_PIN, LOW);

  motor_direction = 0;
}

void start_motor_forward() {
  digitalWrite(MOTOR_FORWARD_PIN, HIGH); // Forward
  digitalWrite(MOTOR_BACKWARD_PIN, LOW);
  motor_direction = 1;
}


void start_motor_backward() {
  digitalWrite(MOTOR_FORWARD_PIN, LOW); // Backward
  digitalWrite(MOTOR_BACKWARD_PIN, HIGH);

  motor_direction = -1;
}

void start_motor_relative(int current, int desired) {
  if (current - desired != 0){
      if ((current - desired) < 0) {
        start_motor_forward();
      } else {
      start_motor_backward();
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(A_PIN, INPUT_PULLUP);
  pinMode(B_PIN, INPUT_PULLUP);
  pinMode(C_PIN, INPUT_PULLUP);
  pinMode(D_PIN, INPUT_PULLUP);
  pinMode(E_PIN, INPUT_PULLUP);
  pinMode(F_PIN, INPUT_PULLUP);
  
  pinMode(MODE_1_PIN, INPUT_PULLUP);
  pinMode(MODE_2_PIN, INPUT_PULLUP);
  pinMode(MODE_3_PIN, INPUT_PULLUP);
  pinMode(MODE_4_PIN, INPUT_PULLUP);
  pinMode(MODE_5_PIN, INPUT_PULLUP);

  pinMode(MOTOR_FORWARD_PIN, OUTPUT); // Forward
  pinMode(MOTOR_BACKWARD_PIN, OUTPUT); // Backward

}


void loop() {
  // put your main code here, to run repeatedly:

    int ASwitch = digitalRead(A_PIN);
    int BSwitch = digitalRead(B_PIN);
    int CSwitch = digitalRead(C_PIN);
    int DSwitch = digitalRead(D_PIN);
    int ESwitch = digitalRead(E_PIN);
    int FSwitch = digitalRead(F_PIN);

    int mode_1 = digitalRead(MODE_1_PIN);
    int mode_2 = digitalRead(MODE_2_PIN);
    int mode_3 = digitalRead(MODE_3_PIN);
    int mode_4 = digitalRead(MODE_4_PIN);
    int mode_5 = digitalRead(MODE_5_PIN);
//
//    Serial.print(mode_1);
//    Serial.print(" ");
//    Serial.print(mode_2);
//    Serial.print(" ");
//    Serial.print(mode_3);
//    Serial.print(" ");
//    Serial.print(mode_4);
//    Serial.print(" ");
//    Serial.print(mode_5);
//    Serial.print(" ");
//    Serial.println();

    if (!mode_1) {
      desired_mode = 1;
    } else if (!mode_2) {
      desired_mode = 2;
    } else if (!mode_3) {
      desired_mode = 3;
    } else if (!mode_4) {
      desired_mode = 4;
    } else if (!mode_5) {
      desired_mode = 5;
    }

    Serial.print("Desired Mode: ");
    Serial.print(desired_mode);
    Serial.print(" | Last Known Mode: ");
    Serial.print(last_known_mode);
    Serial.print(" | Motor Direction: ");
    if (motor_direction == 0) {
      Serial.print("Stopped");
    } else if (motor_direction == 1) {
      Serial.print("Forward (CounterClockwise)");      
    } else if (motor_direction == -1) {
      Serial.print("Backward (Clockwise)");         
    }

    if (!ASwitch && !BSwitch) {
      Serial.print(" | Current Mode: 1");
      last_known_mode = 1;
      if (!mode_1 || desired_mode == 0) {
        stop_motor();
      } else {
        start_motor_relative(1, desired_mode);
      }

    } else if (!BSwitch && !CSwitch) {
      Serial.print(" | Current Mode: 2");
      last_known_mode = 2;
      if (!mode_2) {
        stop_motor();
      } else {
        start_motor_relative(2, desired_mode);
      }
      
    } else if (!CSwitch && !DSwitch) {
      Serial.print(" | Current Mode: 3");
      last_known_mode = 3;
      if (!mode_3) {
        stop_motor();
      } else {
        start_motor_relative(3, desired_mode);
      }
      
    } else if (!DSwitch && !ESwitch) {
      Serial.print(" | Current Mode: 4");
      last_known_mode = 4;
      if (!mode_4) {
        stop_motor();
      } else {
        start_motor_relative(4, desired_mode);
      }
      
    } else if (!ESwitch && !FSwitch) {
      Serial.print(" | Current Mode: 5");
      last_known_mode = 5;
      if (!mode_5) {
        stop_motor();
      } else {
        start_motor_relative(5, desired_mode);
      }
    } else {
        start_motor_relative(last_known_mode, desired_mode);
    }
    Serial.println();
}
