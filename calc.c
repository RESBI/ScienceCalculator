#include <stdio.h>
#include <math.h>

#define InitLength 2000

void Float_initStack(float *Stack, int Length);
int Float_Push(float *Stack, float Num);
float Float_Pop(float *Stack);
float Float_Top(float *Stack);

void Int_initStack(int *Stack, int Length);
int Int_Push(int *Stack, int Num);
int Int_Pop(int *Stack);
int Int_Top(int *Stack);

int factorial(int x);
float mod(float a, float b);
int sign(float a);

float getResult(int *RPC, int LengthOfRPC, float ans);
int getRPC(int *RPC, int *Line, int LOL);

void Float_initStack(float *Stack, int Length) {
  for (int i=0; i<Length+2; i++) {
    Stack[i] = 0;
  }
  Stack[0] = 2;
  Stack[1] = Length;
}

int Float_Push(float *Stack, float Num) {
  if (Stack[0] >= Stack[1]) {
    return 0;
  }
  Stack[(int)Stack[0]] = Num;
  Stack[0] = Stack[0] + 1;
  return 1;
}

float Float_Pop(float *Stack) {
  if (Stack[0] <= 1) {
    return -1;
  }
  Stack[0]-=1;
  return Stack[(int)Stack[0]];
}

float Float_Top(float *Stack) {
  return Stack[(int)Stack[0]-1];
}

void Int_initStack(int *Stack, int Length) {
  for (int i=0; i<Length+2; i++) {
    Stack[i] = 0;
  }
  Stack[0] = 2;
  Stack[1] = Length;
}

int Int_Push(int *Stack, int Num) {
  if (Stack[0] >= Stack[1]) {
    return 0;
  }
  Stack[Stack[0]] = Num;
  Stack[0]++;
  return 1;
}

int Int_Pop(int *Stack) {
  if (Stack[0] < 2) {
    return -9999;
  }
  Stack[0]--;
  return Stack[Stack[0]];
}

int Int_Top(int *Stack) {
  return Stack[Stack[0]-1];
}

int factorial(int x) {
  if (x==0)
    return 1;
  if (x<0)
    return 0;
  int result = 1;
  for (int i=1; i<=x; i++)
    result *= i;
  return result;
}

float mod(float a, float b) {
  while (a>=b) {
    a-=b;
  }
  return a;
}

int sign(float a) {
  return a>0?1:a==0?0:a<0?-1:0;
}

float getResult(int *RPC, int LengthOfRPC, float ans) {
  float Stack[InitLength+2];
  Float_initStack(Stack, InitLength);
  float a, b;
  for (int i=0; i<LengthOfRPC; i++) {
    if (RPC[i] >= 0) {
      Float_Push(Stack, (float)RPC[i]);
    } else if (RPC[i] == -1) { // +
      a = Float_Pop(Stack);
      b = Float_Pop(Stack);
      Float_Push(Stack, a+b);
    } else if (RPC[i] == -2) { // -
      a = Float_Pop(Stack);
      b = Float_Pop(Stack);
      Float_Push(Stack, b-a);
    } else if (RPC[i] == -3) { // *
      a = Float_Pop(Stack);
      b = Float_Pop(Stack);
      Float_Push(Stack, a*b);
    } else if (RPC[i] == -4) { // /
      a = Float_Pop(Stack);
      b = Float_Pop(Stack);
      Float_Push(Stack, b/a);
    } else if (RPC[i] == -5) { // !
      a = Float_Pop(Stack);
      Float_Push(Stack, (float)factorial(a));
    } else if (RPC[i] == -6) { // ^
      a = Float_Pop(Stack);
      b = Float_Pop(Stack);
      Float_Push(Stack, pow(b, a));
    } else if (RPC[i] == -7) { // pi
      Float_Push(Stack, 3.14159265358f);
    } else if (RPC[i] == -8) { // e
      Float_Push(Stack, 2.71828182846f);
    } else if (RPC[i] == -9) { // mod
      a = Float_Pop(Stack);
      b = Float_Pop(Stack);
      Float_Push(Stack, mod(b, a));
    } else if (RPC[i] == -10) { // sign
      a = Float_Pop(Stack);
      Float_Push(Stack, (float)sign(a));
    } else if (RPC[i] == -11) { // sin
      a = Float_Pop(Stack);
      Float_Push(Stack, sin(a));
    } else if (RPC[i] == -12) { // cos
      a = Float_Pop(Stack);
      Float_Push(Stack, cos(a));
    } else if (RPC[i] == -13) { // tan
      a = Float_Pop(Stack);
      Float_Push(Stack, tan(a));
    } else if (RPC[i] == -25) { // ln
      a = Float_Pop(Stack);
      Float_Push(Stack, log(a));
    } else if (RPC[i] == -26) { // lg
      a = Float_Pop(Stack);
      Float_Push(Stack, log(a)/log(10));
    } else if (RPC[i] == -40) { // ans
      Float_Push(Stack, ans);
    }
  }
  return Float_Top(Stack);
}

int getRPC(int *RPC, int *Line, int LOL) {
  int Symbles[502];
  int Numbers[502];
  int TempStack[502];
  Int_initStack(Symbles, 500);
  Int_initStack(Numbers, 500);
  Int_initStack(TempStack, 500);
  int Temp = 0;
  int index = 0;
  int SIGN = 0;
  int bracketsProcessingLine[InitLength];
  int bracketsProcessingRPC[InitLength];
  int TempList[InitLength];
  while (index < LOL) {
    Temp = 0;
    SIGN = 0;
    //printf("Top: %d\t%d\t Index: %d\n", Int_Top(Numbers), Int_Top(Symbles), index);
    while (Line[index] == 32) // pass the "space"
      index++;
    if ((Line[index]>=48)&&(Line[index]<=57)) { // Push number
      while ((Line[index]>=48)&&(Line[index]<=57)) {
	Temp = Temp*10 + (Line[index]-48);
	index++;
      }
      Int_Push(Numbers, Temp);
      while (Symbles[0] > 2) // clear symble stack
	Int_Push(Numbers, Int_Pop(Symbles));
    } else if (Line[index] == 40) { // Processing bracket
	SIGN = 1;
	Temp = -1;
	index++;
	while (SIGN > 0) { // maching the bracket.
	  Temp++;
	  bracketsProcessingLine[Temp] = Line[index];
	  if (Line[index] == 41)
	    SIGN--;
	  if (Line[index] == 40)
	    SIGN++;
	  index++;
	}
	Temp = getRPC(bracketsProcessingRPC, bracketsProcessingLine, Temp);
	for (int i=0; i<Temp; i++)
	  Int_Push(Numbers, bracketsProcessingRPC[i]);
	while (Symbles[0] > 2) // clear symble stack
	  Int_Push(Numbers, Int_Pop(Symbles));
	Int_Push(Numbers, -9999); // Avoid switching the operation symble.
      } else {
      if (Line[index] == 43) { // +
	Int_Push(Symbles, -1);
      } else if (Line[index] == 45) { // -
	Int_Push(Symbles, -2);
      } else if (Line[index] == 42) { // *
	Temp = Int_Top(Numbers);
	if ((Temp==-1)||(Temp==-2)) {
	  Int_Push(Symbles, Int_Pop(Numbers));
	}
	Int_Push(Symbles, -3);
      } else if (Line[index] == 47) { // /
	Temp = Int_Top(Numbers);
	if ((Temp==-1)||(Temp==-2)) {
	  Int_Push(Symbles, Int_Pop(Numbers));
	}
	Int_Push(Symbles, -4);
      } else if (Line[index] == 33) { // !
	Temp = Int_Top(Numbers);
	if ((Temp==-1)||(Temp==-2)||(Temp==-3)||(Temp==-4)) {
	  Int_Push(Symbles, Int_Pop(Numbers));
	}
	Int_Push(Symbles, -5);
      } else if (Line[index] == 94) { // ^
	Temp = Int_Top(Numbers);
	if ((Temp==-1)||(Temp==-2)||(Temp==-3)||(Temp==-4)) {
	  Int_Push(Symbles, Int_Pop(Numbers));
	}
	Int_Push(Symbles, -6);
      } else {
	while (((Line[index]>=65)&&(Line[index]<=90))||((Line[index]>=97)&&(Line[index]<=122))) { // get symble name and length.
	  TempList[Temp] = Line[index];
	  Temp++;
	  index++;
	}
	if ((TempList[0] == 112)&&(TempList[1] == 105)&&(Temp==2)) { // pi=3.1415926
	  Int_Push(Numbers, -7);
	  SIGN = 1; // constent symble
	} else if ((TempList[0] == 101)&&(Temp==1)) { // e=2.71828182846
	  Int_Push(Numbers, -8);
	  SIGN = 1; // constent symble
	} else if ((TempList[0] == 109)&&(TempList[1] == 111)&&(TempList[2] == 100)&&(Temp==3)) { // mod
	  Temp = Int_Top(Numbers);
	  if ((Temp==-1)||(Temp==-2)||(Temp==-3)||(Temp==-4)) {
	    Int_Push(Symbles, Int_Pop(Numbers));
	  }
	  Int_Push(Symbles, -9);
	} else if ((TempList[0] == 115)&&(TempList[1] == 105)&&(TempList[2] == 103)&&(TempList[3] == 110)&&(Temp==4)) { // sign
	  Int_Push(Symbles, -10);
	} else if ((TempList[0] == 115)&&(TempList[1] == 105)&&(TempList[2] == 110)&&(Temp==3)) { // sin
	  Int_Push(Symbles, -11);
	} else if ((TempList[0] == 99)&&(TempList[1] == 111)&&(TempList[2] == 115)&&(Temp==3)) { // cos
	  Int_Push(Symbles, -12);
	} else if ((TempList[0] == 116)&&(TempList[1] == 97)&&(TempList[2] == 110)&&(Temp==3)) { // tan
	  Int_Push(Symbles, -13);
	} else if ((TempList[0] == 108)&&(TempList[1] == 110)&&(Temp==2)) { // ln
	  Int_Push(Symbles, -25);
	} else if ((TempList[0] == 108)&&(TempList[1] == 103)&&(Temp==2)) { // lg
	  Int_Push(Symbles, -26);
	} else if ((TempList[0] == 97)&&(TempList[1] == 110)&&(TempList[2] == 115)&&(Temp==3)) { // ans
	  Int_Push(Symbles, -40);
	  SIGN = 1; // ans is a constent.
	}
	if (SIGN) // pi, e.... is a constent, so we need to clear the symble stack
	  while (Symbles[0] > 2)
	    Int_Push(Numbers, Int_Pop(Symbles));
	index--;
      }
      index++;
    }
  }
  while (Symbles[0] > 2)
    Int_Push(Numbers, Int_Pop(Symbles));

  while (Numbers[0] > 2) {
    Temp = Int_Pop(Numbers);
    if (Temp != -9999) // delet -9999
      Int_Push(TempStack, Temp);
  }
  
  Temp = TempStack[0]-2;
  for (int i=0; i<Temp; i++)
    RPC[i] = Int_Pop(TempStack);
  return Temp;
}

int main() {
  char Line[InitLength];
  int Line_result[InitLength];
  int RPC[InitLength];
  int length, LengthOfLine;
  float ans = 0;
  printf("Press ESC and press ENTER to escape.\n");
  while (1) {
    printf(">> ");
    // Get input;
    for (int i=0; i<InitLength; i++) {
      Line[i] = getchar();
      if (Line[i] == 10) {
	Line[i] = -1;
	break;
      } else if (Line[i] == 27) {
	return 0;
      }
    }
    for (int i=0; i<InitLength; i++) {
      Line_result[i] = Line[i];    
      if (Line[i] == -1) {
	length = i;
	break;
      }
    }

    LengthOfLine = getRPC(RPC, Line_result, length);

    for (int i=0; i<LengthOfLine; i++) {
      if (RPC[i] == -1) {
	printf("+ ");
      } else if (RPC[i] == -2) {
	printf("- ");
      } else if (RPC[i] == -3) {
	printf("* ");
      } else if (RPC[i] == -4) {
	printf("/ ");
      } else if (RPC[i] == -5) {
	printf("! ");
      } else if (RPC[i] == -6) {
	printf("^ ");
      } else if (RPC[i] == -7) {
	printf("pi ");
      } else if (RPC[i] == -8) {
	printf("e ");
      } else if (RPC[i] == -9) {
	printf("mod ");
      } else if (RPC[i] == -10) {
	printf("sign ");
      } else if (RPC[i] == -11) {
	printf("sin ");
      } else if (RPC[i] == -12) {
	printf("cos ");
      } else if (RPC[i] == -13) {
	printf("tan ");
      } else if (RPC[i] == -25) {
	printf("ln ");
      } else if (RPC[i] == -26) {
	printf("lg ");
      } else if (RPC[i] == -40) {
	printf("ans ");
      } else {
	printf("%d ", RPC[i]);
      }
    }
    ans = getResult(RPC, LengthOfLine, ans);
    printf("\nResult = %f\n", ans);
  }
  return 0;
}

/*
  + : -1
  - : -2
  * : -3
  / : -4
  ! : -5
  ^ : -6
  pi: -7
  e : -8
  mod:-9
  sign:-10
  sin:-11
  cos:-12
  tan:-13
  sec:
  cot:
  sinh:
  cosh:
  tanh:
  sech:

  ln:-25
  lg:-26
  ans:-40
  etc...
 */
