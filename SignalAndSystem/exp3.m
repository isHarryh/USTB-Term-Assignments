function exp3()
    % Exp3: 信号的时域抽样与重建
    if ~exist('output', 'dir')
        mkdir('output');
    end

    q1();
    q2();
    q3_wrapper();
end

function val = f_signal(t)
    val = sin(2 * pi * t / 3 + pi / 5);
end

function q1()
    t_continuous = linspace(0, 10, 1000);
    f_continuous = f_signal(t_continuous);

    T_values = [1, 1.5, 2];
    labels = {'T=1s', 'T=1.5s', 'T=2s'};

    f = figure('Visible', 'off', 'Position', [0 0 1800 1200]);

    for i = 1:3
        T = T_values(i);
        lbl = labels{i};

        % 1. Time Domain
        subplot(2, 3, i);
        plot(t_continuous, f_continuous, 'b-', 'LineWidth', 1.5, 'DisplayName', 'Continuous');
        hold on;

        t_samples = 0:T:10; % Equivalent to arange(0, 10.1, T) roughly
        f_samples = f_signal(t_samples);

        stem(t_samples, f_samples, 'r-', 'filled', 'DisplayName', 'Samples');
        xlim([0, 10]);
        ylim([-1.5, 1.5]);
        xlabel('t (s)');
        ylabel('f(t)');
        title(['Sampling at ' lbl]);
        grid on;
        legend('show');
        hold off;

        % 2. Frequency Domain
        subplot(2, 3, i + 3);
        fs = 1 / T;
        N = length(f_samples);

        % FFT
        fft_result = fft(f_samples);
        magnitude = abs(fft_result);

        % Frequency axis
        % Python np.fft.fftfreq returns [0, 1, ..., n/2-1, -n/2, ..., -1] / (d*n)
        % We want positive half: 0 to fs/2

        f_axis = (0:N-1) * (fs / N);
        half_N = floor(N/2) + 1;

        pos_freq = f_axis(1:half_N);
        pos_mag = magnitude(1:half_N);

        stem(pos_freq, pos_mag, 'BaseValue', 0);
        xlim([0, fs/2]);
        % ylim: auto is fine
        xlabel('Frequency (Hz)');
        ylabel('Magnitude');
        title(['Spectrum at ' lbl]);
        grid on;
    end

    saveas(f, 'output/exp3q1.png');
    close(f);
end

function q2()
    input_path = 'input/996839315.wav';
    if ~exist(input_path, 'file')
        disp(['File ' input_path ' not found. Skipping Q2.']);
        return;
    end

    [data_orig, fs_orig] = audioread(input_path);

    % Stereo to mono
    if size(data_orig, 2) > 1
        data_orig = mean(data_orig, 2);
    end

    % Resample and Save helper
    % Python uses signal.resample (FFT based)
    % MATLAB resample uses polyphase. results might slightly differ but acceptable.
    function d_res = process_audio(target_fs, out_name)
         d_res = resample(data_orig, target_fs, fs_orig);
         audiowrite(out_name, d_res, target_fs);
    end

    data_441 = process_audio(44100, 'output/996839315.44100.wav');
    data_22 = process_audio(22050, 'output/996839315.22050.wav');
    data_48 = process_audio(48000, 'output/996839315.48000.wav');

    % Plotting helper
    function [freqs, mag] = get_spectrum_data(data, fs)
        N = length(data);
        w = hanning(N);
        fft_data = fft(data .* w);
        mag_full = abs(fft_data);

        freq_axis = (0:N-1)*(fs/N);
        half = floor(N/2) + 1;

        freqs = freq_axis(1:half);
        mag = mag_full(1:half);
    end

    [f_orig, m_orig] = get_spectrum_data(data_orig, fs_orig);
    [f_441, m_441] = get_spectrum_data(data_441, 44100);
    [f_22, m_22] = get_spectrum_data(data_22, 22050);
    [f_48, m_48] = get_spectrum_data(data_48, 48000);

    f = figure('Visible', 'off', 'Position', [0 0 1000 1600]);

    subplot(4, 1, 1);
    plot(f_orig, m_orig, 'b');
    title(['Original Signal Spectrum (fs=' num2str(fs_orig) 'Hz)']);
    ylabel('Magnitude');
    xlim([0, 25000]); grid on;

    subplot(4, 1, 2);
    plot(f_441, m_441, 'g');
    title('Resampled 44.1kHz Spectrum');
    ylabel('Magnitude');
    xlim([0, 25000]); grid on;

    subplot(4, 1, 3);
    plot(f_22, m_22, 'r');
    title('Resampled 22.05kHz Spectrum');
    ylabel('Magnitude');
    xlim([0, 25000]); grid on;

    subplot(4, 1, 4);
    plot(f_48, m_48, 'm');
    title('Resampled 48kHz Spectrum');
    ylabel('Magnitude');
    xlabel('Frequency (Hz)');
    xlim([0, 25000]); grid on;

    saveas(f, 'output/exp3q2.png');
    close(f);
end

function q3_wrapper()
    q3(5000);
    q3(80);
end

function q3(freq_sample)
    T = 0.8;
    num_cycles = 3;
    total_time = num_cycles * T;

    t = linspace(0, total_time, floor(freq_sample * total_time));

    function y = gaussian(t_val, A, mu, sigma)
        y = A * exp(-((t_val - mu).^2) / (2 * sigma^2));
    end

    ecg_signal = zeros(size(t));
    for cycle = 0:(num_cycles-1)
        offset = cycle * T;
        ecg_signal = ecg_signal + gaussian(t, 0.15, 0.05 + offset, 0.01);
        ecg_signal = ecg_signal + gaussian(t, -0.3, 0.15 + offset, 0.005);
        ecg_signal = ecg_signal + gaussian(t, 1.0, 0.2 + offset, 0.01);
        ecg_signal = ecg_signal + gaussian(t, -0.4, 0.25 + offset, 0.005);
        ecg_signal = ecg_signal + gaussian(t, 0.3, 0.3 + offset, 0.02);
    end

    interference_amplitude = 0.1;
    interference = interference_amplitude * sin(2 * pi * 50 * t);
    ecg_with_interference = ecg_signal + interference;

    % FFT
    fs = freq_sample; % Roughly
    N = length(t);
    freq_axis = (0:N-1)*(fs/N);

    fft_original = fft(ecg_signal);
    mag_original = abs(fft_original);

    fft_mixed = fft(ecg_with_interference);
    mag_mixed = abs(fft_mixed);

    half_N = floor(N/2) + 1;
    pos_freq = freq_axis(1:half_N);
    pos_mag_orig = mag_original(1:half_N);
    pos_mag_mixed = mag_mixed(1:half_N);

    % Notch Filter
    % Zero out 50Hz.
    fft_filtered = fft_mixed;

    % Find index close to 50
    [~, idx_50] = min(abs(freq_axis - 50));
    % MATLAB indices are 1-based
    % In double sided, also need negative frq (or N-k)
    % N corresponds to fs. 50Hz is idx_50.
    % Symmetric part is N - (idx_50 - 1) + 1 ?
    % idx_50 is index in 1..N. freq_axis(idx_50) ~ 50.
    % Negative freq is at N - (idx_50 - 1) + 1 approx.
    % Let's use logic:
    idx_neg50 = N - idx_50 + 2;

    fft_filtered(idx_50) = 0;
    % Check bounds
    if idx_neg50 <= N && idx_neg50 > 0
        fft_filtered(idx_neg50) = 0;
    end

    recovered_signal = real(ifft(fft_filtered));
    mag_filtered = abs(fft_filtered);
    pos_mag_filtered = mag_filtered(1:half_N);

    % Filter Shape for visualization
    f_range = linspace(0, 100, 1000);
    H = ones(size(f_range));
    H(abs(f_range - 50) < 0.1) = 0;

    f = figure('Visible', 'off', 'Position', [0 0 1800 1200]);

    % Layout similar to python: 3x3
    % 1: Original Signal
    subplot(3, 3, 1);
    plot(t, ecg_signal, 'b-', 'LineWidth', 1.5);
    xlim([0, total_time]); ylim([-1.2, 1.5]);
    title('Original ECG Signal'); grid on;

    % 2: With Interference
    subplot(3, 3, 2);
    plot(t, ecg_with_interference, 'r-', 'LineWidth', 1.5);
    xlim([0, total_time]); ylim([-1.2, 1.5]);
    title('ECG with 50Hz Interference'); grid on;

    % 3: Recovered
    subplot(3, 3, 3);
    plot(t, recovered_signal, 'g-', 'LineWidth', 1.5);
    xlim([0, total_time]); ylim([-1.2, 1.5]);
    title('Recovered ECG Signal'); grid on;

    % 4: FFT Original
    subplot(3, 3, 4);
    plot(pos_freq, pos_mag_orig, 'b-', 'LineWidth', 1.5);
    xlim([0, 80]);
    if max(pos_mag_orig) > 0
        ylim([0, max(pos_mag_orig) * 1.1]);
    end
    title('FFT of Original'); grid on;

    % 5: FFT Mixed
    subplot(3, 3, 5);
    plot(pos_freq, pos_mag_mixed, 'r-', 'LineWidth', 1.5);
    xlim([0, 80]);
    if max(pos_mag_mixed) > 0
        ylim([0, max(pos_mag_mixed) * 1.1]);
    end
    title('FFT of Mixed Signal'); grid on;

    % 6: Spectrum after Notch
    subplot(3, 3, 6);
    plot(pos_freq, pos_mag_filtered, 'g-', 'LineWidth', 1.5);
    xlim([0, 80]);
    if max(pos_mag_filtered) > 0
        ylim([0, max(pos_mag_filtered) * 1.1]);
    end
    title('Spectrum After Notch'); grid on;

    % 8 (Center bottom): Filter Shape
    subplot(3, 3, 8);
    plot(f_range, H, 'k-', 'LineWidth', 2);
    xline(50, 'r--', 'LineWidth', 1);
    xlim([0, 80]);
    title('Ideal Notch Filter at 50Hz'); grid on;

    saveas(f, ['output/exp3q3.' num2str(freq_sample) '.png']);
    close(f);
end
