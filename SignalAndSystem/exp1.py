import matplotlib.pyplot as plt
import numpy as np


def q1():
    t = np.linspace(0, 10, 1000)
    signal = np.zeros_like(t)
    # dt = 0.1, area = 1
    # delta(t-2):
    delta_mask1 = (t >= 1.95) & (t <= 2.05)
    signal[delta_mask1] = 10
    # delta(t-4):
    delta_mask2 = (t >= 3.95) & (t <= 4.05)
    signal[delta_mask2] = 10

    plt.figure()
    plt.plot(t, signal)
    plt.xlim(0, 10)
    plt.ylim(-1, 11)
    plt.xlabel("t")
    plt.ylabel("f(t)")
    plt.title("Exp1Q1")
    plt.savefig("output/exp1q1.png")
    plt.close()


def q2():
    t = np.linspace(-2 * np.pi, 2 * np.pi, 1000)
    f = np.exp(-t) * np.sin(2 * np.pi * t)

    plt.figure()
    plt.plot(t, f)
    plt.xlim(-2 * np.pi, 2 * np.pi)
    plt.ylim(-400, 400)
    plt.xlabel("t")
    plt.ylabel("f(t)")
    plt.title("Exp1Q2")
    plt.savefig("output/exp1q2.png")
    plt.close()


def q3():
    t = np.linspace(-2 * np.pi, 2 * np.pi, 1000)
    f = np.sinc(t / 2)  # sin(pi x)/(pi x)

    plt.figure()
    plt.plot(t, f)
    plt.xlim(-2 * np.pi, 2 * np.pi)
    plt.ylim(-0.5, 1.5)
    plt.xlabel("t")
    plt.ylabel("f(t)")
    plt.title("Exp1Q3")
    plt.savefig("output/exp1q3.png")
    plt.close()


def q4():
    t = np.linspace(0, 6 * np.pi, 1000)
    real_part = 2 * np.exp(0.1 * t) * np.cos(0.6 * np.pi * t)
    imag_part = 2 * np.exp(0.1 * t) * np.sin(0.6 * np.pi * t)

    plt.figure()
    plt.plot(t, real_part, label="Re")
    plt.plot(t, imag_part, label="Im")
    plt.legend()
    plt.xlim(0, 6 * np.pi)
    plt.ylim(-15, 15)
    plt.xlabel("t")
    plt.ylabel("f(t)")
    plt.title("Exp1Q4")
    plt.savefig("output/exp1q4.png")
    plt.close()


def q5():
    t = np.linspace(-6, 10, 1000)
    f = np.where((t >= -3) & (t < 2), 1, 0)

    plt.figure()
    plt.step(t, f, where="post")
    plt.xlim(-6, 10)
    plt.ylim(-0.5, 1.5)
    plt.xlabel("t")
    plt.ylabel("f(t)")
    plt.title("Exp1Q5")
    plt.savefig("output/exp1q5.png")
    plt.close()


def q6():
    f = 200  # Hz
    T = 1 / f
    num_samples_per_period = 16
    num_periods = 3
    total_samples = num_periods * num_samples_per_period
    t = np.linspace(0, num_periods * T, total_samples)

    # Square
    square_wave = np.where((t % T) < T / 2, 1, -1)
    plt.figure()
    plt.stem(t, square_wave, basefmt=" ")
    plt.xlim(0, num_periods * T)
    plt.ylim(-1.5, 1.5)
    plt.xlabel("t")
    plt.ylabel("f(t) sampled")
    plt.title("Exp1Q6")
    plt.savefig("output/exp1q6.png")
    plt.close()


def q7():
    f = 3000  # Hz
    T = 1 / f
    num_samples_per_period = 32
    num_periods = 2
    total_samples = num_periods * num_samples_per_period
    t = np.linspace(0, num_periods * T, total_samples)

    # Sawtooth
    sawtooth = (t % T) / T
    plt.figure()
    plt.stem(t, sawtooth, basefmt=" ")
    plt.xlim(0, num_periods * T)
    plt.ylim(-0.1, 1.1)
    plt.xlabel("t")
    plt.ylabel("f(t) sampled")
    plt.title("Exp1Q7")
    plt.savefig("output/exp1q7.png")
    plt.close()


if __name__ == "__main__":
    q1()
    q2()
    q3()
    q4()
    q5()
    q6()
    q7()
