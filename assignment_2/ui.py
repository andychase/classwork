import sys


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
    False: " "
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
    return " ".join(" ".join(_) for _ in zip(fork_display, phi_mapping)) + "  "


def ui(ui_queue):
    while True:
        ui_change = ui_queue.get()
        status_change, index, change = ui_change
        if status_change:
            philosophers[index] = change
            sys.stdout.write("\r")
            sys.stdout.write(get_table())
            sys.stdout.flush()
        else:
            forks[index] = change
