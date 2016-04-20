use_ascii = True

if use_ascii:
    face = " =]"
    thinking = "THK"
    eating = "EAT"
    fork_icon = "Y"
else:
    face = "😀"
    thinking = "🤔"
    eating = "😖"
    fork_icon = "🍴"

philosophers = [
    "nothing",
    "nothing",
    "nothing",
    "nothing",
    "nothing"
]

philosopher_mapping = {
    "nothing": face,
    "eating": eating,
    "thinking": thinking
}

fork_mapping = {
    True: fork_icon,
    False: ""
}

forks = [
    True,
    True,
    True,
    True,
    True,
]


def get_table():
    fork_display = [fork_mapping[fork] for fork in forks]
    phi_mapping = [philosopher_mapping[i] for i in philosophers]
    last_fork = "  {}".format(fork_mapping[forks[-1]])
    return " ".join(" ".join(_) for _ in zip(fork_display, phi_mapping)) + last_fork


def ui():
    print(get_table())
