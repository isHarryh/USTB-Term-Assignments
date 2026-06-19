%% Experiment 1: Uses MATLAB to build transfer-function models
% This script follows exp1/README.md and completes the examples and
% self-practice tasks for transfer-function, zero-pole-gain, conversion,
% feedback connection, and a typical second-order response.

clear; clc; close all;

fprintf('Experiment 1: Uses MATLAB to build transfer-function models\n');
fprintf('==========================================================\n\n');

%% Example 1: Builds a simple transfer-function model
fprintf('Example 1\n');
num_ex1 = [1, 2];
den_ex1 = [1, 2, 3, 4, 5];
G_ex1 = tf(num_ex1, den_ex1)

%% Example 2: Builds a transfer-function model with conv
fprintf('Example 2\n');
num_ex2 = 6 * [1, 5];
den_ex2 = conv(conv([1, 3, 1], [1, 3, 1]), [1, 6]);
G_ex2 = tf(num_ex2, den_ex2)

%% Self-practice 1: Builds G(s) = 5 / (s(s+1)(s^2+4s+4))
fprintf('Self-practice 1\n');
num_p1 = 5;
den_p1 = conv(conv([1, 0], [1, 1]), [1, 4, 4]);
G_p1 = tf(num_p1, den_p1)

%% Example 3: Builds a zero-pole-gain model
fprintf('Example 3\n');
K_ex3 = 6;
z_ex3 = [-1.9294; -0.0353 + 0.9287j; -0.0353 - 0.9287j];
p_ex3 = [-0.9567 + 1.2272j; -0.9567 - 1.2272j; ...
          0.0433 + 0.6412j;  0.0433 - 0.6412j];
G_ex3 = zpk(z_ex3, p_ex3, K_ex3)

%% Self-practice 2: Builds the zero-pole-gain model
% G(s) = 8(s+1-j)(s+1+j) / (s^2(s+5)(s+6)(s^2+1))
fprintf('Self-practice 2\n');
K_p2 = 8;
z_p2 = [-1 + 1j; -1 - 1j];
p_p2 = [0; 0; -5; -6; 1j; -1j];
G_p2 = zpk(z_p2, p_p2, K_p2)
G_p2_tf = tf(G_p2)

%% Example 4: Converts a transfer-function model to a zero-pole-gain model
fprintf('Example 4\n');
num_ex4 = [6.8, 61.2, 95.2];
den_ex4 = [1, 7.5, 22, 19.5, 0];
G_ex4 = tf(num_ex4, den_ex4);
G_ex4_zpk = zpk(G_ex4)

%% Example 5: Converts a zero-pole-gain model to a transfer-function model
fprintf('Example 5\n');
z_ex5 = [-2; -7];
p_ex5 = [0; -3 - 2j; -3 + 2j; -1.5];
K_ex5 = 6.8;
G_ex5 = zpk(z_ex5, p_ex5, K_ex5);
G_ex5_tf = tf(G_ex5)

%% Self-practice 3: Converts G(s) = (s^2+5s+6)/(s^3+2s^2+s) to ZPK
fprintf('Self-practice 3\n');
num_p3 = [1, 5, 6];
den_p3 = [1, 2, 1, 0];
G_p3 = tf(num_p3, den_p3);
G_p3_zpk = zpk(G_p3)
[z_p3, p_p3, K_p3] = tf2zp(num_p3, den_p3);
fprintf('Zeros of self-practice 3:\n'); disp(z_p3);
fprintf('Poles of self-practice 3:\n'); disp(p_p3);
fprintf('Gain of self-practice 3:\n'); disp(K_p3);

%% Self-practice 4: Builds G(s) = 8(s+1)(s+2)/(s(s+5)(s+6)(s+3))
fprintf('Self-practice 4\n');
num_p4 = 8 * conv([1, 1], [1, 2]);
den_p4 = conv(conv(conv([1, 0], [1, 5]), [1, 6]), [1, 3]);
G_p4 = tf(num_p4, den_p4)
G_p4_zpk = zpk(G_p4)

%% Example 6: Simplifies a feedback system
fprintf('Example 6\n');
G1_ex6 = tf(1, [1, 2, 1]);
G2_ex6 = tf(1, [1, 1]);
G_ex6_negative = feedback(G1_ex6, G2_ex6)
G_ex6_positive = feedback(G1_ex6, G2_ex6, 1)

%% Example 7: Simplifies a complex feedback system
fprintf('Example 7\n');
G1_ex7 = tf([1, 7, 24, 24], [1, 10, 35, 50, 24]);
G2_ex7 = tf([10, 5], [1, 0]);
H_ex7 = tf(1, [0.01, 1]);
G_ex7 = feedback(G1_ex7 * G2_ex7, H_ex7)

%% Self-practice 5: Finds unit negative-feedback closed-loop transfer function
% Forward path: G(s) = (2s+1)/(s^2+2s+3)
fprintf('Self-practice 5\n');
G_p5_open = tf([2, 1], [1, 2, 3]);
G_p5_closed = feedback(G_p5_open, 1)

%% Typical second-order system response corresponding to the Simulink example
% Open-loop path contains an integrator and 900/(s+9), with unit negative
% feedback. The equivalent closed-loop transfer function is 900/(s^2+9s+900).
fprintf('Typical second-order system response\n');
G_second_order_open = tf(900, conv([1, 0], [1, 9]));
G_second_order_closed = feedback(G_second_order_open, 1)

figure('Name', 'Experiment 1 - Typical second-order unit-step response');
step(G_second_order_closed, 2);
grid on;
title('Typical Second-order System Unit-step Response');
xlabel('Time (s)');
ylabel('Output');

% figDir = fullfile(fileparts(mfilename('fullpath')), 'figures');
% if ~exist(figDir, 'dir')
%     mkdir(figDir);
% end
% saveas(gcf, fullfile(figDir, 'second_order_step_response.png'));

% fprintf('The response figure is saved to exp1/figures/second_order_step_response.png\n');
