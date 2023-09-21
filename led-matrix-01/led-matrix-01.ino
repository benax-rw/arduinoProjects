int velFrame = 25; //NUMBER OF TIMES THE FRAME WILL BE REPEATED
int pauseDelay = 500; //TIME INTERVAL BETWEEN ROWS

char msgDisplay[] = " I @ RWANDA "; // MESSAGE THAT WILL BE DISPLAYED BY THE MATRIX

//Variables used for scrolling both start at 0
int index = 0; // CURRENT CHARACTER IN THE STRING THAT IS BEING SHOWN
int offset = 0; // QUANTITY OF OFFSET COLUMNS

int rowA[] = {13,8,A3,10,5,A2,4,A0}; //THE ROWS ARE COMMON ANODE
int colA[] = {9,3,2,12,A1,11,7,6}; //THE COLUMNS ARE COMMON CATHODE

//CONSTANTS DEFINE EACH CHARACTER POSITION IN AN ARRAY OF INTEGER (LETTERS)
const int A = 0;
const int B = 1;
const int C = 2;
const int D = 3;
const int E = 4;
const int F = 5;
const int G = 6;
const int H = 7;
const int I = 8;
const int J = 9;
const int K = 10;
const int L =11;
const int M = 12;
const int N = 13;
const int O = 14;
const int P = 15;
const int Q =16;
const int R = 17;
const int S = 18;
const int T = 19;
const int U = 20;
const int V =21;
const int W = 22;
const int X = 23;
const int Y = 24;
const int Z = 25;

//PUNCTUATION
const int COL =26;
const int DASH = 27;
const int BRA2 = 28;
const int _ = 29;
const int LINE = 34;
const int DOT =36;

// EXTRA CHARACTERS
const int FULL =30;
const int CHECK = 31;
const int B2 = 32;
const int TEMP = 33;
const int FACE = 35;
const int COLDOT = 37;
const int HEART = 38;

//MATRIX USED TO STORE A MAP OF BITS TO BE SHOWN / CAN BE CHANGED IF YOU WANT TO USE ANOTHER MAP
byte data[] = {0,0,0,0,0,0,0,0};

//EACH CHARACTER IS AN 8X7 BITMAP WHERE 1 IS ON AND 0 IS OFF
const int _A[] = {B0001000,
                  B0010100,
                  B0100010,
                  B1000001,
                  B1111111,
                  B1000001,
                  B1000001,
                  B0000000};

const int _B[] = {B1111110,
                  B0100001,
                  B0100001,
                  B0111110,
                  B0100001,
                  B0100001,
                  B1111110,
                  B0000000};

const int _C[] = {B0011111,
                  B0100000,
                  B1000000,
                  B1000000,
                  B1000000,
                  B0100000,
                  B0011111,
                  B0000000};

const int _D[] = {B1111100,
                  B0100010,
                  B0100001,
                  B0100001,
                  B0100001,
                  B0100010,
                  B1111100,
                  B0000000};

const int _E[] = {B1111111,
                  B1000000,
                  B1000000,
                  B1111100,
                  B1000000,
                  B1000000,
                  B1111111,
                  B0000000};

const int _F[] = {B1111111,
                  B1000000,
                  B1000000,
                  B1111100,
                  B1000000,
                  B1000000,
                  B1000000,
                  B0000000};

const int _G[] = {B0011111,
                  B0100000,
                  B1000000,
                  B1001111,
                  B1000001,
                  B0100001,
                  B0011111,
                  B0000000};

const int _H[] = {B1000001,
                  B1000001,
                  B1000001,
                  B1111111,
                  B1000001,
                  B1000001,
                  B1000001,
                  B0000000};

const int _I[] = {B1111111,
                  B0001000,
                  B0001000,
                  B0001000,
                  B0001000,
                  B0001000,
                  B1111111,
                  B0000000};

const int _J[] = {B0001111,
                  B0000001,
                  B0000001,
                  B0000001,
                  B0000001,
                  B1000001,
                  B0111110,
                  B0000000};

const int _K[] = {B1000011,
                  B1000100,
                  B1001000,
                  B1110000,
                  B1001000,
                  B1000100,
                  B1000011,
                  B0000000};

const int _L[] = {B1000000,
                  B1000000,
                  B1000000,
                  B1000000,
                  B1000000,
                  B1000000,
                  B1111111,
                  B0000000};

const int _M[] = {B1110110,
                  B1001001,
                  B1001001,
                  B1001001,
                  B1001001,
                  B1001001,
                  B1001001,
                  B0000000};

const int _N[] = {B1000001,
                  B1100001,
                  B1010001,
                  B1001001,
                  B1000101,
                  B1000011,
                  B1000001,
                  B0000000};

const int _O[] = {B0011100,
                  B0100010,
                  B1000001,
                  B1001001,
                  B1000001,
                  B0100010,
                  B0011100,
                  B0000000};

const int _P[] = {B1111110,
                  B0100001,
                  B0100001,
                  B0111110,
                  B0100000,
                  B0100000,
                  B0100000,
                  B0000000};

const int _Q[] = {B0011100,
                  B0100010,
                  B1000001,
                  B1000001,
                  B1000101,
                  B0100010,
                  B0011101,
                  B0000000};

const int _R[] = {B1111110,
                  B0100001,
                  B0100001,
                  B0101110,
                  B0100100,
                  B0100010,
                  B0100001,
                  B0000000};

const int _S[] = {B0111111,
                  B1000000,
                  B1000000,
                  B0111110,
                  B0000001,
                  B0000001,
                  B1111110,
                  B0000000};

const int _T[] = {B1111111,
                  B0001000,
                  B0001000,
                  B0001000,
                  B0001000,
                  B0001000,
                  B0001000,
                  B0000000};

const int _U[] = {B1000001,
                  B1000001,
                  B1000001,
                  B1000001,
                  B1000001,
                  B1000001,
                  B0111110,
                  B0000000};

const int _V[] = {B1000001,
                  B1000001,
                  B1000001,
                  B1000001,
                  B0100010,
                  B0010100,
                  B0001000,
                  B0000000};
                  
const int _W[] = {B1000001,
                  B1001001,
                  B1001001,
                  B1001001,
                  B1001001,
                  B1001001,
                  B0110110,
                  B0000000};

const int _X[] = {B1000001,
                  B0100010,
                  B0010100,
                  B0001000,
                  B0010100,
                  B0100010,
                  B1000001,
                  B0000000};

const int _Y[] = {B1000001,
                  B0100010,
                  B0010100,
                  B0001000,
                  B0001000,
                  B0001000,
                  B0001000,
                  B0000000};

const int _Z[] = {B1111111,
                  B0000010,
                  B0000100,
                  B0111110,
                  B0010000,
                  B0100000,
                  B1111111,
                  B0000000};

const int _COL[] = {B0000000,
                    B0011000,
                    B0011000,
                    B0000000,
                    B0011000,
                    B0011000,
                    B0000000,
                    B0000000};

const int _DASH[] = {B0000000,
                     B0000000,
                     B0000000,
                     B0111110,
                     B0000000,
                     B0000000,
                     B0000000,
                     B0000000};

const int _BRA2[] = {B0010000,
                     B0001000,
                     B0000100,
                     B0000100,
                     B0001000,
                     B0010000,
                     B0000000,
                     B0000000};                  

const int __[] = {B0000000,
                  B0000000,
                  B0000000,
                  B0000000,
                  B0000000,
                  B0000000,
                  B0000000,
                  B0000000};

const int _FULL[] = {B1111111,
                     B1111111,
                     B1111111,
                     B1111111,
                     B1111111,
                     B1111111,
                     B1111111,
                     B0000000};                  

const int _CHECK[] = {B1010101,
                      B0101010,
                      B1010101,
                      B0101010,
                      B1010101,
                      B0101010,
                      B1010101,
                      B0000000};
                  
const int _B2[] = {B0111110,
                   B0000001,
                   B0000001,
                   B0001111,
                   B0000001,
                   B1000001,
                   B0111110,
                   B0000000};

const int _TEMP[] = {B0000011,
                     B0011111,
                     B0111111,
                     B1111110,
                     B1111111,
                     B0011111,
                     B0000011,
                     B0000000};

const int _LINE[] = {B0000001,
                     B0000001,
                     B0000001,
                     B0000001,
                     B0000001,
                     B0000001,
                     B0000001,
                     B0000000};                     
                 
const int _FACE[] = {B0011100,
                  B0100010,
                  B1010101,
                  B1000001,
                  B1001001,
                  B0100010,
                  B0011100,
                  B0000000};                    
                  

const int _DOT[] = {B0000000,
                    B0000000,
                    B0000000,
                    B0000000,
                    B1100000,
                    B1100000,
                    B0000000,
                    B0000000};                     
                  
const int _COLDOT[] = {B0000000,
                       B0110000,
                       B0110000,
                       B0000000,
                       B0110011,
                       B0110011,
                       B0000000,
                       B0000000};                  


const int _HEART[] = {B0110110,
                      B1111111,
                      B1111111,
                      B1111111,
                      B0111110,
                      B0011100,
                      B0001000,
                      B0000000};

//LOAD THE CHARACTER BITS MAP INTO AN ARRAY
// EACH CHARACTER POSITION CORRESPONDS TO ITS INDEX DEFINED PREVIOUSLY
//THIS IS _A (BITMAP OF "A")
//IF INDEX 0 IS FROM "A", THEN LETTERS[A] WILL RETURN THE BITSMAP FROM "A")

const int* letters[] = {
  _A,
  _B,
  _C,
  _D,
  _E,
  _F,
  _G,
  _H,
  _I,
  _J,
  _K,
  _L,
  _M,
  _N,
  _O,
  _P,
  _Q,
  _R,
  _S,
  _T,
  _U, 
  _V,
  _W,
  _X,
  _Y,
  _Z,
  _COL,
  _DASH,
  _BRA2,
  __, 
  _FULL, 
  _CHECK, 
  _B2, 
  _TEMP, 
  _LINE, 
  _FACE, 
  _DOT, 
  _COLDOT, 
  _HEART
  };

void setup(){
  for(int i = 0; i <8; i++){ //WHILE i is from 0 to 7, INCREASES i
    pinMode(rowA[i], OUTPUT); //SET ROWS AS OUTPUT
    pinMode(colA[i], OUTPUT); // SET COLUMNS AS OUTPUT
  }
}

void loop(){
 updateMatrix(); // UPDATE THE MATRIX WITH INFORMATION TO BE SHOWN
}

void updateMatrix(){
  loadSprite(); //LOAD THE BIT MAP
  showSprite(velFrame); //SHOW THE MAP WITH THE SPEED SET IN THE velFrame VARIABLE
}

//AN ARRAY CONTAINING THE POWER OF 2 USED AS A BITS MASK TO CALCULATE WHAT TO SHOW
const int powers[] = {1,2,4,8,16,32,64,128};

//LOAD THE CURRENT STATE OF THE FRAME TO BE DISPLAYED IN THE DATA MATRIX[]
void loadSprite(){
  int currentChar = getChar(msgDisplay[index]); //READ THE CHARACTER FROM THE MATRIX
  int nextChar = getChar(msgDisplay[index+1]); //READ NEXT CHARACTER
  
  for(int row=0; row < 8; row++){ //WHILE row is from 0 to 7, INCREASE row
    data[row] = 0; //RESET THE ROW
    for(int column=0; column < 8; column++){ //WHILE column is from 0 to 7, INCREASE column

    //LOAD THE CURRENT CHARACTER, COMPENSATED BY DISPLACEMENT PIXELS
     data[row] = data[row] + ((powers[column] & (letters[currentChar][row] << offset))); 

     //LOAD THE NEXT CHARACTER COMPENSATED BY DISPLACEMENT PIXELS
     data[row] = data[row] + (powers[column] & (letters[nextChar][row] >> (8-offset))); 
    }
  }
  offset++; // INCREASE THE OFFSET OF A ROW

    //IF OFFSET IS 8, LOAD THE FOLLOWING PAIR OF CHARACTERS NEXT TIME
    if(offset==8){
        offset = 0; index++; if(index==sizeof(msgDisplay)-2){
            index=0;
        }
    } 
}

void showSprite(int velFrame2){
 for(int k = 0; k < velFrame2; k++){ //WHILE k is from 0 to the value of velFrame2, INCREASES k
  for(int column = 0; column < 8; column++){ //WHILE column from 0 to 7, INCREASE column
   for(int i = 0; i < 8; i++){ //WHILE i is from 0 to 7, INCREASE i
       digitalWrite(rowA[i], LOW); // TURN OFF ALL ROW PINS
   }
   for(int i = 0; i < 8; i++){ //WHILE i is from 0 to 7, INCREASE i
     if(i == column){
      digitalWrite(colA[i], LOW);
     } // TURN ON THE CURRENT ROW
     else{
      digitalWrite(colA[i], HIGH);
      } // TURN ON THE REST OF THE ROWS
   }

   for(int row = 0; row < 8; row++){ //WHILE row is from 0 to 7, INCREASE row
    int bit = (data[column] >> row) & 1;
    if(bit == 1){
      digitalWrite(rowA[row], HIGH); //IF THE BIT IN THE DATA MATRIX IS SET, LIGHT THE LED
    }
   }
   delayMicroseconds(pauseDelay); // TIME INTERVAL
  }
 }
}

//RETURNS THE INDEX OF A DATA CHARACTER
//FOR THE CONVERSION OF A STRING AND FOR THE SEARCH IN THE CHARACTER BIT MAP MATRIX
int getChar(char charachter){
 int returnValue = Z;
 switch(charachter){
  case 'A': returnValue = A; break;
  case 'a': returnValue = A; break;
  case 'B': returnValue = B; break;
  case 'b': returnValue = B; break;
  case 'C': returnValue = C; break;
  case 'c': returnValue = C; break;
  case 'D': returnValue = D; break;
  case 'd': returnValue = D; break;
  case 'E': returnValue = E; break;
  case 'e': returnValue = E; break;
  case 'F': returnValue = F; break;
  case 'f': returnValue = F; break;
  case 'G': returnValue = G; break;
  case 'g': returnValue = G; break;
  case 'H': returnValue = H; break;
  case 'h': returnValue = H; break;
  case 'I': returnValue = I; break;
  case 'i': returnValue = I; break;
  case 'J': returnValue = J; break;
  case 'j': returnValue = J; break;
  case 'K': returnValue = K; break;
  case 'k': returnValue = K; break;
  case 'L': returnValue = L; break;
  case 'l': returnValue = L; break;
  case 'M': returnValue = M; break;
  case 'm': returnValue = M; break;
  case 'N': returnValue = N; break;
  case 'n': returnValue = N; break;
  case 'O': returnValue = O; break;
  case 'o': returnValue = O; break;
  case 'P': returnValue = P; break;
  case 'p': returnValue = P; break;
  case 'Q': returnValue = Q; break;
  case 'q': returnValue = Q; break;
  case 'R': returnValue = R; break;
  case 'r': returnValue = R; break;
  case 'S': returnValue = S; break;
  case 's': returnValue = S; break;
  case 'T': returnValue = T; break;
  case 't': returnValue = T; break;
  case 'U': returnValue = U; break;
  case 'u': returnValue = U; break;
  case 'V': returnValue = V; break;
  case 'v': returnValue = V; break;
  case 'W': returnValue = W; break;
  case 'w': returnValue = W; break;
  case 'X': returnValue = X; break;
  case 'x': returnValue = X; break;
  case 'Y': returnValue = Y; break;
  case 'y': returnValue = Y; break;
  case 'Z': returnValue = Z; break;
  case 'z': returnValue = Z; break;
  case ' ': returnValue = _; break;
  case '3': returnValue = B2; break;
  case '<': returnValue = TEMP; break;
  case '*': returnValue = FULL; break;
  case '|': returnValue = LINE; break;  
  case '_': returnValue = _; break;  
  case ':': returnValue = COL; break;  
  case '-': returnValue = DASH; break;  
  case ')': returnValue = BRA2; break;  
  case '%': returnValue = FACE; break;  
  case '.': returnValue = DOT; break;    
  case '^': returnValue = COLDOT; break; 
  case '@': returnValue = HEART; break;      
  }
  return returnValue; // RETURN OF INFORMATION
}
