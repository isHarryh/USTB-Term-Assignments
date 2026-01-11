function exp1()
    % Exp1: 连续时间信号的产生
    % Creates output directory and runs all questions

    if ~exist('output', 'dir')
        mkdir('output');
    end

    q1();
    q2();
    q3();
    q4();
    q5();
    q6();
    q7();
end

function q1()
    t = linspace(0, 10, 1000);
    signal = zeros(size(t));
    % dt = 0.1, area = 1
    % delta(t-2):
    delta_mask1 = (t >= 1.95) & (t <= 2.05);
    signal(delta_mask1) = 10;
    % delta(t-4):
    delta_mask2 = (t >= 3.95) & (t <= 4.05);
    signal(delta_mask2) = 10;

    f = figure('Visible', 'off');
    plot(t, signal, 'LineWidth', 1.5);
    xlim([0, 10]);
    ylim([-1, 11]);
    xlabel('t');
    ylabel('f(t)');
    title('Exp1Q1');
    saveas(f, 'output/exp1q1.png');
    close(f);
end

function q2()
    % Matches exp1.py: t from -2pi to 2pi
    t = linspace(-2*pi, 2*pi, 1000);
    f_t = exp(-t) .* sin(2*pi*t);

    f = figure('Visible', 'off');
    plot(t, f_t);
    xlim([-2*pi, 2*pi]);
    ylim([-400, 400]);
    xlabel('t');
    ylabel('f(t)');
    title('Exp1Q2');
    saveas(f, 'output/exp1q2.png');
    close(f);
end

function q3()
    t = linspace(-2*pi, 2*pi, 1000);
    % Python: np.sinc(x) = sin(pi*x)/(pi*x)
    % MATLAB: sinc(x) = sin(pi*x)/(pi*x)
    % exp1.py: sinc(t/2)
    f_val = sinc(t / 2);

    f = figure('Visible', 'off');
    plot(t, f_val);
    xlim([-2*pi, 2*pi]);
    ylim([-0.5, 1.5]);
    xlabel('t');
    ylabel('f(t)');
    title('Exp1Q3');
    saveas(f, 'output/exp1q3.png');
    close(f);
end

function q4()
    t = linspace(0, 6*pi, 1000);
    real_part = 2 * exp(0.1 * t) .* cos(0.6 * pi * t);
    imag_part = 2 * exp(0.1 * t) .* sin(0.6 * pi * t);

    f = figure('Visible', 'off');
    plot(t, real_part, 'DisplayName', 'Re');
    hold on;
    plot(t, imag_part, 'DisplayName', 'Im');
    legend('show');
    xlim([0, 6*pi]);
    ylim([-15, 15]);
    xlabel('t');
    ylabel('f(t)');
    title('Exp1Q4');
    saveas(f, 'output/exp1q4.png');
    close(f);
end

function q5()
    t = linspace(-6, 10, 1000);
    % where((t >= -3) & (t < 2), 1, 0)
    sig = zeros(size(t));
    sig((t >= -3) & (t < 2)) = 1;

    f = figure('Visible', 'off');
    % Use stairs for 'step' equivalent
    stairs(t, sig, 'LineWidth', 1.5);
    xlim([-6, 10]);
    ylim([-0.5, 1.5]);
    xlabel('t');
    ylabel('f(t)');
    title('Exp1Q5');
    saveas(f, 'output/exp1q5.png');
    close(f);
end

function q6()
    freq = 200; % Hz
    T = 1 / freq;
    num_samples_per_period = 16;
    num_periods = 3;
    total_samples = num_periods * num_samples_per_period;
    t = linspace(0, num_periods * T, total_samples);

    % Square wave manually
    % Python: np.where((t % T) < T / 2, 1, -1)
    square_wave = ones(size(t));
    square_wave(mod(t, T) >= T/2) = -1;

    f = figure('Visible', 'off');
    stem(t, square_wave, 'BaseValue', 0);
    xlim([0, num_periods * T]);
    ylim([-1.5, 1.5]);
    xlabel('t');
    ylabel('f(t) sampled');
    title('Exp1Q6');
    saveas(f, 'output/exp1q6.png');
    close(f);
end

function q7()
    freq = 3000; % Hz
    T = 1 / freq;
    num_samples_per_period = 32;
    num_periods = 2;
    total_samples = num_periods * num_samples_per_period;
    t = linspace(0, num_periods * T, total_samples);

    % Sawtooth: (t % T) / T
    sawtooth_wave = mod(t, T) / T;

    f = figure('Visible', 'off');
    stem(t, sawtooth_wave, 'BaseValue', 0);
    xlim([0, num_periods * T]);
    ylim([-0.1, 1.1]);
    xlabel('t');
    ylabel('f(t) sampled');
    title('Exp1Q7');
    saveas(f, 'output/exp1q7.png');
    close(f);
end
