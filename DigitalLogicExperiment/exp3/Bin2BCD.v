`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
// Create Date: 2026/04/01 23:01:02
// Design Name:
// Module Name: Bin2BCD
//
//////////////////////////////////////////////////////////////////////////////////


module Bin2BCD(
    input clk,
    input [3:0] bin,
    output reg [6:0] seg,
    output reg bit1,
    output reg bit2
);
    localparam [6:0] S0 = 7'b0111111,
                     S1 = 7'b0000110,
                     S2 = 7'b1011011,
                     S3 = 7'b1001111,
                     S4 = 7'b1100110,
                     S5 = 7'b1101101,
                     S6 = 7'b1111101,
                     S7 = 7'b0000111,
                     S8 = 7'b1111111,
                     S9 = 7'b1101111;

    reg bcd_ten;
    reg [3:0] bcd_one;
    reg scan = 0;

    always @ (posedge clk) begin
        if (bin >= 4'd10) begin
            bcd_ten = 1;
            bcd_one = bin - 4'd10;
        end else begin
            bcd_ten = 0;
            bcd_one = bin;
        end

        scan = scan + 1;
        if (scan == 0) begin
            bit1 = 1;
            bit2 = 0;
            case (bcd_ten)
                1'b0: seg = S0;
                1'b1: seg = S1;
                default: seg = S0;
            endcase
        end else begin
            bit1 = 0;
            bit2 = 1;
            case (bcd_one)
                4'd0: seg = S0;
                4'd1: seg = S1;
                4'd2: seg = S2;
                4'd3: seg = S3;
                4'd4: seg = S4;
                4'd5: seg = S5;
                4'd6: seg = S6;
                4'd7: seg = S7;
                4'd8: seg = S8;
                4'd9: seg = S9;
                default: seg = S0;
            endcase
        end
    end

endmodule
