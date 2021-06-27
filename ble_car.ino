
#define LINE_BUF_SIZE 16

#define CMD_FORWARD 1
#define CMD_STOP 0
#define CMD_BACK -1
#define CMD_RIGTH 1
#define CMD_STRAIGHT 0
#define CMD_LEFT -1

#define PIN_MOTOR_FRONT_A 10
#define PIN_MOTOR_FRONT_B 11
#define PIN_MOTOR_BACK_A  12
#define PIN_MOTOR_BACK_B  13

#define UPDATE_VALID_CNT  10
#define UPDATE_DIRECTION_VALID_CNT  1

char buf[LINE_BUF_SIZE];
int ind = 0;

int cmd_move      = CMD_STOP;
int cmd_move_valid  = 0;
int cmd_direction = CMD_STRAIGHT;
int cmd_direction_valid  = 0;
void setup() {
  Serial.begin(9600);
  pinMode(PIN_MOTOR_FRONT_A, OUTPUT);
  pinMode(PIN_MOTOR_FRONT_B, OUTPUT);
  pinMode(PIN_MOTOR_BACK_A, OUTPUT);
  pinMode(PIN_MOTOR_BACK_B, OUTPUT);
}

void loop() {
  read_line();
  car_logic();
  dump_varables();
}

void dump_varables(){

  Serial.print("move: ");
  Serial.print(cmd_move);
  Serial.print("\tmove_valid: ");
  Serial.print(cmd_move_valid);
  Serial.print("\tdirection: ");
  Serial.print(cmd_direction);
  Serial.print("\tdirection_valid: ");
  Serial.println(cmd_direction_valid);
  }

void car_logic(){

  if(cmd_move == CMD_FORWARD && cmd_move_valid > 0){
      digitalWrite(PIN_MOTOR_BACK_A, 1);
      digitalWrite(PIN_MOTOR_BACK_B, 0);
      cmd_move_valid--;
  }else if(cmd_move == CMD_BACK && cmd_move_valid > 0){
      digitalWrite(PIN_MOTOR_BACK_A, 0);
      digitalWrite(PIN_MOTOR_BACK_B, 1);
      cmd_move_valid--;
  }else{
      digitalWrite(PIN_MOTOR_BACK_A, 0);
      digitalWrite(PIN_MOTOR_BACK_B, 0);
  }
  delay(2);
  if(cmd_direction == CMD_RIGTH && cmd_direction_valid > 0){
      digitalWrite(PIN_MOTOR_FRONT_A, 1);
      digitalWrite(PIN_MOTOR_FRONT_B, 0);
      cmd_direction_valid--;
  }else if(cmd_direction == CMD_LEFT && cmd_direction_valid > 0){
      digitalWrite(PIN_MOTOR_FRONT_A, 0);
      digitalWrite(PIN_MOTOR_FRONT_B, 1);
      cmd_direction_valid--;
  }else{
      digitalWrite(PIN_MOTOR_FRONT_A, 0);
      digitalWrite(PIN_MOTOR_FRONT_B, 0);
  }
  delay(8);
  digitalWrite(PIN_MOTOR_FRONT_A, 0);
  digitalWrite(PIN_MOTOR_FRONT_B, 0);
}

//String line;
void read_line() {
  while (Serial.available()) {
    char c = Serial.read();
    Serial.print(c);
    if (c == '<')
    {
      buf[0] = c;
      ind = 1;
    }
    else if ( (c == 'F' || c == 'B' || c == 'R' || c == 'L') && ind == 1)
    {
      buf[1] = c;
      //Serial.print(c);
      ind = 2;
    }
    else if (c == '>' && ind > 3)
    {
      buf[ind] = 0;// string terminate
      //Serial.print(c);
      parse_line();
    }
    else
    {
      if (ind <  LINE_BUF_SIZE - 1)
      {
        buf[ind] = c;
        ind ++;
      }
    }
  }
}

void parse_line() {
  int val = 0;

    val = parse_value(&buf[2]);   
    //Serial.print(val); 
    switch ( buf[1]){        
      case 'F':{        
          if(val > 0 && val <=100){        
            cmd_move = CMD_FORWARD;
            cmd_move_valid = UPDATE_VALID_CNT;
          }else if(val == 0){
            cmd_move = CMD_STOP;         
          }                
        }
        break;
      case 'B':{
          if(val > 0 && val <=100){        
            cmd_move = CMD_BACK;
            cmd_move_valid = UPDATE_VALID_CNT;
          }else if(val == 0){
            cmd_move = CMD_STOP;         
          }
      }
      break;
      case 'R':{
          if(val > 0 && val <=100){        
            cmd_direction = CMD_RIGTH;
            cmd_direction_valid = UPDATE_DIRECTION_VALID_CNT;
          }else if(val == 0){
            cmd_direction = CMD_STOP;         
          }          
        }  
        break;      
      case 'L':{
          if(val > 0 && val <=100){        
            cmd_direction = CMD_LEFT;
            cmd_direction_valid = UPDATE_DIRECTION_VALID_CNT;
          }else if(val == 0){
            cmd_direction = CMD_STOP;         
          }          
        }
        break;
    };
}

int parse_value(char *chr) {
  char c;
  int val = 0;
  for (int i = 0; i < 3; i++) {
    c = *(chr + i);
     Serial.print(c);
    if ( c >= '0' && c <= '9') {
      val *= 10;
      val += (c - '0');
    } else {
      return -1;
    }
  }
  return val;
}
