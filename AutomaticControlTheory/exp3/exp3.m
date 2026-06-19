%% Experiment 3: MATLAB实现控制系统串联校正的频域设计
% This script follows exp3/README.md and completes the two comprehensive
% practice tasks: lead compensation (Practice 1) and lag compensation
% (Practice 2). For each task, Bode diagrams and unit-step responses are
% plotted for both the uncorrected and corrected systems, and key
% frequency-domain / time-domain metrics are reported.

clear; clc; close all;

fprintf('Experiment 3: Series Compensation Design in Frequency Domain\n');
fprintf('============================================================\n\n');

%% ========================================================================
% Comprehensive Practice 1 — Series Lead Compensation
% ========================================================================
% Given: G0(s) = K / (s(s+1))
% Requirements:
%   (1) ess <= 0.1  for ramp input r(t) = t
%   (2) Crossover frequency wc >= 6 rad/s
%   (3) Phase margin gamma >= 60 deg
%
% Design result (from table):
%   K = 10
%   Gc(s) = (0.6159s + 1) / (0.04422s + 1)
% ========================================================================

fprintf('\n--- Comprehensive Practice 1: Lead Compensation ---\n\n');

% ----- Uncorrected system -----
K1 = 10;
G0_1 = tf(K1, [1, 1, 0]);

fprintf('Uncorrected system G0(s) = %d / (s(s+1))\n', K1);
fprintf('  Kv = %g  ->  ess(ramp) = 1/Kv = %g\n', K1, 1/K1);

% Stability margins of uncorrected system
[Gm0_1, Pm0_1, Wcg0_1, Wcp0_1] = margin(G0_1);
fprintf('  Gain margin  Gm = %.2f (%.2f dB)\n', Gm0_1, 20*log10(Gm0_1));
fprintf('  Phase margin Pm = %.2f deg\n', Pm0_1);
fprintf('  Crossover freq  wc = %.4f rad/s\n', Wcp0_1);

% ----- Corrected system -----
Gc_1 = tf([0.6159, 1], [0.04422, 1]);
Gk_1 = Gc_1 * G0_1;          % Open-loop after correction
Gcl0_1 = feedback(G0_1, 1);  % Closed-loop before correction
Gcl_1  = feedback(Gk_1, 1);  % Closed-loop after correction

fprintf('\nLead compensator Gc(s) = (0.6159s + 1) / (0.04422s + 1)\n');
fprintf('  Zero at s = %.4f,  Pole at s = %.4f\n', -1/0.6159, -1/0.04422);
fprintf('  alpha = %.4f\n', 0.04422/0.6159);

[Gm_1, Pm_1, Wcg_1, Wcp_1] = margin(Gk_1);
fprintf('\nCorrected open-loop margins:\n');
fprintf('  Gain margin  Gm = %.2f (%.2f dB)\n', Gm_1, 20*log10(Gm_1));
fprintf('  Phase margin Pm = %.2f deg\n', Pm_1);
fprintf('  Crossover freq  wc = %.4f rad/s\n', Wcp_1);

% ----- Bode diagram (before & after) -----
figure('Name', 'Practice 1 — Bode Diagram');
bode(G0_1, 'b-');
hold on;
bode(Gk_1, 'r--');
hold off;
grid on;
title('Practice 1: Bode Diagram — Before (blue) and After (red) Lead Compensation');
legend('G_0(s) (uncorrected)', 'G_k(s) (corrected)', 'Location', 'best');

% ----- Unit-step response (before & after) -----
figure('Name', 'Practice 1 — Unit-Step Response');
step(Gcl0_1, 'b-');
hold on;
step(Gcl_1, 'r--');
hold off;
grid on;
title('Practice 1: Unit-Step Response — Before (blue) and After (red) Lead Compensation');
xlabel('Time (s)'); ylabel('Output');
legend('Uncorrected', 'Corrected', 'Location', 'best');

% ----- Performance metrics via find() -----
[y0, t0] = step(Gcl0_1);
[y1, t1] = step(Gcl_1);

Css0 = dcgain(Gcl0_1);
Css1 = dcgain(Gcl_1);

% Overshoot
[Ymax0, k0] = max(y0);
[Ymax1, k1] = max(y1);
tp0 = t0(k0);  sigma0 = 100*(Ymax0 - Css0)/Css0;
tp1 = t1(k1);  sigma1 = 100*(Ymax1 - Css1)/Css1;

% Settling time (2% criterion) using find()
idx_settle0 = find(abs(y0 - Css0) > 0.02*Css0, 1, 'last');
idx_settle1 = find(abs(y1 - Css1) > 0.02*Css1, 1, 'last');
if ~isempty(idx_settle0) && idx_settle0 < length(t0)
    ts0 = t0(idx_settle0 + 1);
else
    ts0 = t0(end);
end
if ~isempty(idx_settle1) && idx_settle1 < length(t1)
    ts1 = t1(idx_settle1 + 1);
else
    ts1 = t1(end);
end

% Rise time (10% → 90%) using find()
n10_0 = find(y0 >= 0.1*Css0, 1, 'first');
n90_0 = find(y0 >= 0.9*Css0, 1, 'first');
n10_1 = find(y1 >= 0.1*Css1, 1, 'first');
n90_1 = find(y1 >= 0.9*Css1, 1, 'first');
tr0 = t0(n90_0) - t0(n10_0);
tr1 = t1(n90_1) - t1(n10_1);

fprintf('\nTime-domain metrics (closed-loop):\n');
fprintf('  %-20s %12s %12s\n', 'Metric', 'Uncorrected', 'Corrected');
fprintf('  %-20s %12.4f %12.4f\n', 'Css', Css0, Css1);
fprintf('  %-20s %12.4f %12.4f\n', 'Peak time tp (s)', tp0, tp1);
fprintf('  %-20s %12.2f %12.2f\n', 'Overshoot sigma%%', sigma0, sigma1);
fprintf('  %-20s %12.4f %12.4f\n', 'Rise time tr (s)', tr0, tr1);
fprintf('  %-20s %12.4f %12.4f\n', 'Settling time ts (s)', ts0, ts1);

%% ========================================================================
% Comprehensive Practice 2 — Series Lag Compensation
% ========================================================================
% Given: G0(s) = K / (s(s+1)(0.25s+1))
% Requirements:
%   (1) ess <= 0.2  for ramp input r(t) = t
%   (2) Phase margin gamma >= 45 deg
%
% Design result (from table):
%   K = 5
%   Gc(s) = (16.39s + 1) / (113.386s + 1)
% ========================================================================

fprintf('\n\n--- Comprehensive Practice 2: Lag Compensation ---\n\n');

% ----- Uncorrected system -----
K2 = 5;
G0_2 = tf(K2, conv(conv([1, 0], [1, 1]), [0.25, 1]));

fprintf('Uncorrected system G0(s) = %d / (s(s+1)(0.25s+1))\n', K2);
fprintf('  Kv = %g  ->  ess(ramp) = 1/Kv = %g\n', K2, 1/K2);

% Stability margins of uncorrected system
[Gm0_2, Pm0_2, Wcg0_2, Wcp0_2] = margin(G0_2);
fprintf('  Gain margin  Gm = %.2f (%.2f dB)\n', Gm0_2, 20*log10(Gm0_2));
fprintf('  Phase margin Pm = %.2f deg\n', Pm0_2);
fprintf('  Crossover freq  wc = %.4f rad/s\n', Wcp0_2);

% ----- Corrected system -----
Gc_2 = tf([16.39, 1], [113.386, 1]);
Gk_2 = Gc_2 * G0_2;          % Open-loop after correction
Gcl0_2 = feedback(G0_2, 1);  % Closed-loop before correction
Gcl_2  = feedback(Gk_2, 1);  % Closed-loop after correction

fprintf('\nLag compensator Gc(s) = (16.39s + 1) / (113.386s + 1)\n');
fprintf('  Zero at s = %.4f,  Pole at s = %.4f\n', -1/16.39, -1/113.386);
fprintf('  beta = %.4f\n', 113.386/16.39);

[Gm_2, Pm_2, Wcg_2, Wcp_2] = margin(Gk_2);
fprintf('\nCorrected open-loop margins:\n');
fprintf('  Gain margin  Gm = %.2f (%.2f dB)\n', Gm_2, 20*log10(Gm_2));
fprintf('  Phase margin Pm = %.2f deg\n', Pm_2);
fprintf('  Crossover freq  wc = %.4f rad/s\n', Wcp_2);

% ----- Bode diagram (before & after) -----
figure('Name', 'Practice 2 — Bode Diagram');
bode(G0_2, 'b-');
hold on;
bode(Gk_2, 'r--');
hold off;
grid on;
title('Practice 2: Bode Diagram — Before (blue) and After (red) Lag Compensation');
legend('G_0(s) (uncorrected)', 'G_k(s) (corrected)', 'Location', 'best');

% ----- Unit-step response (before & after) -----
figure('Name', 'Practice 2 — Unit-Step Response');
step(Gcl0_2, 'b-');
hold on;
step(Gcl_2, 'r--');
hold off;
grid on;
title('Practice 2: Unit-Step Response — Before (blue) and After (red) Lag Compensation');
xlabel('Time (s)'); ylabel('Output');
legend('Uncorrected', 'Corrected', 'Location', 'best');

% ----- Performance metrics via find() -----
[y0_2, t0_2] = step(Gcl0_2);
[y2,   t2]   = step(Gcl_2);

Css0_2 = dcgain(Gcl0_2);
Css2   = dcgain(Gcl_2);

% Overshoot
[Ymax0_2, k0_2] = max(y0_2);
[Ymax2,   k2]   = max(y2);
tp0_2 = t0_2(k0_2);  sigma0_2 = 100*(Ymax0_2 - Css0_2)/Css0_2;
tp2   = t2(k2);      sigma2   = 100*(Ymax2   - Css2)  /Css2;

% Settling time (2% criterion) using find()
idx_settle0_2 = find(abs(y0_2 - Css0_2) > 0.02*Css0_2, 1, 'last');
idx_settle2   = find(abs(y2   - Css2)   > 0.02*Css2,   1, 'last');
if ~isempty(idx_settle0_2) && idx_settle0_2 < length(t0_2)
    ts0_2 = t0_2(idx_settle0_2 + 1);
else
    ts0_2 = t0_2(end);
end
if ~isempty(idx_settle2) && idx_settle2 < length(t2)
    ts2 = t2(idx_settle2 + 1);
else
    ts2 = t2(end);
end

% Rise time (10% → 90%) using find()
n10_0_2 = find(y0_2 >= 0.1*Css0_2, 1, 'first');
n90_0_2 = find(y0_2 >= 0.9*Css0_2, 1, 'first');
n10_2   = find(y2   >= 0.1*Css2,   1, 'first');
n90_2   = find(y2   >= 0.9*Css2,   1, 'first');
tr0_2 = t0_2(n90_0_2) - t0_2(n10_0_2);
tr2   = t2(n90_2)     - t2(n10_2);

fprintf('\nTime-domain metrics (closed-loop):\n');
fprintf('  %-20s %12s %12s\n', 'Metric', 'Uncorrected', 'Corrected');
fprintf('  %-20s %12.4f %12.4f\n', 'Css', Css0_2, Css2);
fprintf('  %-20s %12.4f %12.4f\n', 'Peak time tp (s)', tp0_2, tp2);
fprintf('  %-20s %12.2f %12.2f\n', 'Overshoot sigma%%', sigma0_2, sigma2);
fprintf('  %-20s %12.4f %12.4f\n', 'Rise time tr (s)', tr0_2, tr2);
fprintf('  %-20s %12.4f %12.4f\n', 'Settling time ts (s)', ts0_2, ts2);

%% ========================================================================
% Summary
% ========================================================================
fprintf('\n========================================\n');
fprintf('Experiment 3 completed. Both comprehensive practices have been executed.\n');
fprintf('  Practice 1: Lead compensation  — Gc(s) = (0.6159s+1)/(0.04422s+1)\n');
fprintf('  Practice 2: Lag compensation   — Gc(s) = (16.39s+1)/(113.386s+1)\n');
fprintf('========================================\n');
