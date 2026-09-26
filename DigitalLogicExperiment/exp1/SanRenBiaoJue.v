`timescale 1ns / 1ps

module SanRenBiaoJue(
    input A,
    input B,
    input C,
    output Y
    );
    assign Y = (A&B)|(B&C)|(A&C);
endmodule
