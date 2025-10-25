#include "Variable.h"


Map<string, int> Variable::map;

void Variable::create_map(){
    map = Map<string, int>();
    // excludes e & i
    map.add("a", 0);
    map.add("b", 1);
    map.add("c", 2);
    map.add("d", 3);
    map.add("f", 4);
    map.add("g", 5);
    map.add("h", 6);
    map.add("j", 7);
    map.add("k", 8);
    map.add("l", 9);
    map.add("m", 10);
    map.add("n", 11);
    map.add("o", 12);
    map.add("p", 13);
    map.add("q", 14);
    map.add("r", 15);
    map.add("s", 16);
    map.add("t", 17);
    map.add("u", 18);
    map.add("v", 19);
    map.add("w", 20);
    map.add("x", 21);
    map.add("y", 22);
    map.add("z", 23);

    map.add("A", 24);
    map.add("B", 25);
    map.add("C", 26);
    map.add("D", 27);
    map.add("E", 28);
    map.add("F", 29);
    map.add("G", 30);
    map.add("H", 31);
    map.add("I", 32);
    map.add("J", 33);
    map.add("K", 34);
    map.add("L", 35);
    map.add("M", 36);
    map.add("N", 37);
    map.add("O", 38);
    map.add("P", 39);
    map.add("Q", 40);
    map.add("R", 41);
    map.add("S", 42);
    map.add("T", 43);
    map.add("U", 44);
    map.add("V", 45);
    map.add("W", 46);
    map.add("X", 47);
    map.add("Y", 48);
    map.add("Z", 49);
}