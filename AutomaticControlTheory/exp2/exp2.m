%% Experiment 2: Time-Domain Analysis Using MATLAB
% This script follows exp2/README.md and completes all examples and
% self-practice / comprehensive-practice tasks for time-domain analysis
% of control systems.

clear; clc; close all;

fprintf('Experiment 2: Time-Domain Analysis Using MATLAB\n');
fprintf('================================================\n\n');

%% Example 3-1 (Section 3): Pole-Zero Map with pzmap()
fprintf('\n--- Example 3-1: Pole-Zero Map ---\n');

num_31 = [3, 2, 5, 4, 6];
den_31 = [1, 3, 4, 2, 7, 2];

figure('Name', 'Example 3-1');
pzmap(num_31, den_31);
grid on;
title('Pole-Zero Map (Example 3-1)');

fprintf('  Pole-Zero Map plotted for G(s) = (3s^4+2s^3+5s^2+4s+6)/(s^5+3s^4+4s^3+2s^2+7s+2)\n');

%% Example 3-2 (Section 4): Unit-Step Response with step()
fprintf('\n--- Example 3-2: Unit-Step Response ---\n');

% Method 1: Direct step(num, den)
num_32 = [0, 0, 25];
den_32 = [1, 4, 25];

figure('Name', 'Example 3-2 (Method 1)');
step(num_32, den_32);
grid on;
title('Unit-Step Response of G(s)=25/(s^2+4s+25) (Method 1)');

% Method 2: Using tf + step with time vector + plot + dcgain
G_32 = tf([0, 0, 25], [1, 4, 25]);
t_32 = 0:0.1:5;   % from 0 to 5, step 0.1
c_32 = step(G_32, t_32);   % response amplitude stored in variable c

figure('Name', 'Example 3-2 (Method 2)');
plot(t_32, c_32);
grid on;
title('Unit-Step Response of G(s)=25/(s^2+4s+25) (Method 2)');
xlabel('Time (s)'); ylabel('Output');
Css_32 = dcgain(G_32);   % steady-state value

fprintf('  Method 2 steady-state value Css = %.4f\n', Css_32);

%% Example 3-3 (Section 5): Programmatic Performance Metrics (stepanalysis.m)
fprintf('\n--- Example 3-3: Programmatic Performance Metrics ---\n');

% Given second-order transfer function: G(s) = 3 / ((s+1-3i)(s+1+3i))
% Using zpk to build the model
G_33 = zpk([], [-1+3i, -1-3i], 3);

fprintf('  System: G(s) = 3 / ((s+1-3i)(s+1+3i)):\n');

% Compute peak time and overshoot
C_33 = dcgain(G_33);
[y_33, t_33] = step(G_33);

figure('Name', 'Example 3-3');
plot(t_33, y_33);
grid on;
title('Unit-Step Response of G(s)=3/(s^2+2s+10) (Example 3-3)');
xlabel('Time (s)'); ylabel('Output');

[Y_33, k_33] = max(y_33);
timetopeak_33 = t_33(k_33);
percentovershoot_33 = 100 * (Y_33 - C_33) / C_33;

% Compute rise time (0 → 100% criterion for oscillatory system)
n_33 = 1;
while y_33(n_33) < C_33
    n_33 = n_33 + 1;
end
risetime_33 = t_33(n_33);

% Compute settling time (2% criterion)
i_33 = length(t_33);
while (y_33(i_33) > 0.98 * C_33) && (y_33(i_33) < 1.02 * C_33)
    i_33 = i_33 - 1;
end
settlingtime_33 = t_33(i_33);

fprintf('    Css = %.4f\n', C_33);
fprintf('    timetopeak = %.4f s\n', timetopeak_33);
fprintf('    percentovershoot = %.2f%%\n', percentovershoot_33);
fprintf('    risetime = %.4f s\n', risetime_33);
fprintf('    settlingtime = %.4f s\n', settlingtime_33);

%% Self-Practice 1 — Step Response of G(s) = 100/(s^2+5s) (Unit Feedback)
fprintf('\n--- Self-Practice 1: G(s) = 100/(s^2+5s) ---\n');

G_sp1 = tf(100, [1, 5, 0]);  % Forward-path transfer function
% Unit negative feedback: closed-loop transfer function
G_sp1_cl = feedback(G_sp1, 1);

fprintf('  Closed-loop transfer function:\n');
G_sp1_cl

% Step response with performance metrics
[y_sp1, t_sp1] = step(G_sp1_cl);
C_sp1 = dcgain(G_sp1_cl);

% Peak time and overshoot
[Ymax_sp1, k_sp1] = max(y_sp1);
timetopeak_sp1 = t_sp1(k_sp1);
percentovershoot_sp1 = 100 * (Ymax_sp1 - C_sp1) / C_sp1;

% Rise time (10% → 90%)
n_sp1 = 1;
while y_sp1(n_sp1) < 0.1 * C_sp1
    n_sp1 = n_sp1 + 1;
end
m_sp1 = 1;
while y_sp1(m_sp1) < 0.9 * C_sp1
    m_sp1 = m_sp1 + 1;
end
risetime_sp1 = t_sp1(m_sp1) - t_sp1(n_sp1);

% Settling time (2% criterion)
i_sp1 = length(t_sp1);
while (y_sp1(i_sp1) > 0.98 * C_sp1) && (y_sp1(i_sp1) < 1.02 * C_sp1)
    i_sp1 = i_sp1 - 1;
end
settlingtime_sp1 = t_sp1(i_sp1);

fprintf('  Performance metrics:\n');
fprintf('    Steady-state value Css = %.4f\n', C_sp1);
fprintf('    Peak time tp = %.4f s\n', timetopeak_sp1);
fprintf('    Percent overshoot sigma%% = %.2f%%\n', percentovershoot_sp1);
fprintf('    Rise time tr = %.4f s\n', risetime_sp1);
fprintf('    Settling time ts = %.4f s\n', settlingtime_sp1);

figure('Name', 'Self-Practice 1');
step(G_sp1_cl);
grid on;
title('Unit-Step Response of G(s)=100/(s^2+5s) (Closed-Loop)');
xlabel('Time (s)'); ylabel('Output');

%% Self-Practice 2 — Effect of ξ with fixed ω_n = 10
fprintf('\n--- Self-Practice 2: omega_n = 10, xi varies ---\n');

wn2 = 10;
xi_values = [0, 0.25, 0.5, 0.75, 1, 1.25];
colors = lines(length(xi_values));

figure('Name', 'Self-Practice 2');
hold on;
legends_sp2 = {};

for idx = 1:length(xi_values)
    xi = xi_values(idx);
    % Standard second-order system: G(s) = wn^2/(s^2 + 2*xi*wn*s + wn^2)
    num = wn2^2;
    den = [1, 2*xi*wn2, wn2^2];
    G = tf(num, den);

    % Closed-loop poles and natural frequency
    [wn_damp, zeta_damp, p_damp] = damp(G);

    fprintf('  xi = %.2f:\n', xi);
    fprintf('    Closed-loop poles: %s\n', mat2str(p_damp, 4));
    fprintf('    Damping ratio from damp(): %s\n', mat2str(zeta_damp, 4));
    fprintf('    Natural frequency from damp(): %s\n', mat2str(wn_damp, 4));

    step(G, 3);
    legends_sp2{end+1} = sprintf('\\xi = %.2f', xi);
end

hold off; grid on;
title('Step Response for \omega_n = 10 with Varying \xi');
xlabel('Time (s)'); ylabel('Output');
legend(legends_sp2, 'Location', 'best');

% Save the figure
% saveas(gcf, fullfile(fileparts(mfilename('fullpath')), 'figures', 'sp2_xi_varying.png'));

%% Self-Practice 3 — Effect of ω_n with fixed ξ = 0.25
fprintf('\n--- Self-Practice 3: xi = 0.25, omega_n varies ---\n');

xi3 = 0.25;
wn_values = [10, 30, 50];

figure('Name', 'Self-Practice 3');
hold on;
legends_sp3 = {};

for idx = 1:length(wn_values)
    wn = wn_values(idx);
    num = wn^2;
    den = [1, 2*xi3*wn, wn^2];
    G = tf(num, den);

    [wn_damp, zeta_damp, p_damp] = damp(G);
    fprintf('  omega_n = %d:\n', wn);
    fprintf('    Poles: %s\n', mat2str(p_damp, 4));
    fprintf('    Damping ratio: %.4f, Natural freq: %.4f\n', zeta_damp(1), wn_damp(1));

    step(G, 2);
    legends_sp3{end+1} = sprintf('\\omega_n = %d', wn);
end

hold off; grid on;
title('Step Response for \xi = 0.25 with Varying \omega_n');
xlabel('Time (s)'); ylabel('Output');
legend(legends_sp3, 'Location', 'best');

%% Comprehensive Practice — Impulse, Step, Ramp Responses Table
fprintf('\n--- Comprehensive Practice: Impulse / Step / Ramp ---\n');

% Define ξ categories and ω_n values
xi_cases = [
    struct('label', 'xi > 1',    'xi', 2.0);
    struct('label', '0 < xi < 1','xi', 0.25);
    struct('label', 'xi = 0',    'xi', 0.0);
    struct('label', '-1<xi<0',   'xi', -0.5);
    struct('label', 'xi < -1',   'xi', -2.0);
];
wn_cases = [0.2, 1];

Tfinal_step = 80;   % long enough for wn=0.2 cases
Tfinal_impulse = 80;
Tfinal_ramp = 80;

results_table = {};  % Collect results for tabular output

for i_xi = 1:length(xi_cases)
    xi_val = xi_cases(i_xi).xi;
    xi_lbl = xi_cases(i_xi).label;
    for j_wn = 1:length(wn_cases)
        wn_val = wn_cases(j_wn);

        % Build standard second-order transfer function
        num = wn_val^2;
        den = [1, 2*xi_val*wn_val, wn_val^2];
        G = tf(num, den);

        % --- Impulse Response ---
        [y_imp, t_imp] = impulse(G, Tfinal_impulse);

        % --- Step Response ---
        [y_step, t_step] = step(G, Tfinal_step);

        % --- Ramp Response ---
        t_ramp = (0:0.01:Tfinal_ramp)';
        u_ramp = t_ramp;
        y_ramp = lsim(G, u_ramp, t_ramp);

        % Determine stability
        poles_G = pole(G);
        is_stable = all(real(poles_G) < 0);
        is_marginally_stable = any(real(poles_G) == 0) && all(real(poles_G) <= 0);

        % --- Compute metrics for step response (if stable) ---
        if is_stable
            Cstep = dcgain(G);
            [Ymax, kmax] = max(y_step);

            % Detect whether there is genuine overshoot (i.e. response exceeds Css)
            % For overdamped / monotonically rising systems, max(y) = y(end) <~ Css
            if Ymax > Cstep * (1 + 1e-6)
                % Underdamped: genuine peak exists
                tp_val = t_step(kmax);
                pO_val = 100 * (Ymax - Cstep) / Cstep;
            else
                % Overdamped / critically damped: no overshoot
                tp_val = NaN;
                pO_val = 0;
            end

            % Rise time (10%-90%)
            n10 = find(y_step >= 0.1*Cstep, 1, 'first');
            n90 = find(y_step >= 0.9*Cstep, 1, 'first');
            if ~isempty(n10) && ~isempty(n90)
                tr_val = t_step(n90) - t_step(n10);
            else
                tr_val = NaN;
            end

            % Settling time (2%)
            idx_settle = find(abs(y_step - Cstep) > 0.02*Cstep, 1, 'last');
            if ~isempty(idx_settle) && idx_settle < length(t_step)
                ts_val = t_step(idx_settle + 1);
            else
                ts_val = t_step(end);
            end
        elseif is_marginally_stable
            % Marginally stable (ξ = 0): constant-amplitude oscillation
            tp_val = NaN; pO_val = NaN; tr_val = NaN; ts_val = Inf;
        else
            % Unstable
            tp_val = NaN; pO_val = NaN; tr_val = NaN; ts_val = NaN;
        end

        % Record metrics under each input signal type (same system, same metrics)
        results_table{end+1, 1} = 'Impulse';
        results_table{end, 2} = xi_lbl;
        results_table{end, 3} = wn_val;
        results_table{end, 4} = ts_val;
        results_table{end, 5} = tp_val;
        results_table{end, 6} = pO_val;
        results_table{end, 7} = tr_val;

        results_table{end+1, 1} = 'Step';
        results_table{end, 2} = xi_lbl;
        results_table{end, 3} = wn_val;
        results_table{end, 4} = ts_val;
        results_table{end, 5} = tp_val;
        results_table{end, 6} = pO_val;
        results_table{end, 7} = tr_val;

        results_table{end+1, 1} = 'Ramp';
        results_table{end, 2} = xi_lbl;
        results_table{end, 3} = wn_val;
        results_table{end, 4} = ts_val;
        results_table{end, 5} = tp_val;
        results_table{end, 6} = pO_val;
        results_table{end, 7} = tr_val;

        % --- Plot combined responses ---
        figName = sprintf('Comprehensive: %s, \\omega_n=%.1f', xi_lbl, wn_val);
        figure('Name', figName);

        subplot(3,1,1);
        plot(t_imp, y_imp, 'b', 'LineWidth', 1.2);
        grid on;
        title(sprintf('Impulse Response (%s, \\omega_n=%.1f)', xi_lbl, wn_val));
        xlabel('Time (s)'); ylabel('Amplitude');

        subplot(3,1,2);
        plot(t_step, y_step, 'r', 'LineWidth', 1.2);
        grid on;
        title(sprintf('Step Response (%s, \\omega_n=%.1f)', xi_lbl, wn_val));
        xlabel('Time (s)'); ylabel('Amplitude');

        subplot(3,1,3);
        plot(t_ramp, y_ramp, 'g', 'LineWidth', 1.2);
        hold on;
        plot(t_ramp, u_ramp, 'k--', 'LineWidth', 0.8);
        hold off;
        grid on;
        title(sprintf('Ramp Response (%s, \\omega_n=%.1f)', xi_lbl, wn_val));
        xlabel('Time (s)'); ylabel('Amplitude');
        legend('Output', 'Input (ramp)', 'Location', 'best');
    end
end

% Display results table
fprintf('\n  Comprehensive Practice Results Table:\n');
fprintf('  %-10s %-12s %-6s %-10s %-10s %-10s %-10s\n', ...
    'Input', 'xi', 'wn', 'ts', 'tp', 'sigma%%', 'tr');
fprintf('  %s\n', repmat('-', 1, 70));
for r = 1:size(results_table, 1)
    fprintf('  %-10s %-12s %-6.1f', results_table{r,1}, results_table{r,2}, results_table{r,3});
    for c = 4:7
        val = results_table{r,c};
        if isnan(val)
            fprintf(' %-10s', 'N/A');
        elseif isinf(val)
            fprintf(' %-10s', 'Inf');
        else
            fprintf(' %-10.4f', val);
        end
    end
    fprintf('\n');
end

%% Self-Practice 4 — Effect of Zeros and Pole-Zero Cancellation
fprintf('\n--- Self-Practice 4: Zero / Pole Effects ---\n');

% Original system: G0(s) = 10/(s^2+2s+10)
G0_sp4 = tf(10, [1, 2, 10]);

% (1) System with zero at s = -5: G1(s) = (2s+10)/(s^2+2s+10)
G1_sp4 = tf([2, 10], [1, 2, 10]);

% (2) n = m = 2: G2(s) = (s^2+0.5s+10)/(s^2+2s+10)
G2_sp4 = tf([1, 0.5, 10], [1, 2, 10]);

% (3) Numerator constant term = 0: G3(s) = (s^2+0.5s)/(s^2+2s+10)
G3_sp4 = tf([1, 0.5, 0], [1, 2, 10]);

% (4) Derivative response with coefficient 1/10: G4(s) = s/(s^2+2s+10)
G4_sp4 = tf([1, 0], [1, 2, 10]);

figure('Name', 'Self-Practice 4');
hold on;
step(G0_sp4, 5);
step(G1_sp4, 5);
step(G2_sp4, 5);
step(G3_sp4, 5);
step(G4_sp4, 5);
hold off;
grid on;
title('Step Response Comparison — Zero / Pole Effects');
xlabel('Time (s)'); ylabel('Output');
legend('G_0 (original)', 'G_1 (zero at -5)', 'G_2 (n=m=2)', ...
       'G_3 (zero const=0)', 'G_4 (derivative)', 'Location', 'best');

% Compute and display metrics for each
G_list_sp4 = {G0_sp4, G1_sp4, G2_sp4, G3_sp4, G4_sp4};
G_names_sp4 = {'G0 (original)', 'G1 (zero -5)', 'G2 (n=m=2)', ...
               'G3 (zero const=0)', 'G4 (derivative)'};

fprintf('\n  Self-Practice 4 Metrics:\n');
for idx = 1:length(G_list_sp4)
    Gc = G_list_sp4{idx};
    [y, t] = step(Gc, 5);
    C = dcgain(Gc);
    [Ymax, kmax] = max(y);

    % Handle systems with Css = 0 (e.g., pure derivative)
    if abs(C) < 1e-9
        tp = NaN;
        pO = NaN;
        ts = NaN;
        fprintf('  %s: Css=%.4f, tp=N/A (Css=0), sigma%%=N/A, ts=N/A\n', ...
            G_names_sp4{idx}, C);
        continue;
    end

    % Detect genuine overshoot
    if Ymax > C * (1 + 1e-6)
        tp = t(kmax);
        pO = 100 * (Ymax - C) / C;
    else
        tp = NaN;
        pO = 0;
    end

    % Settling time
    i_settle = find(abs(y - C) > 0.02*abs(C) + 1e-6, 1, 'last');
    if ~isempty(i_settle) && i_settle < length(t)
        ts = t(i_settle + 1);
    else
        ts = t(end);
    end

    fprintf('  %s: Css=%.4f, tp=%.4f, sigma%%=%.2f%%, ts=%.4f\n', ...
        G_names_sp4{idx}, C, tp, pO, ts);
end

%% Comprehensive Practice — Additional Zeros (Open-Loop vs Closed-Loop)
fprintf('\n--- Comprehensive Practice: Additional Zeros ---\n');

% Parameters
wn_z = 1;
xi_z = 0.5;
% W0(s) = wn^2/(s^2 + 2*xi*wn*s)  [integrator in open loop, as per Fig 3-4/3-5/3-6]
% The original open loop is W0(s) = wn^2 / (s(s + 2*xi*wn)) = 1/(s^2+s)
W0 = tf(wn_z^2, [1, 2*xi_z*wn_z, 0]);

% Original system closed-loop (Figure 3-4)
% Unity feedback: Phi0 = W0/(1+W0) = wn^2/(s^2+2*xi*wn*s+wn^2)
Phi_orig = feedback(W0, 1);

fprintf('  Original closed-loop (no additional zero):\n');
fprintf('    '); Phi_orig

T_values = [0.2, 1];
figure('Name', 'Additional Open-Loop Zero');
hold on;
step(Phi_orig, 20);
legends_olz = {'Original (no zero)'};

for iT = 1:length(T_values)
    T_val = T_values(iT);
    P_olz = tf([T_val, 1], 1);
    % Additional open-loop zero (Figure 3-5): P(s) cascaded in forward path
    % Phi = P*W0/(1+P*W0)
    G_olz = series(P_olz, W0);
    Phi_olz = feedback(G_olz, 1);

    fprintf('  Open-loop zero, T=%.1f:\n', T_val);
    fprintf('    Zero at s = %.2f\n', -1/T_val);
    fprintf('    Closed-loop TF: '); Phi_olz

    step(Phi_olz, 20);
    legends_olz{end+1} = sprintf('T = %.1f (open-loop zero)', T_val);
end
hold off; grid on;
title('Step Response — Additional Open-Loop Zero');
xlabel('Time (s)'); ylabel('Output');
legend(legends_olz, 'Location', 'best');

figure('Name', 'Additional Closed-Loop Zero');
hold on;
step(Phi_orig, 20);
legends_clz = {'Original (no zero)'};

for iT = 1:length(T_values)
    T_val = T_values(iT);
    P_clz = tf([T_val, 1], 1);
    % Additional closed-loop zero (Figure 3-6):
    % P(s) outside the feedback loop (after takeoff point)
    % Phi = P * [W0/(1+W0)]
    Phi_inner = feedback(W0, 1);  % Inner loop without zero
    Phi_clz = series(P_clz, Phi_inner);

    fprintf('  Closed-loop zero, T=%.1f:\n', T_val);
    fprintf('    Zero at s = %.2f\n', -1/T_val);
    fprintf('    Closed-loop TF: '); Phi_clz

    step(Phi_clz, 20);
    legends_clz{end+1} = sprintf('T = %.1f (closed-loop zero)', T_val);
end
hold off; grid on;
title('Step Response — Additional Closed-Loop Zero');
xlabel('Time (s)'); ylabel('Output');
legend(legends_clz, 'Location', 'best');

%% Comprehensive Practice — Additional Poles (Open-Loop vs Closed-Loop)
fprintf('\n--- Comprehensive Practice: Additional Poles ---\n');

% P(s) = 1/(Ts+1) for pole addition (inverse of zero case)

figure('Name', 'Additional Open-Loop Pole');
hold on;
step(Phi_orig, 40);
legends_olp = {'Original (no pole)'};

for iT = 1:length(T_values)
    T_val = T_values(iT);
    P_olp = tf(1, [T_val, 1]);
    % Additional open-loop pole: Phi = P*W0/(1+P*W0)
    G_olp = series(P_olp, W0);
    Phi_olp = feedback(G_olp, 1);

    fprintf('  Open-loop pole, T=%.1f:\n', T_val);
    fprintf('    Pole at s = %.2f\n', -1/T_val);
    fprintf('    Closed-loop TF: '); Phi_olp

    step(Phi_olp, 40);
    legends_olp{end+1} = sprintf('T = %.1f (open-loop pole)', T_val);
end
hold off; grid on;
title('Step Response — Additional Open-Loop Pole');
xlabel('Time (s)'); ylabel('Output');
legend(legends_olp, 'Location', 'best');

figure('Name', 'Additional Closed-Loop Pole');
hold on;
step(Phi_orig, 40);
legends_clp = {'Original (no pole)'};

for iT = 1:length(T_values)
    T_val = T_values(iT);
    P_clp = tf(1, [T_val, 1]);
    % Additional closed-loop pole: P outside feedback loop (after takeoff point)
    % Phi = P * [W0/(1+W0)]
    Phi_inner2 = feedback(W0, 1);
    Phi_clp = series(P_clp, Phi_inner2);

    fprintf('  Closed-loop pole, T=%.1f:\n', T_val);
    fprintf('    Pole at s = %.2f\n', -1/T_val);
    fprintf('    Closed-loop TF: '); Phi_clp

    step(Phi_clp, 40);
    legends_clp{end+1} = sprintf('T = %.1f (closed-loop pole)', T_val);
end
hold off; grid on;
title('Step Response — Additional Closed-Loop Pole');
xlabel('Time (s)'); ylabel('Output');
legend(legends_clp, 'Location', 'best');

%% Self-Practice 5 — Third-Order System Unit-Step Response Analysis
fprintf('\n--- Self-Practice 5: Third-Order System ---\n');

% (1) Original: Phi(s) = 5(s+2)(s+3) / ((s+4)(s^2+2s+2))
num5a = 5 * conv([1, 2], [1, 3]);
den5a = conv([1, 4], [1, 2, 2]);
Phi5a = tf(num5a, den5a);

fprintf('  (1) Original system:\n');
fprintf('      Poles: %s\n', mat2str(pole(Phi5a), 4));
fprintf('      Zeros: %s\n', mat2str(zero(Phi5a), 4));

[y5a, t5a] = step(Phi5a, 15);
C5a = dcgain(Phi5a);
[Ymax5a, k5a] = max(y5a);
if Ymax5a > C5a * (1 + 1e-6)
    tp5a = t5a(k5a);
    pO5a = 100 * (Ymax5a - C5a) / C5a;
else
    tp5a = NaN;
    pO5a = 0;
end
i5a = find(abs(y5a - C5a) > 0.02*abs(C5a) + 1e-6, 1, 'last');
if ~isempty(i5a) && i5a < length(t5a)
    ts5a = t5a(i5a + 1);
else
    ts5a = t5a(end);
end

fprintf('      Css=%.4f, tp=%.4f, sigma%%=%.2f%%, ts=%.4f\n', C5a, tp5a, pO5a, ts5a);

% (2) Pole moved from -4 to -0.5: Phi(s) = 0.625(s+2)(s+3) / ((s+0.5)(s^2+2s+2))
num5b = 0.625 * conv([1, 2], [1, 3]);
den5b = conv([1, 0.5], [1, 2, 2]);
Phi5b = tf(num5b, den5b);

fprintf('  (2) Pole moved to -0.5:\n');
fprintf('      Poles: %s\n', mat2str(pole(Phi5b), 4));

[y5b, t5b] = step(Phi5b, 40);
C5b = dcgain(Phi5b);
[Ymax5b, k5b] = max(y5b);
if Ymax5b > C5b * (1 + 1e-6)
    tp5b = t5b(k5b);
    pO5b = 100 * (Ymax5b - C5b) / C5b;
else
    tp5b = NaN;
    pO5b = 0;
end
i5b = find(abs(y5b - C5b) > 0.02*abs(C5b) + 1e-6, 1, 'last');
if ~isempty(i5b) && i5b < length(t5b)
    ts5b = t5b(i5b + 1);
else
    ts5b = t5b(end);
end

fprintf('      Css=%.4f, tp=%.4f, sigma%%=%.2f%%, ts=%.4f\n', C5b, tp5b, pO5b, ts5b);

% (3) Zero moved from -2 to -1: Phi(s) = 10(s+1)(s+3) / ((s+4)(s^2+2s+2))
num5c = 10 * conv([1, 1], [1, 3]);
den5c = conv([1, 4], [1, 2, 2]);
Phi5c = tf(num5c, den5c);

fprintf('  (3) Zero moved to -1:\n');
fprintf('      Zeros: %s\n', mat2str(zero(Phi5c), 4));

[y5c, t5c] = step(Phi5c, 15);
C5c = dcgain(Phi5c);
[Ymax5c, k5c] = max(y5c);
if Ymax5c > C5c * (1 + 1e-6)
    tp5c = t5c(k5c);
    pO5c = 100 * (Ymax5c - C5c) / C5c;
else
    tp5c = NaN;
    pO5c = 0;
end
i5c = find(abs(y5c - C5c) > 0.02*abs(C5c) + 1e-6, 1, 'last');
if ~isempty(i5c) && i5c < length(t5c)
    ts5c = t5c(i5c + 1);
else
    ts5c = t5c(end);
end

fprintf('      Css=%.4f, tp=%.4f, sigma%%=%.2f%%, ts=%.4f\n', C5c, tp5c, pO5c, ts5c);

% Plot all three together
figure('Name', 'Self-Practice 5');
hold on;
step(Phi5a, 15);
step(Phi5b, 15);
step(Phi5c, 15);
hold off;
grid on;
title('Third-Order System Step Response Comparison');
xlabel('Time (s)'); ylabel('Output');
legend('(1) Original', '(2) Pole -4 -> -0.5', '(3) Zero -2 -> -1', 'Location', 'best');

%% Self-Practice 6 — High-Order System Unit-Step Response Analysis
fprintf('\n--- Self-Practice 6: High-Order System ---\n');

% Phi1(s) = 1.05(0.4762s+1) / ((0.125s+1)(0.5s+1)(s^2+s+1))
num6a = 1.05 * [0.4762, 1];
den6a_12 = conv([0.125, 1], [0.5, 1]);
den6a = conv(den6a_12, [1, 1, 1]);
Phi6a = tf(num6a, den6a);

fprintf('  Phi1 (original high-order):\n');
fprintf('    Poles: %s\n', mat2str(pole(Phi6a), 4));
fprintf('    Zeros: %s\n', mat2str(zero(Phi6a), 4));
[y6a, t6a] = step(Phi6a, 15);
C6a = dcgain(Phi6a);
[Ymax6a, k6a] = max(y6a);
tp6a = t6a(k6a);
pO6a = 100 * (Ymax6a - C6a) / C6a;
i6a = find(abs(y6a - C6a) > 0.02*abs(C6a) + 1e-6, 1, 'last');
if ~isempty(i6a) && i6a < length(t6a)
    ts6a = t6a(i6a + 1);
else
    ts6a = t6a(end);
end
fprintf('    Css=%.4f, tp=%.4f, sigma%%=%.2f%%, ts=%.4f\n', C6a, tp6a, pO6a, ts6a);

% Phi2(s) = 1.05/(s^2+s+1)  — second-order dominant-pole approximation
Phi6b = tf(1.05, [1, 1, 1]);

fprintf('  Phi2 (dominant-pole approx):\n');
fprintf('    Poles: %s\n', mat2str(pole(Phi6b), 4));
[y6b, t6b] = step(Phi6b, 15);
C6b = dcgain(Phi6b);
[Ymax6b, k6b] = max(y6b);
tp6b = t6b(k6b);
pO6b = 100 * (Ymax6b - C6b) / C6b;
i6b = find(abs(y6b - C6b) > 0.02*abs(C6b) + 1e-6, 1, 'last');
if ~isempty(i6b) && i6b < length(t6b)
    ts6b = t6b(i6b + 1);
else
    ts6b = t6b(end);
end
fprintf('    Css=%.4f, tp=%.4f, sigma%%=%.2f%%, ts=%.4f\n', C6b, tp6b, pO6b, ts6b);

% Phi3(s) = 1.05 / ((0.125s+1)(0.5s+1)(s^2+s+1))  — no zero
num6c = 1.05;
Phi6c = tf(num6c, den6a);  % Same denominator as Phi1, without the zero factor

fprintf('  Phi3 (no zero):\n');
[y6c, t6c] = step(Phi6c, 20);
C6c = dcgain(Phi6c);
[Ymax6c, k6c] = max(y6c);
tp6c = t6c(k6c);
pO6c = 100 * (Ymax6c - C6c) / C6c;
i6c = find(abs(y6c - C6c) > 0.02*abs(C6c) + 1e-6, 1, 'last');
if ~isempty(i6c) && i6c < length(t6c)
    ts6c = t6c(i6c + 1);
else
    ts6c = t6c(end);
end
fprintf('    Css=%.4f, tp=%.4f, sigma%%=%.2f%%, ts=%.4f\n', C6c, tp6c, pO6c, ts6c);

% Phi4(s) = 1.05(s+1) / ((0.125s+1)(0.5s+1)(s^2+s+1))  — different zero
num6d = 1.05 * [1, 1];
Phi6d = tf(num6d, den6a);

fprintf('  Phi4 (zero at -1):\n');
fprintf('    Zeros: %s\n', mat2str(zero(Phi6d), 4));
[y6d, t6d] = step(Phi6d, 15);
C6d = dcgain(Phi6d);
[Ymax6d, k6d] = max(y6d);
tp6d = t6d(k6d);
pO6d = 100 * (Ymax6d - C6d) / C6d;
i6d = find(abs(y6d - C6d) > 0.02*abs(C6d) + 1e-6, 1, 'last');
if ~isempty(i6d) && i6d < length(t6d)
    ts6d = t6d(i6d + 1);
else
    ts6d = t6d(end);
end
fprintf('    Css=%.4f, tp=%.4f, sigma%%=%.2f%%, ts=%.4f\n', C6d, tp6d, pO6d, ts6d);

% Phi5(s) = 1.05(0.4762s+1) / ((0.5s+1)(s^2+s+1))  — remove non-dominant pole (s=-8)
num6e = 1.05 * [0.4762, 1];
den6e = conv([0.5, 1], [1, 1, 1]);
Phi6e = tf(num6e, den6e);

fprintf('  Phi5 (remove non-dominant pole s=-8):\n');
fprintf('    Poles: %s\n', mat2str(pole(Phi6e), 4));
[y6e, t6e] = step(Phi6e, 15);
C6e = dcgain(Phi6e);
[Ymax6e, k6e] = max(y6e);
tp6e = t6e(k6e);
pO6e = 100 * (Ymax6e - C6e) / C6e;
i6e = find(abs(y6e - C6e) > 0.02*abs(C6e) + 1e-6, 1, 'last');
if ~isempty(i6e) && i6e < length(t6e)
    ts6e = t6e(i6e + 1);
else
    ts6e = t6e(end);
end
fprintf('    Css=%.4f, tp=%.4f, sigma%%=%.2f%%, ts=%.4f\n', C6e, tp6e, pO6e, ts6e);

% --- Combined plots ---

% (i) Phi1 vs Phi2: Dominant pole comparison
figure('Name', 'Self-Practice 6-1: Dominant Pole');
hold on;
step(Phi6a, 15);
step(Phi6b, 15);
hold off;
grid on;
title('\Phi_1 vs \Phi_2 — Dominant Pole Comparison');
xlabel('Time (s)'); ylabel('Output');
legend('\Phi_1 (high-order)', '\Phi_2 (dominant-pole)', 'Location', 'best');

% (ii) Phi3 vs Phi4 vs Phi1: Closed-loop zero effect
figure('Name', 'Self-Practice 6-2: Zero Effect');
hold on;
step(Phi6a, 15);
step(Phi6c, 15);
step(Phi6d, 15);
hold off;
grid on;
title('\Phi_1 vs \Phi_3 vs \Phi_4 — Closed-Loop Zero Effect');
xlabel('Time (s)'); ylabel('Output');
legend('\Phi_1 (zero -2.1)', '\Phi_3 (no zero)', '\Phi_4 (zero -1)', 'Location', 'best');

% (iii) Phi1 vs Phi5 vs Phi2: Non-dominant pole & dipole
figure('Name', 'Self-Practice 6-3: Non-Dominant Pole & Dipole');
hold on;
step(Phi6a, 15);
step(Phi6e, 15);
step(Phi6b, 15);
hold off;
grid on;
title('\Phi_1 vs \Phi_5 vs \Phi_2 — Non-Dominant Pole & Dipole');
xlabel('Time (s)'); ylabel('Output');
legend('\Phi_1 (full)', '\Phi_5 (no non-dom pole)', '\Phi_2 (2nd-order)', 'Location', 'best');

%% Summary
fprintf('\n========================================\n');
fprintf('Experiment 2 completed. All examples, self-practices and\n');
fprintf('comprehensive practices have been executed.\n');
fprintf('========================================\n');
