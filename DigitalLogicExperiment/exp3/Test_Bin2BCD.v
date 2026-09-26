`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
// Create Date: 2026/04/01 23:25:25
// Design Name:
// Module Name: Test_Bin2BCD
//
//////////////////////////////////////////////////////////////////////////////////


module Test_Bin2BCD;
    reg clk;
    reg [3:0] bin;
    wire [6:0] seg;
    wire bit1;
    wire bit2;

    Bin2BCD uut (
        .clk(clk),
        .bin(bin),
        .seg(seg),
        .bit1(bit1),
        .bit2(bit2)
    );

    always #5 clk = ~clk; // 100MHz

    initial begin
        clk = 0;
        bin = 4'b0000;

        repeat (16) begin
            #50;
            bin = bin + 1;
        end

        $stop;
    end
endmodule
