"""
Andy Chase
OS2 Concurrency 5

References: http://greenteapress.com/semaphores/downey08semaphores.pdf
"""
import traceback
import functools
import multiprocessing
import sys
from time import sleep

smoking_ascii = """
                   )
                  (
      _ ___________ )
     [_[___________#   jgs
"""


def trace_unhandled_exceptions(func):
    """
    From: https://stackoverflow.com/questions/6728236/exception-thrown-in-multiprocessing-pool-not-detected
    """

    @functools.wraps(func)
    def wrapped_func(*args, **kwargs):
        try:
            func(*args, **kwargs)
        except:
            print('Exception in ' + func.__name__)
            traceback.print_exc()

    return wrapped_func


agentSem = multiprocessing.Semaphore(1)
tobacco = multiprocessing.Semaphore(0)
paper = multiprocessing.Semaphore(0)
match = multiprocessing.Semaphore(0)
q = multiprocessing.Queue(1)


def make_cigarette(smoker, has_message):
    q.put("{} making a cig, already has: {}".format(smoker, has_message))


def smoke():
    sleep(1)


@trace_unhandled_exceptions
def agent1():
    while True:
        agentSem.acquire()
        q.put("agent1 placing tobacco and paper")
        tobacco.release()
        paper.release()


@trace_unhandled_exceptions
def agent2():
    while True:
        agentSem.acquire()
        q.put("agent2 placing paper and match")
        paper.release()
        match.release()


@trace_unhandled_exceptions
def agent3():
    while True:
        agentSem.acquire()
        q.put("agent3 placing tobacco and match")
        tobacco.release()
        match.release()


@trace_unhandled_exceptions
def smoker1():
    while True:
        paper.acquire()
        if not tobacco.acquire(block=False):
            paper.release()
            continue
        else:
            make_cigarette("smoker1", "match, acquired: paper, tobacco")
            agentSem.release()
            smoke()


@trace_unhandled_exceptions
def smoker2():
    while True:
        match.acquire()
        if not paper.acquire(block=False):
            match.release()
            continue
        else:
            make_cigarette("smoker2", "tobacco, acquired: match, paper")
            agentSem.release()
            smoke()


@trace_unhandled_exceptions
def smoker3():
    while True:
        match.acquire()
        if not tobacco.acquire(block=False):
            match.release()
            continue
        else:
            make_cigarette("smoker3", "paper, acquired: tobacco, match")
            agentSem.release()
            smoke()


@trace_unhandled_exceptions
def ui_queue():
    while True:
        print(q.get())


def init(*args):
    global agentSem
    global tobacco
    global paper
    global match
    global q
    (agentSem, tobacco, paper, match, q) = args


def main():
    q = multiprocessing.Queue()
    init_args = (agentSem, tobacco, paper, match, q)
    pool = multiprocessing.Pool(7, initializer=init, initargs=init_args)

    pool.apply_async(agent1)
    pool.apply_async(agent2)
    pool.apply_async(agent3)
    pool.apply_async(smoker1)
    pool.apply_async(smoker2)
    pool.apply_async(smoker3)
    pool.apply_async(ui_queue)
    pool.close()
    pool.join()


if __name__ == "__main__":
    main()
