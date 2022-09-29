
enum button { UNKNOWN, OK, SEEK_DOWN, SEEK_UP, VOLUME_UP, VOLUME_DOWN, SET_UP, SET_DOWN, RESET, ON, OFF };
const int button_count = 11;


class ButtonsSWCReade
{
    public:
        ButtonsSWCReade(int p_pin);
        int read();
        void set_between(int btn, unsigned int min, unsigned int max);
    private:
        int pin;
        int buttons_value_min[button_count] = {0};
        int buttons_value_max[button_count] = {0};
};


class ButtonsSWCWriter
{
    public:
        void press(int btn_press);
        void release(int btn_releas);
        void release_all();
        void set_pin(int btn, int pin);
    private:
        int buttons_to_pin[button_count] = {0};
};

