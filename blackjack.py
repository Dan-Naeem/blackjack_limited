#****************************************************************
'''
    DN
    BLACKJACK LTD Software
    - python edition
'''
#****************************************************************
from random import randint  #used to generate a random number
#****************************************************************
#prints out the deck, used for debugging
def debug(deck):
    print
    print 'now printing the deck'
    for card in deck:
        print ' card#', card, '==', deck[card]
    print
#****************************************************************

'''
    draw and remove a card from the deck
    return card_face, and card_value

    00 - 12 = Diamond       if suit == 0
    13 - 25 = Clubs         if suit == 1
    26 - 38 = Hearts        if suit == 2
    49 - 51 = Spades        if suit == 3

     0  =  K
     1  =  A
     2  =  2
     3  =  3
     4  =  4
     5  =  5
     6  =  6
     7  =  7
     8  =  8
     9  =  9
    10  = 10
    11  =  J
    12  =  Q
'''
#****************************************************************
def draw_card(deck):
    #create var to store card_face and card_value
    card_face = ''
    card_value = 0
    #draw a card
    random_card = randint(0, 51)
    #enter and stay in loop if card is used
    while deck[random_card] == 1:
        random_card += 7
        #if >= 52, subtract
        if random_card >= 52:
            random_card -= 52
    #once unused card is found, remove from deck
    deck[random_card] = 1
    #find suit and num
    suit = random_card / 13
    num = random_card - suit * 13
    #update card_face and card_value
    #adjust card_face
    if num == 0:           # K
        card_face += 'K'
        card_value += 10
    elif num == 1:         # A
        card_face += 'A'
        card_value += 11
    elif num == 11:        # J
        card_face += 'J'
        card_value += 10
    elif num == 12:        # Q
        card_face += 'Q'
        card_value += 10
    else:                       # 2-10
        card_face += str(num)
        card_value += num
    #adjust suit
    if suit == 0:
        card_face += 'D'
    elif suit == 1:
        card_face += 'C'
    elif suit == 2:
        card_face += 'H'
    elif suit == 3:
        card_face += 'S'
    #return vaues
    return card_face, card_value
#****************************************************************

#****************************************************************
#****************************************************************
#****************************************************************

print '****************************************************************'
print 'START BLACKJACK SIMULATION'
#create an array[52], set all values to 0, this is the deck
deck = {}
for card in range(0, 52):
    #add the cards to the deck, set value = 0
    deck[card] = 0
#now that the deck is set, start the game
#enter while loop
again = 'yes'
while again == 'yes':
    raw_input('press enter to begin')
    #player status values
    player_total = 0
    player_hand = ''
    player_ace = 0
    #dealer status values
    dealer_total = 0
    dealer_hand = ''
    dealer_ace = 0
    dealer_hidden = ''
    #deal 2 cards to the player
    for x in range(2):
        #variables to store values
        card_face = ''
        card_value = 0
        #draw a card
        card_face, card_value = draw_card(deck)
        #if an ace was drawn
        if card_face[0] == 'A':
            #add to ace count
            player_ace += 1
        #add to player_hand
        player_hand += card_face + ' '
        #add to player_total
        player_total += card_value
    #end player for loop
    #display player hand
    print ' >>> Player hand: %s' % (player_hand)
    #check for 21
    if player_total == 21:
        print '*** YOU DREW 21 ***'
    #if 2 aces are drawn
    if player_ace == 2:
        print 'YOU HAVE 2 ACES, GIVING YOUR HAND A TOTAL OF 22'
        print 'ONE ACE WILL BE LOWERED'
        print 'YOUR HAND IS NOW A 12'
        #lower player_total
        player_total = 12
        #lower player_ace
        player_ace = 1
    #deal 2 cards to the dealer, one face down and one face up
    for x in range(2):
        #variables to store values
        card_face = ''
        card_value = 0
        #draw a card
        card_face, card_value = draw_card(deck)
        #if an ace was drawn
        if card_face[0] == 'A':
            #add to count
            dealer_ace += 1
        #hide first card
        if x == 0:
            #add to dealer_hidden
            dealer_hidden = card_face
        #show second
        else:
            #add to dealer_hand
            dealer_hand += card_face + ' '
        #add to dealer_total
        dealer_total += card_value
    #end dealer for loop
    #display dealer hand
    print ' >>> Dealer Hand: ??', dealer_hand
    #if 2 aces are drawn
    if dealer_ace == 2:
        #lower dealer_total
        dealer_total = 12
        #lower dealer_ace
        dealer_ace = 1
    #PLAYER - Hit or Stay
    hit = raw_input('hit or stay: ')
    #enter and stay in hit loop if player wants to hit
    while hit == 'hit':
        #var to store values
        card_face = ''
        card_value = 0
        #draw a card
        card_face, card_value = draw_card(deck)
        #if an ace was drawn
        if card_face[0] == 'A':
            #add to ace count
            player_ace += 1
        #add to player_hand
        player_hand += card_face + ' '
        #add to player_total
        player_total += card_value
        #display player_hand
        print ' >>> Player Hand:', player_hand
        #if player_total > 21
        if player_total > 21:
            #check for an ace
            if player_ace > 0:
                #show value w/ ACE as 11
                print 'THE ACE GIVES YOU A SOFT', player_total
                #lower ace
                player_total -= 10
                #lower ace count
                player_ace -= 1
                #show value w/ ACE as 1
                print 'LOWERING THE ACE TO 1 GIVES YOU', player_total
                hit = raw_input('Hit or Stay: ')
            #else if >21 with no ACE
            else:
                print '*** BUST, GAMEOVER ***'
                break
        #check if player == 21
        elif player_total == 21:
            print '*** YOU DREW 21 ***'
            break
        #else hit or stay
        else:
            hit = raw_input('hit or stay: ')
    #end while
    #continue game if the player hasnt lost
    if player_total < 22:
        #dealer hit or stay [dealer only hits if less than 17]
        while dealer_total < 17:
            print 'Dealer Hits'
            #var to store values
            card_face = ''
            card_value = 0
            #draw a card
            card_face, card_value = draw_card(deck)
            #if an ace was drawn
            if card_face[0] == 'A':
                #add to count
                dealer_ace += 1
            #add to dealer_hand
            dealer_hand += card_face + ' '
            #add to dealer_total
            dealer_total += card_value
            #display dealer_hand
            print ' >>> Dealer Hand: ??', dealer_hand
            #if the dealer busts and has an ace
            if dealer_total > 21 and dealer_ace > 0:
                print 'dealer total > 21 and dealer_ace > 0'
                #lower total
                dealer_total -= 10
                #lower ace count
                dealer_ace -= 1
                print 'dealer ace count is now', dealer_ace
        #end while
        #after exitting the dealer while loop, compare final totals
        raw_input('SHOW ALL HANDS')
        print ' >>> Player Hand %s [%d]' % (player_hand, player_total)
        print ' >>> Dealer Hand %s %s [%d]' % (dealer_hidden, dealer_hand, dealer_total)
        #if dealer goes over 21, player wins
        if dealer_total > 21:
            print '*** PLAYER WINS ***'
        #if dealer > player, dealer wins
        elif dealer_total > player_total:
            print '*** DEALER WINS ***'
        #if dealer matches player, tie
        elif dealer_total == player_total:
            print '*** TIE GAME ***'
        #if dealer < player, player wins
        elif dealer_total < player_total:
            print '*** PLAYER WINS ***'
    #end if
    again = raw_input('Go Again? (yes/no) ')
#end while
print
print 'SIMULATION ENDED'
print '****************************************************************'
