import numpy as np
from scipy.stats import norm
import matplotlib.pyplot as plt

prior_probs = {"omega_1": 0.9, "omega_2": 0.1}
class_conditional_probs = {
    "omega_1": norm(loc=-2, scale=0.5),
    "omega_2": norm(loc=2, scale=2),
}
risk_loss = {
    "alpha_1": {"omega_1": 0, "omega_2": 6},
    "alpha_2": {"omega_1": 1, "omega_2": 0},
}

observations = np.array(
    [
        -3.9847,
        -3.5549,
        -1.2401,
        -0.9780,
        -0.7932,
        -2.8531,
        -2.7605,
        -3.7287,
        -3.5414,
        -2.2692,
        -3.4549,
        -3.0752,
        -3.9934,
        2.8792,
        -0.9780,
        0.7932,
        1.1882,
        3.0682,
        -1.5799,
        -1.4885,
        -0.7431,
        -0.4221,
        -1.1186,
        4.2532,
    ]
)


def calculate_posterior_probs(x):
    posterior_probs = {}
    for omega in class_conditional_probs:
        class_cond_prob = class_conditional_probs[omega].pdf(x)
        posterior_probs[omega] = class_cond_prob * prior_probs[omega]
    return posterior_probs


def calculate_conditional_risk(x):
    conditional_risks = {}
    posterior_probs = calculate_posterior_probs(x)
    for alpha in risk_loss:
        risk = 0
        for omega in risk_loss[alpha]:
            risk += posterior_probs[omega] * risk_loss[alpha][omega]
        conditional_risks[alpha] = risk
    return conditional_risks, posterior_probs


def make_decision(observations):
    risk_loss_made = []
    posterior_probs_list = []
    conditional_risks_list = []
    for x in observations:
        conditional_risks, posterior_probs = calculate_conditional_risk(x)
        posterior_probs_list.append(posterior_probs)
        conditional_risks_list.append(conditional_risks)
        min_risk_decision = min(conditional_risks, key=conditional_risks.get)
        risk_loss_made.append(min_risk_decision)

    return risk_loss_made, conditional_risks_list


classification_result, conditional_risks_list = make_decision(observations)
print("Classification Result:", classification_result)


x_values = np.linspace(-5, 5, 500)

conditional_risks_alpha_1 = [
    calculate_conditional_risk(x)[0]["alpha_1"] for x in x_values
]
conditional_risks_alpha_2 = [
    calculate_conditional_risk(x)[0]["alpha_2"] for x in x_values
]

plt.plot(
    x_values,
    conditional_risks_alpha_1,
    label="Conditional Risk for alpha_1",
    linestyle="-",
    color="blue",
)
plt.plot(
    x_values,
    conditional_risks_alpha_2,
    label="Conditional Risk for alpha_2",
    linestyle="-",
    color="red",
)

for i in range(len(observations)):
    if classification_result[i] == "alpha_1":
        plt.plot(
            observations[i],
            conditional_risks_list[i]["alpha_1"],
            marker="o",
            color="blue",
        )
    else:
        plt.plot(
            observations[i],
            conditional_risks_list[i]["alpha_2"],
            marker="s",
            color="red",
        )

plt.xlabel("Sample Value")
plt.ylabel("Conditional Risk")
plt.title("Conditional Risk Distribution")
plt.legend()
plt.grid(True)
plt.show()
