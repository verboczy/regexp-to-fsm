The program is able to build state-machines based on regular expressions. After this, the user can provide expressions. The program decides, whether the expression fits the regular expression.

### Special characters
Regular expressions may contain letters and some special characters. The meaning of special characters are below.
+ +: at least 1 (1 or more)
+ *: any number of (0 or 1 or more)
+ |: or
+ (): defines the scope of other special characters

### Examples
1. a+: at least one letter "a"
2. a*: any number of letter "a" (may be zero)
3. a: exactly one letter "a"
4. a|b: one letter "a" or one letter "b" 
5. (ab)*|(cd)+: either any number of "ab" or at least one "cd"

### Run
1. Compile with command *make*.
2. *./program*
3. Write the desired regular expression!
4. Write the expression(s), from which the program decides, if it fits the regular expression!
5. To exit the program, type "exit".

### Test
The program contains tests, to run these, use the following commands.
1. *make test*
2. *./test*
