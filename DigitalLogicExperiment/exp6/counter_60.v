`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
// Create Date: 2026/04/15 22:47:09
// Design Date:
// Module Name: counter_60
//
//////////////////////////////////////////////////////////////////////////////////

// ����ģ�飺60�����������
module top_counter (
    input  wire       clk100M,   // 100MHz ϵͳʱ��
    input  wire       clrn,      // �첽���㣨�͵�ƽ��Ч��
    output wire [6:0] seg,       // ��ѡ��a~g ��Ӧ seg[6]~seg[0]������Ч
    output wire [1:0] sel        // λѡ��sel[0] Ϊ��λ��sel[1] Ϊʮλ������Ч
);

    wire clk1s;             // 1Hz ʱ��
    wire [3:0] high, low;   // ʮλ�͸�λ

    // ʵ������Ƶģ�飺100MHz -> 1Hz
    divider_1hz u_div (
        .clk_100M(clk100M),
        .clrn(clrn),
        .clk_1s(clk1s)
    );

    // ʵ����60���Ƽ���ģ��
    counter_60 u_cnt (
        .clk_1s(clk1s),
        .clrn(clrn),
        .high(high),
        .low(low)
    );

    // ʵ������̬ɨ����ʾģ��
    display_scan u_display (
        .clk_100M(clk100M),
        .clrn(clrn),
        .high(high),
        .low(low),
        .seg(seg),
        .sel(sel)
    );

endmodule

// ��Ƶģ�飺100MHz -> 1Hz
module divider_1hz (
    input  wire clk_100M,
    input  wire clrn,
    output reg  clk_1s
);
    localparam MAX_CNT = 100_000_000;
    reg [26:0] cnt;

    always @(posedge clk_100M or negedge clrn) begin
        if (!clrn) begin
            cnt <= 0;
            clk_1s <= 0;
        end else begin
            if (cnt == MAX_CNT - 1) begin
                cnt <= 0;
                clk_1s <= ~clk_1s;
            end else begin
                cnt <= cnt + 1;
            end
        end
    end
endmodule

// 60���Ƽ���ģ�飨0~59��ʮλ�͸�λ�ֱ������
module counter_60 (
    input  wire       clk_1s,
    input  wire       clrn,
    output reg  [3:0] high,   // ʮλ
    output reg  [3:0] low     // ��λ
);

    always @(posedge clk_1s or negedge clrn) begin
        if (!clrn) begin
            high <= 4'b0000;
            low  <= 4'b0000;
        end else begin
            if (low == 4'b1001 && high == 4'b0101) begin
                high <= 4'b0000;
                low  <= 4'b0000;
            end else if (low == 4'b1001) begin
                high <= high + 1;
                low  <= 4'b0000;
            end else begin
                low <= low + 1;
            end
        end
    end
endmodule

// ��̬ɨ����ʾģ�飨ʹ��1kHzɨ��Ƶ�ʣ�
module display_scan (
    input  wire       clk_100M,
    input  wire       clrn,
    input  wire [3:0] high,
    input  wire [3:0] low,
    output reg  [6:0] seg,
    output reg  [1:0] sel
);
    reg [16:0] scan_cnt;
    reg        scan_clk;
    localparam SCAN_MAX = 100_000;

    always @(posedge clk_100M or negedge clrn) begin
        if (!clrn) begin
            scan_cnt <= 0;
            scan_clk <= 0;
        end else begin
            if (scan_cnt == SCAN_MAX - 1) begin
                scan_cnt <= 0;
                scan_clk <= ~scan_clk;
            end else begin
                scan_cnt <= scan_cnt + 1;
            end
        end
    end

    // ��̬ɨ��״̬������λѭ����
    reg [1:0] state;
    always @(posedge scan_clk or negedge clrn) begin
        if (!clrn) begin
            state <= 2'b00;
        end else begin
            state <= state + 1;   // 00��01��10��11��00...
        end
    end

    function [6:0] seg_decode;
        input [3:0] bin;
        case (bin)
            4'd0: seg_decode = 7'b0111111;
            4'd1: seg_decode = 7'b0000110;
            4'd2: seg_decode = 7'b1011011;
            4'd3: seg_decode = 7'b1001111;
            4'd4: seg_decode = 7'b1100110;
            4'd5: seg_decode = 7'b1101101;
            4'd6: seg_decode = 7'b1111101;
            4'd7: seg_decode = 7'b0000111;
            4'd8: seg_decode = 7'b1111111;
            4'd9: seg_decode = 7'b1101111;
            default: seg_decode = 7'b0000000;
        endcase
    endfunction

    // ���ݵ�ǰ״̬ѡ����ʾ������ܼ���Ӧ����ֵ
    always @(*) begin
        case (state)
            2'b00: begin   // ��ʾ��λ
                sel = 2'b10;
                seg = seg_decode(low);
            end
            2'b01: begin   // ��ʾʮλ
                sel = 2'b01;
                seg = seg_decode(high);
            end
            default: begin
                sel = 2'b11;   // ȫ��
                seg = 7'b0000000;
            end
        endcase
    end

endmodule
