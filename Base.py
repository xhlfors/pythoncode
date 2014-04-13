#base we need a base package
from time import ctime
class Game(object):
    def __init__(self,pnum,gname=''):
        self.state=''
        self.player_num=pnum
        self.name=gname  #game name
        self.talk_log=[]# talk_log=[(id,talking)]
    pass



class Player(object):
    "the player may can 'speak'"
    def __init__(self,idnum,st=False):
        self.cards=[]    #card at hand
        self.card_hist=[]
        self.can_act=False #if the player  can do action
        self.saying=(-1,'')   #present talkind words. say '' at time '-1'
        self.said=[]    #talking history
        self.state=st # indicating if the player is in the game
        self.id=idnum
    
    def add_card(self, card):
        self.cards.append(card)
    def del_card(self, card=None):
        "delete card from cards and add it to card_hist, if card not specified del the last one. if succeed return 0 else -1"
        if card==None:
            self.cards_hist.append(self.cards.pop())
        else:
            try:
                i=self.cards.index(card)
            except ValueError:
                return -1
            self.cards_hist.append(self.cards.pop(i))
        return 0

    def get_id(self):
        return self.id
    def get_cardsname(self):
        return [cd.name for cd in self.cards]
    def get_cards_histname(self):
        return [cd.name for cd in self.cards_hist]

    def action(self,act):
        "the player can do some actions for example select cards"
        #act is a function let player to do something suc return 0 else -1
        return act(self)
    pass



class Card(object):
    "the card should can take information and send information"
    actions=[] #the card can do something
    props=[] # the card has some properties  shoud be dictionay
    def __init__(self,cardname):
        name=cardname
        cat='' #card category
    pass

class RoleCard(Card):
    def __init__(self,name):
        super(RoleCard,self).__init__(self,name)
    pass

def open_game(*arg,**argkw):
    "initiate the game by sending cards to players"



if __name__=="__main__":
    print 'biuld succeed'
    p1=Player(idnum=12)
    g1=Game(32)
    g1.player_num
    print p1.id