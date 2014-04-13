import Base
#====================================
maxwolf=4
#====================================
class CardnNumError(CardError):
    def __init__(self, word):
        print word + "num can not available"


#====================================
class GM_kill(Base.Game):
    cards=['']
    def __init__(self,pnum=0):
        super(GM_kill, self).__init__(self,pnum,"KillingGame")
        cards.append(MarkerCard("Shrief"))
#+++++++++++++++++++++++++++
class Wolf(RoleCard):
    left_wolfs=range(1,maxwolf)
    def __init__(self,wlfnum):
        super(Wolf,self).__init__(cardname="Wolf")
        if wlfnum in left_wolfs:
            self.wolfnum=left_wolfs.pop(wolfnum-1)
        else:
            raise CardnNumError
