`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//
// Create Date: 2026/04/15 23:15:20
// Design Date:
// Module Name: breath_led
//
//////////////////////////////////////////////////////////////////////////////////

// ������ģ��
module breath_led (
    input  wire clk_100M,   // 100MHz ϵͳʱ��
    input  wire rst_n,      // �첽��λ���͵�ƽ��Ч��
    output reg  led         // LED������ߵ�ƽ������
);
    localparam CLK_FREQ = 100_000_000;      // ϵͳʱ��Ƶ�� 100MHz
    localparam PWM_PERIOD_US = 1_000;       // ����PWM����ʱ��
    localparam HALF_PERIOD_US = 2_000_000;  // ���ν����򽥰��Ĺ���ʱ�������� 20_000��ʵ�� 2_000_000��

    localparam TOTAL_STEPS = HALF_PERIOD_US / PWM_PERIOD_US;        // �ܲ����������ι��ɰ�����PWM��������
    localparam PWM_CNT = PWM_PERIOD_US * (CLK_FREQ / 1_000_000);    // ÿ��PWM�����ڵ�ʱ��������
    localparam DUTY_STEP = PWM_CNT / TOTAL_STEPS;                   // ÿ�β���ռ�ձȵı仯����ʱ����������

    reg [31:0] pwm_cnt;  // PWM���ڼ�������0 ~ PWM_CNT-1��
    reg [31:0] duty;     // ��ǰռ�ձ���ֵ��0 ~ PWM_CNT��
    reg        dir;      // ����0=������1=����
    reg [15:0] step_cnt; // ��ǰ���ɽ׶��ڵĲ���������0 ~ TOTAL_STEPS-1��

    // PWM���ڼ�������ռ�ձȸ���
    always @(posedge clk_100M or negedge rst_n) begin
        if (!rst_n) begin
            pwm_cnt  <= 0;
            duty     <= 0;
            dir      <= 0;
            step_cnt <= 0;
        end else begin
            // PWM���ڼ���
            if (pwm_cnt == PWM_CNT - 1) begin
                // һ��PWM���ڽ���������duty
                pwm_cnt <= 0;
                if (dir == 0) begin
                    // �����׶�
                    if (step_cnt == TOTAL_STEPS - 1) begin
                        // �ѵ��･��ĩβ���л�����
                        dir <= 1;
                        step_cnt <= 0;
                        // duty�������ֵ������������
                    end else begin
                        // ����duty��ʵ�ֽ���
                        duty <= duty + DUTY_STEP;
                        step_cnt <= step_cnt + 1;
                    end
                end else begin
                    // �����׶�
                    if (step_cnt == TOTAL_STEPS - 1) begin
                        // �ѵ��･��ĩβ���л�����
                        dir <= 0;
                        step_cnt <= 0;
                        // duty������Сֵ�������ټ���
                    end else begin
                        // ����duty��ʵ�ֽ���
                        duty <= duty - DUTY_STEP;
                        step_cnt <= step_cnt + 1;
                    end
                end
            end else begin
                pwm_cnt <= pwm_cnt + 1;
            end
        end
    end

    // ����LED���������PWM��duty�ıȽϣ�
    always @(posedge clk_100M or negedge rst_n) begin
        if (!rst_n) begin
            led <= 1'b0;
        end else begin
            led <= (pwm_cnt < duty) ? 1'b1 : 1'b0;
        end
    end

endmodule
