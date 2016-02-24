# BlackJack

This program will be a console game.  There will be another version done in either ios or unity, etc...  Features will be added like logging( file writing ), and hopefully a good A.I.

Atm, the following rules will be in place ( but still being resolved for clarification)

-Dealer shuffles deck(decks)
-dealer distributes cards to player(s) face up
-dealer deals card to himself, face down
-dealer deals second card to player(s) face up
-dealer deals second card to himself, face up
-if dealers second card is an Ace, all players are asked for insurance.
-dealer checks his hand
-insurance payouts are resolved.
-if dealer has BJ, then start new round, otherwise the game proceeds
-if a player has 2 of the same number card, ie, 5 5, they can split.  
-splitting can happen upto 3(subject to change) times but only on first level of split.  Meaning a player cannot split after hitting.
-splits *should* be done before the dealer draws third card.  ie. player sees dealer 2 cards and decides to split, can split again and does, can do one more time but refuses.  No more splitting allowed. Other players get there card, as does dealer. player decides to take action on each of his hand(hit, stand), and then each player does same, as does dealer until completion of round. *note: After going through a few sites, it seems rules for splitting can be different, so I settled on these rules that I wrote.
-players can double on initial hand (first 2 cards dealt) which will automatically make another bet of his bet size as long as they have the money to do it, but will not be able to move forward after round. They will be dealt only 1 card afterwords determing whether they win or lose there betx2 and will be out until the next round. 
-players can double on splits as per doubleing rules
-on all subsequent deals, the players can hit or stand until arriving to a resolution of win/lose
-dealer will stand on 17 (should set an option whether it is Hard17 or soft17[includes Aces]) atm, hard 17 will be the limit
-when the dealer has reached the point where he can no longer draw cards and all players have made there last plays, the round is over. All bets are resolved(including for multiple hands).  All statuses get reset, cards get shuffled and a new round begins.









