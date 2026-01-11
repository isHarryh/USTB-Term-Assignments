function exp2()
    % Exp2: 连续时间信号的傅里叶分析
    if ~exist('output', 'dir')
        mkdir('output');
    end

    q1();
    q2();
    q3();
    q4();
    q5();
end

function q1()
    E = 1.2;
    T = 0.1; % ms? code says T=0.1
    tau = 1/4 * T;

    num_samples = 256;
    t = linspace(0, T, num_samples);

    f_t = zeros(size(t));
    f_t(t < tau) = E;

    harmonics = 21; % 0 to 20
    frequencies = (0:harmonics-1) / T;

    a0 = E * tau / T; % DC
    amplitudes = zeros(1, harmonics);
    amplitudes(1) = a0;

    for n = 1:(harmonics-1)
        % n here corresponds to index n+1 in MATLAB (since 1 is DC)
        % BUT loop variable n is harmonic number
        arg = n * pi * tau / T;
        val = E * tau / T * sin(arg) / arg * 2;
        amplitudes(n+1) = val;
    end

    f = figure('Visible', 'off', 'Position', [0 0 1200 800]);
    subplot(2, 1, 1);
    plot(t, f_t, 'b-', 'LineWidth', 2);
    xlim([0, T]);
    ylim([-0.2, 1.5]);
    xlabel('t (s)');
    ylabel('f(t) (V)');
    title('Exp2Q1 - Signal');
    grid on;

    subplot(2, 1, 2);
    stem(frequencies, amplitudes, 'BaseValue', 0);
    xlim([0, 20/T]);
    ylim([-0.25, 0.75]);
    xlabel('Frequency (Hz)');
    ylabel('F(t)');
    title('Freq. Spec.');
    grid on;

    saveas(f, 'output/exp2q1.png');
    close(f);
end

function q2()
    t = linspace(0, 10, 100);
    f_t = zeros(1, 100);

    % delta(t-3):
    % Python: f_t[30] = 1. In MATLAB index 31 corresponds to 30 if 0-based.
    % linspace 0 to 10 with 100 points.
    % indices: 1..100
    % t(31) is close to 3?
    % t = 0, 0.101..., 10.
    % Let's just set the 31st element to 1 to match python approximately
    f_t(31) = 1;

    freq = linspace(0, 5, 100);
    magnitude = ones(size(freq));

    f = figure('Visible', 'off', 'Position', [0 0 1200 800]);

    subplot(2, 1, 1);
    plot(t, f_t, 'b-', 'LineWidth', 2);
    xlim([0, 10]);
    ylim([-0.1, 1.1]);
    xlabel('t (s)');
    ylabel('f(t)');
    title('Exp2Q2 - Signal');
    grid on;

    subplot(2, 1, 2);
    plot(freq, magnitude, 'r-');
    xlim([0, 5]);
    ylim([-1, 2]);
    xlabel('Frequency (Hz)');
    ylabel('F(t)');
    title('Freq. Spec.');
    grid on;

    saveas(f, 'output/exp2q2.png');
    close(f);
end

function q3()
    frequency = 1; % Hz
    T = 1 / frequency;

    num_samples = 200;
    % linspace(0, T, num_samples) includes endpoint usually.
    % Python: np.linspace(0, T, num_samples, endpoint=False)
    % MATLAB: linspace includes endpoint unless we manipulate.
    t = linspace(0, T, num_samples+1);
    t(end) = []; % Remove last point to act like endpoint=False

    % Triangular
    % Python: period = t % T
    % f_t = np.where(period < T / 2, 16 * period - 4, -16 * (period - T / 2) + 4)
    period_t = mod(t, T);
    f_t = zeros(size(t));
    mask = period_t < T/2;
    f_t(mask) = 16 * period_t(mask) - 4;
    f_t(~mask) = -16 * (period_t(~mask) - T/2) + 4;

    harmonics = -20:20;
    amplitudes = zeros(size(harmonics));

    % Python: loop k in range(21), n = 2*k+1.
    for k = 0:20
        n = 2 * k + 1;
        if n <= 20
            sign_val = (-1)^k;
            amp = 32 / (pi^2 * n^2) * sign_val;

            % Python: idx_neg = 20 - n; idx_pos = 20 + n
            % MATLAB indices for harmonics array:
            % harmonics array is -20, -19, ..., 0, ..., 20. (Size 41)
            % 0 corresponds to index 21. n corresponds to index 21+n. -n to 21-n.
            idx_neg = 21 - n;
            idx_pos = 21 + n;

            amplitudes(idx_neg) = amp;
            amplitudes(idx_pos) = amp;
        end
    end

    f = figure('Visible', 'off', 'Position', [0 0 1200 800]);

    subplot(2, 1, 1);
    plot(t, f_t, 'b-', 'LineWidth', 2);
    xlim([0, T]);
    ylim([-5, 5]);
    xlabel('t (s)');
    ylabel('f(t)');
    title('Exp2Q3 - Signal');
    grid on;

    subplot(2, 1, 2);
    stem(harmonics, amplitudes, 'BaseValue', 0);
    xlim([-20, 20]);
    ylim([-0.5, 2]);
    xlabel('Harmonic');
    ylabel('F(t)');
    title('Freq. Spec.');
    grid on;

    saveas(f, 'output/exp2q3.png');
    close(f);
end

function q4()
    E = 1;
    freq = 5000; % Hz
    T = 1 / freq;
    num_harmonics = 20;

    t = linspace(0, 2 * T, 200);
    harmonics_vec = 1:num_harmonics;

    [T_grid, H_grid] = meshgrid(t, harmonics_vec);

    Z = zeros(size(T_grid));
    dc_component = E / 2;

    % harmonics_vec is 1..20
    % H_grid rows are constant harmonic number

    for i = 1:num_harmonics
        n = harmonics_vec(i);
        Z(i, :) = dc_component - (E / (n * pi)) * sin(2 * pi * n * freq * t);
    end

    accumulated = zeros(size(T_grid));
    accumulated(1, :) = Z(1, :);
    for i = 2:num_harmonics
        accumulated(i, :) = accumulated(i - 1, :) + Z(i, :);
    end

    f = figure('Visible', 'off', 'Position', [0 0 1600 900]);
    ax = axes('Parent', f);
    surf(ax, T_grid * 1e6, H_grid, accumulated, 'EdgeColor', 'none', 'FaceAlpha', 0.9);
    colormap(ax, 'parula'); % 'viridis' not standard in old MATLAB, parula is good
    colorbar(ax);

    xlabel(ax, 'Time (\mus)');
    ylabel(ax, 'Harmonic Order');
    zlabel(ax, 'f(t)');
    title(ax, 'Exp2Q4');
    view(ax, 3);

    saveas(f, 'output/exp2q4.png');
    close(f);
end

function q5()
    E = 1;
    f1 = 1000;
    T1 = 1 / f1;
    tho = 1/4 * T1;
    num_harmonics = 20;

    t = linspace(0, 2 * T1, 200);
    harmonics_vec = 1:num_harmonics;

    [T_grid, H_grid] = meshgrid(t, harmonics_vec);

    Z = zeros(size(T_grid));

    for i = 1:num_harmonics
        n = harmonics_vec(i);
        % sinc(x) = sin(pi*x)/(pi*x).
        % Python: np.sinc(n * tho / T1) => sin(pi * n * tho / T1) / (pi * n * tho / T1)
        % This matches MATLAB sinc definition.

        a_n = (2 * E * tho / T1) * sinc(n * tho / T1);
        Z(i, :) = a_n * cos(2 * pi * n * f1 * t);
    end

    accumulated = zeros(size(T_grid));
    accumulated(1, :) = Z(1, :);
    for i = 2:num_harmonics
        accumulated(i, :) = accumulated(i - 1, :) + Z(i, :);
    end

    f = figure('Visible', 'off', 'Position', [0 0 1600 900]);
    ax = axes('Parent', f);
    surf(ax, T_grid * 1e6, H_grid, accumulated, 'EdgeColor', 'none', 'FaceAlpha', 0.9);
    colormap(ax, 'parula');
    colorbar(ax);

    xlabel(ax, 'Time (\mus)');
    ylabel(ax, 'Harmonic Order');
    zlabel(ax, 'f(t)');
    title(ax, 'Exp2Q5');
    view(ax, 3);

    saveas(f, 'output/exp2q5.png');
    close(f);
end
