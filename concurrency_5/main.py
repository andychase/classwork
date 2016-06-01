"""
References: http://greenteapress.com/semaphores/downey08semaphores.pdf
"""
import multiprocessing

agentSem = multiprocessing.Semaphore(1)
tobacco = multiprocessing.Semaphore(0)
paper = multiprocessing.Semaphore(0)
match = multiprocessing.Semaphore(0)


def agent1():
    agentSem.acquire()
    print("agent1")
    tobacco.release()
    paper.release()


def agent2():
    agentSem.acquire()
    print("agent2")
    paper.release()
    match.release()


def agent3():
    agentSem.acquire()
    print("agent3")
    tobacco.release()
    match.release()


def make_cigarette(has_message):
    print("Making a cig, already has: {}".format(has_message))
    for i in (agentSem, tobacco, paper, match):
        print(i)
    print("")


def smoke():
    print(":()=~~~")


def smoker1():
    while True:
        with paper:
            if not tobacco.acquire(block=False):
                continue
            else:
                make_cigarette("match")
                tobacco.release()
                agentSem.release()
                smoke()
                return


def smoker2():
    while True:
        with paper:
            if not match.acquire(block=False):
                continue
            else:
                make_cigarette("tobacco")
                match.release()
                agentSem.release()
                smoke()
                return


def smoker3():
    while True:
        with match:
            if not paper.acquire(block=False):
                continue
            else:
                make_cigarette("tobacco")
                paper.release()
                agentSem.release()
                smoke()
                return


def init(*args):
    global agentSem
    global tobacco
    global paper
    global match
    (agentSem, tobacco, paper, match) = args


def main():
    init_args = (agentSem, tobacco, paper, match)
    pool = multiprocessing.Pool(6, initializer=init, initargs=init_args)

    pool.apply_async(agent1)
    # pool.apply_async(agent2)
    # pool.apply_async(agent3)
    pool.apply_async(smoker1)
    # pool.apply_async(smoker2)
    # pool.apply_async(smoker3)
    pool.close()
    pool.join()


if __name__ == "__main__":
    main()
