# Concepts-Of-Programming-Languages
 BSM 208 - Sakarya University - HomeWork Repository

# Task One

Analysis tool for the counts of operands in the java file

Firstly Targets:
* Tool can be calculate count of all of operands
* Tool can be split this operands as lexical groups
```
# Example of handle exclude example report:
Operator Founded:
	Line:return ((Deneme)obj).x == this.x  ((Deneme)obj).y == this.y;
	Operator: ==
	Operator Group: [Ikili Operator, Iliskisel Operator]
```
* Tool can be notice the comment line(s)
* List of the operands it has to follow
```
Sayisal Operatorler (Numerical):
+, ++, -, --, *, /, %, &, |, ^, =, +=, -=, /=, *=, %=, &=, |=, ^= 
Iliskisel Operatorler (Releational):
<, <=, >, >=, ==, !=
Mantiksal Operatorler (Logical):
&&, ||, !
```
Secondary Targets:
* Tool can be handle more then 1 files at the one call 
* Tool have debug mode for the founded operators
* Tool have expanded mode of the debug for the all steps of the analysis
* Tool can be handle all of java operands
