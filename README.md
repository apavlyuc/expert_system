# expert_system

Training project for UNIT Factory.
Purpose: find unknown variables in equations(in terms of boolean maths).

Done according to subject requirements. You can see it in res/expert-system.en.pdf.

# Pre-install requirements
You ned to have Make utility and g++ compiler which supports c++14.

# Usage
Open project folder and run ```console make```

Create input file.
The file should have the following structure:
```console cat file.txt
  #comment starts with '#'
  A + B => C  # this is equation
  =A          # this is facts which value is true, all other facts is undefined by default.
  ?C          # this is facts which value we try to find.
```

And pass it to the program.
```console ./expert -f file.txt```

For more options, or information tru to run program with -h flag.
