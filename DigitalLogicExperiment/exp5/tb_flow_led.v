`timescale 1ns / 1ps

module tb_flow_led;
    reg clk_100M;
    reg rst_n;
    reg dir;
    reg freq_sel;
    wire [7:0] led;

    flow_led uut (
        .clk_100M(clk_100M),
        .rst_n(rst_n),
        .dir(dir),
        .freq_sel(freq_sel),
        .led(led)
    );

    always #5 clk_100M = ~clk_100M; // 100MHz

    initial begin
        clk_100M = 0;
        rst_n = 0;
        dir = 0;
        freq_sel = 0;

        // ��λ�ͷ�
        #100;
        rst_n = 1;

        // ��������� 1Hzģʽ
        #5000;

        // ��������
        dir = 1;
        #5000;

        // �л�Ƶ��Ϊ2Hz
        freq_sel = 1;
        #5000;
        $stop;
    end
endmodule
