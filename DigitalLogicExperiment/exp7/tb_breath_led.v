`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
// Create Date: 2026/04/15 23:17:26
// Design Name:
// Module Name: tb_breath_led
//
//////////////////////////////////////////////////////////////////////////////////

module tb_breath_led();
    reg clk_100M;
    reg rst_n;
    wire led;

    // ʵ����������ģ��
    breath_led uut (
        .clk_100M(clk_100M),
        .rst_n(rst_n),
        .led(led)
    );

    // ����100MHzʱ��
    initial begin
        clk_100M = 0;
        forever #5 clk_100M = ~clk_100M;
    end

    // ���Լ���
    initial begin
        rst_n = 0;  // ��λ
        #100;
        rst_n = 1;  // �ͷŸ�λ
        #100000000;  // ����100ms
        $finish;
    end

endmodule
