import multiprocessing
import random

import time

from ui import ui

philosopher_names = {
    "Pierre Abélard",
    "Sylviane Agacinski",
    "Pierre d'Ailly",
    "Edmond Fleg",
    "Charles de Montalembert"
}

forks = []
ui_queue = None


def think(index):
    ui_queue.put((True, index, "thinking"))
    time.sleep(random.randint(1, 20))


def modify_forks(index, put_down=False):
    ui_queue.put((False, index, put_down))
    if index == 4:
        ui_queue.put((False, 0, put_down))
    else:
        ui_queue.put((False, index + 1, put_down))


def get_forks(left_fork, right_fork, index):
    while True:
        left_fork.acquire(True)
        if right_fork.acquire(False):
            modify_forks(index, put_down=False)
            return
        else:
            left_fork.release()
            time.sleep(1)


def eat(index):
    ui_queue.put((True, index, "eating"))
    time.sleep(random.randint(2, 9))


def put_forks(left_fork, right_fork, index):
    modify_forks(index, put_down=True)
    left_fork.release()
    right_fork.release()


def philosopher(index_name):
    index, name = index_name
    left_fork = forks[index]
    if index == 4:
        right_fork = forks[0]
    else:
        right_fork = forks[index + 1]

    while True:
        think(index)
        ui_queue.put((True, index, "nothing"))
        get_forks(left_fork, right_fork, index)
        eat(index)
        put_forks(left_fork, right_fork, index)


def init(f, q):
    global forks
    global ui_queue
    forks = f
    ui_queue = q


def main():
    f = [multiprocessing.Lock() for _ in range(5)]
    q = multiprocessing.Queue()

    pool = multiprocessing.Pool(5, initializer=init, initargs=(f, q))

    pool.map_async(philosopher, enumerate(philosopher_names))
    ui(q)


if __name__ == "__main__":
    main()
