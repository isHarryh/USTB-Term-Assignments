`timescale 1ns / 1ps

module flow_led (
    input       clk_100M,
    input       rst_n,    // �첽��λ���͵�ƽ��Ч��
    input       dir,      // ����0-�������ң�1-��������
    input       freq_sel, // Ƶ�ʣ�0-1Hz��1-2Hz
    output reg [7:0] led
);
    localparam CNT_1HZ = 10 - 1;
    localparam CNT_2HZ = 5 - 1;
    reg [27:0] cnt;

    always @(posedge clk_100M or negedge rst_n) begin
        if (!rst_n) begin
            cnt <= 0;
            led <= 8'b00000000;
        end else begin
            if (cnt == (freq_sel ? CNT_2HZ : CNT_1HZ)) begin
                cnt <= 0;
                if (dir == 0)
                    led <= {~led[0], led[7:1]}; // ��������
                else
                    led <= {led[6:0], ~led[7]}; // ��������
            end else begin
                cnt <= cnt + 1;
            end
        end
    end
endmodule
