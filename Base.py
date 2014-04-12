#base we need a base package
from time import ctime
class Game(object):
    def __init__(self,pnum,gname=''):
        state=''
        player_num=pnum
        name=gname  #game name
        talk_log=[]# talk_log=[(id,talking)]
    pass
class Player(object):
    "the player may can 'speak'"
    def __init__(self,idnum,st=False):
        cards=[]    #card at hand
        card_hist=[]
        can_act=False #if the player  can do action
        saying=(-1,'')   #present talkind words. say '' at time '-1'
        said=[]    #talking history
        state=st # indicating if the player is in the game
        id=idnum
    
    def add_card(self, card):
        self.cards.append(card)
    def del_card(self, card=None):
        "delete card from cards and add it to card_hist, if card not specified del the last one. if succeed return 0 else -1"
        if card==None:
            self.cards_hist.append(self.cards.pop())
            return 0
        elif:
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
        #act is a function let player to do something
        pass
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