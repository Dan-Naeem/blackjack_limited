/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> 
// <><><><><><><><> <><><><><><><><>                                   <><><><><><><><> 
// <><><><><><><><> <><><><><><><><>            LCD DISPLAY            <><><><><><><><> 
// <><><><><><><><> <><><><><><><><>                                   <><><><><><><><> 
// <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> 

//lcd functions
void clearline1()
{
  lcd.setCursor(0,0);
  lcd.print("                ");
}

void clearline2()
{
  lcd.setCursor(0,1);
  lcd.print("                ");  
}

void clearall()
{
  clearline1();
  clearline2();
}

void firstline()
{
  lcd.setCursor(0,0);
}

void secondline()
{
  lcd.setCursor(0,1);
}

//wait for 1 sec
void wait1()
{
  delay(1000);
}

//wait for 2 secs
void wait2()
{
  delay(2000);
}

//display Dealer Hits
void dealer_hits()                                                    //<><><><><><><><><><><><>
{
  clearall();
  firstline();
  lcd.print("     DEALER     ");
  secondline();
  lcd.print("      HITS      ");
}

//display current state of game, display both hands
void current_state(String player_hand, String dealer_hand)
{
  clearall();
  firstline();
  lcd.print(player_hand);
  secondline();
  lcd.print("X");
  lcd.setCursor(2,1);
  lcd.print(dealer_hand);
}

//show all hands
void show_all(String player_hand, String dealer_hidden, String dealer_hand)
{
  clearall();
  firstline();
  lcd.print(player_hand);
  secondline();
  lcd.print(dealer_hidden);
  lcd.setCursor(1,1);
  lcd.print(dealer_hand);
}

//lose animation
void lose_animation()
{
  clearall();
  firstline();
  lcd.print("  **  YOU  **  ");
  secondline();
  lcd.print("  **  LOSE  **  ");
}

//win animation
void win_animation()
{
  clearall();
  firstline();
  lcd.print("  **  YOU  **  ");
  secondline();
  lcd.print("  **  WIN  **  ");
}

//tie game animation
void tie_animation()
{
  clearall();
  firstline();
  lcd.print("  **  TIE  **  ");
  secondline();
  lcd.print("  **  GAME  **  ");
}

// <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> 
// <><><><><><><><> <><><><><><><><>                                   <><><><><><><><> 
// <><><><><><><><> <><><><><><><><>           BUTTON INPUT            <><><><><><><><> 
// <><><><><><><><> <><><><><><><><>                                   <><><><><><><><> 
// <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> 

//setup button pins
const int leftButton = 13;      //input for no
const int rightButton = 8;      //input for yes


//initialize player response variables
int no = 0;                  //responds to leftButton
int yes = 0;                 //responds to rightButton

//reset player responses
void reset_response()
{
    no = 0;
    yes = 0;
}

//wait for players response, reset after recieving input
int response()
{
  while (no == 0 && yes == 0)
  {
    //check for input
    no = digitalRead(leftButton);
    yes = digitalRead(rightButton);
    //if input was recieved
    if (no == 1 || yes == 1)
    {
      //break from while loop
      break;
    }
  }
  //return player's response
  if (no == 1)
  {
    reset_response();
    return 0;
  }
  else if (yes == 1)
  {
    reset_response();
    return 1;
  }
}

// <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> 
// <><><><><><><><> <><><><><><><><>                                   <><><><><><><><> 
// <><><><><><><><> <><><><><><><><>             BLACKJACK             <><><><><><><><> 
// <><><><><><><><> <><><><><><><><>                                   <><><><><><><><> 
// <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> 

//create an array[52], this is your deck of cards
char deck[52];

//function that draws and removes a card from the deck
void draw_card(String &card_face, int &card_value)
{
  //draw a card
  int random_card = random(0,52);
  //enter and stay in loop if card is used
  while (deck[random_card] == '1')
  {
    random_card++;
    if (random_card >= 52)
    {
      random_card -= 52;
    }//end if
  }//end while
  //once unused card is found, remove from deck
  deck[random_card] = '1';
  //find suit and num
  int suit = random_card / 13;
  int num = random_card - suit * 13;
  //adjust card_face
  if (num == 0)             // K
  {
    card_face += "K";
    card_value += 10;
  }
  else if (num == 1)        // A
  {
    card_face += "A";
    card_value += 11;
  }
  else if (num == 2)        // 2
  {
    card_face += "2";
    card_value += num;
  }
  else if (num == 3)        // 3
  {
    card_face += "3";
    card_value += num;
  }
  else if (num == 4)        // 4
  {
    card_face += "4";
    card_value += num;
  }
  else if (num == 5)        // 5
  {
    card_face += "5";
    card_value += num;
  }
  else if (num == 6)        // 6
  {
    card_face += "6";
    card_value += num;
  }
  else if (num == 7)        // 7
  {
    card_face += "7";
    card_value += num;
  }
  else if (num == 8)        // 8
  {
    card_face += "8";
    card_value += num;
  }
  else if (num == 9)        // 9
  {
    card_face += "9";
    card_value += num;
  }
  else if (num == 10)        // 10
  {
    card_face += "10";
    card_value += num;
  }
  else if (num == 11)       // J
  {
    card_face += "J";
    card_value += 10;
  }
  else if (num == 12)       // Q
  {
    card_face += "Q";
    card_value += 10;
  }
  //remove suit
  /*
  //adjust suit
  if (suit == 0)        // Diamonds
  {
    card_face += "D";
  }
  else if (suit == 1)   // Clubs
  {
    card_face += "C";
  }
  else if (suit == 2)   // Hearts
  {
    card_face += "H";
  }
  else if (suit == 3)   //Spades
  {
    card_face += "S";
  }
  */
  //values passed by reference have been altered
}

// <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> 
// <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> 
// <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> <><><><><><><><> 

void setup() 
{
  //short delay (2 seconds)
  wait2();
  
  //intialize the button pins as inputs
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // Print a message to the LCD.
  firstline();
  lcd.print("  Welcome to   ") ;
  secondline();
  lcd.print(" BlackJack Ltd ");
  
  //short delay
  wait1();
}

void loop() 
{
  //clear screen
  clearall();
  wait1();

  //start screen
  firstline();
  lcd.print ("   PRESS ANY    ");
  secondline();
  lcd.print(" BUTTON TO PLAY ");

  //wait for response
  response();
  clearall();
  wait1();

  //setting up deck
  firstline();
  lcd.print("   SHUFFLING   ");
  secondline();
  lcd.print("      DECK      ");
  wait1();
  
  //go thru the deck, make every card '0'
  for (int i = 0; i < 52; i++)
  {
    deck[i] = '0';
  }
  
  //create player status values
  int player_total = 0;
  String player_hand = "";
  int player_ace = 0;
  
  //dealer status values
  int dealer_total = 0;
  String dealer_hand = "";
  int dealer_ace = 0;
  String dealer_hidden = "";

  //deal 2 cards to the player
  for (int i = 0; i < 2; i++ )
  {
    //variables to store values
    String card_face = "";
    int card_value = 0;
    
    //draw a card
    draw_card(card_face, card_value);
    
    //if an ace was drawn
    if (card_face[0] == 'A')
    {
      //addto ace count
      player_ace++;
    }

    //add to player hand and total
    player_hand += card_face;
    player_total += card_value;    
  }//end player for loop

  //display player hand
  clearall();
  wait1();
  firstline();
  lcd.print("YOUR HAND");
  secondline();
  lcd.print(player_hand);
  wait2();
  
  //check for 21
  if (player_total == 21)
  {
    clearall();
    firstline();
    lcd.print("* YOU DREW 21 *");
  }

  //if 2 aces are drawn
  if (player_ace == 2)
  {
    //display message when 2 ACES are drawn
    clearall();
    firstline();
    lcd.print("2 ACES");
    secondline();
    lcd.print("PROTOCOL");

    //lower player total
    player_total = 12;
    //lower player ace
    player_ace = 1;
  }

  //deal 2 cards to the dealer
  for (int i = 0; i < 2; i++)
  {
    //variables to store values
    String card_face = "";
    int card_value = 0;

    //draw a card
    draw_card(card_face, card_value);

    //if an ace was drawn
    if (card_face[0] == 'A')
    {
      //add to ace count
      dealer_ace++;
    }

    //hide first card
    if (i == 0)
    {
      //add to dealer hidden
      dealer_hidden = card_face;
    }
    //show second card
    else
    {
      //add to dealer hand
      dealer_hand += card_face;
    }

    //add to dealer total
    dealer_total += card_value;
  }//end dealer for loop

  //display dealer hand
  clearall();
  wait1();
  firstline();
  lcd.print("DEALER HAND");
  secondline();
  lcd.print("X");
  lcd.setCursor(2,1);
  lcd.print(dealer_hand);
  wait2();

  //if 2 aces are drawn
  if (dealer_ace == 2)
  {
    //lower dealer total
    dealer_total = 12;
    //lower dealer ace
    dealer_ace = 1;
  }

  //set up visuals
  clearall();
  wait1();
  firstline();
  // 10D10C<---PLAYER
  lcd.print(player_hand);
  lcd.setCursor(5,0);
  lcd.print("<--- PLAYER");
  secondline();
  // DEALER--->XX 10S
  lcd.print("DEALER --->");
  lcd.setCursor(13,1);
  lcd.print("X");
  lcd.setCursor(14,1);
  lcd.print(dealer_hand);
  wait2();

  //ask to hit (hit or stay message)
  firstline();
  lcd.setCursor(5,0);
  lcd.print("           ");
  secondline();
  lcd.print("           ");
  wait1();
  secondline();
  lcd.print("STAY/HIT");

  //player hit or stay
  int hit = response();

  //enter and stay in while loop if player wants to hit
  while (hit == 1)
  {
    //show HIT (hit message)
    wait1();
    secondline();
    lcd.print("          ");
    secondline();
    lcd.print(" > HIT <  ");
    wait1();

    //reset HIT
    hit = 0;
    
    //var to store values
    String card_face = "";
    int card_value = 0;

    //draw a card
    draw_card(card_face, card_value);

    //if an ace was drawn
    if (card_face[0] == 'A')
    {
      //add to player ace
      player_ace += 1;
    }

    //add to player hand and total
    player_hand += card_face ;
    player_total += card_value;

    //display player hand
    firstline();
    lcd.print(player_hand);

    //if player total > 21
    if (player_total > 21)
    {
      //check for an ace
      if (player_ace > 0)
      {
        //show value w/ ACE as 11
        // "THE ACE GIVE YOU A SOFT", PLAYER TOTAL
        // "SOFT HAND LOWERED"
        // "ACE LOWERED"

        //lower ace
        player_total -= 10;
        
        //lower ace count
        player_ace--;

        //show value w/ ACE as 1
        // print "LOWER THE ACE TO 1 GIVES YOU", player_total

        //hit or stay
        wait1();
        secondline();
        lcd.print("          ");
        wait1();
        secondline();
        lcd.print("STAY/HIT");
        hit = response();
      }
    
      //else if >21 with no ACE
      else
      {
        //print BUST, GAMEOVER
        wait1();
        secondline();
        lcd.print("          ");
        wait1();
        secondline();
        lcd.print(" > BUST <");
        wait1();

        //lose animation
        lose_animation();
        
        //break
        break;
      }
    }//end > 21

    //check if player == 21
    else if (player_total == 21)
    {
      //print "YOU DREW 21"
      clearall();
      firstline();
      lcd.print(" ** YOU DREW ** ");
      secondline();
      lcd.print("  ***  21  ***  ");
      // break;
      break;
    }

    //else hit or stay
    else
    {
      //hit or stay
      wait1();
      secondline();
      lcd.print("          ");
      wait1();
      secondline();
      lcd.print("STAY/HIT");
      hit = response();
    }
  }//end player while HIT == 1
  
  //if < 22 && if stay (display stay message)
  if (player_total < 22)
  {
    if (hit == 0)
    {
      wait1();
      secondline();
      lcd.print("          ");
      secondline();
      lcd.print(" > STAY < ");
    }
  }  

  wait1();

  //show current state                                                
  current_state(player_hand, dealer_hand);

  wait2();
  wait2();

  //continue game if player hasnt lost
  if (player_total < 22)
  {
    //dealer hit or stay [ dealer only hits if < 17]
    while (dealer_total < 17)
    {
      // print dealer hits                                                
      dealer_hits();

      wait2();

      //var to store values
      String card_face = "";
      int card_value = 0;

      //draw card
      draw_card(card_face, card_value);

      //if an ace was drawn
      if (card_face[0] == 'A')
      {
        //add to daeler count
        dealer_ace++;
      }

      //add to dealer hand and total
      dealer_hand += card_face;
      dealer_total += card_value;

      //display dealer hand
      current_state(player_hand, dealer_hand);

      wait2();
      wait2();

      //if the dealer busts and has an ACE
      if (dealer_total > 21 && dealer_ace > 0)
      {
        //lower total
        dealer_total -= 10;
        //lower ace count
        dealer_ace -= 1;
      }
    }//end dealer while

    //after exiting the dealer while loop, compare final totals
    // print SHOWING ALL AHNDS
    clearall();
    firstline();
    lcd.print("     SHOWING");
    secondline();
    lcd.print("     ALL HANDS");
    wait2();
    wait1();

    //show_hands
    show_all(player_hand, dealer_hidden, dealer_hand);

    wait2();
    wait2();

    //if dealer > 21, player wins
    if (dealer_total > 21)
    {
      win_animation();
    }
    //if dealer > player, dealer wins
    else if (dealer_total > player_total)
    {
      lose_animation();
    }
    //if dealer matches player, tie
    else if (dealer_total == player_total)
    {
      tie_animation();
    }
    //if dealer < player, playes wins
    else if (dealer_total < player_total)
    {
      win_animation();
    }
  }

  wait2();
  
/*
 * END OF GAME
 * LOOP AROUND
 */

  
}

