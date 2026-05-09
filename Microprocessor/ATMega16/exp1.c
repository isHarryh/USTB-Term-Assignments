#include "iom16v.h"
#include <macros.h>
#include <AVR_HJ-2G.H>

#define K1_DOWN ((PIND & BIT(0)) == 0) // K1
#define K2_DOWN ((PIND & BIT(1)) == 0) // K2

#define MODE_LEFT 1  // 从左向右
#define MODE_RIGHT 2 // 从右向左

void left_flow(void);
void right_flow(void);

void main()
{
    uchar mode = MODE_LEFT; // 默认

    LEDON();                    // 打开LED总开关
    SEGOFF();                   // 关闭数码管显示
    PORTB = 0xFF;               // 熄灭LED
    DDRB = 0xFF;                // PB口全输出
    DDRD &= ~(BIT(0) | BIT(1)); // PD0, PD1 输入
    PORTD |= BIT(0) | BIT(1);   // 开启上拉电阻

    while (1)
    {
        // 检测K1
        if (K1_DOWN)
        {
            Delayms(20); // 延时消抖
            if (K1_DOWN)
            {
                while (K1_DOWN)
                    ;             // 等待按键释放
                mode = MODE_LEFT; // 切换到从左向右
            }
        }

        // 检测K2
        if (K2_DOWN)
        {
            Delayms(20);
            if (K2_DOWN)
            {
                while (K2_DOWN)
                    ;              // 等待按键释放
                mode = MODE_RIGHT; // 切换到从右向左
            }
        }

        // 执行流水灯
        if (mode == MODE_LEFT)
            left_flow();
        else
            right_flow();
    }
}

/* 从左向右流水灯：依次点亮左侧1,2,...,8个LED，再循环 */
void left_flow(void)
{
    uchar cnt, i;
    for (cnt = 1; cnt <= 8; cnt++)
    {
        PORTB = 0xFF; // 先全部熄灭
        for (i = 0; i < cnt; i++)
            PORTB &= ~BIT(i); // 逐个点亮
        Delayms(200);
    }
}

/* 从右向左流水灯：依次点亮右侧1,2,...,8个LED，再循环 */
void right_flow(void)
{
    uchar cnt, i;
    for (cnt = 1; cnt <= 8; cnt++)
    {
        PORTB = 0xFF; // 先全部熄灭
        for (i = 0; i < cnt; i++)
            PORTB &= ~BIT(7 - i); // 逐个点亮
        Delayms(200);
    }
}
