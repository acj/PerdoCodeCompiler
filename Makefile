#  CSE450 Project
#  Adam Jensen (jensena8@cse.msu.edu)
#  Ronald Nussbaum (nussbau3@cse.msu.edu)

CC=g++ -g
CFLAGS = -ll -ly -g
YFLAGS = -d

OBJ = parser.tab.o lex.yy.o ASTAdd.o ASTAnd.o ASTArray.o ASTArrayIndex.o \
	Assembler.o ASTAssignment.o ASTBlock.o ASTChar.o ASTCharVariable.o \
	ASTDivide.o ASTEqual.o ASTExponent.o ASTFire.o ASTFunction.o \
	ASTFunctionCall.o ASTGetEnergy.o ASTGetMove.o ASTGetRotate.o \
	ASTGetShields.o ASTGreaterThan.o ASTGreaterThanEqual.o ASTIf.o \
	ASTIfElse.o ASTLessThan.o ASTLessThanEqual.o ASTMod.o ASTMultiply.o \
	ASTNode.o ASTNotEqual.o ASTOr.o ASTPrint.o ASTRandom.o ASTResize.o \
	ASTReturn.o ASTScanAngle.o ASTScanDistance.o ASTScanId.o ASTSetMove.o \
	ASTSetRotate.o ASTSetShields.o ASTSize.o ASTString.o ASTSubtract.o \
	ASTTime.o ASTUnaryMinus.o ASTValue.o ASTVariable.o ASTWhile.o \
	ASTZeros.o common.o SymbolTable.o

all: $(OBJ)
	$(CC) -o perdoc $(OBJ) $(CFLAGS)

parser.tab.o: parser.y
	bison -d parser.y
	$(CC) -c parser.tab.c

lex.yy.o: parser.tab.o
	flex lexer.l
	$(CC) -c lex.yy.c

Assembler.o : Assembler.cpp
	$(CC) -c Assembler.cpp

ASTAdd.o: ASTAdd.cpp
	$(CC) -c ASTAdd.cpp

ASTAnd.o: ASTAnd.cpp
	$(CC) -c ASTAnd.cpp

ASTArray.o: ASTArray.cpp
	$(CC) -c ASTArray.cpp

ASTArrayIndex.o: ASTArrayIndex.cpp
	$(CC) -c ASTArrayIndex.cpp

ASTAssignment.o: ASTAssignment.cpp
	$(CC) -c ASTAssignment.cpp

ASTChar.o: ASTChar.cpp
	$(CC) -c ASTChar.cpp

ASTCharVariable.o: ASTCharVariable.cpp
	$(CC) -c ASTCharVariable.cpp

ASTDivide.o: ASTDivide.cpp
	$(CC) -c ASTDivide.cpp

ASTEqual.o: ASTEqual.cpp
	$(CC) -c ASTEqual.cpp

ASTExponent.o: ASTExponent.cpp
	$(CC) -c ASTExponent.cpp

ASTFire.o: ASTFire.cpp
	$(CC) -c ASTFire.cpp

ASTFunction.o: ASTFunction.cpp
	$(CC) -c ASTFunction.cpp

ASTFunctionCall.o: ASTFunctionCall.cpp
	$(CC) -c ASTFunctionCall.cpp

ASTGetEnergy.o: ASTGetEnergy.cpp
	$(CC) -c ASTGetEnergy.cpp

ASTGetMove.o: ASTGetMove.cpp
	$(CC) -c ASTGetMove.cpp

ASTGetRotate.o: ASTGetRotate.cpp
	$(CC) -c ASTGetRotate.cpp

ASTGetShields.o: ASTGetShields.cpp
	$(CC) -c ASTGetShields.cpp

ASTGreaterThan.o: ASTGreaterThan.cpp
	$(CC) -c ASTGreaterThan.cpp

ASTGreaterThanEqual.o: ASTGreaterThanEqual.cpp
	$(CC) -c ASTGreaterThanEqual.cpp

ASTIf.o: ASTIf.cpp
	$(CC) -c ASTIf.cpp

ASTIfElse.o: ASTIfElse.cpp
	$(CC) -c ASTIfElse.cpp

ASTLessThan.o: ASTLessThan.cpp
	$(CC) -c ASTLessThan.cpp

ASTLessThanEqual.o: ASTLessThanEqual.cpp
	$(CC) -c ASTLessThanEqual.cpp

ASTMod.o: ASTMod.cpp
	$(CC) -c ASTMod.cpp

ASTMultiply.o: ASTMultiply.cpp
	$(CC) -c ASTMultiply.cpp

ASTNode.o: ASTNode.cpp
	$(CC) -c ASTNode.cpp

ASTNotEqual.o: ASTNotEqual.cpp
	$(CC) -c ASTNotEqual.cpp

ASTOr.o: ASTOr.cpp
	$(CC) -c ASTOr.cpp

ASTPrint.o: ASTPrint.cpp
	$(CC) -c ASTPrint.cpp

ASTRandom.o: ASTRandom.cpp
	$(CC) -c ASTRandom.cpp

ASTResize.o: ASTResize.cpp
	$(CC) -c ASTResize.cpp

ASTReturn.o: ASTReturn.cpp
	$(CC) -c ASTReturn.cpp

ASTScanAngle.o: ASTScanAngle.cpp
	$(CC) -c ASTScanAngle.cpp

ASTScanDistance.o: ASTScanDistance.cpp
	$(CC) -c ASTScanDistance.cpp

ASTScanId.o: ASTScanId.cpp
	$(CC) -c ASTScanId.cpp

ASTSetMove.o: ASTSetMove.cpp
	$(CC) -c ASTSetMove.cpp

ASTSetRotate.o: ASTSetRotate.cpp
	$(CC) -c ASTSetRotate.cpp

ASTSetShields.o: ASTSetShields.cpp
	$(CC) -c ASTSetShields.cpp

ASTSize.o: ASTSize.cpp
	$(CC) -c ASTSize.cpp

ASTString.o: ASTString.cpp
	$(CC) -c ASTString.cpp

ASTSubtract.o: ASTSubtract.cpp
	$(CC) -c ASTSubtract.cpp

ASTTime.o: ASTTime.cpp
	$(CC) -c ASTTime.cpp

ASTUnaryMinus.o: ASTUnaryMinus.cpp
	$(CC) -c ASTUnaryMinus.cpp

ASTValue.o: ASTValue.cpp
	$(CC) -c ASTValue.cpp

ASTVariable.o: ASTVariable.cpp
	$(CC) -c ASTVariable.cpp

ASTWhile.o: ASTWhile.cpp
	$(CC) -c ASTWhile.cpp

ASTZeros.o: ASTZeros.cpp
	$(CC) -c ASTZeros.cpp

ASTBlock.o: ASTBlock.cpp
	$(CC) -c ASTBlock.cpp

common.o: common.cpp
	$(CC) -c common.cpp

SymbolTable.o: SymbolTable.cpp
	$(CC) -c SymbolTable.cpp

snapshot:
	tar cf ../snapshots/`date +%Y%m%d`.tar lexer.l parser.y AST*

clean:
	rm -f *.o lex.yy.c parser*.tab.c parser*.tab.h perdoc
