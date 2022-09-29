#include <Arduino.h>
#include <buttons.h>


void ButtonsSWCWriter::press(int btn_press)
{
    if( btn_press == UNKNOWN )
    {
        return;
    }

    // Открывем пин на землю
    pinMode(buttons_to_pin[btn_press], OUTPUT);
}


void ButtonsSWCWriter::release(int btn_releas)
{
    if( btn_releas == UNKNOWN )
    {
        return;
    }

    // Запираем пин
    pinMode(buttons_to_pin[btn_releas], INPUT);
}


void ButtonsSWCWriter::set_pin(int btn, int pin)
{
    buttons_to_pin[btn] = pin;
}


void ButtonsSWCWriter::release_all()
{
    for( int i = 0; i < button_count; i++ ){
        release(i);
    }
}


ButtonsSWCReade::ButtonsSWCReade(int p_pin)
{
    pin = p_pin;
}


void ButtonsSWCReade::set_between(int btn, unsigned int min, unsigned int max)
{
    buttons_value_min[btn] = min;
    buttons_value_max[btn] = max;
}


int ButtonsSWCReade::read()
{
    int btn_swc_read_value = analogRead(pin);

    for(int btn = 0; btn < button_count; btn++)
    {
        if( buttons_value_min[btn] < btn_swc_read_value && btn_swc_read_value < buttons_value_max[btn] )
        {
            return btn;
        }
    }

    return UNKNOWN;
}