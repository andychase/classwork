import multiprocessing

from ui import ui

philosopher_names = {
    "Pierre Abélard",
    "Sylviane Agacinski",
    "Pierre d'Ailly",
    "Edmond Fleg",
    "Charles de Montalembert"
}



def think():
    pass


def get_forks():
    pass


def eat():
    pass


def put_forks():
    pass


def philosopher(index, queue_and_name):
    queue, name = queue_and_name
    while True:
        think()
        get_forks()
        eat()
        put_forks()


def main():
    #q = multiprocessing.Queue()
    #p = multiprocessing.Pool(5)
    #result = p.map_async(philosopher, enumerate(zip([q]*5, philosopher_names)))
    ui()


if __name__ == "__main__":
    main()
