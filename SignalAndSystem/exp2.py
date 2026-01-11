import matplotlib.pyplot as plt
import numpy as np


def q1():
    E = 1.2
    T = 0.1  # ms
    tau = 1 / 4 * T

    num_samples = 256
    t = np.linspace(0, T, num_samples)

    f_t = np.zeros_like(t)
    f_t[t < tau] = E

    harmonics = 21  # 0 to 20
    frequencies = np.arange(harmonics) / T

    a0 = E * tau / T  # DC
    amplitudes = np.zeros(harmonics)
    amplitudes[0] = a0

    for n in range(1, harmonics):
        # a_n = E * tau / T * sin(n*pi*tau/T) / (n*pi*tau/T)
        arg = n * np.pi * tau / T
        amplitudes[n] = E * tau / T * np.sin(arg) / arg * 2  # 乘以2是因为有正负两边

    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 8))

    ax1.plot(t, f_t, "b-", linewidth=2)
    ax1.set_xlim(0, T)
    ax1.set_ylim(-0.2, 1.5)
    ax1.set_xlabel("t (s)")
    ax1.set_ylabel("f(t) (V)")
    ax1.set_title("Exp2Q1 - Signal")
    ax1.grid(True, alpha=0.3)

    ax2.stem(frequencies, amplitudes, basefmt=" ")
    ax2.set_xlim(0, 20 / T)
    ax2.set_ylim(-0.25, 0.75)
    ax2.set_xlabel("Frequency (Hz)")
    ax2.set_ylabel("F(t)")
    ax2.set_title("Freq. Spec.")
    ax2.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig("output/exp2q1.png")
    plt.close()


def q2():
    t = np.linspace(0, 10, 100)
    f_t = np.zeros(100)

    # delta(t-3):
    f_t[30] = 1
    freq = np.linspace(0, 5, 100)
    magnitude = np.ones_like(freq)

    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 8))

    ax1.plot(t, f_t, "b-", linewidth=2)
    ax1.set_xlim(0, 10)
    ax1.set_ylim(-0.1, 1.1)
    ax1.set_xlabel("t (s)")
    ax1.set_ylabel("f(t)")
    ax1.set_title("Exp2Q2 - Signal")
    ax1.grid(True, alpha=0.3)

    ax2.plot(freq, magnitude, "r-")
    ax2.set_xlim(0, 5)
    ax2.set_ylim(-1, 2)
    ax2.set_xlabel("Frequency (Hz)")
    ax2.set_ylabel("F(t)")
    ax2.set_title("Freq. Spec.")
    ax2.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig("output/exp2q2.png")
    plt.close()


def q3():
    f = 1  # Hz
    T = 1 / f

    num_samples = 200
    t = np.linspace(0, T, num_samples, endpoint=False)

    # Triangular
    period = t % T
    f_t = np.where(period < T / 2, 16 * period - 4, -16 * (period - T / 2) + 4)

    harmonics = np.arange(-20, 21)  # -20 to 20
    amplitudes = np.zeros(len(harmonics))
    for k in range(21):
        n = 2 * k + 1
        if n <= 20:
            sign = (-1) ** k
            amp = 32 / (np.pi**2 * n**2) * sign
            idx_neg = 20 - n
            idx_pos = 20 + n
            amplitudes[idx_neg] = amp
            amplitudes[idx_pos] = amp

    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 8))

    ax1.plot(t, f_t, "b-", linewidth=2)
    ax1.set_xlim(0, T)
    ax1.set_ylim(-5, 5)
    ax1.set_xlabel("t (s)")
    ax1.set_ylabel("f(t)")
    ax1.set_title("Exp2Q3 - Signal")
    ax1.grid(True, alpha=0.3)

    ax2.stem(harmonics, amplitudes, basefmt=" ")
    ax2.set_xlim(-20, 20)
    ax2.set_ylim(-0.5, 2)
    ax2.set_xlabel("Harmonic")
    ax2.set_ylabel("F(t)")
    ax2.set_title("Freq. Spec.")
    ax2.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig("output/exp2q3.png")
    plt.close()


def q4():
    E = 1
    f = 5000  # Hz
    T = 1 / f
    num_harmonics = 20

    t = np.linspace(0, 2 * T, 200)
    harmonics = np.arange(1, num_harmonics + 1)

    T_grid, H_grid = np.meshgrid(t, harmonics)

    # 计算每个谐波在每个时刻的值
    Z = np.zeros_like(T_grid, dtype=float)
    dc_component = E / 2

    for i, n in enumerate(harmonics):
        Z[i, :] = dc_component - (E / (n * np.pi)) * np.sin(2 * np.pi * n * f * t)

    # 计算谐波叠加（逐步累加）
    accumulated = np.zeros_like(T_grid, dtype=float)
    accumulated[0, :] = Z[0, :]
    for i in range(1, num_harmonics):
        accumulated[i, :] = accumulated[i - 1, :] + Z[i, :]

    # 3D网格图
    fig = plt.figure(figsize=(16, 9))
    ax = fig.add_subplot(111, projection="3d")

    surf = ax.plot_surface(T_grid * 1e6, H_grid, accumulated, cmap="viridis", alpha=0.9)

    ax.set_xlabel("Time (μs)")
    ax.set_ylabel("Harmonic Order")
    ax.set_zlabel("f(t)")
    ax.set_title("Exp2Q4")

    fig.colorbar(surf, ax=ax, label="Amplitude")
    plt.savefig("output/exp2q4.png", bbox_inches="tight")
    plt.close()


def q5():
    E = 1
    f1 = 1000
    T1 = 1 / f1
    tho = 1 / 4 * T1
    num_harmonics = 20

    t = np.linspace(0, 2 * T1, 200)
    harmonics = np.arange(1, num_harmonics + 1)

    T_grid, H_grid = np.meshgrid(t, harmonics)

    # 计算每个谐波在每个时刻的值
    Z = np.zeros_like(T_grid, dtype=float)

    for i, n in enumerate(harmonics):
        # 矩形波的谐波：a_n cos(2pi n f1 t)
        # a_n = (2 * E * tho / T1) * sinc(n * tho / T1)
        # sinc(x) = sin(pi x)/(pi x), 但这里 sin(n pi tho / T1) / (n pi tho / T1) = sinc(n tho / T1)
        a_n = (2 * E * tho / T1) * np.sinc(n * tho / T1)
        Z[i, :] = a_n * np.cos(2 * np.pi * n * f1 * t)

    # 计算谐波叠加（逐步累加）
    accumulated = np.zeros_like(T_grid, dtype=float)
    accumulated[0, :] = Z[0, :]
    for i in range(1, num_harmonics):
        accumulated[i, :] = accumulated[i - 1, :] + Z[i, :]

    # 3D网格图
    fig = plt.figure(figsize=(16, 9))
    ax = fig.add_subplot(111, projection="3d")

    surf = ax.plot_surface(T_grid * 1e6, H_grid, accumulated, cmap="viridis", alpha=0.9)

    ax.set_xlabel("Time (μs)")
    ax.set_ylabel("Harmonic Order")
    ax.set_zlabel("f(t)")
    ax.set_title("Exp2Q5")

    fig.colorbar(surf, ax=ax, label="Amplitude")
    plt.savefig("output/exp2q5.png", dpi=100, bbox_inches="tight")
    plt.close()


if __name__ == "__main__":
    q1()
    q2()
    q3()
    q4()
    q5()
