// Garoando em Linha - Ver. 0.3
// Desenvolvido por Haoji (rafaelme.com)

#include <AFMotor.h>
#include <Ultrasonic.h>
#include <IRremote.h>

// Creating ultrasound sensors
Ultrasonic ultra(A0,A1);

// Creating front motors
AF_DCMotor front_left(4);
AF_DCMotor front_right(3);

// Sensor IR
int RECV_PIN = 16;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Testing Motors");

  // set front motors speed
  front_left.setSpeed(200);
  front_right.setSpeed(200);
  // turn front motors on
  front_left.run(RELEASE);
  front_right.run(RELEASE);
}

void loop() {
  // sensores
  Serial.print("Sensor de ultrasom: ");
  Serial.print(ultra.Ranging(CM)); // CM ou INC (polegadas)
  Serial.print(" cm     " );
  Serial.println();
  delay(1000);
  
  if (irrecv.decode(&results)) {
    front_right.run(FORWARD);
    front_left.run(FORWARD);
    delay(1000);
    //Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  
  if (ultra.Ranging(CM) < 10) {
  // mover para tras
  front_right.run(BACKWARD);
  front_left.run(BACKWARD);
  delay(1000);
  }
  // parar
  front_right.run(RELEASE);
  front_left.run(RELEASE);
}
