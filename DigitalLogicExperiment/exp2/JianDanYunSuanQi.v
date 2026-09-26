`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
// Create Date: 2026/03/26 00:18:43
// Design Name:
// Module Name: JianDanYunSuanQi
//
//////////////////////////////////////////////////////////////////////////////////


module JianDanYunSuanQi(
       input [1:0]a,
       input [1:0]b,
       input [1:0]sel,
       output reg [1:0]out,
       output reg co
    );
    always @(*) begin
        case (sel)
            2'b00: begin
                {co, out} = a + b;
            end
            2'b01: begin
                co = 1'b0;
                if (a > b)
                    out = 2'b11;
                else
                    out = 2'b00;
            end
            2'b10: begin
                co = 1'b0;
                out = a & b;
            end
            2'b11: begin
                co = 1'b0;
                out = a | b;
            end
            default: begin
                out = 2'b00;
                co = 1'b0;
            end
        endcase
    end
endmodule
