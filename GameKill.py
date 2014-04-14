import Base
#===============COUNST=====================
maxwolf=4
maxvillager=10
#=============ERROR=======================
class CardNumError(Base.CardError):
    def __init__(self, word):
        print word + "num can not available"


#=============CLASS=======================
class GM_kill(Base.Game):
    cards=['']
    def __init__(self,pnum=0):
        super(GM_kill, self).__init__(self,pnum,"KillingGame")
        cards.append(MarkerCard("Shrief"))
    def set_max(w, v):
        maxwolf=w
        maxvillager=v
#+++++++++++++++++++++++++++
class Wolf(Base.RoleCard):
    left_wolfs=range(1,maxwolf)
    def __init__(self,wlfnum,whos=None):
        super(Wolf,self).__init__(cardname="Wolf",whos=whos)
        if wlfnum in left_wolfs:
            self.wlfnum=left_wolfs.pop(wlfnum-1)
        else:
            raise CardNumError
    def vote2kill(self,id):
        "vote to kill someone(id)" #send a signal to the host tell and tell other self._whos voted
        pass #only alive can vote
    
    def vote2exc(self,id):
        "vote to exc the killer"
        pass #only alive can vote
#+++++++++++++++++++++++++++
class Villager(Base.RoleCard):
    left_villagers=range(1,maxvillager)
    def __init__(self,vlgnum,whos=None):
        super(Villager,self).__init__(cardname="Villager",whos=whos)
        if vlgnum in left_villagers:
            self.vlgnum=left_villagers.pop(vlgnum-1)
        else:
            raise CardNumError
    def vote2exc(self,id):
        pass #only alive can vote
#++++++++++++++++++++++++++++
class Couple(Base.MarkerCard):
    left_couple=[1,2]
    def __init__(self,num,whos=None):
        super(Coulple,self).__init__(cardname="Couple",whos=whos)
        if num in left_couple:
            self.num=left_couple.pop(num-1)
        else:
            raise CardNumError
    #!here may needs to right a iterator to find who is the lover
    def kill_my_lover(self):
        pass #! shall we public the who are the lovers after death?
#++++++++++++++++++++++++++++

class Prophet(Villager):
    def __init__(self,vlgnum,whos=None):
        super(Prophet,self).__init__(self,vlgnum,whos=whos)
        self.name="Prophet"
        self.roleknown={}
    def what_is_he(pl):
       if pl.id in self.roleknown:
           return False #ask again
       else:
           for card in pl.cards:
               if isinstance(card,Wolf):
                   self.roleknown[pl.id]="Wolf"
                   break
           else:
               self.roleknown[pl.id]="Villager"
           return True
    def i_know_he(self,pl):
        try:
            return self.roleknown[pl.id]
        except KeyError:
            return False


#=========FUNC====================



