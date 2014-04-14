import Base
import GameKill


a={1:10}


def i_know_he(a):
    try:
        return a[2]
    except KeyError:
        return False

print i_know_he(a)