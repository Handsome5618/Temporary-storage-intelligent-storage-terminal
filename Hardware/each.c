#include "each.h"
#include "delay.h"

int usart[5];//stm32接收数据数组

static Usart_data usart_data_t ;
void Usart_Receive_Data(int16_t data)//接收Usart3传过来的数据
{
    if(data == 1)
    {
        usart_data_t.stata = 1;
        while(1)
        {
            usart_data_t.stata = 0;
            if(USART3->DR != 1)
            {
                usart[0] = USART3->DR;
                usart_data_t.stata = 2;
                break;
            }
        }
    }
    if(data == 2)
    {

        while(1)
        {
            if(USART3->DR != 2)
            {
                usart[2] = USART3->DR;
                usart_data_t.stata = 3;
                break;
            }
        }

    }
    if(data == 4 || usart_data_t.stata == 5)
    {

        while(1)
        {
            if(USART3->DR != 4)
            {
                usart[3] = USART3->DR;
                usart_data_t.stata = 5;
                break;
            }
        }
    }


    if(data == 3)
    {
        usart_data_t.stata = 4;
    }

    if(usart_data_t.stata == 1)
    {

        usart[1] = USART3->DR;

    }
    if(usart_data_t.stata == 2)
    {

        usart[3] = USART3->DR;

    }
}
void Usart_Data(void)
{
    usart_data_t.distance_1=usart[0]<<8|usart[1];
    usart_data_t.distance_2=usart[1];
    usart_data_t.angle = usart[2];
    usart_data_t.add_x = usart[3];

}
Usart_data* get_Usart1_data_point(void)
{
    return &usart_data_t;
}


