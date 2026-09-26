`timescale 1ns / 1ps

module jkff (
    input clk,   // 时钟（下降沿有效）
    input clrn,  // 异步复位（低电平有效）
    input prn,   // 异步置位（低电平有效）
    input j, k,  // 输入
    output reg q // 输出
);
    always @(negedge clk, negedge prn, negedge clrn) begin
        if (prn == 0) // 异步置位
            q <= 1'b1;
        else if (clrn == 0) // 异步复位
            q <= 1'b0;
        else
            case ({j, k})
                2'b00: q <= q; // 保持
                2'b01: q <= 1'b0; // 复位
                2'b10: q <= 1'b1; // 置位
                2'b11: q <= ~q; // 翻转
            endcase
    end
endmodule
