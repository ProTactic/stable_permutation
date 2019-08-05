# Stable permutation

Stable permutation is a tool to generate all the possible permutations of a word,
where the case is matter, without switching the order of the characters.

## Getting started

Before continuing notice that the current version will only work on .unix machines.

These instructions will get you a copy of the project up and running on your local machine.

### Downloading
This project is open source on github, so just clone from https://github.com/ProTactic/stable_permutation.git:

```
git clone https://github.com/ProTactic/stable_permutation.git
```

### Installing
You will need to have the make program in your machine
Once you have it run:
```
make
```

## Running
Here are some example of how to run the program

Simple permutaion of ab
```
user:~#: spr ab
Starting p of ab with 4 options
ab
aB
Ab
AB
```

Exclude char permutation:
```
user:~#: # spr -eC a5
Starting p of a5 with 10 options
a0
a1
a2
a3
a4
a5
a6
a7
a8
a9
```

