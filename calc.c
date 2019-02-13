#include <stdio.h>
#include <math.h>

#define InitLength 2000

void Double_initStack(double *Stack, int Length);
int Double_Push(double *Stack, double Num);
double Double_Pop(double *Stack);
double Double_Top(double *Stack);

int factorial(int x);
double mod(double a, double b);
int sign(double a);

double getResult(double *RPC, int LengthOfRPC, double ans);
int getRPC(double *RPC, int *Line, int LOL);

void Double_initStack(double *Stack, int Length) {
  for (int i=0; i<Length+2; i++) {
    Stack[i] = 0;
  }
  Stack[0] = 2;
  Stack[1] = Length;
}

int Double_Push(double *Stack, double Num) {
  if (Stack[0] >= Stack[1]) {
    return 0;
  }
  Stack[(int)Stack[0]] = Num;
  Stack[0] = Stack[0] + 1;
  return 1;
}

double Double_Pop(double *Stack) {
  if (Stack[0] <= 1) {
    return -1;
  }
  Stack[0]-=1;
  return Stack[(int)Stack[0]];
}

double Double_Top(double *Stack) {
  return Stack[(int)Stack[0]-1];
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

double mod(double a, double b) {
  while (a>=b) {
    a-=b;
  }
  return a;
}

int sign(double a) {
  return a>0?1:a==0?0:a<0?-1:0;
}

double getResult(double *RPC, int LengthOfRPC, double ans) {
  double Stack[InitLength+2];
  Double_initStack(Stack, InitLength);
  double a, b;
  for (int i=0; i<LengthOfRPC; i++) {
    if (RPC[i] >= 0) {
      Double_Push(Stack, (double)RPC[i]);
    } else if (RPC[i] == -1) { // +
      a = Double_Pop(Stack);
      b = Double_Pop(Stack);
      Double_Push(Stack, a+b);
    } else if (RPC[i] == -2) { // -
      a = Double_Pop(Stack);
      b = Double_Pop(Stack);
      Double_Push(Stack, b-a);
    } else if (RPC[i] == -3) { // *
      a = Double_Pop(Stack);
      b = Double_Pop(Stack);
      Double_Push(Stack, a*b);
    } else if (RPC[i] == -4) { // /
      a = Double_Pop(Stack);
      b = Double_Pop(Stack);
      Double_Push(Stack, b/a);
    } else if (RPC[i] == -5) { // !
      a = Double_Pop(Stack);
      Double_Push(Stack, (double)factorial(a));
    } else if (RPC[i] == -6) { // ^
      a = Double_Pop(Stack);
      b = Double_Pop(Stack);
      Double_Push(Stack, pow(b, a));
    } else if (RPC[i] == -7) { // pi
      Double_Push(Stack, 3.14159265358f);
    } else if (RPC[i] == -8) { // e
      Double_Push(Stack, 2.71828182846f);
    } else if (RPC[i] == -9) { // mod
      a = Double_Pop(Stack);
      b = Double_Pop(Stack);
      Double_Push(Stack, mod(b, a));
    } else if (RPC[i] == -10) { // sign
      a = Double_Pop(Stack);
      Double_Push(Stack, (double)sign(a));
    } else if (RPC[i] == -11) { // sin
      a = Double_Pop(Stack);
      Double_Push(Stack, sin(a));
    } else if (RPC[i] == -12) { // cos
      a = Double_Pop(Stack);
      Double_Push(Stack, cos(a));
    } else if (RPC[i] == -13) { // tan
      a = Double_Pop(Stack);
      Double_Push(Stack, tan(a));
    } else if (RPC[i] == -25) { // ln
      a = Double_Pop(Stack);
      Double_Push(Stack, log(a));
    } else if (RPC[i] == -26) { // lg
      a = Double_Pop(Stack);
      Double_Push(Stack, log(a)/log(10));
    } else if (RPC[i] == -40) { // ans
      Double_Push(Stack, ans);
    }
  }
  return Double_Top(Stack);
}

int getRPC(double *RPC, int *Line, int LOL) {
  double Symbles[502];
  double Numbers[502];
  double TempStack[502];
  Double_initStack(Symbles, 500);
  Double_initStack(Numbers, 500);
  Double_initStack(TempStack, 500);
  double Temp = 0;
  int index = 0;
  int SIGN = 0;
  int bracketsProcessingLine[InitLength];
  double bracketsProcessingRPC[InitLength];
  double TempList[InitLength];
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
      Double_Push(Numbers, Temp);
      while (Symbles[0] > 2) // clear symble stack
	Double_Push(Numbers, Double_Pop(Symbles));
    } else if (Line[index] == 40) { // Processing bracket
	SIGN = 1;
	Temp = -1;
	index++;
	while (SIGN > 0) { // maching the bracket.
	  Temp++;
	  bracketsProcessingLine[(int)Temp] = Line[index];
	  if (Line[index] == 41)
	    SIGN--;
	  if (Line[index] == 40)
	    SIGN++;
	  index++;
	}
	Temp = getRPC(bracketsProcessingRPC, bracketsProcessingLine, Temp);
	for (int i=0; i<Temp; i++)
	  Double_Push(Numbers, bracketsProcessingRPC[i]);
	while (Symbles[0] > 2) // clear symble stack
	  Double_Push(Numbers, Double_Pop(Symbles));
	Double_Push(Numbers, -9999); // Avoid switching the operation symble.
      } else {
      if (Line[index] == 43) { // +
	Double_Push(Symbles, -1);
      } else if (Line[index] == 45) { // -
	Double_Push(Symbles, -2);
      } else if (Line[index] == 42) { // *
	Temp = Double_Top(Numbers);
	if ((Temp==-1)||(Temp==-2)) {
	  Double_Push(Symbles, Double_Pop(Numbers));
	}
	Double_Push(Symbles, -3);
      } else if (Line[index] == 47) { // /
	Temp = Double_Top(Numbers);
	if ((Temp==-1)||(Temp==-2)) {
	  Double_Push(Symbles, Double_Pop(Numbers));
	}
	Double_Push(Symbles, -4);
      } else if (Line[index] == 33) { // !
	Temp = Double_Top(Numbers);
	if ((Temp==-1)||(Temp==-2)||(Temp==-3)||(Temp==-4)) {
	  Double_Push(Symbles, Double_Pop(Numbers));
	}
	Double_Push(Symbles, -5);
      } else if (Line[index] == 94) { // ^
	Temp = Double_Top(Numbers);
	if ((Temp==-1)||(Temp==-2)||(Temp==-3)||(Temp==-4)) {
	  Double_Push(Symbles, Double_Pop(Numbers));
	}
	Double_Push(Symbles, -6);
      } else {
	while (((Line[index]>=65)&&(Line[index]<=90))||((Line[index]>=97)&&(Line[index]<=122))) { // get symble name and length.
	  TempList[(int)Temp] = Line[index];
	  Temp++;
	  index++;
	}
	if ((TempList[0] == 112)&&(TempList[1] == 105)&&(Temp==2)) { // pi=3.1415926
	  Double_Push(Numbers, -7);
	  SIGN = 1; // constent symble
	} else if ((TempList[0] == 101)&&(Temp==1)) { // e=2.71828182846
	  Double_Push(Numbers, -8);
	  SIGN = 1; // constent symble
	} else if ((TempList[0] == 109)&&(TempList[1] == 111)&&(TempList[2] == 100)&&(Temp==3)) { // mod
	  Temp = Double_Top(Numbers);
	  if ((Temp==-1)||(Temp==-2)||(Temp==-3)||(Temp==-4)) {
	    Double_Push(Symbles, Double_Pop(Numbers));
	  }
	  Double_Push(Symbles, -9);
	} else if ((TempList[0] == 115)&&(TempList[1] == 105)&&(TempList[2] == 103)&&(TempList[3] == 110)&&(Temp==4)) { // sign
	  Double_Push(Symbles, -10);
	} else if ((TempList[0] == 115)&&(TempList[1] == 105)&&(TempList[2] == 110)&&(Temp==3)) { // sin
	  Double_Push(Symbles, -11);
	} else if ((TempList[0] == 99)&&(TempList[1] == 111)&&(TempList[2] == 115)&&(Temp==3)) { // cos
	  Double_Push(Symbles, -12);
	} else if ((TempList[0] == 116)&&(TempList[1] == 97)&&(TempList[2] == 110)&&(Temp==3)) { // tan
	  Double_Push(Symbles, -13);
	} else if ((TempList[0] == 108)&&(TempList[1] == 110)&&(Temp==2)) { // ln
	  Double_Push(Symbles, -25);
	} else if ((TempList[0] == 108)&&(TempList[1] == 103)&&(Temp==2)) { // lg
	  Double_Push(Symbles, -26);
	} else if ((TempList[0] == 97)&&(TempList[1] == 110)&&(TempList[2] == 115)&&(Temp==3)) { // ans
	  Double_Push(Symbles, -40);
	  SIGN = 1; // ans is a constent.
	}
	if (SIGN) // pi, e.... is a constent, so we need to clear the symble stack
	  while (Symbles[0] > 2)
	    Double_Push(Numbers, Double_Pop(Symbles));
	index--;
      }
      index++;
    }
  }
  while (Symbles[0] > 2)
    Double_Push(Numbers, Double_Pop(Symbles));

  while (Numbers[0] > 2) {
    Temp = Double_Pop(Numbers);
    if (Temp != -9999) // delet -9999
      Double_Push(TempStack, Temp);
  }
  
  Temp = TempStack[0]-2;
  for (int i=0; i<Temp; i++)
    RPC[i] = Double_Pop(TempStack);
  return (int)Temp;
}

int main() {
  char Line[InitLength];
  int Line_result[InitLength];
  double RPC[InitLength];
  int length, LengthOfLine;
  double ans = 0;
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
	printf("%ld ", (long long)RPC[i]);
      }
    }
    ans = getResult(RPC, LengthOfLine, ans);
    printf("\nans = %Lf\n", ans);
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
