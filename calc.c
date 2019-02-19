#include <stdio.h>
#include <math.h>
#include <time.h>

#define InitLength 2000

#define Symble_add -1
#define Symble_sub -2
#define Symble_mul -3
#define Symble_div -4
#define Symble_factorial -5
#define Symble_exponentiation -6
#define Symble_pi -7
#define Symble_e -8
#define Symble_mod -9
#define Symble_sign -10
#define Symble_sin -11
#define Symble_cos -12
#define Symble_tan -13
#define Symble_ln -25
#define Symble_lg -26
#define Symble_ans -40

#define Constant_E 2.718281828459045235360287471352662497757247093
#define Constant_Pi 3.141592653589793238462643383279502884197169399

#define Error_Processing_Bracket_Not_Matched_Missed_Right -1
#define Error_Processing_Bracket_Not_Matched_Missed_Left -2
  
void Double_initStack(double *Stack, int Length);
int Double_Push(double *Stack, double Num);
double Double_Pop(double *Stack);
double Double_Top(double *Stack);

int factorial(int x);
int mod(int a, int b);
int sign(double a);

double getResult(double *RPC, int LengthOfRPC, double ans);
int getRPC(double *RPC, int *Line, int LOL);
int getPriority(int Symble);

void printRPC(double *RPC, int LengthOfLine);

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
  if (Stack[0] < 3) {
    return 0;
  }
  Stack[0]-=1;
  return Stack[(int)Stack[0]];
}

double Double_Top(double *Stack) {
  if (Stack[0] < 3) {
    return 0;
  }
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

int mod(int a, int b) {
  while (a>=b) {
    a-=b;
  }
  return a;
}

int sign(double a) {
  return a>0?1:a==0?0:a<0?-1:0;
}

int getPriority(int Symble) {
  if (Symble == Symble_add) { // Add
    return 0;
  } else if (Symble == Symble_sub) { // Sub
    return 0;
  } else if (Symble == Symble_mul) { // Mul
    return 1;
  } else if (Symble == Symble_div) { // Div
    return 1;
  } else if (Symble == Symble_mod) { // Mod
    return 1;
  } else if (Symble == Symble_factorial) { // Factorial
    return 2;
  } else if (Symble == Symble_exponentiation) { // Exponentiation
    return 2;
  } else { // Numbers is GOD!
    return 9999;
  }
}

double getResult(double *RPC, int LengthOfRPC, double ans) {
  double Stack[InitLength+2];
  Double_initStack(Stack, InitLength);
  double a, b;
  for (int i=0; i<LengthOfRPC; i++) {
    if (RPC[i] >= 0) {
      Double_Push(Stack, (double)RPC[i]);
    } else if (RPC[i] == Symble_add) { // +
      a = Double_Pop(Stack);
      b = Double_Pop(Stack);
      Double_Push(Stack, a+b);
    } else if (RPC[i] == Symble_sub) { // -
      a = Double_Pop(Stack);
      b = Double_Pop(Stack);
      Double_Push(Stack, b-a);
    } else if (RPC[i] == Symble_mul) { // *
      a = Double_Pop(Stack);
      b = Double_Pop(Stack);
      Double_Push(Stack, a*b);
    } else if (RPC[i] == Symble_div) { // /
      a = Double_Pop(Stack);
      b = Double_Pop(Stack);
      if (a == 0) {
	printf("Math Error[Operation:Division] Divisor cannot be zero.\n");
	return 0;
      }
      Double_Push(Stack, b/a);
    } else if (RPC[i] == Symble_factorial) { // !
      a = Double_Pop(Stack);
      if (a<=0) {
	printf("Math Error[Operation:Factorial] %f is not an natural number.\n", a);
	return 0;
      } else if ((double)(int)a != a) {
	printf("Math Error[Operation:Factorial] %f is not an integer number.\n", a);
	return 0;
      }
      Double_Push(Stack, (double)factorial(a));
    } else if (RPC[i] == Symble_exponentiation) { // ^
      a = Double_Pop(Stack);
      b = Double_Pop(Stack);
      Double_Push(Stack, pow(b, a));
    } else if (RPC[i] == Symble_pi) { // pi
      Double_Push(Stack, Constant_Pi);
    } else if (RPC[i] == Symble_e) { // e
      Double_Push(Stack, Constant_E);
    } else if (RPC[i] == Symble_mod) { // mod
      a = Double_Pop(Stack);
      b = Double_Pop(Stack);
      if ((double)(int)a != a) {
	printf("Math Error[Operation:Mod] %f is not an integer number.\n", a);
	return 0;
      } else if ((double)(int)b != b) {
	printf("Math Error[Operation:Mod] %f is not an integer number.\n", b);
	return 0;
      }
      Double_Push(Stack, mod(b, a));
    } else if (RPC[i] == Symble_sign) { // sign
      a = Double_Pop(Stack);
      Double_Push(Stack, (double)sign(a));
    } else if (RPC[i] == Symble_sin) { // sin
      a = Double_Pop(Stack);
      Double_Push(Stack, sin(a));
    } else if (RPC[i] == Symble_cos) { // cos
      a = Double_Pop(Stack);
      Double_Push(Stack, cos(a));
    } else if (RPC[i] == Symble_tan) { // tan
      a = Double_Pop(Stack);
      Double_Push(Stack, tan(a));
    } else if (RPC[i] == Symble_ln) { // ln
      a = Double_Pop(Stack);
      if (a<=0) {
	printf("Math Error[Operation:ln] x cannot smaller then zero.\n");
	return 0;
      }
      Double_Push(Stack, log(a));
    } else if (RPC[i] == Symble_lg) { // lg
      a = Double_Pop(Stack);
      if (a<=0) {
	printf("Math Error[Operation:lg] x cannot smaller then zero.\n");
	return 0;
      }
      Double_Push(Stack, log(a)/log(10));
    } else if (RPC[i] == Symble_ans) { // ans
      Double_Push(Stack, ans);
    }
  }
  return Double_Top(Stack);
}

int getRPC(double *RPC, int *Line, int LOL) {
  double Symbles[(int)InitLength+2];
  double Numbers[(int)InitLength+2];
  double TempStack[(int)InitLength+2];
  Double_initStack(Symbles, (int)InitLength);
  Double_initStack(Numbers, (int)InitLength);
  Double_initStack(TempStack, (int)InitLength);
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
      while (SIGN > 0) { // matching the bracket.
	Temp++;
	bracketsProcessingLine[(int)Temp] = Line[index];
	if (Line[index] == 41)
	  SIGN--;
	if (Line[index] == 40)
	  SIGN++;
	index++;
	if ((index > LOL)&&(sign!=0)) {
	  return Error_Processing_Bracket_Not_Matched_Missed_Right;
	}
      }
      Temp = getRPC(bracketsProcessingRPC, bracketsProcessingLine, Temp);
      for (int i=0; i<Temp; i++)
	Double_Push(Numbers, bracketsProcessingRPC[i]);
      Double_Push(Numbers, -9999); // Avoid switching the operation symble.
      while (Symbles[0] > 2)
	Double_Push(Numbers, Double_Pop(Symbles));
    } else if (Line[index] == 41) { // if right bracket, return error.
      return Error_Processing_Bracket_Not_Matched_Missed_Left;
    } else {
      if (Line[index] == 43) { // +
	Double_Push(Symbles, Symble_add);
      } else if (Line[index] == 45) { // -
	Double_Push(Symbles, Symble_sub);
      } else if (Line[index] == 42) { // *
	Temp = Double_Top(Numbers);
	if (getPriority(Symble_mul) > getPriority(Temp)) {
	  Double_Push(Symbles, Double_Pop(Numbers));
	}
	Double_Push(Symbles, Symble_mul);
      } else if (Line[index] == 47) { // /
	Temp = Double_Top(Numbers);
	if (getPriority(Symble_div) > getPriority(Temp)) {
	  Double_Push(Symbles, Double_Pop(Numbers));
	}
	Double_Push(Symbles, Symble_div);
      } else if (Line[index] == 33) { // !
	Temp = Double_Top(Numbers);
	while (getPriority(Symble_factorial) > getPriority(Temp)) { // Get all operation out.
	  Double_Push(Symbles, Double_Pop(Numbers));
	  Temp = Double_Top(Numbers);
	}
	Double_Push(Numbers, Symble_factorial);
	while (Symbles[0] > 2) // clear symble stack
	  Double_Push(Numbers, Double_Pop(Symbles));
      } else if (Line[index] == 94) { // ^
	Temp = Double_Top(Numbers);
	if (getPriority(Symble_exponentiation) > getPriority(Temp)) {
	  Double_Push(Symbles, Double_Pop(Numbers));
	}
	Double_Push(Symbles, Symble_exponentiation);
      } else {
	while (((Line[index]>=65)&&(Line[index]<=90))||((Line[index]>=97)&&(Line[index]<=122))) { // get symble name and length.
	  TempList[(int)Temp] = Line[index];
	  Temp++;
	  index++;
	}
	if ((TempList[0] == 112)&&(TempList[1] == 105)&&(Temp==2)) { // pi=3.1415926
	  Double_Push(Numbers, Symble_pi);
	  SIGN = 1; // constant symble
	} else if ((TempList[0] == 101)&&(Temp==1)) { // e=2.71828182846
	  Double_Push(Numbers, Symble_e);
	  SIGN = 1; // constant symble
	} else if ((TempList[0] == 109)&&(TempList[1] == 111)&&(TempList[2] == 100)&&(Temp==3)) { // mod
	  Temp = Double_Top(Numbers);
	  if (getPriority(Symble_mod) > getPriority(Temp)) {
	    Double_Push(Symbles, Double_Pop(Numbers));
	  }
	  Double_Push(Symbles, Symble_mod);
	} else if ((TempList[0] == 115)&&(TempList[1] == 105)&&(TempList[2] == 103)&&(TempList[3] == 110)&&(Temp==4)) { // sign
	  Double_Push(Symbles, Symble_sign);
	} else if ((TempList[0] == 115)&&(TempList[1] == 105)&&(TempList[2] == 110)&&(Temp==3)) { // sin
	  Double_Push(Symbles, Symble_sin);
	} else if ((TempList[0] == 99)&&(TempList[1] == 111)&&(TempList[2] == 115)&&(Temp==3)) { // cos
	  Double_Push(Symbles, Symble_cos);
	} else if ((TempList[0] == 116)&&(TempList[1] == 97)&&(TempList[2] == 110)&&(Temp==3)) { // tan
	  Double_Push(Symbles, Symble_tan);
	} else if ((TempList[0] == 108)&&(TempList[1] == 110)&&(Temp==2)) { // ln
	  Double_Push(Symbles, Symble_ln);
	} else if ((TempList[0] == 108)&&(TempList[1] == 103)&&(Temp==2)) { // lg
	  Double_Push(Symbles, Symble_lg);
	} else if ((TempList[0] == 97)&&(TempList[1] == 110)&&(TempList[2] == 115)&&(Temp==3)) { // ans
	  Double_Push(Symbles, Symble_ans);
	  SIGN = 1; // ans is a constant.
	}
	if (SIGN) // pi, e.... is a constant, so we need to clear the symble stack
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
    //printf("%d ", (int)Temp);
    if (Temp != -9999) // delet -9999
      Double_Push(TempStack, Temp);
  }
  Temp = TempStack[0]-2;
  for (int i=0; i<Temp; i++)
    RPC[i] = Double_Pop(TempStack);
  //printf("\n");
  return (int)Temp;
}

void printRPC(double *RPC, int LengthOfLine) {
  for (int i=0; i<LengthOfLine; i++) {
    if (RPC[i] == Symble_add) {
      printf("+ ");
    } else if (RPC[i] == Symble_sub) {
      printf("- ");
    } else if (RPC[i] == Symble_mul) {
      printf("* ");
    } else if (RPC[i] == Symble_div) {
      printf("/ ");
    } else if (RPC[i] == Symble_factorial) {
      printf("! ");
    } else if (RPC[i] == Symble_exponentiation) {
      printf("^ ");
    } else if (RPC[i] == Symble_pi) {
      printf("pi ");
    } else if (RPC[i] == Symble_e) {
      printf("e ");
    } else if (RPC[i] == Symble_mod) {
      printf("mod ");
    } else if (RPC[i] == Symble_sign) {
      printf("sign ");
    } else if (RPC[i] == Symble_sin) {
      printf("sin ");
    } else if (RPC[i] == Symble_cos) {
      printf("cos ");
    } else if (RPC[i] == Symble_tan) {
      printf("tan ");
    } else if (RPC[i] == Symble_ln) {
      printf("ln ");
    } else if (RPC[i] == Symble_lg) {
      printf("lg ");
    } else if (RPC[i] == Symble_ans) {
      printf("ans ");
    } else {
      printf("%ld ", (long long)RPC[i]);
    }
  }
  printf("\n");
}

int main() {
  char Line[InitLength];
  int Line_result[InitLength];
  double RPC[InitLength];
  int length, LengthOfLine;
  double ans = 0;
  float startTime;
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

    if (LengthOfLine == Error_Processing_Bracket_Not_Matched_Missed_Right) {
      printf("Input Error[Bracket]: Missing ')'!\n");
      continue;
    } else if (LengthOfLine == Error_Processing_Bracket_Not_Matched_Missed_Left) {
      printf("Input Error[Bracket]: Missing '('!\n");
      continue;
    } else if (LengthOfLine == 0) {
      continue;
    }

    //printRPC(RPC, LengthOfLine);
    
    startTime = clock();
    ans = getResult(RPC, LengthOfLine, ans);
    printf("ans = %Lf\nUsing time: %fms\n", ans, clock()-startTime);
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
