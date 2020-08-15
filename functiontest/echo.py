#!/usr/bin/python3

import os
import multiprocessing as mp


def server():
    print("start server ...")
    os.system("../echoserver 127.0.0.1 5000")



def client():
    print("start client ...")
    os.system("../hello 127.0.0.1 5000")


if __name__ == "__main__":

    # mp.set_start_method('spawn')
    s = mp.Process(target=server)
    c = mp.Process(target=client)
    s.start()
    c.start

    s.join()
    c.join()
    print ("exit main thread")
    pass