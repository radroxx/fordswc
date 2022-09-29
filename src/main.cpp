#include <Arduino.h>
#include <Every.h>
#include <buttons.h>

// Config service led pin
#define LED_PIN 13

const long unsigned int button_read_tiks = 50; // 50 ms
const unsigned int button_mode_change_wait = 3000/button_read_tiks; // 2 sec
unsigned int button_mode_change_counter = 0;

int button_mode = 0; // media
//int button_mode = 1; // cruise

// Read buttons tiks
Every button_reade_timer(button_read_tiks);

// Reader buttons pin
ButtonsSWCReade button_a(A0);

// Write buttons
ButtonsSWCWriter button_writer;


void setup()
{
  //Serial.begin(115200);

  // Config input interface
  // Настройка зависит от резистора на пине
  button_a.set_between( OK,          660, 680);
  button_a.set_between( SEEK_DOWN,   490, 510);
  button_a.set_between( SEEK_UP,     340, 360);
  button_a.set_between( VOLUME_UP,   213, 233);
  button_a.set_between( VOLUME_DOWN, 113, 133);


  // Config buttons pin
  button_writer.set_pin( OK,          2 ); // 2036 Om
  button_writer.set_pin( SEEK_DOWN,   3 ); // 1036 Om
  button_writer.set_pin( SEEK_UP,     4 ); // 561.7 Om
  button_writer.set_pin( VOLUME_UP,   5 ); // 300.7 Om
  button_writer.set_pin( VOLUME_DOWN, 6 ); // 146.7 Om

  button_writer.set_pin( SET_UP,      7 ); // 604 Om
  button_writer.set_pin( SET_DOWN,    8 ); // 303 Om
  button_writer.set_pin( RESET,       9 ); // 121 Om
  button_writer.set_pin( ON,         10 ); // 1115 Om
  button_writer.set_pin( OFF,        11 ); // 0 Om

  button_writer.release_all();

  // 3 hello blink
  for(unsigned int i = 0; i < 3; i++)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);
    delay(300);
  }
}


void btn_loop()
{
  int press_button_a = button_a.read();

  if( press_button_a == UNKNOWN ) {
    button_writer.release_all();
    button_mode_change_counter = 0;
    digitalWrite(LED_PIN, LOW);

    return;
  }

  // Переключение режима кнопок при длительном зажатии центральной кнопки
  if( press_button_a == OK ) {
    button_mode_change_counter++;
    if( button_mode_change_counter == button_mode_change_wait) {
      button_mode++;
      if( button_mode > 1 ) { button_mode=0; }
    }
  }

  if( button_mode == 0 ) {
    button_writer.press(press_button_a);
    digitalWrite(LED_PIN, HIGH);
  }
  
  if( button_mode == 1 ) {
    switch(press_button_a)
    {
      case OK:
        button_writer.press(ON);
        break;
      case VOLUME_UP:
        button_writer.press(SET_UP);
        break;
      case VOLUME_DOWN:
        button_writer.press(SET_DOWN);
        break;
      case SEEK_DOWN:
        button_writer.press(RESET);
        break;
      case SEEK_UP:
        button_writer.press(OFF);
        break;
    }
    digitalWrite(LED_PIN, HIGH);
  }

}


void loop()
{
  if( button_reade_timer() ) {
    btn_loop();
  }
}
