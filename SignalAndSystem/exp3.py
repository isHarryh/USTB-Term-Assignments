import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import numpy as np
import scipy.io.wavfile as wavfile
import scipy.signal as signal
import os

def q1():
    # 定义信号
    def f(t):
        return np.sin(2 * np.pi * t / 3 + np.pi / 5)

    # 时间范围
    t_continuous = np.linspace(0, 10, 1000)
    f_continuous = f(t_continuous)

    # 采样周期
    T_values = [1, 1.5, 2]
    labels = ['T=1s', 'T=1.5s', 'T=2s']

    # 创建子图 2x3
    fig, axes = plt.subplots(2, 3, figsize=(18, 12))

    for i, (T, label) in enumerate(zip(T_values, labels)):
        # 时间域子图
        ax_time = axes[0, i]

        # 绘制连续信号
        ax_time.plot(t_continuous, f_continuous, 'b-', linewidth=1.5, label='Continuous')

        # 采样点
        t_samples = np.arange(0, 10.1, T)
        f_samples = f(t_samples)

        # 绘制采样点
        ax_time.stem(t_samples, f_samples, 'r-', markerfmt='ro', basefmt=' ', label='Samples')

        ax_time.set_xlim(0, 10)
        ax_time.set_ylim(-1.5, 1.5)
        ax_time.set_xlabel('t (s)')
        ax_time.set_ylabel('f(t)')
        ax_time.set_title(f'Sampling at {label}')
        ax_time.grid(True, alpha=0.3)
        ax_time.legend()

        # 频谱子图
        ax_freq = axes[1, i]

        # 计算FFT
        fs = 1 / T  # 采样频率
        freq = np.fft.fftfreq(len(f_samples), 1/fs)
        fft_result = np.fft.fft(f_samples)
        magnitude = np.abs(fft_result)
        pos_freq = freq[:len(freq)//2]
        pos_mag = magnitude[:len(freq)//2]

        # 绘制频谱
        ax_freq.stem(pos_freq, pos_mag, basefmt=' ')
        ax_freq.set_xlim(0, fs/2)
        ax_freq.set_ylim(0, max(pos_mag) * 1.1)
        ax_freq.set_xlabel('Frequency (Hz)')
        ax_freq.set_ylabel('Magnitude')
        ax_freq.set_title(f'Spectrum at {label}')
        ax_freq.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig('output/exp3q1.png', dpi=100, bbox_inches='tight')
    plt.close()



def q2():
    input_path = "input/996839315.wav"
    if not os.path.exists(input_path):
        print(f"File {input_path} not found. Skipping Q2.")
        return

    # 1. Read Original
    # wavfile.read returns (rate, data)
    fs_orig, data_orig = wavfile.read(input_path)

    # Handle stereo -> mono
    if data_orig.ndim > 1:
        data_orig = data_orig.mean(axis=1)

    # Convert to float
    data_orig_float = data_orig.astype(float)

    # Helper: Resample and Save
    def resample_and_save(target_fs, output_filename):
        if fs_orig == target_fs:
            data_resampled = data_orig_float
        else:
            # Calculate new number of samples
            num_samples = int(len(data_orig_float) * target_fs / fs_orig)
            # Use signal.resample
            data_resampled = signal.resample(data_orig_float, num_samples)

        # Save
        data_save = np.clip(data_resampled, -32768, 32767).astype(np.int16)
        wavfile.write(output_filename, target_fs, data_save)
        return data_resampled

    # Helper: Calculate Spectrum
    def get_spectrum(data, fs):
        n = len(data)
        window = np.hanning(n)
        fft_data = np.fft.fft(data * window)
        freqs = np.fft.fftfreq(n, 1/fs)
        mag = np.abs(fft_data)
        mask = freqs >= 0
        return freqs[mask], mag[mask]

    # Process
    data_441 = resample_and_save(44100, "output/996839315.44100.wav")
    data_22 = resample_and_save(22050, "output/996839315.22050.wav")
    data_48 = resample_and_save(48000, "output/996839315.48000.wav")

    # Spectra
    f_orig, m_orig = get_spectrum(data_orig_float, fs_orig)
    f_441, m_441 = get_spectrum(data_441, 44100)
    f_22, m_22 = get_spectrum(data_22, 22050)
    f_48, m_48 = get_spectrum(data_48, 48000)

    # Plot
    fig, axes = plt.subplots(4, 1, figsize=(10, 16), constrained_layout=True)

    axes[0].plot(f_orig, m_orig, 'b')
    axes[0].set_title(f"Original Signal Spectrum (fs={fs_orig}Hz)")
    axes[0].set_ylabel("Magnitude")

    axes[1].plot(f_441, m_441, 'g')
    axes[1].set_title("Resampled 44.1kHz Spectrum")
    axes[1].set_ylabel("Magnitude")

    axes[2].plot(f_22, m_22, 'r')
    axes[2].set_title("Resampled 22.05kHz Spectrum")
    axes[2].set_ylabel("Magnitude")

    axes[3].plot(f_48, m_48, 'm')
    axes[3].set_title("Resampled 48kHz Spectrum")
    axes[3].set_ylabel("Magnitude")
    axes[3].set_xlabel("Frequency (Hz)")

    for ax in axes:
        ax.set_xlim(0, 25000)
        ax.grid(True, alpha=0.3)

    plt.savefig("output/exp3q2.png", dpi=100)
    plt.close()


def q3(freq_sample: int = 5000):
    """
    基于傅里叶分析的心电信号(ECG)工频干扰消除。
    """
    T = 0.8  # s
    num_cycles = 3
    total_time = num_cycles * T

    t = np.linspace(0, total_time, int(freq_sample * total_time))

    def gaussian(t, A, mu, sigma):
        return A * np.exp(-((t - mu)**2) / (2 * sigma**2))

    ecg_signal = np.zeros_like(t)
    for cycle in range(num_cycles):
        offset = cycle * T
        # P波
        ecg_signal += gaussian(t, 0.15, 0.05 + offset, 0.01)
        # Q波
        ecg_signal += gaussian(t, -0.3, 0.15 + offset, 0.005)
        # R波
        ecg_signal += gaussian(t, 1.0, 0.2 + offset, 0.01)
        # S波
        ecg_signal += gaussian(t, -0.4, 0.25 + offset, 0.005)
        # T波
        ecg_signal += gaussian(t, 0.3, 0.3 + offset, 0.02)

    # 干扰信号：50Hz正弦波
    interference_amplitude = 0.1
    interference = interference_amplitude * np.sin(2 * np.pi * 50 * t)
    ecg_with_interference = ecg_signal + interference

    # FFT of original signal
    fs = len(t) / total_time
    freq = np.fft.fftfreq(len(t), 1/fs)
    fft_original = np.fft.fft(ecg_signal)
    mag_original = np.abs(fft_original)
    pos_freq = freq[:len(freq)//2]
    pos_mag_orig = mag_original[:len(freq)//2]

    # FFT of mixed signal
    fft_mixed = np.fft.fft(ecg_with_interference)
    mag_mixed = np.abs(fft_mixed)
    pos_mag_mixed = mag_mixed[:len(freq)//2]

    # 理想陷波器：50Hz
    notch_freq = 50
    f_range = np.linspace(0, 100, 1000)
    H = np.ones_like(f_range)
    H[np.abs(f_range - notch_freq) < 0.1] = 0

    # 应用陷波器
    idx_50 = np.argmin(np.abs(freq - 50))
    idx_neg50 = np.argmin(np.abs(freq + 50))
    fft_filtered = fft_mixed.copy()
    # 简单的两点置零
    fft_filtered[idx_50] = 0
    fft_filtered[idx_neg50] = 0

    # 逆FFT得到复原信号
    recovered_signal = np.real(np.fft.ifft(fft_filtered))
    mag_filtered = np.abs(fft_filtered)
    pos_mag_filtered = mag_filtered[:len(freq)//2]

    fig = plt.figure(figsize=(18, 12))
    gs = gridspec.GridSpec(3, 3, figure=fig)

    # 左上: Original
    ax1 = fig.add_subplot(gs[0, 0])
    ax1.plot(t, ecg_signal, 'b-', linewidth=1.5)
    ax1.set_xlim(0, total_time)
    ax1.set_ylim(-1.2, 1.5)
    ax1.set_title('Original ECG Signal')
    ax1.grid(True, alpha=0.3)

    # 右上: With Interference
    ax2 = fig.add_subplot(gs[0, 1])
    ax2.plot(t, ecg_with_interference, 'r-', linewidth=1.5)
    ax2.set_xlim(0, total_time)
    ax2.set_ylim(-1.2, 1.5)
    ax2.set_title('ECG with 50Hz Interference')
    ax2.grid(True, alpha=0.3)

    # 第一行第三列: Recovered
    ax6 = fig.add_subplot(gs[0, 2])
    ax6.plot(t, recovered_signal, 'g-', linewidth=1.5)
    ax6.set_xlim(0, total_time)
    ax6.set_ylim(-1.2, 1.5)
    ax6.set_title('Recovered ECG Signal')
    ax6.grid(True, alpha=0.3)

    # 左下: Original FFT
    ax4 = fig.add_subplot(gs[1, 0])
    ax4.plot(pos_freq, pos_mag_orig, 'b-', linewidth=1.5)
    ax4.set_xlim(0, 80)
    ax4.set_ylim(0, max(pos_mag_orig) * 1.1)
    ax4.set_title('FFT of Original')
    ax4.grid(True, alpha=0.3)

    # 右下: Mixed FFT
    ax3 = fig.add_subplot(gs[1, 1])
    ax3.plot(pos_freq, pos_mag_mixed, 'r-', linewidth=1.5)
    ax3.set_xlim(0, 80)
    ax3.set_ylim(0, max(pos_mag_mixed) * 1.1)
    ax3.set_title('FFT of Mixed Signal')
    ax3.grid(True, alpha=0.3)

    # 第二行第三列: Filtered FFT
    ax7 = fig.add_subplot(gs[1, 2])
    ax7.plot(pos_freq, pos_mag_filtered, 'g-', linewidth=1.5)
    ax7.set_xlim(0, 80)
    ax7.set_ylim(0, max(pos_mag_filtered) * 1.1)
    ax7.set_title('Spectrum After Notch')
    ax7.grid(True, alpha=0.3)

    # 第三行居中: Filter Shape
    ax5 = fig.add_subplot(gs[2, 1])
    ax5.plot(f_range, H, 'k-', linewidth=2)
    ax5.axvline(notch_freq, color='r', linestyle='--', linewidth=1)
    ax5.set_xlim(0, 80)
    ax5.set_title('Ideal Notch Filter at 50Hz')
    ax5.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig(f'output/exp3q3.{freq_sample}.png', dpi=100, bbox_inches='tight')
    plt.close()

if __name__ == "__main__":
    q1()
    q2()
    q3(5000)
    q3(80)
