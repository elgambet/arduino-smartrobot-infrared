/*
  Dance.ino - Make elegoo smart robot car v1.0 dance
  Created by Pablo Gambetta December 2016
  Released into the public domain.
*/

// [esp] Incluir librerias necesarias para la conectividad y la conduccion del auto
// [eng] Include libraries necessary for the connectivity and driving of the car
#include <IRremote.h>
#include <Drivelib.h>

// [esp] Incluir drivelib
// [eng] Include drivelib
Drivelib drivelib;

// [esp] Definir los botones del control
// [eng] Define control buttons

int receiverpin = 12;

#define FORWARD 16736925
#define BACKWARD 16754775
#define STOP 16712445
#define LEFT 16720605
#define RIGHT 16761405

// [esp] Configurar el receptor de infrarojos
// [eng] Setting up the infrared receiver
IRrecv irrecv(receiverpin);
decode_results results;

/**
* [esp] Funcion de configuracion. Corre unicamente una vez. 
* [eng] Setup function. Only run once.
*/
void setup()
{
  // [esp] Parar
  // [eng] Stop
  drivelib.stop();
  // [esp] Abrir el puerto serial y establecer la velocidad en baudios a 9600
  // [eng] Open the serial port and set the baud rate to 9600
  Serial.begin(9600);
  // [esp] Configurar el pin receptor del sensor infrarojo
  // [eng] Configure infrared sensor receiver pin
  pinMode(receiverpin, INPUT);
  // [esp] Comenzar el proceso de recepcion de infrarojo
  // [eng] Begin the infrared receiving process.
  irrecv.enableIRIn();
}

/**
* [esp] Funcion que analiza el input recivido mediante infrarojo y ejecuta la accion correspondiente.
* [eng] Function that analize the input received by infrared and executes the corresponding action.
*/
void check_command(unsigned long BUTTON)
{
  switch (BUTTON)
  {
  case FORWARD:
    drivelib.forward();
    break;
  case BACKWARD:
    drivelib.backward();
    break;
  case LEFT:
    drivelib.left();
    break;
  case RIGHT:
    drivelib.right();
    break;
  case STOP:
    drivelib.stop();
    break;
  }
}

/**
* [esp] Funcion principal. Corre indefinidamente.
* [eng] Main function. Runs repeatedly.
*/
void loop()
{
  // [esp] Decodificar el input recibido.
  // [eng] Decode the received input.
  if (irrecv.decode(&results))
  {
    // [esp] Después de recibir, esta funcion debe ser llamada para reiniciar el receptor y prepararlo para recibir otro código.
    // [eng] After receiving, this must be called to reset the receiver and prepare it to receive another code.
    irrecv.resume();
    // [esp] LLamar a la funcion check_command
    // [eng] Call check_command function
    check_command(results.value);
    Serial.println(results.value);
  }
}
