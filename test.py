import Base
import GameKill

a=''
def foo(a,who=''):
    print who
def ffoo(a,who='a'):
    foo(a,who=who)
ffoo(a)