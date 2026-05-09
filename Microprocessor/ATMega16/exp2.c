#include "iom16v.h"
#include <macros.h>
#include <AVR_HJ-2G.H>

#define K1_DOWN ((PIND & BIT(2)) == 0) // K1飞线接PD2
#define K2_DOWN ((PIND & BIT(3)) == 0) // K2飞线接PD3

#define MODE_LEFT 1  // 从左向右
#define MODE_RIGHT 2 // 从右向左

volatile uchar mode = MODE_LEFT; // 1=左向右流水灯；2=右向左流水灯

// 外部中断0服务程序（K1，向量号2）
#pragma interrupt_handler INT0_ISR:2
void INT0_ISR(void)
{
    Delayms(20);              // 消抖
    if (K1_DOWN) // 确认按下
    {
        while (K1_DOWN)
            ;     // 等待按键释放
        mode = MODE_LEFT; // 切换为从左向右
    }
}

// 外部中断1服务程序（K2，向量号3）
#pragma interrupt_handler INT1_ISR:3
void INT1_ISR(void)
{
    Delayms(20);              // 消抖
    if (K2_DOWN) // 确认按下
    {
        while (K2_DOWN)
            ;     // 等待按键释放
        mode = MODE_RIGHT; // 切换为从右向左
    }
}

// 从左向右流水灯
void left_flow(void)
{
    uchar cnt, i;
    for (cnt = 1; cnt <= 8; cnt++)
    {
        PORTB = 0xFF;
        for (i = 0; i < cnt; i++)
            PORTB &= ~BIT(i); // 逐位点亮
        Delayms(200);
    }
}

// 从右向左流水灯
void right_flow(void)
{
    uchar cnt, i;
    for (cnt = 1; cnt <= 8; cnt++)
    {
        PORTB = 0xFF;
        for (i = 0; i < cnt; i++)
            PORTB &= ~BIT(7 - i); // 逐位点亮
        Delayms(200);
    }
}

void main()
{
    LEDON();                    // 打开LED总开关
    SEGOFF();                   // 关闭数码管
    DDRB = 0xFF;                // PB口输出
    PORTB = 0xFF;               // 全部熄灭
    DDRD &= ~(BIT(2) | BIT(3)); // PD2, PD3 输入
    PORTD |= BIT(2) | BIT(3);   // 使能上拉

    // 外部中断初始化：INT1下降沿, INT0下降沿触发
    MCUCR |= (1 << ISC11) | (0 << ISC10) | (1 << ISC01) | (0 << ISC00);

    GICR |= (1 << INT1) | (1 << INT0); // 使能INT1和INT0

    GIFR |= (1 << INTF1) | (1 << INTF0); // 清除中断标志

    SREG |= BIT(7); // 全局开中断

    while (1)
    {
        if (mode == MODE_LEFT)
            left_flow();
        else
            right_flow();
    }
}
