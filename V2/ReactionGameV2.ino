//Button Pins
const int leftPlayerButton = 8;
const int rightPlayerButton = 12;
const int resetButton = 5;

//LED Pins
const int reactionLed = 10;
const int leftPlayerLed = 9;
const int rightPlayerLed = 11;
const int leftPlayerScoreLed1 = 3;
const int leftPlayerScoreLed2 = 4;
const int rightPlayerScoreLed1 = 7;
const int rightPlayerScoreLed2 = 6;

//Variables
int minTime = 10;
int maxTime = 50;
unsigned long ledOnTime;

int leftButtonState;
int rightButtonState;
int resetButtonState;
int reactionLedState;

bool gameStart;
int leftPlayerScore;
int rightPlayerScore;

int randomNum;

void setup() {
  startup();
  leftPlayerScore = 0;
  rightPlayerScore = 0;
  // put your setup code here, to run once:
  //Sets the random seed to generate the random numbers
  randomSeed(analogRead(0));
  //Sets the button pins to input mode
  pinMode(leftPlayerButton, INPUT);
  pinMode(rightPlayerButton, INPUT);
  pinMode(resetButton, INPUT);
  //Sets the LED pins to output mode
  pinMode(reactionLed,OUTPUT);
  pinMode(leftPlayerLed,OUTPUT);
  pinMode(rightPlayerLed,OUTPUT);
  pinMode(leftPlayerScoreLed1,OUTPUT);
  pinMode(leftPlayerScoreLed2,OUTPUT);
  pinMode(rightPlayerScoreLed1,OUTPUT);
  pinMode(rightPlayerScoreLed2,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(resetButton) == HIGH){
    digitalWrite(reactionLed, LOW);
    reactionLedState = LOW;
    digitalWrite(leftPlayerLed, LOW);
    digitalWrite(rightPlayerLed, LOW);
    setTime();
    gameStart = true;
  }
  if (gameStart == true){
    game(ledOnTime);
  }

}

void game(int ledOnTime) {
  if (millis() == ledOnTime){
    digitalWrite(reactionLed, HIGH);
      reactionLedState = HIGH;
  }
  leftButtonState = digitalRead(leftPlayerButton);
  rightButtonState = digitalRead(rightPlayerButton);
  if (reactionLedState == HIGH && leftButtonState == HIGH){
    playerScore("left");
    score();
  }
  if (reactionLedState == HIGH && rightButtonState == HIGH){
    playerScore("right");
    score();
  }
  if (reactionLedState == LOW && leftButtonState == HIGH){
    playerMiss("left");
    score();
  }
  if (reactionLedState == LOW && rightButtonState == HIGH){
    playerMiss("right");
    score();
  }
}

void setTime() {
  randomNum = random(minTime, maxTime);
  ledOnTime = millis() + (randomNum * 100);
  Serial.println(ledOnTime);
}

void playerMiss(String player){
  gameStart = false;
  if (player == "left"){
    digitalWrite(leftPlayerLed, HIGH);
    Serial.println("LEFT LED ON");
    leftPlayerScore = 0;
    Serial.println(rightPlayerScore);
    Serial.println(leftPlayerScore);
  }else if (player == "right"){
    digitalWrite(rightPlayerLed, HIGH);
    Serial.println("RIGHT LED ON");
    rightPlayerScore = 0;
    Serial.println(rightPlayerScore);
    Serial.println(leftPlayerScore);
  }
}

void playerScore(String player){
  gameStart = false;
  if (player == "left"){
    leftPlayerScore = leftPlayerScore +1;
    rightPlayerScore = 0;
  }else if (player == "right"){
    rightPlayerScore = rightPlayerScore +1;
    leftPlayerScore = 0;
  }
}

void score() {
  if (leftPlayerScore == 0){
    digitalWrite(leftPlayerScoreLed1, LOW);
    digitalWrite(leftPlayerScoreLed2, LOW);
  }
  if (leftPlayerScore == 1){
    digitalWrite(leftPlayerScoreLed1, HIGH);
    digitalWrite(leftPlayerScoreLed2, LOW);
  }
  if (leftPlayerScore == 2){
    digitalWrite(leftPlayerScoreLed1, LOW);
    digitalWrite(leftPlayerScoreLed2, HIGH);
  }
  if (leftPlayerScore == 3){
    winner("left");
  }
  if (rightPlayerScore == 0){
    digitalWrite(rightPlayerScoreLed1, LOW);
    digitalWrite(rightPlayerScoreLed2, LOW);
  }
  if (rightPlayerScore == 1){
    digitalWrite(rightPlayerScoreLed1, HIGH);
    digitalWrite(rightPlayerScoreLed2, LOW);
  }
  if (rightPlayerScore == 2){
    digitalWrite(rightPlayerScoreLed1, LOW);
    digitalWrite(rightPlayerScoreLed2, HIGH);
  }
  if (rightPlayerScore == 3){
    winner("right");
  }
}

void startup(){
  //Test mainboard LEDs
  mainboardTest();
  
  //Test Scoreboard LEDs
  scoreboardTest();
}

void mainboardTest(){
  //Test mainboard LEDs
  digitalWrite(leftPlayerLed, HIGH);
  delay(200);
  digitalWrite(leftPlayerLed, LOW);
  digitalWrite(reactionLed, HIGH);
  delay(200);
  digitalWrite(reactionLed, LOW);
  digitalWrite(rightPlayerLed, HIGH);
  delay(200);
  digitalWrite(rightPlayerLed, LOW);
}

void scoreboardTest(){
  digitalWrite(leftPlayerScoreLed1, HIGH);
  delay(200);
  digitalWrite(leftPlayerScoreLed1, LOW);
  digitalWrite(leftPlayerScoreLed2, HIGH);
  delay(200);
  digitalWrite(leftPlayerScoreLed2, LOW);
  digitalWrite(rightPlayerScoreLed2, HIGH);
  delay(200);
  digitalWrite(rightPlayerScoreLed2, LOW);
  digitalWrite(rightPlayerScoreLed1, HIGH);
  delay(200);
  digitalWrite(rightPlayerScoreLed1, LOW);
}

void winner(String player){
  if (player == "left"){
    while (true){
      digitalWrite(leftPlayerScoreLed1, HIGH);
      delay(50);
      digitalWrite(leftPlayerScoreLed1, LOW);
      digitalWrite(leftPlayerScoreLed2, HIGH);
      delay(50);
      digitalWrite(leftPlayerScoreLed2, LOW);
    }
  }
  if (player == "right"){
    while (true){
      digitalWrite(rightPlayerScoreLed1, HIGH);
      delay(50);
      digitalWrite(rightPlayerScoreLed1, LOW);
      digitalWrite(rightPlayerScoreLed2, HIGH);
      delay(50);
      digitalWrite(rightPlayerScoreLed2, LOW);
    }
  }
}
