#include <MotorDriver.h>

enum serialCommandSpecifier{
  SERIAL_COMMAND_SET      = 0,
  SERIAL_COMMAND_GET      = 1,
  SERIAL_COMMAND_EXECUTE  = 2,
  SERIAL_COMMAND_UNDEF    = 3
  };

  
enum serialCommandFunction{
  SERIAL_COMMAND_FUNCTION_MOTOR      = 0,
  SERIAL_COMMAND_FUNCTION_UNDEF
  };

enum serialCommandFunctionParameterDirection{
  SERIAL_COMMAND_FUNCTION_MOTOR_DIRECTION_FORWARD      = 0,
  SERIAL_COMMAND_FUNCTION_MOTOR_DIRECTION_BACKWARD     = 1,
  SERIAL_COMMAND_FUNCTION_MOTOR_DIRECTION_STOP         = 2,
  SERIAL_COMMAND_FUNCTION_MOTOR_DIRECTION_RELEASE      = 3, 
  SERIAL_COMMAND_FUNCTION_MOTOR_DIRECTION_UNDEF
  };

enum serialCommandFunctionParameterMotorSelection{
  SERIAL_COMMAND_FUNCTION_MOTOR_SELECTION_A     = 0,
  SERIAL_COMMAND_FUNCTION_MOTOR_SELECTION_B     = 1,
  SERIAL_COMMAND_FUNCTION_MOTOR_SELECTION_C     = 2,
  SERIAL_COMMAND_FUNCTION_MOTOR_SELECTION_D     = 3,
  SERIAL_COMMAND_FUNCTION_MOTOR_SELECTION_M     = 4,
  SERIAL_COMMAND_FUNCTION_MOTOR_SELECTION_UNDEF
  };

struct serialCommandMotorSet{
  serialCommandFunctionParameterMotorSelection motorSelection = SERIAL_COMMAND_FUNCTION_MOTOR_SELECTION_UNDEF;
  serialCommandFunctionParameterDirection  motorDirection = SERIAL_COMMAND_FUNCTION_MOTOR_DIRECTION_UNDEF;
  uint8_t motorSpeed = 0;
};
  

MotorDriver MAIN_motorControl;
String serialCommand;
serialCommandSpecifier MAIN_receiveSerialCommand = SERIAL_COMMAND_UNDEF;
serialCommandFunction  MAIN_receivedSerialCommandFunction = SERIAL_COMMAND_FUNCTION_UNDEF;
serialCommandMotorSet  MAIN_receivedSerialMotorSettings;

void setup()
{
 Serial.begin(9600);
}


void loop()
{
  bool validCommandReceived = false;
  if (Serial.available() > 0){
    serialCommand = Serial.readString();
    serialCommand.trim();
    validCommandReceived = CheckForValidCommand();
  }
  if (validCommandReceived){
    if ( MAIN_receivedSerialCommandFunction == SERIAL_COMMAND_FUNCTION_MOTOR){
      
    }
      MAIN_motorControl.motor(1,FORWARD,255);
    }

}

/**
 * @brief check for a valid command\n
 * byte[0] Command: [S]et, G[get], [E]xecute
 * byte[1] Function/Interface: [M]otor
 * byte[2] Function/Interface sub specifier: motor [A],[B],[C],[D],[M]ulti selection
 * byte[3] Function/Interface parameter: motor direction [F]orward, [B]ackward, [S]top, R[elease]
 * byte[4] Function/Interface parameter: motor speed [0]...[9]
 * @return true if a valid command is received, else false
 */
bool CheckForValidCommand(){
  if (serialCommand.length() != 5)
  {
    return false;  
  }

  switch(serialCommand[0]){
    case 'S':
     MAIN_receiveSerialCommand = serialCommandSpecifier::SERIAL_COMMAND_SET;
    break;
    case 'G':
     MAIN_receiveSerialCommand = serialCommandSpecifier::SERIAL_COMMAND_GET;
    break;
    case 'E':
     MAIN_receiveSerialCommand = serialCommandSpecifier::SERIAL_COMMAND_EXECUTE;
    break;
    default:
     MAIN_receiveSerialCommand = serialCommandSpecifier::SERIAL_COMMAND_UNDEF;
     return false;
    break;    
  }


  switch(serialCommand[1]){
    case 'M':
     MAIN_receivedSerialCommandFunction = SERIAL_COMMAND_FUNCTION_MOTOR;
    break;
    default:
     MAIN_receivedSerialCommandFunction = SERIAL_COMMAND_FUNCTION_UNDEF;
     return false;
    break;    
  }

  if (MAIN_receivedSerialCommandFunction == SERIAL_COMMAND_FUNCTION_MOTOR){
   switch(serialCommand[2]){
      case 'A':
          MAIN_receivedSerialMotorSettings.motorSelection = SERIAL_COMMAND_FUNCTION_MOTOR_SELECTION_A;
      break;
      case 'B':
          MAIN_receivedSerialMotorSettings.motorSelection = SERIAL_COMMAND_FUNCTION_MOTOR_SELECTION_B;
      break;
      case 'C':
          MAIN_receivedSerialMotorSettings.motorSelection = SERIAL_COMMAND_FUNCTION_MOTOR_SELECTION_C;
      break;
      case 'D':
          MAIN_receivedSerialMotorSettings.motorSelection = SERIAL_COMMAND_FUNCTION_MOTOR_SELECTION_D;
      break;
      case 'M':
          MAIN_receivedSerialMotorSettings.motorSelection = SERIAL_COMMAND_FUNCTION_MOTOR_SELECTION_M;
      break;     
      default:
          MAIN_receivedSerialMotorSettings.motorSelection = SERIAL_COMMAND_FUNCTION_MOTOR_SELECTION_UNDEF;
          return false;  
      break;
    }    
    
    
    switch(serialCommand[3]){
      case 'F':
          MAIN_receivedSerialMotorSettings.motorDirection = SERIAL_COMMAND_FUNCTION_MOTOR_DIRECTION_FORWARD;
      break;
      case 'B':
          MAIN_receivedSerialMotorSettings.motorDirection = SERIAL_COMMAND_FUNCTION_MOTOR_DIRECTION_BACKWARD;
      break;
      case 'S':
          MAIN_receivedSerialMotorSettings.motorDirection = SERIAL_COMMAND_FUNCTION_MOTOR_DIRECTION_STOP;
      break;
      case 'R':
          MAIN_receivedSerialMotorSettings.motorDirection = SERIAL_COMMAND_FUNCTION_MOTOR_DIRECTION_RELEASE;
      break;
      default:
          MAIN_receivedSerialMotorSettings.motorDirection = SERIAL_COMMAND_FUNCTION_MOTOR_DIRECTION_UNDEF;
          return false;
      break;
    }

       switch(serialCommand[4]){
      case '0':
        MAIN_receivedSerialMotorSettings.motorSpeed = 0;
      break;
      case '1':
        MAIN_receivedSerialMotorSettings.motorSpeed = 255/9*1;
      break;
      case '2':
        MAIN_receivedSerialMotorSettings.motorSpeed = 255/9*2;
      break;
      case '3':
        MAIN_receivedSerialMotorSettings.motorSpeed = 255/9*3;
      break;
      case '4':
        MAIN_receivedSerialMotorSettings.motorSpeed = 255/9*4;
      break;
      case '5':
        MAIN_receivedSerialMotorSettings.motorSpeed = 255/9*5;
      break;
      case '6':
        MAIN_receivedSerialMotorSettings.motorSpeed = 255/9*6;
      break;
      case '7':
        MAIN_receivedSerialMotorSettings.motorSpeed = 255/9*7;
      break;
      case '8':
        MAIN_receivedSerialMotorSettings.motorSpeed = 255/9*8;
      break;
      case '9':
        MAIN_receivedSerialMotorSettings.motorSpeed = 255/9*9;
      break;                
      default:
         MAIN_receivedSerialMotorSettings.motorSpeed = 0;
         return false;
      break;
    }
  }
  else {
    //function not recognize
    return false;
  }

  return true;

}
