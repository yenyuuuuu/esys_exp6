#include "mbed.h"
#include "mbed_events.h"


InterruptIn button(USER_BUTTON);
DigitalOut led(LED1);
Timeout  press_threhold;

EventQueue queue(32 * EVENTS_EVENT_SIZE);



void button_release_detecting()
{
    button.enable_irq();
}



void button_pressed()
{
    button.disable_irq();
    
    press_threhold.attach(&button_release_detecting, 1.0);
    // queue.call(printf, "call button_pressed.\n");
    
}

void button_released()
{
    led = !led;
    queue.call(printf, "call button_released.\n");
}


// main() runs in its own thread in the OS
int main()
{
    Thread t;
    t.start(callback(&queue, &EventQueue::dispatch_forever));

    button.fall(&button_pressed);
    button.rise(&button_released);

    while (1);
}